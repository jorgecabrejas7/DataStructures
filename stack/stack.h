/**
 * @file stack.h
 * @brief Defines the interface for an array-based Stack of integers.
 *
 * == Clear Definition ==
 * A Stack is a linear, abstract data structure that follows the Last-In,
 * First-Out (LIFO) principle. This means the last integer element added to
 * the stack is the first one to be removed. This implementation uses a
 * dynamic array as its underlying storage mechanism for integers.
 *
 * == Key Properties and Characteristics ==
 * - Stores 'int' data type exclusively.
 * - LIFO (Last-In, First-Out): Operations (push and pop) occur only at one
 *   end of the structure, called the 'top'.
 * - Array-based: Integer elements are stored in a contiguous block of memory.
 * - Dynamic sizing: The underlying array can grow if more space is needed for
 *   new integer elements, similar to a vector.
 * - 'top' index: An integer index is maintained to keep track of the position
 *   of the topmost element. An empty stack is typically represented by 'top'
 *   being -1.
 * - Capacity: The total number of integer elements the underlying array can
 *   hold before a resize is needed.
 * - Size: The current number of integer elements in the stack.
 *
 * == Common Operations ==
 * - push: Adds an integer element to the top of the stack.
 * - pop: Removes and returns the integer element from the top of the stack.
 * - peek (or top): Returns the integer element at the top of the stack without
 *   removing it.
 * - isEmpty: Checks if the stack contains any integer elements.
 * - size: Returns the number of integer elements currently in the stack.
 * - create/destroy: To manage the lifecycle of the stack.
 *
 * == Typical Use Cases ==
 * - Function call management (call stack) in program execution.
 * - Parsing expressions (e.g., infix to postfix conversion, postfix evaluation).
 * - Undo/Redo functionality in applications.
 * - Backtracking algorithms (e.g., solving mazes, N-queens problem).
 * - Depth-First Search (DFS) in graph traversal.
 *
 * == Advantages (Array-based Stack) ==
 * - Efficient push and pop: Amortized O(1) time complexity for push and pop
 *   operations when reallocations are infrequent.
 * - Cache-friendly: Contiguous memory layout can lead to better cache
 *   utilization for the stored integers compared to linked-list based stacks,
 *   though stack operations typically only access the top.
 * - Simplicity: Generally simpler to implement than a linked-list based stack
 *   if dynamic array mechanisms are already understood or available.
 *
 * == Disadvantages (Array-based Stack) ==
 * - Reallocation overhead: If the stack grows beyond its current capacity, a
 *   costly reallocation (O(N)) is required to create a larger array and copy
 *   elements.
 * - Potential wasted space: If the stack's capacity is significantly larger than
 *   its current size, memory may be underutilized. This can be somewhat managed
 *   but isn't as flexible as node-based allocation.
 * - Fixed maximum size (if not dynamic): A purely static array-based stack would
 *   have a fixed size, but this implementation is dynamic.
 */

#ifndef STACK_H
#define STACK_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, realloc, free
#include <stdio.h>   // For printf in stack_print (and NULL)

// Forward declaration
typedef struct Stack Stack;

/**
 * @brief Structure representing the array-based Stack for storing int elements.
 *
 * @param data A pointer to the dynamically allocated array where int elements are stored.
 * @param top The index of the top-most int element in the stack.
 *            Initialized to -1 for an empty stack.
 * @param capacity The total number of int elements that can be stored in the
 *                 currently allocated memory block pointed to by 'data' before
 *                 a reallocation is necessary.
 */
struct Stack {
    int* data;
    int top;
    int capacity;
};

// === Function Prototypes ===

/**
 * @brief Creates a new, empty stack with a specified initial capacity.
 *
 * If initial_capacity is 0, the internal data pointer will be NULL initially.
 * Memory will be allocated upon the first push operation or explicit reservation.
 *
 * @param initial_capacity The initial number of int elements the stack can hold.
 *                         Must be a non-negative integer.
 * @return Stack* A pointer to the newly created Stack structure, or NULL if
 *                memory allocation for the Stack structure itself fails or
 *                if initial_capacity is negative.
 *                (Note: Allocation of the 'data' array itself, if initial_capacity > 0,
 *                can also fail, in which case the Stack struct is freed and NULL returned).
 * @note The caller is responsible for eventually calling stack_destroy() on the
 *       returned stack to free its resources.
 */
Stack* stack_create(int initial_capacity);

/**
 * @brief Destroys the stack, freeing all associated memory.
 *
 * This function deallocates the memory used for storing the int elements (the 'data'
 * array) and the memory for the Stack structure itself.
 * If 's' is NULL, the function performs no operation.
 *
 * @param s A pointer to the Stack to be destroyed. Can be NULL.
 * @post All memory associated with 's' (both the data array and the struct
 *       itself) is freed. The pointer 's' becomes invalid and should not be
 *       used subsequently.
 */
void stack_destroy(Stack* s);

