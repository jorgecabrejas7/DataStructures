/**
 * @file deque.c
 * @brief Stub implementation for a circular array-based Deque.
 *        All functions print a "not implemented" message and return a default value.
 */
#include "deque.h"  // Assuming deque.h is in the same directory or include path is set
#include <stdio.h>  // For printf
#include <stdlib.h> // For NULL
// #include <stdbool.h> // bool is already included via deque.h

Deque* deque_create(int initial_capacity) {
    printf("STUB: deque_create not implemented\n");
    (void)initial_capacity; // Parameter unused in stub
    return NULL;
}

void deque_destroy(Deque* dq) {
    printf("STUB: deque_destroy not implemented\n");
    (void)dq; // Parameter unused in stub
}

bool deque_add_first(Deque* dq, int item) {
    printf("STUB: deque_add_first not implemented\n");
    (void)dq;   // Parameter unused in stub
    (void)item; // Parameter unused in stub
    return false;
}

bool deque_add_last(Deque* dq, int item) {
    printf("STUB: deque_add_last not implemented\n");
    (void)dq;
    (void)item;
    return false;
}

int deque_remove_first(Deque* dq, bool* success) {
    printf("STUB: deque_remove_first not implemented\n");
    (void)dq; // Parameter unused in stub
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

int deque_remove_last(Deque* dq, bool* success) {
    printf("STUB: deque_remove_last not implemented\n");
    (void)dq;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

int deque_peek_first(const Deque* dq, bool* success) {
    printf("STUB: deque_peek_first not implemented\n");
    (void)dq;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

int deque_peek_last(const Deque* dq, bool* success) {
    printf("STUB: deque_peek_last not implemented\n");
    (void)dq;
    if (success) {
        *success = false;
    }
    return 0; // Default return, actual value meaningless if success is false
}

bool deque_is_empty(const Deque* dq) {
    printf("STUB: deque_is_empty not implemented\n");
    (void)dq;
    return true;
}

int deque_size(const Deque* dq) {
    printf("STUB: deque_size not implemented\n");
    (void)dq;
    return 0;
}

int deque_capacity(const Deque* dq) {
    printf("STUB: deque_capacity not implemented\n");
    (void)dq;
    return 0;
}

void deque_clear(Deque* dq) {
    printf("STUB: deque_clear not implemented\n");
    (void)dq;
}

bool deque_reserve(Deque* dq, int new_capacity) {
    printf("STUB: deque_reserve not implemented\n");
    (void)dq;
    (void)new_capacity;
    return false; // Or true if new_capacity <= current capacity (0 for stub)
                  // For a minimal stub, false is fine indicating it didn't really "succeed" in reserving.
}

void deque_print(const Deque* dq) {
    printf("STUB: deque_print not implemented\n");
    (void)dq;
}