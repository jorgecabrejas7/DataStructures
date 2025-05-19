/**
 * @file binary_search_tree.c
 * @brief Stub implementation for a Binary Search Tree.
 *        All functions print a "not implemented" message and return a default value.
 */
#include "binary_search_tree.h" // Assuming binary_search_tree.h is in the same directory or include path is set
#include <stdio.h>              // For printf
#include <stdlib.h>             // For NULL
// #include <stdbool.h> // bool is already included via binary_search_tree.h

BinarySearchTree* bst_create() {
    printf("STUB: bst_create not implemented\n");
    return NULL;
}

void bst_destroy(BinarySearchTree* tree) {
    printf("STUB: bst_destroy not implemented\n");
    (void)tree; // Parameter unused in stub
}

bool bst_insert(BinarySearchTree* tree, int value) {
    printf("STUB: bst_insert not implemented\n");
    (void)tree;  // Parameter unused in stub
    (void)value; // Parameter unused in stub
    return false;
}

bool bst_contains(const BinarySearchTree* tree, int value) {
    printf("STUB: bst_contains not implemented\n");
    (void)tree;
    (void)value;
    return false;
}

bool bst_remove(BinarySearchTree* tree, int value) {
    printf("STUB: bst_remove not implemented\n");
    (void)tree;
    (void)value;
    return false;
}

// Corrected return type to int as per .h file
int bst_size(const BinarySearchTree* tree) {
    printf("STUB: bst_size not implemented\n");
    (void)tree;
    return 0;
}

bool bst_is_empty(const BinarySearchTree* tree) {
    printf("STUB: bst_is_empty not implemented\n");
    (void)tree;
    return true;
}

// Added bst_clear as it's in the .h file
void bst_clear(BinarySearchTree* tree) {
    printf("STUB: bst_clear not implemented\n");
    (void)tree;
}

// Corrected function signature for bst_find_min as per .h file
int bst_find_min(const BinarySearchTree* tree, bool* success) {
    printf("STUB: bst_find_min not implemented\n");
    (void)tree;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

// Corrected function signature for bst_find_max as per .h file
int bst_find_max(const BinarySearchTree* tree, bool* success) {
    printf("STUB: bst_find_max not implemented\n");
    (void)tree;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

int bst_height(const BinarySearchTree* tree) {
    printf("STUB: bst_height not implemented\n");
    (void)tree;
    return -1; // As per .h file: height of empty tree = -1
}

// Corrected visitor function signature as per .h file
void bst_in_order_traversal(const BinarySearchTree* tree, void (*visitor)(int data, void* user_data), void* user_data) {
    printf("STUB: bst_in_order_traversal not implemented\n");
    (void)tree;
    (void)visitor;
    (void)user_data;
}

// Corrected visitor function signature as per .h file
void bst_pre_order_traversal(const BinarySearchTree* tree, void (*visitor)(int data, void* user_data), void* user_data) {
    printf("STUB: bst_pre_order_traversal not implemented\n");
    (void)tree;
    (void)visitor;
    (void)user_data;
}

// Corrected visitor function signature as per .h file
void bst_post_order_traversal(const BinarySearchTree* tree, void (*visitor)(int data, void* user_data), void* user_data) {
    printf("STUB: bst_post_order_traversal not implemented\n");
    (void)tree;
    (void)visitor;
    (void)user_data;
}

