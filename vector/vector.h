/**
 * @file vector.h
 * @brief Defines the interface for a dynamic array (Vector) of integers.
 *
 * == Clear Definition ==
 * The Vector is a dynamic array data structure that stores elements of type int.
 * It provides a sequence container that can change its size dynamically.
 * Elements are stored contiguously in memory, allowing for efficient random access.
 *
 * == Key Properties and Characteristics ==
 * - Stores 'int' data type exclusively.
 * - Contiguous memory: Elements are stored side-by-side in a single block of
 *   memory, which can improve cache performance.
 * - Dynamic sizing: The vector can automatically grow its internal storage if
 *   more space is needed for new elements. It can also be explicitly asked to
 *   reserve a certain amount of storage or to shrink its storage to fit the
 *   current number of elements.
 * - Random access: Elements can be accessed directly by their index in constant
 *   time (O(1)).
 * - Ordered: The order of elements as they are inserted is preserved.
 * - Size vs. Capacity:
 *   - 'size' is the number of actual int elements currently stored in the vector.
 *   - 'capacity' is the total number of int elements the currently allocated
 *     storage can hold before a reallocation is needed. Capacity is always
 *     greater than or equal to size.
 *
 * == Common Operations ==
 * - Creation and destruction of the vector.
 * - Adding integer elements to the end (push_back).
 * - Removing integer elements from the end (pop_back).
 * - Accessing integer elements by their index (get_item).
 * - Modifying integer elements by their index (set_item).
 * - Inserting and removing integer elements at arbitrary positions within the vector.
 * - Querying the current number of elements (size) and allocated storage (capacity).
 * - Clearing all integer elements from the vector.
 * - Managing capacity (reserving space, shrinking to fit content).
 *
 * == Typical Use Cases ==
 * - When a collection of integers is needed, but the exact quantity of items is not
 *   known at compile time or is expected to change during runtime.
 * - Situations requiring fast random access to integer elements (e.g., lookup by position).
 * - As a more flexible and safer alternative to C's built-in arrays for integer sequences.
 * - As an underlying storage mechanism for other data structures (e.g., stacks, queues).
 *
 * == Advantages ==
 * - Fast random access: O(1) time complexity for getting or setting elements by index.
 * - Efficient addition/removal at the end: O(1) amortized time complexity for
 *   operations like push_back and pop_back.
 * - Cache-friendly: Contiguous memory layout can lead to better cache utilization
 *   and performance compared to node-based structures like linked lists for iteration.
 *
 * == Disadvantages ==
 * - Costly insertions/deletions in the middle: O(N) time complexity for inserting or
 *   deleting elements at positions other than the end, as subsequent elements
 *   need to be shifted.
 * - Expensive reallocations: When the vector's capacity is exceeded and it needs to
 *   grow, a new, larger block of memory must be allocated, and all existing
 *   elements copied over. This is an O(N) operation, though its amortized cost
 *   is low if a good growth strategy (e.g., doubling capacity) is used.
 * - Potential for wasted space: If the vector's capacity is significantly larger
 *   than its current size, memory may be underutilized (though this can be
 *   managed with shrink_to_fit).
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, realloc, free

// Forward declaration of the Vector struct allows its use in function prototypes
// before the full struct definition.
typedef struct Vector Vector;

/**
 * @brief Structure representing the Vector for storing int elements.
 *
 * @param data A pointer to the dynamically allocated array where int elements are stored.
 * @param size The current number of int elements actually present in the vector.
 * @param capacity The total number of int elements that can be stored in the
 *                 currently allocated memory block pointed to by 'data' before
 *                 a reallocation is necessary.
 */

struct Vector {
    int* data;
    int size;
    int capacity;
};

// === Function Prototypes ===

/**
 * @brief Creates a new, empty vector with a specified initial capacity for int elements.
 *
 * If initial_capacity is 0, the internal data pointer will be NULL initially. Memory
 * will be allocated upon the first addition of an element or explicit reservation.
 *
 * @param initial_capacity The initial number of int elements the vector can hold.
 *                         Must be a non-negative integer.
 * @return Vector* A pointer to the newly created Vector structure, or NULL if
 *                 memory allocation fails or if initial_capacity is negative.
 * @note The caller is responsible for eventually calling vector_destroy() on the
 *       returned vector to free its resources.
 */
Vector* vector_create(int initial_capacity);

