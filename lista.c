#include "lista.h"
#include <stdlib.h>
const static int ERROR = -1;
const static int OK = 0;
const static int VACIO = 0;


lista_t* lista_crear(){
	lista_t* lista = calloc(1, sizeof(lista_t));
	if(!lista){
		return NULL;
	}
	else return lista;
}
nodo_t* crear_nodo(void* elemento){
	nodo_t * nodo_nuevo = calloc(1, sizeof(nodo_t));
	if(!nodo_nuevo){
		return NULL;
	}
	nodo_nuevo->elemento = elemento;
	return nodo_nuevo;
}
nodo_t* insertar_nodo(nodo_t * nodo_actual, void * elemento, bool * error){
	if(!nodo_actual){
		nodo_t * nodo_nuevo = crear_nodo(elemento);
		if(!nodo_nuevo){
			(*error) = true;
			return NULL;
		}
		return nodo_nuevo;
	}
	nodo_actual->siguiente = insertar_nodo(nodo_actual->siguiente, elemento, error);
	return nodo_actual;
}
nodo_t * ultimo_nodo (nodo_t * nodo_inicio){
	nodo_t * nodo_actual = nodo_inicio;
	while(nodo_actual->siguiente != NULL){
		nodo_actual = nodo_actual->siguiente;
	}
	return nodo_actual;
}
int lista_insertar(lista_t* lista, void* elemento){
	if(!lista){
		return ERROR;
	}
	bool error = false;
	nodo_t * primer_nodo = insertar_nodo(lista->nodo_inicio, elemento, &error);
	if(error){
		return ERROR;
	}
	lista->nodo_inicio = primer_nodo;
	lista->nodo_fin = ultimo_nodo(lista->nodo_inicio);
	(lista->cantidad)++;
	return OK;
}

int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	if(!lista){
		return ERROR;
	}
	if(posicion >= lista->cantidad){
		int resultado = lista_insertar(lista, elemento);
		return resultado;
	}
	nodo_t* nodo_actual = lista->nodo_inicio;
	nodo_t * nodo_nuevo = crear_nodo(elemento);
	if(!nodo_nuevo){
		return ERROR;
	}
	if(posicion != VACIO){
		size_t i = 0;
		while(i != posicion - 1){
			nodo_actual = nodo_actual->siguiente;
			i++;
		}
		nodo_nuevo->siguiente = nodo_actual->siguiente;
		nodo_actual->siguiente = nodo_nuevo;
	}else{
		nodo_nuevo->siguiente = nodo_actual;
		lista->nodo_inicio = nodo_nuevo;

	}
	(lista->cantidad)++;
	return OK;
}
/*
POST: retorna el anteultimo nodo de la lista.
*/
nodo_t* nodo_ante_ultimo(nodo_t * nodo_actual, nodo_t * ultimo_nodo){
	if(nodo_actual->siguiente == ultimo_nodo){
		return nodo_actual;
	}
	return nodo_ante_ultimo(nodo_actual->siguiente, ultimo_nodo);
}

int lista_borrar(lista_t* lista){
	if(!lista || !lista->nodo_inicio || lista->cantidad == VACIO){
		return ERROR;
	}
	nodo_t * nodo_aux = lista->nodo_fin;
	if(lista->cantidad == 1){
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
	}else{
		lista->nodo_fin = nodo_ante_ultimo(lista->nodo_inicio, lista->nodo_fin);
		lista->nodo_fin->siguiente = NULL;
	}
	free(nodo_aux);
	(lista->cantidad)--;
	return OK; 
}

