/**
 * @file deque.h
 * @brief Defines the interface for a circular array-based Deque (Double-Ended Queue) of integers.
 *
 * == Clear Definition ==
 * A Deque (pronounced "deck", short for Double-Ended Queue) is a linear, abstract
 * data structure that generalizes a queue. Unlike a standard queue where elements
 * are added at one end (rear) and removed from the other (front), a deque allows
 * integer elements to be added and removed from both ends (front and rear).
 *
 * This implementation uses a dynamic circular array (ring buffer) as its
 * underlying storage mechanism for integers.
 *
 * == Key Properties and Characteristics ==
 * - Stores 'int' data type exclusively.
 * - Supports FIFO and LIFO: Elements can be added/removed from either the front
 *   or the rear. This means it can behave like a queue or a stack.
 * - Circular Array-based: Integer elements are stored in a contiguous block of
 *   memory treated as circular.
 * - Dynamic sizing: The underlying array can grow if more space is needed.
 * - 'front' index: An integer index indicating the position of the first (leftmost)
 *   element in the deque.
 * - 'rear' index: An integer index indicating the position *after* the last (rightmost)
 *   element. (This is one common convention; another is 'rear' points to the last element.
 *   We will use 'rear' as the next available slot at the back for consistency with queue).
 *   Alternatively, for deque, 'front' and 'rear' can directly point to the elements,
 *   and 'size' is crucial. Let's define `front` as the index of the first element
 *   and `rear` as the index of the last element. Adjustments are needed if empty.
 *   For a simpler circular array implementation, it's often easier to maintain `front`
 *   and `size`, from which `rear` can be derived, or maintain `front` and `rear`
 *   as in a queue and adjust insertion/deletion logic for both ends.
 *
 *   Let's adopt the `front` and `size` model for this Deque for easier management
 *   of circularity and empty/full states, similar to how one might manage a queue:
 *   - `front`: Index of the first element.
 *   - `size`: Number of elements.
 *   - `rear` (conceptual): Can be calculated as `(front + size - 1 + capacity) % capacity` if it points to the last element.
 *     Or, if `rear` is the next available slot after the last element, it is `(front + size) % capacity`.
 *     To simplify, we will manage `front` and `size`. Adding to front decrements `front` (circularly).
 *     Adding to rear increments the effective end position.
 *
 * == Key Properties (Revised for this specific implementation) ==
 * - Stores 'int' data type exclusively.
 * - Circular Array-based: Integer elements stored in a contiguous block of memory.
 * - Dynamic sizing: The array can grow.
 * - 'front' index: Index of the first element in the deque. If empty, its value is convention-dependent (e.g., 0).
 * - 'size': Number of elements currently in the deque.
 * - 'capacity': Total number of elements the array can hold.
 *
 * == Common Operations ==
 * - add_first (push_front): Adds an 'int' element to the front.
 * - add_last (push_back): Adds an 'int' element to the rear.
 * - remove_first (pop_front): Removes and returns the 'int' element from the front.
 * - remove_last (pop_back): Removes and returns the 'int' element from the rear.
 * - peek_first: Returns the 'int' element at the front without removing it.
 * - peek_last: Returns the 'int' element at the rear without removing it.
 * - isEmpty, isFull, size, create/destroy.
 *
 * == Typical Use Cases ==
 * - Implementing a LIFO stack (using add_first/remove_first or add_last/remove_last).
 * - Implementing a FIFO queue (using add_last/remove_first).
 * - Storing a history of operations (e.g., undo/redo limited to N steps).
 * - Sliding window algorithms (efficiently adding to one end and removing from other).
 * - Work-stealing job schedulers.
 *
 * == Advantages (Circular Array-based Deque) ==
 * - Efficient operations at both ends: Amortized O(1) for add/remove/peek at front/rear.
 * - Good memory utilization with circular array.
 * - Versatile: Can act as a stack or a queue.
 *
 * == Disadvantages (Circular Array-based Deque) ==
 * - Reallocation overhead: Similar to vector/queue, resizing is O(N) and requires
 *   unrolling elements if the circular buffer is wrapped.
 * - Complexity of circular logic: Managing front, rear (or size), and capacity with
 *   modulo arithmetic for both ends requires careful implementation.
 */

