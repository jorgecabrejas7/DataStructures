/**
 * @file fenwick_tree.c
 * @brief Stub implementation for a Fenwick Tree (Binary Indexed Tree - BIT).
 *        All functions print a "not implemented" message and return a default value.
 */
#include "fenwick_tree.h" // Assuming fenwick_tree.h is in the same directory or include path is set
#include <stdio.h>        // For printf
#include <stdlib.h>       // For NULL
// #include <stdbool.h> // bool is already included via fenwick_tree.h

FenwickTree* fenwick_tree_create(int logical_size) { // Corrected parameter type to int
    printf("STUB: fenwick_tree_create not implemented\n");
    (void)logical_size; // Parameter unused in stub
    return NULL;
}

void fenwick_tree_destroy(FenwickTree* ft) {
    printf("STUB: fenwick_tree_destroy not implemented\n");
    (void)ft; // Parameter unused in stub
}

// Corrected parameter types to int
bool fenwick_tree_update(FenwickTree* ft, int index, int delta) {
    printf("STUB: fenwick_tree_update not implemented\n");
    (void)ft;    // Parameter unused in stub
    (void)index; // Parameter unused in stub
    (void)delta; // Parameter unused in stub
    return false; // As per .h, returns bool
}

// Corrected function name, parameter type to int, and return type to int
int fenwick_tree_query_prefix_sum(const FenwickTree* ft, int index) {
    printf("STUB: fenwick_tree_query_prefix_sum not implemented\n");
    (void)ft;
    (void)index;
    return 0; // As per .h, returns int
}

// Corrected function name, parameter types to int, and return type to int
int fenwick_tree_query_range_sum(const FenwickTree* ft, int range_start, int range_end) {
    printf("STUB: fenwick_tree_query_range_sum not implemented\n");
    (void)ft;
    (void)range_start;
    (void)range_end;
    return 0; // As per .h, returns int
}

// Corrected return type to int
int fenwick_tree_get_size(const FenwickTree* ft) {
    printf("STUB: fenwick_tree_get_size not implemented\n");
    (void)ft;
    return 0; // As per .h, returns int
}

// Added missing stub for fenwick_tree_print_internal_array
void fenwick_tree_print_internal_array(const FenwickTree* ft) {
    printf("STUB: fenwick_tree_print_internal_array not implemented\n");
    (void)ft;
}