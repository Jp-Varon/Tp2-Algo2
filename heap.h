#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdio.h>
#include <stdlib.h>

typedef int (*heap_comparador)(void*, void*);

typedef void (*heap_liberar_elemento)(void*);

typedef struct heap{
	void ** vector;
	int tope;
	heap_comparador comparador;
	heap_liberar_elemento destructor;
}heap_t;

heap_t* crear_heap(heap_comparador comparador, heap_liberar_elemento destructor);

int posicion_padre(int n);

int posicion_hijo_derecho(int n);

int posicion_hijo_izquierdo(int n);

void swap(void ** vector, int i, int j);

void shift_up(heap_t * heap, int n);

int heap_insertar(heap_t * heap, void * elemento);

void shift_down(heap_t * heap, int n);

void * heap_extraer_raiz(heap_t * heap);

void destruir_heap(heap_t * heap);


#endif /* __HEAP_H__ */
