#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair_2 ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair_2 * createPair( char * key,  void * value) {
    Pair_2 * new = (Pair_2 *)malloc(sizeof(Pair_2));
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

int is_equal_2(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}

void insertMap(HashMap * map, char * key, void * value) {
    Pair_2 *new = createPair(key,value);
    size_t i = hash(key,map->capacity);
    float lleno = map->size/map->capacity;
    if (lleno > 0.7){
      enlarge(map);//duplicar
    } 
    while (map->buckets[i] != NULL && map->buckets[i]->key != NULL)  {
      i = (i + 1) % map->capacity;
    }
    map->buckets[i] = new;
    map->current = i;
    map->size++;
}

void enlarge(HashMap * map) { // ya
  enlarge_called = 1; //no borrar (testing purposes)
  Pair_2 **oldBruckets = map->buckets;
  size_t largo = map->capacity;
  map->capacity *=2 ;//dublicar la capacidad
  map->buckets = (Pair_2 **)calloc(map->capacity,sizeof(Pair_2 *));
  map->size = 0;
  for(size_t i = 0; i < largo;i++){
    if(oldBruckets[i] != NULL){
      insertMap(map,oldBruckets[i]->key,oldBruckets[i]->value); 
    }
  }
}
 
HashMap * createMap(long capacity) { //ya
  HashMap *map = (HashMap*)malloc(sizeof(HashMap));
  map->buckets = (Pair_2 **)calloc(capacity,sizeof(Pair_2*));
  map->capacity = capacity;
  map->current = -1;
  map->size = 0;
  return map;
}

void eraseMap(HashMap * map,  char * key) {    //ya 
  Pair_2 *pairEliminar = searchMap(map, key); 
  if(pairEliminar != NULL){
    pairEliminar->key=NULL;
    map->size--;
  }
}

Pair_2 * searchMap(HashMap * map,  char * key) {   // ya
  size_t i = hash(key, map->capacity);
  while(!is_equal_2(key, map->buckets[i]->key)){
    i = (i+1)% map->capacity;
    if (map->buckets[i] == NULL) return NULL;
  }
  map->current = i;
  return map->buckets[i];
}

Pair_2 * firstMap(HashMap * map) {
  if(map->size == 0)return NULL;
  for(size_t i = 0; i < map->capacity; i++){
    if(map->buckets[i] != NULL && map->buckets[i]->key !=NULL){
      map->current = i;
      return map->buckets[i];
    }
  }
  return NULL;
}

Pair_2 * nextMap(HashMap * map) {
  if(map->size == 0)return NULL;
  for(size_t i = map->current + 1; i < map->capacity; i++){
    if(map->buckets[i] !=NULL && map->buckets[i]->key != NULL){
      map->current = i;
      return map->buckets[i]; 
    } 
  }
  return  NULL;
}
