/**
 * @file red_black_tree.c
 * @brief Stub implementation for a Red-Black Tree.
 *        All functions print a "not implemented" message and return a default value.
 */
#include "red_black_tree.h" // Assuming red_black_tree.h is in the same directory or include path is set
#include <stdio.h>          // For printf
#include <stdlib.h>         // For NULL
// #include <stdbool.h> // bool is already included via red_black_tree.h

RedBlackTree* rbt_create() {
    printf("STUB: rbt_create not implemented\n");
    return NULL;
}

void rbt_destroy(RedBlackTree* tree) {
    printf("STUB: rbt_destroy not implemented\n");
    (void)tree; // Parameter unused in stub
}

bool rbt_insert(RedBlackTree* tree, int value) {
    printf("STUB: rbt_insert not implemented\n");
    (void)tree;  // Parameter unused in stub
    (void)value; // Parameter unused in stub
    return false; // As per .h: "false if value already exists or alloc failed"
}

bool rbt_contains(const RedBlackTree* tree, int value) {
    printf("STUB: rbt_contains not implemented\n");
    (void)tree;
    (void)value;
    return false;
}

bool rbt_remove(RedBlackTree* tree, int value) {
    printf("STUB: rbt_remove not implemented\n");
    (void)tree;
    (void)value;
    return false;
}

// Corrected return type to int as per .h file
int rbt_size(const RedBlackTree* tree) {
    printf("STUB: rbt_size not implemented\n");
    (void)tree;
    return 0;
}

bool rbt_is_empty(const RedBlackTree* tree) {
    printf("STUB: rbt_is_empty not implemented\n");
    (void)tree;
    return true; // As per .h: "true if tree's root is the NIL sentinel (or size is 0)"
}

// Corrected visitor function signature as per .h file
void rbt_in_order_traversal(const RedBlackTree* tree, void (*visitor)(int value, void* user_data), void* user_data) {
    printf("STUB: rbt_in_order_traversal not implemented\n");
    (void)tree;
    (void)visitor;
    (void)user_data;
}

// Functions from your .c stub that were not in the .h file are omitted:
// - rbt_get_height
// - rbt_pre_order_traversal
// - rbt_post_order_traversal
// - rbt_destroy_nodes_recursive (internal helper)
// - rbt_insert_recursive (internal helper)
// If these are intended to be public, they should be added to red_black_tree.h