#ifndef DEQUE_H
#define DEQUE_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, realloc, free
#include <stdio.h>   // For printf in deque_print (and NULL)

// Forward declaration
typedef struct Deque Deque;

/**
 * @brief Structure representing the circular array-based Deque for storing int elements.
 *
 * 'front' is the index of the first logical element.
 * Elements are stored from data[front] up to data[(front + size - 1 + capacity) % capacity].
 * When adding to front, 'front' moves backward (circularly).
 * When adding to rear, elements are placed at data[(front + size) % capacity].
 *
 * @param data A pointer to the dynamically allocated array where int elements are stored.
 * @param front The index in 'data' where the first element of the deque is located.
 *              If size is 0, 'front' is typically 0 but its exact value is less critical.
 * @param size The current number of int elements actually present in the deque.
 * @param capacity The total number of int elements that can be stored in the
 *                 currently allocated memory block pointed to by 'data' before
 *                 a reallocation is necessary.
 */
struct Deque {
    int* data;
    int front;
    int size;
    int capacity;
};

// === Function Prototypes ===

/**
 * @brief Creates a new, empty deque with a specified initial capacity.
 *
 * If initial_capacity is 0, the internal data pointer will be NULL initially.
 * Memory will be allocated upon the first addition of an element.
 *
 * @param initial_capacity The initial number of int elements the deque can hold.
 *                         Must be a non-negative integer.
 * @return Deque* A pointer to the newly created Deque structure, or NULL if
 *                memory allocation fails or if initial_capacity is negative.
 * @note The caller is responsible for eventually calling deque_destroy() on the
 *       returned deque to free its resources.
 */
Deque* deque_create(int initial_capacity);

/**
 * @brief Destroys the deque, freeing all associated memory.
 *
 * Deallocates the 'data' array and the Deque structure itself.
 * If 'dq' is NULL, the function performs no operation.
 *
 * @param dq A pointer to the Deque to be destroyed. Can be NULL.
 * @post All memory associated with 'dq' is freed. 'dq' becomes invalid.
 */
void deque_destroy(Deque* dq);

/**
 * @brief Adds an int item to the front (head) of the deque.
 *
 * If the deque is full (size == capacity), it will attempt to resize.
 *
 * @param dq A pointer to the Deque. Must not be NULL.
 * @param item The int value to be added.
 * @return bool true if the item was successfully added, false if memory
 *              allocation failed during a potential resize.
 * @pre 'dq' must be a valid, non-NULL pointer to a Deque.
 * @post If successful, 'item' becomes the new first element. 'front' index is
 *       updated (decremented circularly). 'size' is incremented. Capacity might increase.
 */
bool deque_add_first(Deque* dq, int item);

/**
 * @brief Adds an int item to the rear (tail) of the deque.
 *
 * If the deque is full (size == capacity), it will attempt to resize.
 *
 * @param dq A pointer to the Deque. Must not be NULL.
 * @param item The int value to be added.
 * @return bool true if the item was successfully added, false if memory
 *              allocation failed during a potential resize.
 * @pre 'dq' must be a valid, non-NULL pointer to a Deque.
 * @post If successful, 'item' becomes the new last element. 'size' is incremented.
 *       The conceptual 'rear' position is updated. Capacity might increase.
 */
bool deque_add_last(Deque* dq, int item);

/**
 * @brief Removes and returns the int item from the front (head) of the deque.
 *
 * The 'success' output parameter indicates if removal was possible.
 *
 * @param dq A pointer to the Deque. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, set to true if an
 *                item was removed (deque not empty), false otherwise. Must not be NULL.
 * @return int The int item removed from the front. Meaningful only if '*success' is true.
 * @pre 'dq' must be a valid, non-NULL pointer to a Deque.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @post If successful, 'front' index is updated (incremented circularly).
 *       'size' is decremented.
 */
int deque_remove_first(Deque* dq, bool* success);

