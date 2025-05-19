#include "vector.h"

Vector* vector_create(int initial_capacity){
    if(initial_capacity < 0) return NULL;
    Vector* v = malloc(sizeof(Vector));
    if (v == NULL) return NULL;
    if (initial_capacity == 0) {
        v->capacity = initial_capacity;
        v->data = NULL;
        v->size = 0;
        return v;
    }
    v->capacity = initial_capacity;
    v->size = 0;
    v->data = (int*) malloc(initial_capacity * sizeof(int));

    return v;

}