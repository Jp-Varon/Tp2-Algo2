#include "juego.h"
#define MAX_RUTA 100
#define MAX_NOMBRE 50
#define LECTURA "r"

const static int CONTADOR_INICIAL = 0;
const static int CANT_LEIDOS_PROTA = 5;
const static int MAX_POKE_COMBATE = 6;
const static char AFIRMATIVO_MAY = 'Y';
const static char AFIRMATIVO_MIN = 'y';
const static int LEIDOS_PRINCIPAL = 1;
const static char CARACTER_GYM = 'G';
const static int LEIDOS_GYM = 3;
const static char CARACTER_LIDER = 'L';
const static char CARACTER_POKEMON = 'P';
const static int LEIDOS_POKEMON = 4;





void destruir_prota(juego_t * juego){
	if(!juego->personaje){
		return;
	}
	for (size_t i = 0; (int)i < juego->personaje->cant_poke_caja; ++i){
		pokemon_t * pokemon_actual = (pokemon_t*)lista_elemento_en_posicion(juego->personaje->pokemon_caja, i);
		free(pokemon_actual);
	}
	lista_destruir(juego->personaje->poke_combates);
	lista_destruir(juego->personaje->pokemon_caja);
	juego->personaje->poke_combates = NULL;
	juego->personaje->pokemon_caja = NULL;
	juego->personaje->cant_poke_combate = CONTADOR_INICIAL;
	free(juego->personaje);
}
/*
PRE: la ruta enviada debe ser de un archivo que contenga un personaje.
POST: sube los datos del archivo que contiene a un personaje.
*/
personaje_t* subir_archivo(char ruta[MAX_RUTA], juego_t * juego){
	if(!juego->personaje_vacio){
		destruir_prota(juego);
	}
	personaje_t * prota = calloc(1, sizeof(personaje_t));
	if(!prota){
		return NULL;
	}
	FILE* archivo = fopen(ruta, LECTURA);
	if(!archivo){
		printf("ERROR, el archivo no existe!!\n");
		free(prota);
		return NULL;
	}
	char nombre[MAX_NOMBRE];
	char letra;
	int velocidad;
	int defensa;
	int ataque;
	fscanf(archivo,"%c;%[^\n]\n", &letra, prota->nombre);
	int leidos = fscanf(archivo,"%c;%[^;];%i;%i;%i\n", &letra, nombre, &velocidad, &defensa, &ataque);
	bool error = false;
	pokemon_t * pokemon_actual = NULL;
	prota->poke_combates = lista_crear();
	prota->pokemon_caja = lista_crear();
	while(leidos == CANT_LEIDOS_PROTA && !error){
		pokemon_actual = calloc(1, sizeof(pokemon_t));
		if(!pokemon_actual){
			error = true;
		}else{			
			strcpy(pokemon_actual->nombre, nombre);
			pokemon_actual->velocidad = velocidad;
			pokemon_actual->defensa = defensa;
			pokemon_actual->ataque = ataque;
			if(prota->cant_poke_combate < MAX_POKE_COMBATE){
				lista_insertar(prota->poke_combates, pokemon_actual);
				(prota->cant_poke_combate)++;
			}
			lista_insertar(prota->pokemon_caja, pokemon_actual);
			(prota->cant_poke_caja)++;
			leidos = fscanf(archivo,"%c;%[^;];%i;%i;%i\n", &letra, nombre, &velocidad, &defensa, &ataque);
		}
	}
	juego->personaje_vacio = false;
	fclose(archivo);
	return prota;
}

