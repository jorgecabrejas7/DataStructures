/**
 * @file stack.c
 * @brief Stub implementation for an array-based Stack.
 *        All functions print a "not implemented" message and return a default value.
 */
#include "stack.h"  // Assuming stack.h is in the same directory or include path is set
#include <stdio.h>  // For printf
#include <stdlib.h> // For NULL
// #include <stdbool.h> // bool is already included via stack.h

// Corrected parameter type to int
Stack* stack_create(int initial_capacity) {
    printf("STUB: stack_create not implemented\n");
    (void)initial_capacity; // Parameter unused in stub
    return NULL;
}

void stack_destroy(Stack* s) {
    printf("STUB: stack_destroy not implemented\n");
    (void)s; // Parameter unused in stub
}

bool stack_push(Stack* s, int item) {
    printf("STUB: stack_push not implemented\n");
    (void)s;    // Parameter unused in stub
    (void)item; // Parameter unused in stub
    return false;
}

// Corrected signature to match .h (returns int, takes bool* success)
int stack_pop(Stack* s, bool* success) {
    printf("STUB: stack_pop not implemented\n");
    (void)s; // Parameter unused in stub
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

// Corrected signature to match .h (returns int, takes bool* success)
int stack_peek(const Stack* s, bool* success) {
    printf("STUB: stack_peek not implemented\n");
    (void)s;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

bool stack_is_empty(const Stack* s) {
    printf("STUB: stack_is_empty not implemented\n");
    (void)s;
    return true;
}

// Corrected return type to int
int stack_size(const Stack* s) {
    printf("STUB: stack_size not implemented\n");
    (void)s;
    return 0;
}

// Added stub for stack_capacity
int stack_capacity(const Stack* s) {
    printf("STUB: stack_capacity not implemented\n");
    (void)s;
    return 0;
}

void stack_clear(Stack* s) {
    printf("STUB: stack_clear not implemented\n");
    (void)s;
}

// Added stub for stack_reserve
bool stack_reserve(Stack* s, int new_capacity) {
    printf("STUB: stack_reserve not implemented\n");
    (void)s;
    (void)new_capacity;
    return false;
}

// Added stub for stack_print
void stack_print(const Stack* s) {
    printf("STUB: stack_print not implemented\n");
    (void)s;
}

// stack_is_full was in the original stub but not in stack.h, so it's omitted.