/**
 * @brief Adds an int item to the top of the stack.
 *
 * If the stack's current capacity is insufficient to hold the new item,
 * the stack will attempt to resize its internal storage (typically by
 * reallocating to a larger capacity).
 *
 * @param s A pointer to the Stack. Must not be NULL.
 * @param item The int value to be pushed onto the stack.
 * @return bool true if the item was successfully pushed, false if memory
 *              allocation failed during a potential resize operation.
 * @pre 's' must be a valid, non-NULL pointer to a Stack.
 * @post If successful, the 'top' index is incremented, the size of the stack
 *       increases by 1, and the new 'item' is stored at the new top position.
 *       The stack's capacity might increase if a resize was necessary.
 */
bool stack_push(Stack* s, int item);

/**
 * @brief Removes and returns the int item from the top of the stack.
 *
 * The 'success' output parameter is used to indicate whether the pop operation
 * was successful. If the stack is empty, 'success' will be set to false, and
 * the returned int value is undefined and should not be used.
 *
 * @param s A pointer to the Stack. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this variable will
 *                be set to true if an item was successfully popped (stack not empty),
 *                or false if the stack was empty. Must not be NULL.
 * @return int The int item removed from the top of the stack. This value is only
 *             meaningful if '*success' is true upon function return.
 * @pre 's' must be a valid, non-NULL pointer to a Stack.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @post If successful (stack was not empty), the 'top' index is decremented,
 *       and the size of the stack decreases by 1. Capacity remains unchanged.
 */
int stack_pop(Stack* s, bool* success);

/**
 * @brief Returns the int item at the top of the stack without removing it.
 *
 * The 'success' output parameter is used to indicate whether the peek operation
 * was successful. If the stack is empty, 'success' will be set to false, and
 * the returned int value is undefined and should not be used.
 *
 * @param s A pointer to a constant Stack. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this variable will
 *                be set to true if an item was successfully peeked (stack not empty),
 *                or false if the stack was empty. Must not be NULL.
 * @return int The int item at the top of the stack. This value is only meaningful
 *             if '*success' is true upon function return.
 * @pre 's' must be a valid, non-NULL pointer to a Stack.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 */
int stack_peek(const Stack* s, bool* success);

/**
 * @brief Checks if the stack is empty.
 *
 * @param s A pointer to a constant Stack. Must not be NULL.
 * @return bool true if the stack's top index is -1 (i.e., contains no int elements),
 *              false otherwise.
 * @pre 's' must be a valid, non-NULL pointer to a Stack.
 */
bool stack_is_empty(const Stack* s);

/**
 * @brief Returns the current number of int elements stored in the stack.
 *
 * Calculated as top + 1.
 *
 * @param s A pointer to a constant Stack. Must not be NULL.
 * @return int The number of int elements in the stack.
 * @pre 's' must be a valid, non-NULL pointer to a Stack.
 */
int stack_size(const Stack* s);

/**
 * @brief Returns the current storage capacity of the stack's underlying array.
 *
 * @param s A pointer to a constant Stack. Must not be NULL.
 * @return int The current capacity of the stack.
 * @pre 's' must be a valid, non-NULL pointer to a Stack.
 */
int stack_capacity(const Stack* s);

/**
 * @brief Removes all int elements from the stack, effectively making it empty.
 *
 * This operation resets the 'top' index to -1. It does not change the stack's
 * capacity; the allocated memory is retained for potential future use.
 *
 * @param s A pointer to the Stack. Must not be NULL.
 * @pre 's' must be a valid, non-NULL pointer to a Stack.
 * @post The stack's 'top' index becomes -1 (size becomes 0). Its capacity
 *       remains unchanged.
 */
void stack_clear(Stack* s);

/**
 * @brief Requests that the stack capacity be at least 'new_capacity'.
 *
 * If 'new_capacity' is greater than the current stack capacity, the function
 * attempts to reallocate the internal storage to 'new_capacity'.
 * If 'new_capacity' is less than or equal to the current capacity, this function
 * typically does nothing and is considered successful.
 * This function will not shrink the capacity if 'new_capacity' is smaller than
 * current capacity.
 * It also ensures 'new_capacity' is not less than current size (data loss prevention).
 *
 * @param s A pointer to the Stack. Must not be NULL.
 * @param new_capacity The desired minimum capacity. Must be non-negative.
 *                     If new_capacity is less than current stack size, the operation will fail
 *                     to prevent data loss (returns false).
 * @return bool true if the capacity is successfully ensured (either by reallocation,
 *              or because it was already sufficient/no change needed as per rules),
 *              or false if 'new_capacity' is negative, less than current size, or if
 *              memory allocation fails.
 * @pre 's' must be a valid, non-NULL pointer to a Stack.
 * @post If successful and 'new_capacity' was greater than original capacity (and also
 *       greater or equal to current size), the stack's 'capacity' is at least
 *       'new_capacity'. The 'top' index and int elements remain unchanged.
 */
bool stack_reserve(Stack* s, int new_capacity);

/**
 * @brief Prints the elements of the stack to standard output.
 *        (Primarily for debugging and testing purposes).
 *
 * Prints from top to bottom. Format: Stack (Top to Bottom): [top, ..., bottom] or [empty]
 *
 * @param s A pointer to a constant Stack. Can be NULL.
 */
void stack_print(const Stack* s);

#endif // STACK_H