void ingresar_archivo_prota(juego_t * juego){
	system("clear");
	char ruta[MAX_RUTA];
	printf("Ingresar ruta o nombre del archivo:\n");
	scanf(" %s", ruta);
	juego->personaje = subir_archivo(ruta, juego);
	if(juego->personaje){
	printf("se subio con exito el archivo, presione enter para volver al menu principal\n");	
	}else printf("no se pudo subir el archivo del personaje, presione enter para volver al menu principal\n");
	getchar();
	getchar();
	system("clear");
}
/*
POST: retorna true si la letra coincide con las esperadoas, caso contrario,
	retornara false.
*/
bool respuesta_afirmativa(char respuesta){
	return (respuesta == AFIRMATIVO_MAY || respuesta == AFIRMATIVO_MIN);
}
/*
PRE: la ruta enviada debe ser de un archivo que contenga uno o varios gyms.
POST: sube los datos del archivo que contiene a uno o varios gimnasios.
*/
void subir_gym(char ruta[MAX_RUTA], juego_t * juego, bool * gym_vacio){
	FILE* archivo = fopen(ruta, LECTURA);
	if(!archivo){
		printf("ERROR, el archivo no existe!!\n");
		return;
	}
	gimnasio_t * gimnasio_actual = NULL;
	entrenador_t * entrenador_actual = NULL;
	char letra;
	bool error = false;
	int leidos = fscanf(archivo, "%c;", &letra);
	int leidos_gym;
	int leidos_pokemon;
	while(leidos == LEIDOS_PRINCIPAL && !error){
		if(letra == CARACTER_GYM){
			if(gimnasio_actual){
				lista_apilar(gimnasio_actual->entrenadores, entrenador_actual);
				(gimnasio_actual->cant_entrenadores)++;
				heap_insertar(juego->gimnasios, gimnasio_actual);
				(juego->cant_gimnasios++);
			}
			gimnasio_actual = calloc(1, sizeof(gimnasio_t));
			if(!gimnasio_actual){
				error = true;
			}else{
				leidos_gym = fscanf(archivo, "%[^;];%i;%i\n", gimnasio_actual->nombre_gym, &(gimnasio_actual->dificultad), &(gimnasio_actual->id_funcion));
				if(leidos_gym == LEIDOS_GYM){
					gimnasio_actual->entrenadores = lista_crear();
				}else{
					error = true;
					free(gimnasio_actual);
					gimnasio_actual = NULL;
				}
			}
		}else if(letra == CARACTER_LIDER){
			entrenador_actual = calloc(1, sizeof(entrenador_t));
			if(!entrenador_actual){
				error = true;
			}else{
				entrenador_actual->pokemones = lista_crear();
				fscanf(archivo, "%[^\n]\n", entrenador_actual->nombre);
			}
		}else if(letra == CARACTER_POKEMON){
			pokemon_t * pokemon_actual = calloc(1, sizeof(pokemon_t));
			if(!pokemon_actual){
				error = true;
			}
			leidos_pokemon = fscanf(archivo, "%[^;];%i;%i;%i\n", pokemon_actual->nombre, &(pokemon_actual->velocidad), &(pokemon_actual->defensa), &(pokemon_actual->ataque));
			if(leidos_pokemon == LEIDOS_POKEMON){
				lista_insertar(entrenador_actual->pokemones, pokemon_actual);
				(entrenador_actual->cant_pokemon)++;
			}else{
				error = true;
				free(pokemon_actual);
			}
		}else{
			lista_apilar(gimnasio_actual->entrenadores, entrenador_actual);
			(gimnasio_actual->cant_entrenadores)++;
			entrenador_actual = calloc(1, sizeof(entrenador_t));
			if(!entrenador_actual){
				error = true;
			}else{
				entrenador_actual->pokemones = lista_crear();
				fscanf(archivo, "%[^\n]\n", entrenador_actual->nombre);
			}

		}
		leidos = fscanf(archivo, "%c;", &letra);
	}
	if(gimnasio_actual){
		lista_insertar(gimnasio_actual->entrenadores, entrenador_actual);
		(gimnasio_actual->cant_entrenadores)++;
		heap_insertar(juego->gimnasios, gimnasio_actual);
		(juego->cant_gimnasios++);
	}else {
		(*gym_vacio) = true;
	}
	fclose(archivo);
}

void ingresar_archivo_gym (juego_t * juego){
	system("clear");
	char ruta[MAX_RUTA];
	printf("Ingresar ruta o nombre del archivo:\n");
	scanf(" %s", ruta);
	bool gym_vacio = false;
	subir_gym(ruta, juego, &gym_vacio);
	if(!gym_vacio){
		printf("se subio con exito el archivo, desea subir otro?(y/n)\n");
	}else printf("no se pudo subir con exito el archivo, desea subir otro?(y/n)\n");
	getchar();
	char respuesta = (char)getchar();
	if(respuesta_afirmativa(respuesta)){
		ingresar_archivo_gym(juego);
	}
}
/*
POST: imprime por pantalla el pokemon recibido.
*/
bool mostrar_pokemones(void* elemento, void* contador){
    if(elemento){
    	printf("POSICION: %i\n", (*(int*)contador)++);
        printf("Nombre pokemon:%s  ", ((pokemon_t*)elemento)->nombre);
    	printf("Velocidad: %i  ", ((pokemon_t*)elemento)->velocidad);
    	printf("Defensa: %i  ", ((pokemon_t*)elemento)->defensa);
    	printf("Ataque: %i\n\n", ((pokemon_t*)elemento)->ataque);	
    }
    return true;
}

