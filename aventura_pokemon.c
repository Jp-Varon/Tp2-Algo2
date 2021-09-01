#include "juego.h"
#include "batallas.h"
#define ROJO "\x1b[31m"
#define ROJO_CLARO "\x1b[31;1m"
#define BLANCO "\x1b[37m"
#define BLANCO_CLARO "\x1b[37;1m"
#define NEGRO "\x1b[30m"
#define VERDE "\x1b[32;1m"
#define AZUL "\x1b[34m"
#define PURPURA_FUERTE "\x1b[35m"
#define PURPURA "\x1b[35;1m"
#define AMARILLO "\x1b[33;1m"
#define DORADO "\x1b[33m"
#define CIAN "\x1b[36;1m"
#define FIN "\x1b[0m"
const static int PRIMERO = 1;
const static int SEGUNDO = -1;
const static int VACIO = 0;
const static char ARCHIVO_PER_MAY = 'E';
const static char ARCHIVO_PER_MIN = 'e';
const static char ARCHIVO_GYM_MIN = 'a';
const static char ARCHIVO_GYM_MAY = 'A'; 
const static char INICIAR_JUEGO_MAY = 'I';
const static char INICIAR_JUEGO_MIN = 'i';
const static char CARACTER_SIM_MAY = 'S';
const static char CARACTER_SIM_MIN = 's';
const static char MOSTRAR_ENTRENADOR_MAY = 'E';
const static char MOSTRAR_ENTRENADOR_MIN = 'e';
const static char MOSTRAR_GYM_MAY = 'G';
const static char MOSTRAR_GYM_MIN = 'g';
const static char CAMBIAR_POKE_MAY = 'C';
const static char CAMBIAR_POKE_MIN = 'c';
const static char CONTINUAR_MAY = 'N';
const static char CONTINUAR_MIN = 'n';
const static int MAX_STATS = 63;
const static int MAX_CANT_POKE_COMBATE = 6;
const static int EMPATE = 0;
const static int CONTADOR_INICIAL = 0;
const static char PEDIR_LIDER_MAY = 'T';
const static char PEDIR_LIDER_MIN = 't';
const static char REINTENTAR_GYM_MAY = 'R';
const static char REINTENTAR_GYM_MIN = 'r';
const static char FINALIZAR_PARTIDA_MAY = 'F';
const static char FINALIZAR_PARTIDA_MIN = 'f';
const static int ERROR = -1;
const static int OK = 0;

/*
POST: retorna el gymnasio con la dificultad mas chica.
*/
int comparar_gyms(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2)
        return VACIO;

    if(((gimnasio_t*)elemento1)->dificultad>((gimnasio_t*)elemento2)->dificultad)
        return PRIMERO;
    if(((gimnasio_t*)elemento1)->dificultad<((gimnasio_t*)elemento2)->dificultad)
        return SEGUNDO;
    return VACIO;
}

/*
POST: libera toda la menoria utilizada por un entrenador.
*/
void destruir_entrenador(entrenador_t * entrenador_actual){
	if(!entrenador_actual){
		return;
	}
	for (size_t i = 0; (int)i < entrenador_actual->cant_pokemon; ++i){
		pokemon_t * pokemon_actual = (pokemon_t*)lista_elemento_en_posicion(entrenador_actual->pokemones, i);
		free(pokemon_actual);
	}
	lista_destruir(entrenador_actual->pokemones);
	free(entrenador_actual);
}
/*
POST: destruye toda la memoria utilizada por un gimnasio.
*/
void destructor_gym(gimnasio_t * gimnasio){
	for (size_t i = 0; (int)i < gimnasio->cant_entrenadores; ++i){
		entrenador_t * entrenador_actual = (entrenador_t*)lista_tope(gimnasio->entrenadores);
		lista_desapilar(gimnasio->entrenadores);
		destruir_entrenador(entrenador_actual);
	}
	lista_destruir(gimnasio->entrenadores);
	free(gimnasio);
}
/*
POST: destruye toda la memoria utilizada por un gimnasio.
*/
void destruir_gyms(void * elemento){
	if(!elemento){
		return;
	}
	destructor_gym((gimnasio_t*)elemento);
}


/*
POST: retorna true si la letra coincide con las esperadoas, caso contrario,
	retornara false.
*/
bool respuesta_valida(char respuesta){
	return (respuesta == ARCHIVO_PER_MAY || respuesta == ARCHIVO_PER_MIN || respuesta == ARCHIVO_GYM_MAY || respuesta == ARCHIVO_GYM_MIN || respuesta == INICIAR_JUEGO_MAY || respuesta == INICIAR_JUEGO_MIN || respuesta == CARACTER_SIM_MAY || respuesta == CARACTER_SIM_MIN);
}
/*
POST: muestra por pantalla el logo de pokemon.
*/
void mostrar_logo(){
	printf(AMARILLO"\t\t\t                                .::.\n");
	printf("\t\t\t                              .;:**'            \n");
	printf("\t\t\t                              `                  \n");
	printf("\t\t\t  .:XHHHHk.              db.   .;;.     dH  MX   \n");
	printf("\t\t\toMMMMMMMMMMM       ~MM  dMMP :MMMMMR   MMM  MR      ~MRMN\n");
	printf("\t\t\tQMMMMMb  'MMX       MMMMMMP !MX' :M~   MMM MMM  .oo. XMMM 'MMM\n");
	printf("\t\t\t  `MMMM.  )M> :X!Hk. MMMM   XMM.o'  .  MMMMMMM X?XMMM MMM>!MMP\n");
	printf("\t\t\t   'MMMb.dM! XM M'?M MMMMMX.`MMMMMMMM~ MM MMM XM `'' MX MMXXMM\n");
	printf("\t\t\t    ~MMMMM~ XMM. .XM XM`'MMMb.~*?**~ .MMX M t MMbooMM XMMMMMP\n");
	printf("\t\t\t     ?MMM>  YMMMMMM! MM   `?MMRb.    `'''   !L'MMMMM XM IMMM\n");
	printf("\t\t\t      MMMX   'MMMM'  MM       ~m:           !Mh.''' dMI IMMP\n");
	printf("\t\t\t      'MMM.                                             IMX\n");
	printf("\t\t\t       ~M!M                                             IMP\n\n\n\n\n"FIN);
}


