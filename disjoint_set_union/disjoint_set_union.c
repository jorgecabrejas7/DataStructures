/**
 * @file disjoint_set_union.c
 * @brief Stub implementation for a Disjoint Set Union (DSU) data structure.
 *        All functions print a "not implemented" message and return a default value.
 */
#include "disjoint_set_union.h" // Assuming disjoint_set_union.h is in the same directory or include path is set
#include <stdio.h>              // For printf
#include <stdlib.h>             // For NULL
// #include <stdbool.h> // bool is already included via disjoint_set_union.h

DSU* dsu_create(int num_elements) { // Corrected parameter type to int
    printf("STUB: dsu_create not implemented\n");
    (void)num_elements; // Parameter unused in stub
    return NULL;
}

void dsu_destroy(DSU* dsu) {
    printf("STUB: dsu_destroy not implemented\n");
    (void)dsu; // Parameter unused in stub
}

int dsu_find(DSU* dsu, int element_id) {
    printf("STUB: dsu_find not implemented\n");
    (void)dsu;         // Parameter unused in stub
    (void)element_id;  // Parameter unused in stub
    return -1; // As per .h: Returns -1 if element_id is out of bounds
}

bool dsu_union_sets(DSU* dsu, int element_id1, int element_id2) {
    printf("STUB: dsu_union_sets not implemented\n");
    (void)dsu;          // Parameter unused in stub
    (void)element_id1;  // Parameter unused in stub
    (void)element_id2;  // Parameter unused in stub
    return false;
}

// Corrected function name from dsu_are_connected to dsu_are_in_same_set
bool dsu_are_in_same_set(DSU* dsu, int element_id1, int element_id2) {
    printf("STUB: dsu_are_in_same_set not implemented\n");
    (void)dsu;
    (void)element_id1;
    (void)element_id2;
    return false;
}

// Added stub for dsu_get_num_sets
int dsu_get_num_sets(const DSU* dsu) {
    printf("STUB: dsu_get_num_sets not implemented\n");
    (void)dsu;
    // For a stub representing an empty or uninitialized DSU,
    // 0 is a reasonable default. If create returned a DSU with num_elements,
    // then num_elements would be the initial num_sets.
    return 0;
}

// Added stub for dsu_get_set_size
int dsu_get_set_size(DSU* dsu, int element_id) {
    printf("STUB: dsu_get_set_size not implemented\n");
    (void)dsu;
    (void)element_id;
    // As per .h: Returns 0 or -1 if element_id is out of bounds. 0 is fine for a stub.
    return 0;
}

// Added stub for dsu_print_parents
void dsu_print_parents(const DSU* dsu) {
    printf("STUB: dsu_print_parents not implemented\n");
    (void)dsu;
}