#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "pa2mm.h"

typedef struct cosa{
    int clave;
    char contenido[10];
}cosa;

cosa* crear_cosa(int clave){
    cosa* c = (cosa*)malloc(sizeof(cosa));
    if(c)
        c->clave = clave;
    return c;
}

void destruir_cosa(cosa* c){
    free(c);
}

void destructor_de_cosas(void* elemento){
    if(!elemento)
        return;
    destruir_cosa((cosa*)elemento);
}

int comparar_cosas(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2)
        return 0;

    if(((cosa*)elemento1)->clave>((cosa*)elemento2)->clave)
        return 1;
    if(((cosa*)elemento1)->clave<((cosa*)elemento2)->clave)
        return -1;
    return 0;
}

int main (){
	heap_t * heap = NULL;
	heap = crear_heap(comparar_cosas, destructor_de_cosas);
	cosa* c100= crear_cosa(100);
    cosa* c50= crear_cosa(50);
    cosa* c40= crear_cosa(40);
    cosa* c60= crear_cosa(60);
    cosa* c300= crear_cosa(300);
    cosa* c200= crear_cosa(200);
    cosa* c400= crear_cosa(400);
    cosa* c150= crear_cosa(150);
    cosa* c250= crear_cosa(250);
    cosa* c240= crear_cosa(240);
    cosa* c230= crear_cosa(230);
    pa2m_afirmar(heap_insertar(heap, c100) == 0, "se pudo insertar el elemento c100");
    pa2m_afirmar(heap_insertar(heap, c50) == 0, "se pudo insertar el elemento c50");
    pa2m_afirmar(heap_insertar(heap, c300) == 0, "se pudo insertar el elemento c300");
    pa2m_afirmar(heap_insertar(heap, c200) == 0, "se pudo insertar el elemento c200");
    pa2m_afirmar(heap_insertar(heap, c400) == 0, "se pudo insertar el elemento c400");
    pa2m_afirmar(heap_insertar(heap, c40) == 0, "se pudo insertar el elemento c40");
    pa2m_afirmar(heap_insertar(heap, c150) == 0, "se pudo insertar el elemento c150");
    pa2m_afirmar(heap_insertar(heap, c250) == 0, "se pudo insertar el elemento c250");
    pa2m_afirmar(heap_insertar(heap, c60) == 0, "se pudo insertar el elemento c60");
    pa2m_afirmar(heap_insertar(heap, c240) == 0, "se pudo insertar el elemento c240");
    pa2m_afirmar(heap_insertar(heap, c230) == 0, "se pudo insertar el elemento c230");
    pa2m_afirmar(heap_extraer_raiz(heap) == (cosa*)c40, "la raiz es c40");
    pa2m_afirmar(heap_extraer_raiz(heap) == (cosa*)c50, "la raiz es c50");
    pa2m_afirmar(heap_extraer_raiz(heap) == (cosa*)c60, "la raiz es c60");
    pa2m_afirmar(heap_extraer_raiz(heap) == (cosa*)c100, "la raiz es c100");
    pa2m_afirmar(heap_extraer_raiz(heap) == (cosa*)c150, "la raiz es c150");
    pa2m_afirmar(heap_extraer_raiz(heap) == (cosa*)c200, "la raiz es c200");
    pa2m_afirmar(heap_extraer_raiz(heap) == (cosa*)c230, "la raiz es c230");
    pa2m_afirmar(heap_extraer_raiz(heap) == (cosa*)c240, "la raiz es c240");
    pa2m_afirmar(heap_extraer_raiz(heap) == (cosa*)c250, "la raiz es c250");
    pa2m_afirmar(heap_extraer_raiz(heap) == (cosa*)c300, "la raiz es c300");
    pa2m_afirmar(heap_extraer_raiz(heap) == (cosa*)c400, "la raiz es c400");
    //cosa* c1_nuevo = heap_extraer_raiz(heap);
    //printf("clave: %i\n", c1_nuevo->clave);
    free(c40);
    free(c50);
    free(c60);
    free(c100);
    free(c300);
    free(c200);
    free(c150);
    free(c400);
    free(c250);
    free(c240);
    free(c230);
	destruir_heap(heap);
	return 0;

}