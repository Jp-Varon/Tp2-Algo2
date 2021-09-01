#ifndef __JUEGO_H__
#define __JUEGO_H__

#include "heap.h"
#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NOMBRE 50
#define MAX_FUNCIONES_BATALLAS 5

typedef struct pokemon{
	char nombre[MAX_NOMBRE];
	int velocidad;
	int defensa;
	int ataque;
	int cant_mejoras;
}pokemon_t;

typedef struct entrenador{
	char nombre[MAX_NOMBRE];
	lista_t * pokemones;
	int cant_pokemon;
}entrenador_t;

typedef struct gimnasio{
	char nombre_gym[MAX_NOMBRE];
	int dificultad;
	int id_funcion;
	lista_t * entrenadores;
	int cant_entrenadores;
}gimnasio_t;

typedef struct personaje{
	char nombre[MAX_NOMBRE];
	lista_t * poke_combates;
	int cant_poke_combate;
	lista_t * pokemon_caja;
	int cant_poke_caja;
	int cant_medallas;	
}personaje_t;

typedef struct juego{
	personaje_t * personaje;
	bool personaje_vacio;
	heap_t * gimnasios;
	int cant_gimnasios;
	int (*funciones_batalla[MAX_FUNCIONES_BATALLAS])(void*, void*);
	bool es_simulacion;
}juego_t;
/*
POST: se cargan los datos recibidos por un archivo, para crear al personaje.
*/
void ingresar_archivo_prota(juego_t * juego);
/*
POST: se cargan los datos recibidos por uno o mas archivos, para crear los gyms
*/
void ingresar_archivo_gym (juego_t * juego);
/*
POST: imprime por pantalla al personaje principal y sus pokemones.
*/
void mostrar_personaje(personaje_t * personaje);
/*
POST: imprime por pantalla el gym recibido, junto con sus entrenadores
	y sus respectivos pokemones 
*/
void mostrar_gym(gimnasio_t * gimnasio);
/*
POST: imprime por pantalla al entrenador recibido, junto con sus pokemones.
*/
void mostrar_entrenador(entrenador_t * entrenador);
/*
POST: intercambia los pokemones de combate del personaje por alguno de su 
	caja de almacenamiento.
*/
void cambiar_pokemon(personaje_t * personaje);
/*
PRE: se tuvo que haberle ganado al lider del gimnasio.
POST:  se agrega un pokemon del lider de gimnasio a la caja del personaje.
*/
void pedir_pokemon(entrenador_t * lider, personaje_t * personaje);
/*
POST: libera la memoria utilizada para almacenar los gyms.
*/
void destruir_gimnasios(heap_t * gimnasios);
/*
POST: libera la memoria utilizada para almacenar al personaje.
*/
void destruir_prota(juego_t * juego);

#endif /* __JUEGO_H__ */