/**
 * @brief Destroys the vector, freeing all associated memory.
 *
 * This function deallocates the memory used for storing the int elements and
 * the memory for the Vector structure itself.
 * If 'vec' is NULL, the function performs no operation.
 *
 * @param vec A pointer to the Vector to be destroyed. Can be NULL.
 * @post All memory associated with 'vec' (both the data array and the struct
 *       itself) is freed. The pointer 'vec' becomes invalid and should not be
 *       used subsequently.
 */
void vector_destroy(Vector* vec);

/**
 * @brief Returns the current number of int elements stored in the vector.
 *
 * @param vec A pointer to a constant Vector. Must not be NULL.
 * @return int The number of int elements in the vector.
 * @pre 'vec' must be a valid, non-NULL pointer to a Vector that has been
 *      initialized by vector_create().
 */
int vector_size(const Vector* vec);

/**
 * @brief Returns the current storage capacity of the vector.
 *
 * Capacity is the maximum number of int elements the vector can hold with its
 * current memory allocation before needing to resize.
 *
 * @param vec A pointer to a constant Vector. Must not be NULL.
 * @return int The current capacity of the vector.
 * @pre 'vec' must be a valid, non-NULL pointer to a Vector.
 */
int vector_capacity(const Vector* vec);

/**
 * @brief Checks if the vector is empty (i.e., contains no int elements).
 *
 * @param vec A pointer to a constant Vector. Must not be NULL.
 * @return bool true if the vector's size is 0, false otherwise.
 * @pre 'vec' must be a valid, non-NULL pointer to a Vector.
 */
bool vector_is_empty(const Vector* vec);

/**
 * @brief Adds an int item to the end of the vector.
 *
 * If the vector's current capacity is insufficient to hold the new item,
 * the vector will attempt to resize its internal storage (typically by
 * reallocating to a larger capacity).
 *
 * @param vec A pointer to the Vector. Must not be NULL.
 * @param item The int value to be added to the vector.
 * @return bool true if the item was successfully added, false if memory
 *              allocation failed during a potential resize operation.
 * @pre 'vec' must be a valid, non-NULL pointer to a Vector.
 * @post If successful, the size of the vector is incremented by 1, and the new
 *       'item' is stored at the last position. The vector's capacity might
 *       increase if a resize was necessary.
 */
bool vector_push_back(Vector* vec, int item);

/**
 * @brief Retrieves the int item located at the specified index in the vector.
 *
 * The 'success' output parameter is used to indicate whether the retrieval
 * was successful. If 'index' is out of bounds, 'success' will be set to false,
 * and the returned int value is undefined and should not be used.
 *
 * @param vec A pointer to a constant Vector. Must not be NULL.
 * @param index The zero-based index of the int item to retrieve.
 * @param success A pointer to a boolean variable. On return, this variable will
 *                be set to true if 'index' was valid and the item was retrieved,
 *                or false if 'index' was out of bounds [0, size-1]. Must not be NULL.
 * @return int The int item at the specified 'index'. This value is only meaningful
 *             if '*success' is true upon function return.
 * @pre 'vec' must be a valid, non-NULL pointer to a Vector.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @pre For successful retrieval, 'index' must be in the range [0, vector_size(vec) - 1].
 */
int vector_get_item(const Vector* vec, int index, bool* success);

/**
 * @brief Modifies the int item at the specified index to a new value.
 *
 * @param vec A pointer to the Vector. Must not be NULL.
 * @param index The zero-based index of the int item to be modified.
 * @param item The new int value to store at the specified 'index'.
 * @return bool true if the item was successfully set (i.e., 'index' was valid),
 *              false if 'index' was out of bounds [0, size-1].
 * @pre 'vec' must be a valid, non-NULL pointer to a Vector.
 * @pre 'index' must be in the range [0, vector_size(vec) - 1] for the operation
 *      to be successful.
 * @post If successful (returns true), the int element at the given 'index' in the
 *       vector is updated to 'item'. The size and capacity remain unchanged.
 */
bool vector_set_item(Vector* vec, int index, int item);

/**
 * @brief Inserts an int item at the specified index, shifting subsequent elements to the right.
 *
 * If the current capacity is insufficient, the vector will attempt to resize.
 * All int elements originally at or after 'index' are shifted one position towards
 * the end of the vector to make space for the new item.
 *
 * @param vec A pointer to the Vector. Must not be NULL.
 * @param index The zero-based index at which the 'item' should be inserted.
 *              Valid range for 'index' is [0, vector_size(vec)].
 *              Inserting at vector_size(vec) is equivalent to vector_push_back().
 * @param item The int value to insert.
 * @return bool true if the item was successfully inserted, false if memory
 *              allocation failed during a potential resize or if 'index' is
 *              out of the valid range (i.e., < 0 or > vector_size(vec)).
 * @pre 'vec' must be a valid, non-NULL pointer to a Vector.
 * @pre 'index' must be in the range [0, vector_size(vec)].
 * @post If successful, the size of the vector is incremented by 1. The 'item' is
 *       placed at 'index', and all elements previously at 'index' or later are
 *       shifted one position to the right. Capacity might have increased.
 */
