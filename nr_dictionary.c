#include <stddef.h>
#include <malloc.h>
#include <string.h>
#include "nr_dictionary.h"

void nr_dictionary_realloc(nr_dictionary_t *dict) {
    if (!dict) return;
    dict->headers = realloc(dict->headers, dict->count*sizeof(nr_dictionary_header_t));
}

int nr_dictionary_indexof(nr_dictionary_t *dict, char* key) {
    int i;
    for (i = 0; i < dict->count; i++)
        if (strcmp(dict->headers[i].key, key) == 0)
            return i;
    return -1;
}

int nr_dictionary_init(nr_dictionary_t *dict) {
    dict->headers = malloc(1*sizeof(nr_dictionary_header_t*));
    if (!dict->headers) return 0;
    dict->count = 0;
    return 1;
}

int nr_dictionary_add(nr_dictionary_t* dict, char* key, char* value) {
    if (!dict)return 0;
    if (nr_dictionary_indexof(dict, key) != -1) return 0;
    size_t index = dict->count++;
    nr_dictionary_realloc(dict);
    dict->headers[index].key = key;
    dict->headers[index].value = value;
    return 1;
}

int nr_dictionary_remove(nr_dictionary_t* dict, char* key) {
    int index;
    if ((index = nr_dictionary_indexof(dict, key)) < 0)
        return 0;
    int i;
    for (i = index; i < dict->count-1; i++) {
        dict->headers[i] = dict->headers[i+1];
    }
    nr_dictionary_realloc(dict);
    dict->count--;
    return 1;
}

void nr_dictionary_free(nr_dictionary_t *dict) {
    free(dict->headers);
}