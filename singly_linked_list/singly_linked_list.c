/**
 * @file singly_linked_list.c
 * @brief Stub implementation for a Singly Linked List.
 *        All functions print a "not implemented" message and return a default value.
 */
#include "singly_linked_list.h" // Assuming singly_linked_list.h is in the same directory or include path is set
#include <stdio.h>              // For printf
#include <stdlib.h>             // For NULL
// #include <stdbool.h> // bool is already included via singly_linked_list.h

SinglyLinkedList* sll_create() {
    printf("STUB: sll_create not implemented\n");
    return NULL;
}

void sll_destroy(SinglyLinkedList* list) {
    printf("STUB: sll_destroy not implemented\n");
    (void)list; // Parameter unused in stub
}

// Corrected return type to int
int sll_size(const SinglyLinkedList* list) {
    printf("STUB: sll_size not implemented\n");
    (void)list;
    return 0;
}

bool sll_is_empty(const SinglyLinkedList* list) {
    printf("STUB: sll_is_empty not implemented\n");
    (void)list;
    return true;
}

bool sll_add_first(SinglyLinkedList* list, int item) {
    printf("STUB: sll_add_first not implemented\n");
    (void)list; // Parameter unused in stub
    (void)item; // Parameter unused in stub
    return false;
}

bool sll_add_last(SinglyLinkedList* list, int item) {
    printf("STUB: sll_add_last not implemented\n");
    (void)list;
    (void)item;
    return false;
}

// Corrected index type to int
bool sll_insert_at(SinglyLinkedList* list, int index, int item) {
    printf("STUB: sll_insert_at not implemented\n");
    (void)list;
    (void)index;
    (void)item;
    return false;
}

int sll_get_first(const SinglyLinkedList* list, bool* success) {
    printf("STUB: sll_get_first not implemented\n");
    (void)list; // Parameter unused in stub
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

int sll_get_last(const SinglyLinkedList* list, bool* success) {
    printf("STUB: sll_get_last not implemented\n");
    (void)list;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

// Corrected index type to int
int sll_get_at(const SinglyLinkedList* list, int index, bool* success) {
    printf("STUB: sll_get_at not implemented\n");
    (void)list;
    (void)index;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

int sll_remove_first(SinglyLinkedList* list, bool* success) {
    printf("STUB: sll_remove_first not implemented\n");
    (void)list;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

int sll_remove_last(SinglyLinkedList* list, bool* success) {
    printf("STUB: sll_remove_last not implemented\n");
    (void)list;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

// Corrected index type to int
int sll_remove_at(SinglyLinkedList* list, int index, bool* success) {
    printf("STUB: sll_remove_at not implemented\n");
    (void)list;
    (void)index;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

bool sll_contains(const SinglyLinkedList* list, int item) {
    printf("STUB: sll_contains not implemented\n");
    (void)list;
    (void)item;
    return false;
}

void sll_clear(SinglyLinkedList* list) {
    printf("STUB: sll_clear not implemented\n");
    (void)list;
}

void sll_print(const SinglyLinkedList* list) {
    printf("STUB: sll_print not implemented\n");
    (void)list;
}

// Functions from your .c stub that were not in the .h file are omitted:
// - sll_push_front (use sll_add_first)
// - sll_pop_front (use sll_remove_first)
// - sll_peek_front (use sll_get_first)
// - sll_push_back (use sll_add_last)
// - sll_find
// - sll_remove_value
// - sll_reverse
// - sll_for_each