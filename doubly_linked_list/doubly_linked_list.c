/**
 * @file doubly_linked_list.c
 * @brief Stub implementation for a Doubly Linked List.
 *        All functions print a "not implemented" message and return a default value.
 */
#include "doubly_linked_list.h" // Assuming doubly_linked_list.h is in the same directory or include path is set
#include <stdio.h>              // For printf
#include <stdlib.h>             // For NULL
// #include <stdbool.h> // bool is already included via doubly_linked_list.h

DoublyLinkedList* dll_create() {
    printf("STUB: dll_create not implemented\n");
    return NULL;
}

void dll_destroy(DoublyLinkedList* list) {
    printf("STUB: dll_destroy not implemented\n");
    (void)list; // Parameter unused in stub
}

// Corrected return type to int as per .h file
int dll_size(const DoublyLinkedList* list) {
    printf("STUB: dll_size not implemented\n");
    (void)list;
    return 0;
}

bool dll_is_empty(const DoublyLinkedList* list) {
    printf("STUB: dll_is_empty not implemented\n");
    (void)list;
    return true;
}

bool dll_add_first(DoublyLinkedList* list, int item) {
    printf("STUB: dll_add_first not implemented\n");
    (void)list; // Parameter unused in stub
    (void)item; // Parameter unused in stub
    return false;
}

bool dll_add_last(DoublyLinkedList* list, int item) {
    printf("STUB: dll_add_last not implemented\n");
    (void)list;
    (void)item;
    return false;
}

// Corrected index type to int as per .h file
bool dll_insert_at(DoublyLinkedList* list, int index, int item) {
    printf("STUB: dll_insert_at not implemented\n");
    (void)list;
    (void)index;
    (void)item;
    return false;
}

int dll_get_first(const DoublyLinkedList* list, bool* success) {
    printf("STUB: dll_get_first not implemented\n");
    (void)list; // Parameter unused in stub
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

int dll_get_last(const DoublyLinkedList* list, bool* success) {
    printf("STUB: dll_get_last not implemented\n");
    (void)list;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

// Corrected index type to int as per .h file
int dll_get_at(const DoublyLinkedList* list, int index, bool* success) {
    printf("STUB: dll_get_at not implemented\n");
    (void)list;
    (void)index;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

int dll_remove_first(DoublyLinkedList* list, bool* success) {
    printf("STUB: dll_remove_first not implemented\n");
    (void)list;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

int dll_remove_last(DoublyLinkedList* list, bool* success) {
    printf("STUB: dll_remove_last not implemented\n");
    (void)list;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

// Corrected index type to int as per .h file
int dll_remove_at(DoublyLinkedList* list, int index, bool* success) {
    printf("STUB: dll_remove_at not implemented\n");
    (void)list;
    (void)index;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

bool dll_contains(const DoublyLinkedList* list, int item) {
    printf("STUB: dll_contains not implemented\n");
    (void)list;
    (void)item;
    return false;
}

void dll_clear(DoublyLinkedList* list) {
    printf("STUB: dll_clear not implemented\n");
    (void)list;
}

void dll_print_forward(const DoublyLinkedList* list) {
    printf("STUB: dll_print_forward not implemented\n");
    (void)list;
}

void dll_print_backward(const DoublyLinkedList* list) {
    printf("STUB: dll_print_backward not implemented\n");
    (void)list;
}

