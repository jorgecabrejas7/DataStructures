/* Placeholder for binary_heap.h */
/**
 * @file binary_heap.h
 * @brief Defines the interface for an array-based Binary Min-Heap of integers.
 *
 * == Clear Definition ==
 * A Binary Min-Heap is a specialized tree-based data structure that satisfies
 * the heap property: in a min-heap, for any given node 'N', the 'int' value
 * in 'N' is less than or equal to the 'int' values in its children.
 * The smallest 'int' element is always at the root of the heap.
 *
 * This implementation uses a dynamic array to store the 'int' elements and
 * maintains the structure of a complete binary tree. A complete binary tree
 * is a binary tree in which every level, except possibly the last, is completely
 * filled, and all nodes in the last level are as far left as possible.
 *
 * == Key Properties and Characteristics ==
 * - Stores 'int' data type exclusively.
 * - Min-Heap Property: The key of each node is less than or equal to the keys
 *   of its children. This implies the minimum element is at the root.
 * - Complete Binary Tree Structure: This allows the heap to be efficiently
 *   represented using an array. For a node at index `i`:
 *   - Its left child is at index `2*i + 1`.
 *   - Its right child is at index `2*i + 2`.
 *   - Its parent is at index `floor((i-1)/2)`.
 *   (Assuming 0-based indexing for the array).
 * - Dynamic Sizing: The underlying array can grow if more space is needed.
 * - Not Sorted: While the minimum element is at the root, the heap is not
 *   fully sorted. There's no specific relationship between sibling nodes or
 *   nodes in different subtrees (other than what's implied by the heap property
 *   cascading down).
 *
 * == Common Operations ==
 * - Insertion (add/insert): Adds a new 'int' element to the heap, maintaining
 *   the heap property by "sifting up" or "percolating up" the new element.
 * - Extract Minimum (extract_min): Removes and returns the minimum 'int' element
 *   (the root), then restructures the heap to maintain the heap property by
 *   replacing the root with the last element and "sifting down" or "percolating down".
 * - Peek Minimum (peek_min): Returns the minimum 'int' element without removing it.
 * - Get Size: Returns the number of 'int' elements in the heap.
 * - Build Heap: Creates a heap from an arbitrary array of 'int's in O(N) time.
 *   (This is a more advanced operation, can be added later; basic create is empty heap).
 * - Create/Destroy: Manages the lifecycle.
 *
 * == Typical Use Cases ==
 * - Implementing Priority Queues: Heaps are the most common way to implement them.
 * - Heap Sort algorithm.
 * - Graph algorithms like Dijkstra's shortest path and Prim's minimum spanning tree.
 * - Finding the k-th smallest/largest element efficiently.
 *
 * == Advantages ==
 * - Efficient insertion and extract_min: O(log N) time complexity.
 * - Efficient peek_min: O(1) time complexity.
 * - Space efficient: Uses an array, no overhead for pointers like node-based trees.
 * - Build_heap can be done in O(N) time.
 *
 * == Disadvantages ==
 * - Searching for an arbitrary 'int' element (not min) is O(N) as the heap
 *   property doesn't help much beyond the root.
 * - Not suitable if frequent searching for arbitrary elements is needed.
 * - Deletion of an arbitrary element (not min) is more complex (O(log N) after
 *   finding it in O(N), or requires additional structures to locate elements).
 *   For this basic heap, we'll focus on extract_min.
 */

#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, realloc, free
#include <stdio.h>   // For printf in heap_print (and NULL)

// Forward declaration
typedef struct BinaryHeap BinaryHeap;

/**
 * @brief Structure representing the array-based Binary Min-Heap for storing int elements.
 *
 * @param data A pointer to the dynamically allocated array where int elements are stored.
 * @param size The current number of int elements actually present in the heap.
 * @param capacity The total number of int elements that can be stored in the
 *                 currently allocated memory block pointed to by 'data' before
 *                 a reallocation is necessary.
 */
struct BinaryHeap {
    int* data;
    int size;
    int capacity;
};

// === Function Prototypes ===

/**
 * @brief Creates a new, empty binary min-heap with a specified initial capacity.
 *
 * If initial_capacity is 0, the internal data pointer will be NULL initially.
 * Memory will be allocated upon the first insertion.
 *
 * @param initial_capacity The initial number of int elements the heap can hold.
 *                         Must be a non-negative integer.
 * @return BinaryHeap* A pointer to the newly created BinaryHeap structure, or NULL if
 *                     memory allocation fails or if initial_capacity is negative.
 * @note The caller is responsible for eventually calling binary_heap_destroy() on the
 *       returned heap to free its resources.
 */
