#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
    char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap * map, char * key, void * value) { //LISTO :D
    if (searchMap(map, key) != NULL) return ;

    long posicion = hash(key, map->capacity) ;

    while (map->buckets[posicion] != NULL && map->buckets[posicion]->key != NULL){ //sondeo lineal :)
        posicion = (posicion + 1) % map->capacity ;
    }
    
    Pair * parcito = createPair(strdup(key), value) ;
    map->buckets[posicion] = parcito ;
    map->size++ ;
    map->current = posicion ;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}

HashMap * createMap(long capacity) { //LISTO :D
    HashMap * map = (HashMap *)malloc(sizeof(HashMap)) ;
    if (map == NULL) return NULL ;

    map->buckets = (Pair **)calloc(capacity, sizeof(Pair *)) ;//dejar todo en nulo
    
    map->size = 0 ;
    map->capacity = capacity ;
    map->current = -1 ;
    return map ;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   
    long posicion = hash(key, map->capacity) ; //buscamos la posicion de key
    long pos_aux = posicion ;
    do{
        Pair* par = map->buckets[posicion] ;
        if (par == NULL){ // si hay un espacio vacio
            map->current = -1 ;
            return NULL ;}
        
        if (par->key != NULL && strcmp(par->key, key)){ // si no es NULL y las claves coinciden
            map->current = posicion ;
            return par ;}
        posicion = (posicion + 1) % map->capacity ;
    } while (posicion != pos_aux) ;

    map->current = -1 ;
    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
