//
//  HashMap.h
//  TablaHashLab
//
//  Created by Matias Barrientos on 11-08-18.
//  Copyright © 2018 Matias Barrientos. All rights reserved.
//

#ifndef HashMap_h
#define HashMap_h


typedef struct HashMap HashMap;

typedef struct Pair_2 {
     char * key;
     void * value;
} Pair_2;

HashMap * createMap(long capacity);

void insertMap(HashMap * table, char * key, void * value);

void eraseMap(HashMap * table, char * key);

Pair_2 * searchMap(HashMap * table, char * key);

Pair_2 * firstMap(HashMap * table);

Pair_2 * nextMap(HashMap * table);

void enlarge(HashMap * map);

#endif /* HashMap_h */