/*
POST: muestra por pantalla el logo del menu inicio.
*/
void logo_inicio(){
	printf(VERDE"                                    ______\n");
	printf(" /'\\_/`\\                           /\\__  _\\          __          __           \n");
	printf("/\\      \\     __    ___   __  __   \\/_/\\ \\/     ___ /\\_\\    ___ /\\_\\    ___   \n");
	printf("\\ \\ \\__\\ \\  /'__`\\/' _ `\\/\\ \\/\\ \\     \\ \\ \\   /' _ `\\/\\ \\  /'___\\/\\ \\  / __`\\ \n");
	printf(" \\ \\ \\_/\\ \\/\\  __//\\ \\/\\ \\ \\ \\_\\ \\     \\_\\ \\__/\\ \\/\\ \\ \\ \\/\\ \\__/\\ \\ \\/\\ \\L\\ \\ \n");
	printf("  \\ \\_\\  \\_\\ \\____\\ \\_\\ \\_\\ \\____/     /\\_____\\ \\_\\ \\_\\ \\_\\ \\____\\\\_\\ \\ \\____/  \n");
	printf("   \\/_/ \\/_/\\/____/\\/_/\\/_/\\/___/      \\/_____/\\/_/\\/_/\\/_/\\/____/ \\/_/\\/___/ \n\n\n\n\n\n");
}
/*
POST: retorna la opcion elegida por el usuario.
*/
char presentacion_inicio(){
	mostrar_logo();
	printf("ingrese 'ENTER' para continuar\n");
	getchar();
	system("clear");
	logo_inicio();
	printf("ingresar archivo del personaje ('E' o 'e')\n\n");
	printf("ingresar archivos de gimnasios ('A' o 'a')\n\n");
	printf("comenzar partida ('I' o 'i')\n\n");
	printf("simular partida ('S' o 's')\n\n");
	char respuesta;
	scanf(" %c"FIN, &respuesta);
	if(!respuesta_valida(respuesta)){
		return presentacion_inicio();
	}
	return respuesta;
}
/*
PRE: se tuvo que haber reservado con exito memoria para almacenar un juego_t.
POST: se puede subir un archivo del personaje, de los gyms, comenzar el juego
	o simularlo.
*/
void menu_inicio(juego_t * juego){
	char respuesta = presentacion_inicio();
	if(respuesta == ARCHIVO_PER_MAY || respuesta == ARCHIVO_PER_MIN){
		ingresar_archivo_prota(juego);
		menu_inicio(juego);
	}else if(respuesta == ARCHIVO_GYM_MAY || respuesta == ARCHIVO_GYM_MIN){
		if(!juego->gimnasios){
			juego->gimnasios = crear_heap(comparar_gyms, destruir_gyms);
		}
		ingresar_archivo_gym(juego);
		menu_inicio(juego);
	}else if(respuesta == INICIAR_JUEGO_MAY || respuesta == INICIAR_JUEGO_MIN){
		return;
	}else{
		juego->es_simulacion = true;
	}
}
/*
POST: imprime por pantalla el logo del menu gimnasio.
*/
void logo_gym(){
	printf(BLANCO"                                    ____                           \n");
	printf(" /'\\_/`\\                           /\\  _`\\                         \n");
	printf("/\\      \\     __    ___   __  __   \\ \\ \\L\\_\\  __  __    ___ ___    \n");
	printf("\\ \\ \\__\\ \\  /'__`\\/' _ `\\/\\ \\/\\ \\   \\ \\ \\L_L /\\ \\/\\ \\ /' __` __`\\  \n");
	printf(" \\ \\ \\_/\\ \\/\\  __//\\ \\/\\ \\ \\ \\_\\ \\   \\ \\ \\/, \\ \\ \\_\\ \\/\\ \\/\\ \\/\\ \\ \n");
	printf("  \\ \\_\\  \\_\\ \\____\\ \\_\\ \\_\\ \\____/    \\ \\____/\\/`____ \\ \\_\\ \\_\\ \\_\\\n");
	printf("   \\/_/ \\/_/\\/____/\\/_/\\/_/\\/___/      \\/___/  `/___/> \\/_/\\/_/\\/_/\n");
	printf("                                                  /\\___/           \n");
	printf("                                                  \\/__/            \n\n\n\n\n");
}
/*
POST: retorna true si la letra coincide con las esperadoas, caso contrario,
	retornara false.
*/
bool respuesta_gym_valida(char respuesta){
	return (respuesta == MOSTRAR_ENTRENADOR_MAY || respuesta == MOSTRAR_ENTRENADOR_MIN || respuesta == MOSTRAR_GYM_MAY || respuesta == MOSTRAR_GYM_MIN || respuesta == CAMBIAR_POKE_MAY || respuesta == CAMBIAR_POKE_MIN || respuesta == CONTINUAR_MAY || respuesta == CONTINUAR_MIN);
}
/*
POST: retorna la opcion elegida por el usuario.
*/
char presentacion_gym(){
	logo_gym();
	printf("Mostrar entrenador ('E' o 'e')\n\n");
	printf("Mostrar Gym actual ('G' o 'g')\n\n");
	printf("Cambiar pokemon ('C' o 'c')\n\n");
	printf("Realizar siguiente batalla ('N' o 'n')\n\n");
	char respuesta;
	scanf(" %c"FIN, &respuesta);
	while(!respuesta_gym_valida(respuesta)){
		system("clear");
		return presentacion_gym();
	}
	return respuesta;
}
/*
PRE: se tuvieron que subir con exito el personaje y los gyms de un archivo.
POST: se puede mostrar el personaje, el gym actual, cambiar los pokemones
	del personaje o avanzar a las peleas.
*/
void menu_gimnasio(juego_t * juego, gimnasio_t * gym_actual){
	system("clear");
	char respuesta = presentacion_gym();
	if(respuesta == MOSTRAR_ENTRENADOR_MAY || respuesta == MOSTRAR_ENTRENADOR_MIN){
		system("clear");
		mostrar_personaje(juego->personaje);
		printf("ingrese enter para volver al menu gym:\n");
		getchar();
		getchar();
		system("clear");
		menu_gimnasio(juego, gym_actual);
	}else if(respuesta == MOSTRAR_GYM_MAY || respuesta == MOSTRAR_GYM_MIN){
		system("clear");
		mostrar_gym(gym_actual);
		printf("ingrese enter para volver al menu gym:\n");
		getchar();
		getchar();
		system("clear");
		menu_gimnasio(juego, gym_actual);
	}else if(respuesta == CAMBIAR_POKE_MAY || respuesta == CAMBIAR_POKE_MIN){
		cambiar_pokemon(juego->personaje);
		printf("ingrese enter para volver al menu gym:\n");
		getchar();
		getchar();
		system("clear");
		menu_gimnasio(juego, gym_actual);
	}else{
		return;
	}
}
/*
POST: imprime por pantalla el logo del menu batalla.
*/
void logo_batalla(){
	printf(FIN CIAN"                                    ____              __             ___    ___               \n");
	printf(" /'\\_/`\\                           /\\  _`\\           /\\ \\__         /\\_ \\  /\\_ \\              \n");
	printf("/\\      \\     __    ___   __  __   \\ \\ \\L\\ \\     __  \\ \\ ,_\\    __  \\//\\ \\ \\//\\ \\      __     \n");
	printf("\\ \\ \\__\\ \\  /'__`\\/' _ `\\/\\ \\/\\ \\   \\ \\  _ <'  /'__`\\ \\ \\ \\/  /'__`\\  \\ \\ \\  \\ \\ \\   /'__`\\   \n");
	printf(" \\ \\ \\_/\\ \\/\\  __//\\ \\/\\ \\ \\ \\_\\ \\   \\ \\ \\L\\ \\/\\ \\L\\.\\_\\ \\ \\_/\\ \\L\\.\\_ \\_\\ \\_ \\_\\ \\_/\\ \\L\\.\\_ \n");
	printf("  \\ \\_\\  \\_\\ \\____\\ \\_\\ \\_\\ \\____/    \\ \\____/\\ \\__/.\\_\\ \\__\\ \\__/.\\_\\/\\____\\/\\____\\ \\__/.\\_\\ \n");
	printf("   \\/_/ \\/_/\\/____/\\/_/\\/_/\\/___/      \\/___/  \\/__/\\/_/ \\/__/\\/__/\\/_/\\/____/\\/____/\\/__/\\/_/\n\n");
}
/*
POST: retorna true si la letra coincide con las esperadoas, caso contrario,
	retornara false.
*/
bool letra_batalla_valida(char letra){
	return (letra == CONTINUAR_MAY || letra == CONTINUAR_MIN);
}
/*
PRE: ambos entrenadores deben tener pokemones para combatir.
POST: muestra por pantalla los pokemones combatientes y el resultado de 
	la batalla.
*/
void menu_batalla(pokemon_t * pokemon_prota, pokemon_t * pokemon_rival, int resultado, personaje_t * personaje, entrenador_t * entrenador){
	system("clear");
	logo_batalla();
	printf("\t\tENTRENADOR: %-10s\t\t\t\t\t\t\t ENTRENADOR:%s\n", personaje->nombre, entrenador->nombre);
	printf("\t\tPOKEMON PERSONAJE:\t\t\t\t\t\t\t POKEMON Rival:\n");
	printf("\t\tNombre: %-15s\t\t\t\t\t\t\t Nombre:%s\n", pokemon_prota->nombre, pokemon_rival->nombre);
	printf("\t\tVelocidad: %i\t\t\t\t\t\t\t\t Velocidad: %i\n", pokemon_prota->velocidad, pokemon_rival->velocidad);
	printf("\t\tDefensa: %i\t\t\t\t\t\t\t\t Defensa: %i\n", pokemon_prota->defensa, pokemon_rival->defensa);
	printf("\t\tAtaque: %i\t\t\t\t\t\t\t\t Ataque: %i\n\n\n", pokemon_prota->ataque, pokemon_rival->ataque);
	printf(ROJO_CLARO"\t        ..--+++--.. \t\t\t\t\t\t\t\t..--+++--..\n");
	printf("\t     .-'###########`-. \t\t\t\t\t\t\t     .-'###########`-.\n"); 
	printf("\t   +'#################`+     "FIN PURPURA"\t\t __  __            "FIN ROJO_CLARO"\t\t   +'#################`+\n");
	printf("\t  '#####################`    "FIN PURPURA"\t\t/\\ \\/\\ \\           "FIN ROJO_CLARO"\t\t  '#####################`\n");
	printf("\t '#######################`   "FIN PURPURA"\t\t\\ \\ \\ \\ \\    ____  "FIN ROJO_CLARO"\t\t '#######################`\n");
	printf(FIN NEGRO"\t:-------------------------:  "FIN PURPURA"\t\t \\ \\ \\ \\ \\  /',__\\ "FIN NEGRO"\t\t:-------------------------:\n");
	printf("\t:-------------------------:  "FIN PURPURA"\t\t  \\ \\ \\_/ \\/\\__, `\\"FIN NEGRO"\t\t:-------------------------:\n");
	printf(FIN BLANCO_CLARO"\t.#########################;  "FIN PURPURA"\t\t   \\ `\\___/\\/\\____/"FIN BLANCO_CLARO"\t\t.#########################;\n");
	printf("\t + #######################+  "FIN PURPURA"\t\t    `\\/__/  \\/___/ "FIN BLANCO_CLARO"\t\t + #######################+\n");
	printf("\t  `.####################.'\t\t\t\t\t\t  `.####################.'\n");
	printf("\t    `._#############_.'\t\t\t\t\t\t\t    `._#############_.'\n");
	printf("\t       `--..___..--'\t\t\t\t\t\t\t\t`--..___..--' \n"FIN);
	if(resultado > 0){
		printf(CIAN"\t\t\t\t\t\tGANADOR: %s\n\n", pokemon_prota->nombre);
	}else printf(ROJO_CLARO"\t\t\t\t\t\tGANADOR: %s\n\n", pokemon_rival->nombre);
	printf("ingrese N/n para continuar:\n");
	char letra;
	scanf(" %c"FIN, &letra);
	printf(FIN);
	if(!letra_batalla_valida(letra)){
		menu_batalla(pokemon_prota, pokemon_rival, resultado, personaje, entrenador);
	}
}
/*
PRE: el pokemon del personaje tuvo que haber ganado su pelea.
POST: al pokemon se le aumentan sus estadisticas en 1.
*/
void mejorar_stats(pokemon_t * pokemon){
	if(pokemon->cant_mejoras < MAX_STATS){
		(pokemon->ataque)++;
		(pokemon->velocidad)++;
		(pokemon->defensa)++;
		pokemon->cant_mejoras = pokemon->cant_mejoras + 3;
	}
}
/*
PRE: se debe haber creado funciones de batallas.
POST: retorna al entrenador ganador.
*/
int bucle_batalla(juego_t * juego, entrenador_t * entrenador, int (*batalla_pokemon)(void*, void*)){
	int i = CONTADOR_INICIAL;
	int j = CONTADOR_INICIAL;
	while(i < juego->personaje->cant_poke_combate && j < entrenador->cant_pokemon && j < MAX_CANT_POKE_COMBATE){
		pokemon_t * pokemon_prota = lista_elemento_en_posicion(juego->personaje->poke_combates, (size_t)i);
		pokemon_t * pokemon_rival = lista_elemento_en_posicion(entrenador->pokemones, (size_t)j);
		int resultado = batalla_pokemon((void*)pokemon_prota,(void*)pokemon_rival);
		if(!juego->es_simulacion){
			menu_batalla(pokemon_prota, pokemon_rival, resultado, juego->personaje, entrenador);
		}
		if(resultado > EMPATE){
			mejorar_stats(pokemon_prota);
			j++;
		}else{
			i++;
		}
	}
	if(i < juego->personaje->cant_poke_combate){
		return PRIMERO;
	}else return SEGUNDO;
}
/*
POST: imprime por pantalla el logo del menu derrota.
*/
void logo_derrota(){
	printf(ROJO_CLARO"                                    ____                                __               \n");
	printf(" /'\\_/`\\                           /\\  _`\\                             /\\ \\__            \n");
	printf("/\\      \\     __    ___   __  __   \\ \\ \\/\\ \\     __   _ __   _ __   ___\\ \\ ,_\\    __     \n");
	printf("\\ \\ \\__\\ \\  /'__`\\/' _ `\\/\\ \\/\\ \\   \\ \\ \\ \\ \\  /'__`\\/\\`'__\\/\\`'__\\/ __`\\ \\ \\/  /'__`\\   \n");
	printf(" \\ \\ \\_/\\ \\/\\  __//\\ \\/\\ \\ \\ \\_\\ \\   \\ \\ \\_\\ \\/\\  __/\\ \\ \\/ \\ \\ \\//\\ \\L\\ \\ \\ \\_/\\ \\L\\.\\_ \n");
	printf("  \\ \\_\\ \\_\\ \\____\\ \\_\\ \\_\\ \\____/    \\ \\____/\\ \\____\\ \\_\\  \\ \\_\\ \\____/\\ \\__\\ \\__/.\\_\\ \n");
	printf("   \\/_/ \\/_/\\/____/\\/_/\\/_/\\/___/      \\/___/  \\/____/ \\/_/   \\/_/ \\/___/  \\/__/\\/__/\\/_/\n\n\n\n\n\n\n");
}
/*
POST: retorna true si la letra coincide con las esperadoas, caso contrario,
	retornara false.
*/
bool letra_derrota_valida(char letra){
	return(letra == CAMBIAR_POKE_MAY || letra == CAMBIAR_POKE_MIN || letra == REINTENTAR_GYM_MAY || letra == REINTENTAR_GYM_MIN || letra == FINALIZAR_PARTIDA_MAY || letra == FINALIZAR_PARTIDA_MIN);
}
/*
POST: retorna la opcion elegida por el usuario.
*/
char presentacion_derrota(){
	system("clear");
	logo_derrota();
	printf("Cambiar de pokemon (C o c)\n\n");
	printf("Reintentar gimnasio (R o r)\n\n");
	printf("Finalizar partida (F o f)\n");
	char letra;
	scanf(" %c", &letra);
	printf(FIN);
	while(!letra_derrota_valida(letra)){
		return presentacion_derrota();
	}
	return letra;
}
/*
PRE: se tuvo que haber perdido contra algun entrenador.
POST: se puede terminar el juego, reintentarlo o cambiar los pokemones
	del personaje.
*/
void menu_derrota(juego_t * juego, bool * se_rindio){
	char respuesta = presentacion_derrota();
	if(respuesta == CAMBIAR_POKE_MAY || respuesta == CAMBIAR_POKE_MIN){
		cambiar_pokemon(juego->personaje);
		printf("ingrese enter para volver al menu gym:\n");
		getchar();
		getchar();
		system("clear");
		menu_derrota(juego, se_rindio);
	}else if(respuesta == FINALIZAR_PARTIDA_MAY || respuesta == FINALIZAR_PARTIDA_MIN){
		(*se_rindio) = true;
	}else return;
}
/*
PRE: debe haberse subido con exito el personaje y los gyms.
POST: si se gano el gym, se aumenta la cantidad de medallas del usuario, 
	caso de rendirse, se libera la memoria de todos los entrenadores del gym.
*/
void bucle_gym(juego_t * juego, gimnasio_t * gym_actual, bool * se_rindio){
	int resultado;
	while(gym_actual->cant_entrenadores != CONTADOR_INICIAL && !(*se_rindio)){
		menu_gimnasio(juego, gym_actual);
		entrenador_t *entrenador_actual = (entrenador_t*)lista_tope(gym_actual->entrenadores);
		resultado = bucle_batalla(juego, entrenador_actual, juego->funciones_batalla[gym_actual->id_funcion - 1]);
		if(resultado > EMPATE){
			(gym_actual->cant_entrenadores)--;
		}else{
			menu_derrota(juego, se_rindio);
			while(!(*se_rindio) && resultado < EMPATE){
				resultado = bucle_batalla(juego, entrenador_actual,juego->funciones_batalla[gym_actual->id_funcion - 1]);
				if(resultado < EMPATE){
					menu_derrota(juego, se_rindio);
				}
			}
			(gym_actual->cant_entrenadores)--;
		}
		if(gym_actual->cant_entrenadores != CONTADOR_INICIAL){
			destruir_entrenador(entrenador_actual);
			lista_desapilar(gym_actual->entrenadores);
		}
	}
	if(gym_actual->cant_entrenadores == CONTADOR_INICIAL){
		(juego->personaje->cant_medallas)++;
	}
	if((*se_rindio)){
		while(gym_actual->cant_entrenadores != CONTADOR_INICIAL){
			entrenador_t *entrenador_actual = (entrenador_t*)lista_tope(gym_actual->entrenadores);
			destruir_entrenador(entrenador_actual);
			lista_desapilar(gym_actual->entrenadores);
			(gym_actual->cant_entrenadores)--;
		}
	}
}
/*
POST: inmprime por pantalla el logo de menu victoria.
*/
void logo_victoria(){
	printf(DORADO"                                    __  __              __                                  \n");
	printf(" /'\\_/`\\                           /\\ \\/\\ \\  __        /\\ \\__                __             \n");
	printf("/\\      \\     __    ___   __  __   \\ \\ \\ \\ \\/\\_\\    ___\\ \\ ,_\\   ___   _ __ /\\_\\     __     \n");
	printf("\\ \\ \\__\\ \\  /'__`\\/' _ `\\/\\ \\/\\ \\   \\ \\ \\ \\ \\/\\ \\  /'___\\ \\ \\/  / __`\\/\\`'__\\/\\ \\  /'__`\\   \n");
	printf(" \\ \\ \\_/\\ \\/\\  __//\\ \\/\\ \\ \\ \\_\\ \\   \\ \\ \\_/ \\ \\ \\/\\ \\__/\\ \\ \\_/\\ \\L\\ \\ \\ \\/ \\ \\ \\/\\ \\L\\.\\_ \n");
	printf("  \\ \\_\\  \\_\\ \\____\\ \\_\\ \\_\\ \\____/    \\ `\\___/\\ \\_\\ \\_____\\ \\__\\ \\____/\\ \\_\\  \\ \\_\\ \\__/.\\_\\\n");
	printf("   \\/_/ \\/_/\\/____/\\/_/\\/_/\\/___/      `\\/__/  \\/_/\\/____/ \\/__/\\/___/  \\/_/   \\/_/\\/__/\\/_/\n");
	printf("\n\n\n\n");	
}
/*
POST: retorna true si la letra coincide con las esperadoas, caso contrario,
	retornara false.
*/
bool letra_victoria_valida(char letra){
	return (letra == PEDIR_LIDER_MAY || letra == PEDIR_LIDER_MIN || letra == CAMBIAR_POKE_MAY || letra == CAMBIAR_POKE_MIN || letra == CONTINUAR_MAY || letra == CONTINUAR_MIN);
}
/*
POST: retorna la opcion elegida por el usuario.
*/
char presentacion_victoria(bool * cambio_realizado){
	system("clear");
	logo_victoria();
	if(!(*cambio_realizado)){
		printf("Pedir prestado pokemon del lider(T o t)\n\n");
	}
	printf("Cambiar pokemones(C o c)\n\n");
	printf("Proximo Gimnasio (N o n)\n\n");
	char letra;
	scanf(" %c"FIN, &letra);
	while(!letra_victoria_valida(letra)){
		return presentacion_victoria(cambio_realizado);
	}
	return letra;
}
/*
PRE: se tuvo que haber ganado un gimnasio.
POST: se puede pedir un pokemon del lider, cambiar los pokemones del personaje
	o avanzar al proximo gym.
*/
void menu_victoria(entrenador_t * lider, personaje_t * personaje, bool *cambio_realizado){
	char respuesta = presentacion_victoria(cambio_realizado);
	if(!(*cambio_realizado)){
		if(respuesta == PEDIR_LIDER_MAY || respuesta == PEDIR_LIDER_MIN){
			if(!(*cambio_realizado)){
				pedir_pokemon(lider, personaje);
			}
			(*cambio_realizado) = true;
			menu_victoria(lider, personaje, cambio_realizado);
		}
	}
	if(respuesta == CAMBIAR_POKE_MAY || respuesta == CAMBIAR_POKE_MIN){
		cambiar_pokemon(personaje);
		menu_victoria(lider, personaje, cambio_realizado);
	}else return;
}
/*
POST: se imprime por patalla una felicitacion por haber ganado el juego.
*/
void maestro_pokemon(){
	system("clear");
	printf(" ____                                               \n");
	printf("/\\  _`\\                                             \n");
	printf("\\ \\ \\L\\_\\  _ __    __    ____      __  __    ___    \n");
	printf(" \\ \\  _\\L /\\`'__\\/'__`\\ /',__\\    /\\ \\/\\ \\ /' _ `\\  \n");
	printf("  \\ \\ \\L\\ \\ \\ \\//\\  __//\\__, `\\   \\ \\ \\_\\ \\/\\ \\/\\ \\ \n");
	printf("   \\ \\____/\\ \\_\\\\ \\____\\/\\____/    \\ \\____/\\ \\_\\ \\_\\\n");
	printf("    \\/___/  \\/_/ \\/____/\\/___/      \\/___/  \\/_/\\/_/\n");

	printf("\n");
	printf("                                  __                     ____        __                                            \n");
	printf(" /'\\_/`\\                         /\\ \\__                 /\\  _`\\     /\\ \\                                           \n");
	printf("/\\      \\     __       __    ____\\ \\ ,_\\  _ __   ___    \\ \\ \\L\\ \\___\\ \\ \\/'\\      __    ___ ___     ___     ___    \n");
	printf("\\ \\ \\__\\ \\  /'__`\\   /'__`\\ /',__\\\\ \\ \\/ /\\`'__\\/ __`\\   \\ \\ ,__/ __`\\ \\ , <    /'__`\\/' __` __`\\  / __`\\ /' _ `\\  \n");
	printf(" \\ \\ \\_/\\ \\/\\ \\L\\.\\_/\\  __//\\__, `\\\\ \\ \\_\\ \\ \\//\\ \\L\\ \\   \\ \\ \\/\\ \\L\\ \\ \\ \\`\\  /\\  __//\\ \\/\\ \\/\\ \\/\\ \\L\\ \\/\\ \\/\\ \\ \n");
	printf("  \\ \\_\\  \\_\\ \\__/.\\_\\ \\____\\/\\____/ \\ \\__\\\\ \\_\\\\ \\____/    \\ \\_\\ \\____/\\ \\_\\ \\_\\ \\____\\ \\_\\ \\_\\ \\_\\ \\____/\\ \\_\\ \\_\\\n");
	printf("   \\/_/ \\/_/\\/__/\\/_/\\/____/\\/___/   \\/__/ \\/_/ \\/___/      \\/_/\\/___/  \\/_/\\/_/\\/____/\\/_/\\/_/\\/_/\\/___/  \\/_/\\/_/\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	
	printf(FIN DORADO"                                                                                        8888888\n");
	printf("                                                                                   888888      88   \n");
	printf("                                                                            8888888             88  \n");
	printf("                                                                      8888888                    88 \n");
	printf("                                                                8888888                           8 \n");
	printf("                                                          8888888                                 88\n"FIN);
	printf(ROJO"                                              8GLt1ii1fG888"FIN DORADO"                                        0\n"FIN);
	printf(ROJO"                                             C;.       ,f8"FIN DORADO"                                         0\n");
	printf("                                      8888888"FIN ROJO"0i          18"FIN DORADO"                                        0\n");
	printf("                              88888888        "FIN ROJO"8t          t"FIN DORADO"                                        0\n");
	printf("                      88888888                  "FIN ROJO"1         .G"FIN DORADO"                                       0\n");
	printf("             888888888                          "FIN ROJO"8:         f"FIN DORADO"                                 8888888\n");
	printf("     888888888                                   "FIN ROJO"L         t"FIN DORADO"                    8888888888888       \n");
	printf("808888                                           "FIN ROJO"0,        f"FIN DORADO"        8888888888888                   \n");
	printf("08 8888                                          "FIN ROJO"8,       .C"FIN DORADO"88888888                                \n");
	printf("88    88                                         "FIN ROJO"G.       ,C8"FIN DORADO"                                       \n");
	printf(" 8     808                                    888"FIN ROJO"Gtti   ,  .;tC08"FIN DORADO"                                   \n");
	printf(" 8088888 88                              88888      "FIN ROJO"1   :1,    ,:;i1111i18"FIN DORADO"                          \n");
	printf("888       0                          88888          "FIN ROJO"1    ;L1.            L"FIN DORADO"                          \n");
	printf("88        88                     88888              "FIN ROJO"f     :LC1,          t"FIN DORADO"                          \n");
	printf(" 88        0                 88888                  "FIN ROJO"G.      ;fCLi,.     .G"FIN DORADO"                          \n");
	printf("  88       88            8888                       "FIN ROJO" 1        ;8 8GL1i;:f"FIN DORADO"                           \n");
	printf("   88      88       88888                           "FIN ROJO" 8;      ;G        8 "FIN DORADO"                           \n");
	printf("    88     88   88888                                "FIN ROJO" 0; .,iL8 "FIN DORADO"                                     \n");
	printf("     88    088888                                     "FIN ROJO" 8LG8 "FIN DORADO"                                        \n");
	printf("       888008                                                                                       \n"FIN);
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	
}
/*
PRE: se tuvo que haber cargado con exito los archivos del personaje y los gyms
POST: en caso de ganar, se muestra por pantalla la felicitacion de ganar el
	juego. 	
*/
void aventura_pokemon(juego_t * juego){
	bool se_rindio = false;
	while(juego->personaje->cant_medallas != juego->cant_gimnasios && !se_rindio){
		gimnasio_t * gym_actual = heap_extraer_raiz(juego->gimnasios);
		bucle_gym(juego, gym_actual, &se_rindio);
		if(gym_actual->cant_entrenadores == CONTADOR_INICIAL && !se_rindio){
			entrenador_t * lider = (entrenador_t*)lista_tope(gym_actual->entrenadores);
			bool cambio_realizado = false;
			menu_victoria(lider, juego->personaje, &cambio_realizado);
			destruir_entrenador(lider);
		}
		destruir_gyms(gym_actual);
	}
	if(juego->personaje->cant_medallas == juego->cant_gimnasios){
		maestro_pokemon();
	}
}
/*
PRE: se tuvo que haber perdido en algun gym.
POST: imprime por pantalla la simulacion terminada en derrota.
*/
void derrota_simulacion(gimnasio_t * gym_actual, entrenador_t * entrenador_actual){
	system("clear");
	printf(ROJO_CLARO" ____                                __               \n");
	printf("/\\  _`\\                             /\\ \\__            \n");
	printf("\\ \\ \\/\\ \\     __   _ __   _ __   ___\\ \\ ,_\\    __     \n");
	printf(" \\ \\ \\ \\ \\  /'__`\\/\\`'__\\/\\`'__\\/ __`\\ \\ \\/  /'__`\\   \n");
	printf("  \\ \\ \\_\\ \\/\\  __/\\ \\ \\/ \\ \\ \\//\\ \\L\\ \\ \\ \\_/\\ \\L\\.\\_    __  __  __ \n");
	printf("   \\ \\____/\\ \\____\\\\ \\_\\  \\ \\_\\\\ \\____/\\ \\__\\ \\__/.\\_\\  /\\_\\/\\_\\/\\_\\\n");
	printf("    \\/___/  \\/____/ \\/_/   \\/_/ \\/___/  \\/__/\\/__/\\/_/  \\/_/\\/_/\\/_/\n");
	printf(" ____                 __            __              \n");
	printf("/\\  _`\\              /\\ \\__  __    /\\ \\             \n");
	printf("\\ \\ \\L\\ \\ __     _ __\\ \\ ,_\\/\\_\\   \\_\\ \\     __     \n");
	printf(" \\ \\ ,__/'__`\\  /\\`'__\\ \\ \\/\\/\\ \\  /'_` \\  /'__`\\   \n");
	printf("  \\ \\ \\/\\ \\L\\.\\_\\ \\ \\/ \\ \\ \\_\\ \\ \\/\\ \\L\\ \\/\\ \\L\\.\\_ \n");
	printf("   \\ \\_\\ \\__/.\\_\\\\ \\_\\  \\ \\__\\\\ \\_\\ \\___,_\\ \\__/.\\_\\\n");
	printf("    \\/_/\\/__/\\/_/ \\/_/   \\/__/ \\/_/\\/__,_ /\\/__/\\/_/\n");
	printf(" ____                          ___                            __              \n");
	printf("/\\  _`\\   __                  /\\_ \\    __                    /\\ \\           \n");
	printf("\\ \\ \\L\\_\\/\\_\\    ___      __  \\//\\ \\  /\\_\\  ____      __     \\_\\ \\     __     \n");
	printf(" \\ \\  _\\/\\/\\ \\ /' _ `\\  /'__`\\  \\ \\ \\ \\/\\ \\/\\_ ,`\\  /'__`\\   /'_` \\  /'__`\\   \n");
	printf("  \\ \\ \\/  \\ \\ \\/\\ \\/\\ \\/\\ \\L\\.\\_ \\_\\ \\_\\ \\ \\/_/  /_/\\ \\L\\.\\_/\\ \\L\\ \\/\\ \\L\\.\\_ \n");
	printf("   \\ \\_\\   \\ \\_\\ \\_\\ \\_\\ \\__/.\\_\\/\\____\\\\ \\_\\/\\____\\ \\__/.\\_\\ \\___,_\\ \\__/.\\_\\\n");
	printf("    \\/_/    \\/_/\\/_/\\/_/\\/__/\\/_/\\/____/ \\/_/\\/____/\\/__/\\/_/\\/__,_ /\\/__/\\/_/\n"FIN);
	
	printf("\n\n\n\n");
	printf("Nombre del gimnasio: %s \n",gym_actual->nombre_gym);
	mostrar_entrenador(entrenador_actual);
	

}
/*
PRE: se tuvo que haber cargado con exito los archivos del personaje y los gyms
POST: simula la partida.
*/
void bucle_simulacion(juego_t * juego, gimnasio_t * gym_actual, bool * perdio){
	int resultado;
	while(gym_actual->cant_entrenadores != CONTADOR_INICIAL && !(*perdio)){
		entrenador_t *entrenador_actual = (entrenador_t*)lista_tope(gym_actual->entrenadores);
		resultado = bucle_batalla(juego, entrenador_actual, juego->funciones_batalla[gym_actual->id_funcion - 1]);
		if(resultado < EMPATE){
			(*perdio) = true;
			derrota_simulacion(gym_actual, entrenador_actual);
		}
		(gym_actual->cant_entrenadores)--;
		destruir_entrenador(entrenador_actual);
		lista_desapilar(gym_actual->entrenadores);
	}
}
/*
PRE: se tuvo que haber cargado con exito los archivos del personaje y los gyms
POST: simula la partida.
*/
void simulacion(juego_t * juego){
	bool perdio = false;
	while(juego->personaje->cant_medallas != juego->cant_gimnasios && !perdio){
		gimnasio_t * gym_actual = heap_extraer_raiz(juego->gimnasios);
		bucle_simulacion(juego, gym_actual, &perdio);
		if(gym_actual->cant_entrenadores == CONTADOR_INICIAL){
			(juego->personaje->cant_medallas)++;
		}
		destruir_gyms(gym_actual);
	}
	if(juego->personaje->cant_medallas == juego->cant_gimnasios){
		maestro_pokemon();
	}
}

int main (){
	juego_t * juego = calloc(1, sizeof(juego_t));
	if(!juego){
		return ERROR;
	}
	juego->funciones_batalla[0] = funcion_batalla_1;
	juego->funciones_batalla[1] = funcion_batalla_2;
	juego->funciones_batalla[2] = funcion_batalla_3;
	juego->funciones_batalla[3] = funcion_batalla_4;
	juego->funciones_batalla[4] = funcion_batalla_5;
	juego->personaje_vacio = true;
	juego->es_simulacion = false;
	menu_inicio(juego);
	if(juego->personaje_vacio || !juego->gimnasios || juego->cant_gimnasios == CONTADOR_INICIAL){
		system("clear");
		printf("NO SE SUBIERON ARCHIVOS NECESARIOS PARA COMENZAR EL JUEGO\n"FIN);
		if(!juego->personaje_vacio){
			destruir_prota(juego);
		}
		if(juego->gimnasios){
			destruir_gimnasios(juego->gimnasios);
		}
		free(juego);
		return ERROR;
	}
	if(!juego->es_simulacion){
		aventura_pokemon(juego);
	}else simulacion(juego);
	printf(FIN);
	destruir_prota(juego);
	destruir_gimnasios(juego->gimnasios);
	free(juego);
	return OK;
}