void mostrar_personaje(personaje_t * personaje){
	printf("NOMBRE PERSONAJE:%s\n", personaje->nombre);
	printf("pokemones de combate:\n");
	int contador = CONTADOR_INICIAL;
	lista_con_cada_elemento(personaje->poke_combates, mostrar_pokemones, (void*)&contador);
	contador = CONTADOR_INICIAL;
	printf("\n\npokemones en la caja:\n");
	lista_con_cada_elemento(personaje->pokemon_caja, mostrar_pokemones, (void*)&contador);
}
/*
POST: retorna true si el pokemon recibido esta dentro de los pokemones de
	combate, caso contrario, retorna false. 
*/
bool verificar_pokemon(pokemon_t * pokemon_caja, personaje_t * personaje){
	if(!pokemon_caja){
		return true;
	}
	int i = CONTADOR_INICIAL;
	bool copia = false;
	while (i < personaje->cant_poke_combate && !copia){
		pokemon_t * pokemon_actual = (pokemon_t*)lista_elemento_en_posicion(personaje->poke_combates, (size_t)i);
		if(pokemon_caja == pokemon_actual){
			copia = true;
		}
		i++;
	}
	return copia;
}


void cambiar_pokemon(personaje_t * personaje){
	if(personaje->cant_poke_caja <= MAX_POKE_COMBATE){
		printf("no hay pokemones en la caja para cambiar...\n");
		return;
	}
	system("clear");
	char respuesta;
	printf("desea ver las posiciones de los pokemones?(Y o y)\n");
	scanf(" %c", &respuesta);
	if(respuesta_afirmativa(respuesta)){
		mostrar_personaje(personaje);
	}
	size_t pos_poke_equipo;
	size_t pos_poke_caja;
	printf("ingrese posicion del pokemon del equipo a cambiar:\n");
	scanf(" %zu", &pos_poke_equipo);
	printf("ingrese posicion del pokemon de la caja a cambiar:\n");
	scanf(" %zu", &pos_poke_caja);
	pokemon_t * pokemon_caja = (pokemon_t *)lista_elemento_en_posicion(personaje->pokemon_caja, pos_poke_caja);
	bool copia = verificar_pokemon(pokemon_caja, personaje);
	while(copia){
		printf("ERROR!!\n");
		printf("el pokemon ya se encuentra en el team de lucha...\n");
		printf("ingrese posicion del pokemon del equipo a cambiar:\n");
		scanf(" %zu", &pos_poke_equipo);
		printf("ingrese posicion del pokemon de la caja a sacar:\n");
		scanf(" %zu", &pos_poke_caja);
		pokemon_caja = (pokemon_t *)lista_elemento_en_posicion(personaje->pokemon_caja, pos_poke_caja);
		copia = verificar_pokemon(pokemon_caja, personaje);
	}
	lista_borrar_de_posicion(personaje->poke_combates, pos_poke_equipo);
	lista_insertar_en_posicion(personaje->poke_combates, pokemon_caja, pos_poke_equipo);
	printf("se intercambio con exito los pokemones!!\n");
}
/*
POST: imprime por pantalla el entrenador recibido. 
*/
bool mostrar_entrenadores(void* elemento, void* auxiliar){
	if(elemento){
        printf("NOMBRE ENTRENADOR: %s\n", ((entrenador_t*)elemento)->nombre);
        int contador = CONTADOR_INICIAL;
        lista_con_cada_elemento(((entrenador_t*)elemento)->pokemones, mostrar_pokemones, (void*)&contador);
    }
    return true;
}

void mostrar_gym(gimnasio_t * gimnasio){
	printf("Nombre GYM:%s\n\n", gimnasio->nombre_gym);
	lista_con_cada_elemento(gimnasio->entrenadores, mostrar_entrenadores, NULL);

}

void mostrar_entrenador(entrenador_t * entrenador){
	mostrar_entrenadores((void*)entrenador, NULL);
}

void pedir_pokemon(entrenador_t * lider, personaje_t * personaje){
	size_t posicion;
	mostrar_entrenador(lider);
	printf("ingrese posicion del pokemon a pedir prestado\n");
	scanf(" %zu", &posicion);
	while((int)posicion > lider->cant_pokemon){
		printf("ERROR!!\n");
		printf("posicion invalida\n");
		printf("ingrese posicion del pokemon a pedir prestado\n");
		scanf(" %zu", &posicion);
	}
	pokemon_t * pokemon_nuevo = lista_elemento_en_posicion(lider->pokemones, posicion);
	lista_borrar_de_posicion(lider->pokemones, posicion);
	(lider->cant_pokemon--);
	lista_insertar(personaje->pokemon_caja, pokemon_nuevo);
	(personaje->cant_poke_caja)++;
}

void destruir_gimnasios(heap_t * gimnasios){
	destruir_heap(gimnasios);
}