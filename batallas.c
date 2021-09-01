#include "batallas.h"
#include "juego.h"

int funcion_batalla_1(void* pkm_1, void* pkm_2){
	int ataque_poke_1 = ((pokemon_t*)pkm_1)->ataque;
	int ataque_poke_2 = ((pokemon_t*)pkm_2)->ataque;
    if(ataque_poke_1 >= ataque_poke_2){
    	return GANO_PRIMERO;
    }else return GANO_SEGUNDO;
}

int funcion_batalla_2(void* pkm_1, void* pkm_2){
	int velocidad_poke_1 = ((pokemon_t*)pkm_1)->velocidad;
	int velocidad_poke_2 = ((pokemon_t*)pkm_2)->velocidad;
	if(velocidad_poke_1 >= velocidad_poke_2){
		return GANO_PRIMERO;
	}else return GANO_SEGUNDO;
}

int funcion_batalla_3(void* pkm_1, void* pkm_2){
	int defensa_poke_1 = ((pokemon_t*)pkm_1)->defensa;
	int defensa_poke_2 = ((pokemon_t*)pkm_2)->defensa;
	if(defensa_poke_1 >= defensa_poke_2){
		return GANO_PRIMERO;
	}else return GANO_SEGUNDO;
}

int funcion_batalla_4(void* pkm_1, void* pkm_2){
	size_t nombre_poke_1 = strlen(((pokemon_t*)pkm_1)->nombre);
	size_t nombre_poke_2 = strlen(((pokemon_t*)pkm_2)->nombre);
	if(nombre_poke_1 >= nombre_poke_2){
		return GANO_PRIMERO;
	}else return GANO_SEGUNDO;
}

int funcion_batalla_5(void* pkm_1, void* pkm_2){
	char letra_poke_1 = ((pokemon_t*)pkm_1)->nombre[0];
	char letra_poke_2 = ((pokemon_t*)pkm_2)->nombre[0];
	if(letra_poke_1 >= letra_poke_2){
		return GANO_PRIMERO;
	}else return GANO_SEGUNDO;
}