BinaryHeap* binary_heap_create(int initial_capacity);

/**
 * @brief Destroys the binary min-heap, freeing all associated memory.
 *
 * Deallocates the 'data' array and the BinaryHeap structure itself.
 * If 'heap' is NULL, the function performs no operation.
 *
 * @param heap A pointer to the BinaryHeap to be destroyed. Can be NULL.
 * @post All memory associated with 'heap' is freed. 'heap' becomes invalid.
 */
void binary_heap_destroy(BinaryHeap* heap);

/**
 * @brief Inserts an integer value into the binary min-heap.
 *
 * The value is added to the end of the array (to maintain the complete tree
 * property temporarily) and then "sifted up" to its correct position to
 * restore the min-heap property. If the heap is full, it will attempt to resize.
 *
 * @param heap A pointer to the BinaryHeap. Must not be NULL.
 * @param value The int value to insert.
 * @return bool true if the value was successfully inserted (and memory allocation
 *              for a potential resize succeeded), false if memory allocation failed.
 * @pre 'heap' must be a valid, non-NULL pointer to a BinaryHeap.
 * @post If successful, 'size' is incremented. The 'value' is added to the heap,
 *       and the min-heap property is maintained. Capacity might increase.
 */
bool binary_heap_insert(BinaryHeap* heap, int value);

/**
 * @brief Removes and returns the minimum integer value (the root) from the heap.
 *
 * The root is replaced by the last element in the heap, which is then "sifted down"
 * to its correct position to restore the min-heap property.
 * The 'success' output parameter indicates if removal was possible.
 *
 * @param heap A pointer to the BinaryHeap. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, set to true if an
 *                item was extracted (heap not empty), false otherwise. Must not be NULL.
 * @return int The minimum int value removed from the heap. Meaningful only if '*success' is true.
 * @pre 'heap' must be a valid, non-NULL pointer to a BinaryHeap.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @post If successful, 'size' is decremented. The smallest element is removed,
 *       and the min-heap property is restored.
 */
int binary_heap_extract_min(BinaryHeap* heap, bool* success);

/**
 * @brief Returns the minimum integer value (the root) from the heap without removing it.
 *
 * The 'success' output parameter indicates if peeking was possible.
 *
 * @param heap A pointer to a constant BinaryHeap. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, set to true if an
 *                item was peeked (heap not empty), false otherwise. Must not be NULL.
 * @return int The minimum int value at the root. Meaningful only if '*success' is true.
 * @pre 'heap' must be a valid, non-NULL pointer to a BinaryHeap.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 */
int binary_heap_peek_min(const BinaryHeap* heap, bool* success);

/**
 * @brief Checks if the binary min-heap is empty.
 *
 * @param heap A pointer to a constant BinaryHeap. Must not be NULL.
 * @return bool true if the heap's size is 0, false otherwise.
 * @pre 'heap' must be a valid, non-NULL pointer to a BinaryHeap.
 */
bool binary_heap_is_empty(const BinaryHeap* heap);

/**
 * @brief Returns the current number of integer elements in the heap.
 *
 * @param heap A pointer to a constant BinaryHeap. Must not be NULL.
 * @return int The number of int elements in the heap.
 * @pre 'heap' must be a valid, non-NULL pointer to a BinaryHeap.
 */
int binary_heap_size(const BinaryHeap* heap);

/**
 * @brief Returns the current storage capacity of the heap's underlying array.
 *
 * @param heap A pointer to a constant BinaryHeap. Must not be NULL.
 * @return int The current capacity of the heap.
 * @pre 'heap' must be a valid, non-NULL pointer to a BinaryHeap.
 */
int binary_heap_capacity(const BinaryHeap* heap);

/**
 * @brief Removes all integer elements from the heap, making it empty.
 *
 * Resets 'size' to 0. Capacity remains unchanged.
 *
 * @param heap A pointer to the BinaryHeap. Must not be NULL.
 * @pre 'heap' must be a valid, non-NULL pointer to a BinaryHeap.
 * @post The heap's 'size' becomes 0. Capacity remains unchanged.
 */
void binary_heap_clear(BinaryHeap* heap);

/**
 * @brief (Optional helper for testing/debugging) Prints the elements of the heap's
 *        underlying array. This is NOT a tree traversal print.
 *
 * Format: Heap Array: [e0, e1, ..., eN-1] or [empty]
 *
 * @param heap A pointer to a constant BinaryHeap. Can be NULL.
 */
void binary_heap_print_array(const BinaryHeap* heap);


#endif // BINARY_HEAP_H