int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	if(!lista || !lista->nodo_inicio){
		return ERROR;
	}
	if(posicion >= lista->cantidad){
		int resultado = lista_borrar(lista);
		return resultado;
	}
	nodo_t * nodo_borrar = lista->nodo_inicio;
	if(posicion != VACIO){
		nodo_t * nodo_anterior = lista->nodo_inicio;
		size_t i = 0;
		size_t j = 0;
		while(i != posicion){
			while(j != posicion - 1){
				nodo_anterior = nodo_anterior->siguiente;
				j++;
			}
			nodo_borrar = nodo_borrar->siguiente;
			i++;
		}
		nodo_anterior->siguiente = nodo_borrar->siguiente;
	}
	else{
		lista->nodo_inicio = nodo_borrar->siguiente;
	}
	free(nodo_borrar);
	(lista->cantidad)--;
	return OK;

}

void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	if((!lista) || (posicion >= lista->cantidad) || (lista->cantidad == 0)){
		return NULL;
	}
	size_t i = 0;
	nodo_t * nodo_actual = lista->nodo_inicio;
	while(i != posicion){
		nodo_actual = nodo_actual->siguiente;
		i++;
	}
	return nodo_actual->elemento;
}

void* lista_ultimo(lista_t* lista){
	if(!lista || lista->cantidad == VACIO){
		return NULL;
	}
	nodo_t * ultimo_nodo = lista->nodo_fin;
	return ultimo_nodo->elemento;
}

bool lista_vacia(lista_t* lista){
	return ((!lista)|| (lista->cantidad == VACIO));
}

size_t lista_elementos(lista_t* lista){
	if(!lista){
		return (size_t)VACIO;
	}else return lista->cantidad;
}

int lista_apilar(lista_t* lista, void* elemento){
	return lista_insertar(lista, elemento);
}

int lista_desapilar(lista_t* lista){
	return lista_borrar(lista);
}

void* lista_tope(lista_t* lista){
	if(!lista){
		return NULL;
	}
	nodo_t * ultimo_nodo = lista->nodo_fin;
	if(!ultimo_nodo){
		return NULL;
	}else return ultimo_nodo->elemento;
}

int lista_encolar(lista_t* lista, void* elemento){
	return lista_insertar(lista, elemento);
}

int lista_desencolar(lista_t* lista){
	return lista_borrar_de_posicion(lista, 0);
}

void* lista_primero(lista_t* lista){
	if(!lista){
		return NULL;
	}
	nodo_t * primer_nodo = lista->nodo_inicio;
	if(!primer_nodo){
		return NULL;	
	}
	return primer_nodo->elemento;
}

void lista_destruir(lista_t* lista){
	if(!lista){
		return;
	}
	int resultado = 0;
	while(lista->cantidad != VACIO){
		resultado = lista_borrar(lista);
	}
	if(resultado == 0){
		free(lista);
	}
}

lista_iterador_t* lista_iterador_crear(lista_t* lista){
	lista_iterador_t* iterador = calloc(1, sizeof(lista_iterador_t));
	if(!iterador || !lista){
		free(iterador);
		return NULL;
	}
	iterador->lista = lista;
	iterador->corriente = lista->nodo_inicio;
	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if(!iterador || !iterador->corriente){
		return false;
	}else return true;
}

bool lista_iterador_avanzar(lista_iterador_t* iterador){
	if(!iterador || !iterador->corriente){
		return false;
	}
	iterador->corriente =  iterador->corriente->siguiente;
	if(!iterador->corriente){
		return false;
	}
	return true;
}

void* lista_iterador_elemento_actual(lista_iterador_t* iterador){
	if(!iterador || !iterador->corriente){
		return NULL;
	}else return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t* iterador){
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t* lista, bool (*funcion)(void*, void*), void *contexto){
	if(!lista || !funcion || lista->cantidad == 0){
		return (size_t) VACIO;
	}
	size_t contador = 0;
	nodo_t * nodo_actual = lista->nodo_inicio;
	bool resultado = (*funcion)(nodo_actual->elemento, contexto);
	while((nodo_actual != NULL ) && (resultado == true)){
		contador++;
		nodo_actual = nodo_actual->siguiente;
		if(nodo_actual != NULL){
			resultado = (*funcion)(nodo_actual->elemento, contexto);
		}
	}
	return contador;
}