bool vector_insert_item(Vector* vec, int index, int item);

/**
 * @brief Removes the int item from the end of the vector and returns its value.
 *
 * The 'success' output parameter indicates if an item was successfully popped.
 * If the vector is empty, 'success' will be set to false, and the returned
 * int value is undefined.
 *
 * @param vec A pointer to the Vector. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this will be set
 *                to true if an item was popped, or false if the vector was empty.
 *                Must not be NULL.
 * @return int The int item removed from the end of the vector. This value is only
 *             meaningful if '*success' is true upon function return.
 * @pre 'vec' must be a valid, non-NULL pointer to a Vector.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @post If successful (vector was not empty), the size of the vector is
 *       decremented by 1.
 */
int vector_pop_back(Vector* vec, bool* success);

/**
 * @brief Removes the int item at the specified index, shifting subsequent elements to the left.
 *
 * All int elements originally after 'index' are shifted one position towards
 * the beginning of the vector to fill the gap.
 *
 * @param vec A pointer to the Vector. Must not be NULL.
 * @param index The zero-based index of the int item to remove.
 * @return bool true if the item was successfully removed (i.e., 'index' was valid),
 *              false if 'index' was out of bounds [0, size-1].
 * @pre 'vec' must be a valid, non-NULL pointer to a Vector.
 * @pre 'index' must be in the range [0, vector_size(vec) - 1] for the operation
 *      to be successful.
 * @post If successful, the size of the vector is decremented by 1. Elements
 *       after the removed item are shifted left. Capacity remains unchanged.
 */
bool vector_remove_item(Vector* vec, int index);

/**
 * @brief Removes all int elements from the vector, setting its size to 0.
 *
 * This operation does not change the vector's capacity. The allocated memory
 * is retained for potential future use, unless vector_shrink_to_fit() is called.
 *
 * @param vec A pointer to the Vector. Must not be NULL.
 * @pre 'vec' must be a valid, non-NULL pointer to a Vector.
 * @post The size of the vector becomes 0. Its capacity remains unchanged.
 */
void vector_clear(Vector* vec);

/**
 * @brief Requests that the vector capacity be at least 'new_capacity'.
 *
 * If 'new_capacity' is greater than the current vector capacity, the function
 * attempts to reallocate the internal storage to 'new_capacity'.
 * If 'new_capacity' is less than or equal to the current capacity, this function
 * typically does nothing and is considered successful.
 * This function will not shrink the capacity if 'new_capacity' is smaller than
 * current capacity. Use vector_shrink_to_fit() for that purpose.
 * It also ensures 'new_capacity' is not less than current size (data loss prevention).
 *
 * @param vec A pointer to the Vector. Must not be NULL.
 * @param new_capacity The desired minimum capacity. Must be non-negative.
 *                     If new_capacity is less than current vector size, the operation will fail
 *                     to prevent data loss (returns false).
 * @return bool true if the capacity is successfully ensured (either by reallocation,
 *              or because it was already sufficient/no change needed as per rules),
 *              or false if 'new_capacity' is negative, less than current size, or if
 *              memory allocation fails.
 * @pre 'vec' must be a valid, non-NULL pointer to a Vector.
 * @post If successful and 'new_capacity' was greater than original capacity (and also
 *       greater or equal to current size), the vector's 'capacity' is at least
 *       'new_capacity'. The 'size' and int elements remain unchanged.
 */
bool vector_reserve(Vector* vec, int new_capacity);

/**
 * @brief Reduces the capacity of the vector to match its current size.
 *
 * This operation attempts to reallocate the internal storage to free up any
 * unused capacity. If the size is 0, the internal data pointer might become
 * NULL after this operation, and capacity becomes 0.
 *
 * @param vec A pointer to the Vector. Must not be NULL.
 * @return bool true if the operation was successful (or if capacity already matched size),
 *              false if memory reallocation failed.
 * @pre 'vec' must be a valid, non-NULL pointer to a Vector.
 * @post If successful, the vector's 'capacity' is made equal to its 'size'.
 *       If size is 0, capacity becomes 0 and data pointer may be NULL.
 */
bool vector_shrink_to_fit(Vector* vec);

#endif // VECTOR_H