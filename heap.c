#include "heap.h"

heap_t* crear_heap(heap_comparador comparador, heap_liberar_elemento destructor){
	if(!comparador){
		return NULL;
	}
	heap_t* heap = calloc(1, sizeof(heap_t));
	if(!heap){
		return NULL;
	}
	heap->comparador = comparador;
	heap->destructor = destructor;
	return heap;
}
int posicion_padre(int n){
	return (n-1)/2;
}

int posicion_hijo_derecho(int n){
	return 2*n+2;
}

int posicion_hijo_izquierdo(int n){
	return 2*n+1;
}

void swap(void ** vector, int i, int j){
	void * aux = vector[i];
	vector[i] = vector[j];
	vector[j] = aux;
}

void shift_up(heap_t * heap, int n){
	if(n == 0){
		return;
	}
	int padre = posicion_padre(n);
	if(heap->comparador(heap->vector[n], heap->vector[padre]) < 0){
		swap(heap->vector, n, padre);
		shift_up(heap, padre);
	}
}

int heap_insertar(heap_t * heap, void * elemento){
	if(!heap){
		return -1;
	}
	void ** vector_aux = realloc((heap->vector), (size_t)(heap->tope + 1) * (sizeof(void *)));
	if(!vector_aux){
		return -1;
	}
	(heap->tope)++;
	heap->vector = vector_aux;
	heap->vector[heap->tope - 1] = elemento;
	shift_up(heap, heap->tope - 1);
	return 0;
}

void shift_down(heap_t * heap, int n){
	int pos_der = posicion_hijo_derecho(n);
	int pos_izq = posicion_hijo_izquierdo(n); 
	int pos_menor = pos_izq;
	if(pos_izq >= heap->tope){
		return;
	}
	if(pos_der < heap->tope){
		if(heap->comparador(heap->vector[pos_der], heap->vector[pos_izq]) <= 0){
			pos_menor = pos_der;
		}	
	}

	if(heap->comparador(heap->vector[n], heap->vector[pos_menor]) > 0){
		swap(heap->vector, n, pos_menor);
		shift_down(heap, pos_menor);
	}
}

void * heap_extraer_raiz(heap_t * heap){
	if(heap->tope == 0){
		return NULL;
	}
	void * elemento = heap->vector[0];
	heap->vector[0] = heap->vector[heap->tope - 1];
	(heap->tope)--;
	if(heap->tope != 0){
		shift_down(heap, 0);
	} 
	return elemento;
}

void destruir_heap(heap_t * heap){
	if(!heap){
		return;
	}
	while(heap->tope != 0){
		void * elemento = heap_extraer_raiz(heap);
		if(heap->destructor){
			heap->destructor(elemento);
		}
	}
	free(heap->vector);
	free(heap);
}