/**
 * @brief Removes and returns the int item from the rear (tail) of the deque.
 *
 * The 'success' output parameter indicates if removal was possible.
 *
 * @param dq A pointer to the Deque. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, set to true if an
 *                item was removed (deque not empty), false otherwise. Must not be NULL.
 * @return int The int item removed from the rear. Meaningful only if '*success' is true.
 * @pre 'dq' must be a valid, non-NULL pointer to a Deque.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @post If successful, 'size' is decremented. The conceptual 'rear' position is updated.
 */
int deque_remove_last(Deque* dq, bool* success);

/**
 * @brief Returns the int item at the front (head) of the deque without removing it.
 *
 * The 'success' output parameter indicates if peeking was possible.
 *
 * @param dq A pointer to a constant Deque. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, set to true if an
 *                item was peeked (deque not empty), false otherwise. Must not be NULL.
 * @return int The int item at the front. Meaningful only if '*success' is true.
 * @pre 'dq' must be a valid, non-NULL pointer to a Deque.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 */
int deque_peek_first(const Deque* dq, bool* success);

/**
 * @brief Returns the int item at the rear (tail) of the deque without removing it.
 *
 * The 'success' output parameter indicates if peeking was possible.
 *
 * @param dq A pointer to a constant Deque. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, set to true if an
 *                item was peeked (deque not empty), false otherwise. Must not be NULL.
 * @return int The int item at the rear. Meaningful only if '*success' is true.
 * @pre 'dq' must be a valid, non-NULL pointer to a Deque.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 */
int deque_peek_last(const Deque* dq, bool* success);

/**
 * @brief Checks if the deque is empty.
 *
 * @param dq A pointer to a constant Deque. Must not be NULL.
 * @return bool true if the deque's size is 0, false otherwise.
 * @pre 'dq' must be a valid, non-NULL pointer to a Deque.
 */
bool deque_is_empty(const Deque* dq);

/**
 * @brief Returns the current number of int elements in the deque.
 *
 * @param dq A pointer to a constant Deque. Must not be NULL.
 * @return int The number of int elements in the deque.
 * @pre 'dq' must be a valid, non-NULL pointer to a Deque.
 */
int deque_size(const Deque* dq);

/**
 * @brief Returns the current storage capacity of the deque's underlying array.
 *
 * @param dq A pointer to a constant Deque. Must not be NULL.
 * @return int The current capacity of the deque.
 * @pre 'dq' must be a valid, non-NULL pointer to a Deque.
 */
int deque_capacity(const Deque* dq);

/**
 * @brief Removes all int elements from the deque, making it empty.
 *
 * Resets 'front' to 0 and 'size' to 0. Capacity remains unchanged.
 *
 * @param dq A pointer to the Deque. Must not be NULL.
 * @pre 'dq' must be a valid, non-NULL pointer to a Deque.
 * @post The deque's 'size' becomes 0, 'front' is reset (e.g., to 0).
 *       Capacity remains unchanged.
 */
void deque_clear(Deque* dq);

/**
 * @brief Requests that the deque capacity be at least 'new_capacity'.
 *
 * If 'new_capacity' is greater than current capacity, attempts to reallocate.
 * Elements are unrolled into linear order in the new array during resize.
 * If 'new_capacity' < current size, the operation fails.
 *
 * @param dq A pointer to the Deque. Must not be NULL.
 * @param new_capacity The desired minimum capacity. Must be non-negative.
 * @return bool true if successful or no change needed, false on failure
 *              (e.g., allocation error, new_capacity < size).
 * @pre 'dq' must be a valid, non-NULL pointer to a Deque.
 * @post If successful and resize occurred, 'capacity' is updated, 'front' is 0,
 *       and elements are linearly arranged.
 */
bool deque_reserve(Deque* dq, int new_capacity);

/**
 * @brief Prints the elements of the deque to standard output from front to rear.
 *        (Primarily for debugging and testing purposes).
 *
 * Format: Deque (Front to Rear): [e1, e2, ..., eN] or [empty]
 *
 * @param dq A pointer to a constant Deque. Can be NULL.
 */
void deque_print(const Deque* dq);


#endif // DEQUE_H