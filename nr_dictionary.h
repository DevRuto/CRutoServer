//
// Created by Ruto on 7/31/2016.
//

#ifndef CDICTIONARY_NR_DICTIONARY_H
#define CDICTIONARY_NR_DICTIONARY_H

#include <stddef.h>

typedef struct nr_dictionary_header {
    char *key;
    char *value;
} nr_dictionary_header_t;

typedef struct nr_dictionary {
    nr_dictionary_header_t *headers;
    size_t count;
} nr_dictionary_t;

int nr_dictionary_add(nr_dictionary_t* dict, char* key, char* value);
int nr_dictionary_remove(nr_dictionary_t* dict, char* key);
int nr_dictionary_indexof(nr_dictionary_t* dict, char* key);

int nr_dictionary_init(nr_dictionary_t* dict);
void nr_dictionary_free(nr_dictionary_t* dict);

#endif //CDICTIONARY_NR_DICTIONARY_H
