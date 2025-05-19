/**
 * @file segment_tree.c
 * @brief Stub implementation for a Segment Tree supporting range sum queries and point updates.
 *        All functions print a "not implemented" message and return a default value.
 */
#include "segment_tree.h" // Assuming segment_tree.h is in the same directory or include path is set
#include <stdio.h>        // For printf
#include <stdlib.h>       // For NULL
// #include <stdbool.h> // bool is already included via segment_tree.h
// #include <limits.h> // Not strictly needed for sum stubs

// Corrected signature to match .h (segment_tree_build)
SegmentTree* segment_tree_build(const int* input_array, int array_size) {
    printf("STUB: segment_tree_build not implemented\n");
    (void)input_array; // Parameter unused in stub
    (void)array_size;  // Parameter unused in stub
    return NULL;
}

void segment_tree_destroy(SegmentTree* st) {
    printf("STUB: segment_tree_destroy not implemented\n");
    (void)st; // Parameter unused in stub
}

// Corrected signature to match .h (segment_tree_query_range_sum)
int segment_tree_query_range_sum(const SegmentTree* st, int query_left, int query_right, bool* success) {
    printf("STUB: segment_tree_query_range_sum not implemented\n");
    (void)st;          // Parameter unused in stub
    (void)query_left;  // Parameter unused in stub
    (void)query_right; // Parameter unused in stub
    if (success) {
        *success = false;
    }
    return 0; // Default sum for a stub, actual value meaningless if success is false
}

// Corrected signature to match .h (segment_tree_update_point)
bool segment_tree_update_point(SegmentTree* st, int array_index, int new_value) {
    printf("STUB: segment_tree_update_point not implemented\n");
    (void)st;          // Parameter unused in stub
    (void)array_index; // Parameter unused in stub
    (void)new_value;   // Parameter unused in stub
    return false;
}

// Added stub for segment_tree_get_original_size
int segment_tree_get_original_size(const SegmentTree* st) {
    printf("STUB: segment_tree_get_original_size not implemented\n");
    (void)st;
    return 0;
}

// Added stub for segment_tree_print_internal_array
void segment_tree_print_internal_array(const SegmentTree* st) {
    printf("STUB: segment_tree_print_internal_array not implemented\n");
    (void)st;
}

// The generic segment_tree_create, segment_tree_update, segment_tree_query,
// and example combine functions from the original stub are omitted as they
// do not match the specific API in segment_tree.h for range sum / point update.