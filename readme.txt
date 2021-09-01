1ª parte:
	el trabajo consiste en simular una aventura pokemon. Al comenzar, el juego
	le pide al usuario que ingrese un archivo que contenga a un protagonista,
	dicho archivo debe estar bien formateado (ejemplo de archivo bien
	formateado en el pdf del trabajo) . Tambien se le pide al usuario que 
	ingrese uno o varios archivos que contengas gimnasios, en 
	caso que el usuario no ingrese ambos archivos, el juego no comenzara.
	se crearon structs para almacenar los datos recojidos de los archivos, 
	siendo 'pokemon_t' el que almacena los datos de los pokemones. 
	'entrenador_t' el que almacena los datos de un entrenador, este contiene una
	lista de pokemones. 'gimnasio_t' el que almacena los datos de los gimnasios,
	este contiene una pila de entrenadores. 'personaje_t' el que almacena los 
	datos del personaje del juego, este contiene dos listas de pokemones. Por 
	ultimo tenemos a 'juego_t' que contiene la estructura de todo el juego.
	Una vez que el usuario ingresa ambos archivos (del personaje y el/los gym) 
	decide si juega de manera normal o simula la partida, en caso de simularla,
	se mostrara por pantalla si consiguio ser un maestro pokemon o si perdio en
	alguno de los gym en la marcha, una vez finalizada la simulacion, termina el
	juego. 
	Si se decidio jugarlo de manera normal, se comienza por el gym con la dificultad mas
	chica y se va combatiendo contra los entrenadores de dicho gym, 
	hasta llegar al lider del gimnasio, se tiene la opcion de que el personaje
	principal cada vez que le gana o pierde contra un entrenador rival, 
	pueda cambiar sus pokemones de pelea, si se tiene la capacidad de ganarle al
	lider del gym, se le entregara la medalla de dicho gimnacio, con la posibilidad
	de poder pedir prestado un pokemon del lider y agregarlo a al conjunto 
	de pokemones del personaje, pero se agregara en la caja, no en el equipo 
	para pelear. cada vez que se le gana a un lider, se va avanzando al 
	siguiente gimnacio y repitiendo el proceso, hasta llegar a el ultimo, si se
	gana, se mostrara por pantalla un reconocimiento y se convertira en maestro
	pokemon.


	Structs utilizados:
	typedef struct pokemon{
		char nombre[MAX_NOMBRE]; ---> guarda el nombre del pokemon
		int velocidad; -------------> guarda velocidad del pokemon
		int defensa; ---------------> guarda la defensa del pokemon
		int ataque; ----------------> guarda el ataque del pokemon
		int cant_mejoras; ----------> contador de mejoras realizadas.
	}pokemon_t;
	se utiliza este struct para guardar los datos recojidos de los archivos
	que tengan que ver con los pokemones.

	typedef struct entrenador{
	char nombre[MAX_NOMBRE]; -------> guarda en nombre del entrenador
	lista_t * pokemones; -----------> lista donde se guardan todos los pokemones
	int cant_pokemon; --------------> cantidad de pokemones del entrenador
	}entrenador_t;

	se utiliza para guardar a los entrenadores de los gimnasios.

	typedef struct gimnasio{
	char nombre_gym[MAX_NOMBRE]; ---> guarda el nombre del gimnasio
	int dificultad; ----------------> guarda la dificuldad del gimnasio(utilizado para ordenar el heap)
	int id_funcion;	----------------> guarda la id para utilizar las funciones de batalla
	lista_t * entrenadores; --------> lisra donde se guardan a los entrenadores de los gimnasios
	int cant_entrenadores; ---------> cantidad de entrenadores que hay en el gimnasio
	}gimnasio_t;

	se utiliza para entender como es un gym y guardar todo los datos recojidos
	del archivo.

	typedef struct personaje{
	char nombre[MAX_NOMBRE]; -------> guarda el nombre del personaje
	lista_t * poke_combates; -------> lista donde se guardan los pokemones que combaten en las batallas.
	int cant_poke_combate; ---------> cantidad de pokemones disponible para pelear.
	lista_t * pokemon_caja; --------> lista donde se guardan todos los pokemones del personaje principal.
	int cant_poke_caja; ------------> cantidad de pokemones totates del personaje.
	int cant_medallas;	------------> cantidad de medallas obtenidas del personaje.
	}personaje_t;

	struct utilizado para guardar a todo el personaje enviado por el usuario.

	*Aclaracion: se decidio por utilizar un contador externo en los structs 
	donde hay lista porque y no utilizar el contador de la lista porque se toma
	que ese contador es interno y no se deberia tocar ni utilizar para operaciones
	fuera de la lista.

2ª parte:

	LINEA DE COMPILACION
	se compila con la siguiente linea:
		" gcc *.c -o aventura_pokemon -g -std=c99  -Wall -Wconversion
		 -Wtype-limits -pedantic -Werror -O0"
	en el cual: 
		gcc: es un compilador de programas en c.
		*.c: significa que se deberan compilar todos los archivos con extencion .c en 
			la carpeta donde nos encontremos.
		-g -std=c99  -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0: 
			flags nesesarios para que el programa nos informe de cualquier error que tengamos.
		-o aventura_pokemon: como llamaremos al programa ya compilado y listo para ejecutar 

LINEA DE EJECUCION:
	se ejecuta de la siguiente manera:
		"./aventura_pokemon"
	en el cual:
		./: lo que escribas despues de el sera un archivo dentro del directorio donde te
			encontras y no un comando.
		aventura_pokemon: nombre del archivo a ejecutar.

	