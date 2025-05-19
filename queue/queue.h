/**
 * @file queue.h
 * @brief Defines the interface for a circular array-based Queue of integers.
 *
 * == Clear Definition ==
 * A Queue is a linear, abstract data structure that follows the First-In,
 * First-Out (FIFO) principle. This means the first integer element added
 * (enqueued) to the queue is the first one to be removed (dequeued).
 * This implementation uses a dynamic circular array (also known as a ring
 * buffer) as its underlying storage mechanism for integers.
 *
 * == Key Properties and Characteristics ==
 * - Stores 'int' data type exclusively.
 * - FIFO (First-In, First-Out): Elements are added at one end (the 'rear' or
 *   'tail') and removed from the other end (the 'front' or 'head').
 * - Circular Array-based: Integer elements are stored in a contiguous block
 *   of memory. The array is treated as circular, meaning the end of the
 *   array wraps around to the beginning. This allows for efficient use of
 *   space and avoids shifting elements on enqueue/dequeue.
 * - Dynamic sizing: The underlying array can grow if more space is needed for
 *   new integer elements.
 * - 'front' index: An integer index indicating the position of the first (oldest)
 *   element in the queue.
 * - 'rear' index: An integer index indicating the position *after* the last
 *   element, i.e., the next available slot for enqueueing.
 * - 'size': An integer count of the current number of elements in the queue.
 *   This helps distinguish between a full and an empty queue when front and
 *   rear indices might coincide in a circular buffer if size was not tracked.
 * - 'capacity': The total number of integer elements the underlying array can
 *   hold before a resize is needed.
 *
 * == Common Operations ==
 * - enqueue: Adds an integer element to the rear of the queue.
 * - dequeue: Removes and returns the integer element from the front of the queue.
 * - peek (or front): Returns the integer element at the front of the queue
 *   without removing it.
 * - isEmpty: Checks if the queue contains any integer elements.
 * - isFull (implicitly): Checks if size == capacity.
 * - size: Returns the number of integer elements currently in the queue.
 * - create/destroy: To manage the lifecycle of the queue.
 *
 * == Typical Use Cases ==
 * - Task scheduling (e.g., print queues, CPU scheduling).
 * - Buffering data (e.g., I/O buffers, network packet queues).
 * - Breadth-First Search (BFS) in graph traversal.
 * - Simulating waiting lines.
 * - Implementing other data structures (e.g., some types of priority queues).
 *
 * == Advantages (Circular Array-based Queue) ==
 * - Efficient enqueue and dequeue: O(1) time complexity for both operations
 *   (amortized O(1) if resizing is considered, but typically O(1) as elements
 *   are not shifted).
 * - Good memory utilization: The circular array effectively reuses space.
 * - Cache-friendly (potentially): Elements can be somewhat contiguous, though
 *   the circular nature can break strict contiguity in memory if the queue wraps.
 *
 * == Disadvantages (Circular Array-based Queue) ==
 * - Reallocation overhead: If the queue grows beyond its current capacity, a
 *   costly reallocation (O(N)) is required to create a larger array and copy
 *   elements. Elements need to be "unrolled" into the new linear array.
 * - Potential wasted space: If capacity is much larger than size, memory is
 *   underutilized. This is common to array-based dynamic structures.
 * - Complexity of circular logic: Implementation requires careful handling of
 *   front and rear indices with modulo arithmetic.
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, realloc, free
#include <stdio.h>   // For printf in queue_print (and NULL)

// Forward declaration
typedef struct Queue Queue;

/**
 * @brief Structure representing the circular array-based Queue for storing int elements.
 *
 * @param data A pointer to the dynamically allocated array where int elements are stored.
 * @param front The index of the front-most (oldest) int element in the queue.
 * @param rear The index of the next available slot *after* the last element.
 *             Elements are enqueued at data[rear].
 * @param size The current number of int elements actually present in the queue.
 * @param capacity The total number of int elements that can be stored in the
 *                 currently allocated memory block pointed to by 'data' before
 *                 a reallocation is necessary.
 */
struct Queue {
    int* data;
    int front;
    int rear;
    int size;
    int capacity;
};

// === Function Prototypes ===

/**
 * @brief Creates a new, empty queue with a specified initial capacity.
 *
 * If initial_capacity is 0, the internal data pointer will be NULL initially.
 * Memory will be allocated upon the first enqueue operation.
 *
 * @param initial_capacity The initial number of int elements the queue can hold.
 *                         Must be a non-negative integer. A capacity of 0 is allowed.
 *                         If creating a queue with capacity 0, internal data will be NULL
 *                         until the first element is enqueued and a resize occurs.
 * @return Queue* A pointer to the newly created Queue structure, or NULL if
 *                memory allocation for the Queue structure itself fails or
 *                if initial_capacity is negative. (Note: Allocation of the 'data'
 *                array, if initial_capacity > 0, can also fail).
 * @note The caller is responsible for eventually calling queue_destroy() on the
 *       returned queue to free its resources.
 */
Queue* queue_create(int initial_capacity);

/**
 * @brief Destroys the queue, freeing all associated memory.
 *
 * This function deallocates the memory used for storing the int elements (the 'data'
 * array) and the memory for the Queue structure itself.
 * If 'q' is NULL, the function performs no operation.
 *
 * @param q A pointer to the Queue to be destroyed. Can be NULL.
 * @post All memory associated with 'q' (both the data array and the struct
 *       itself) is freed. The pointer 'q' becomes invalid and should not be
 *       used subsequently.
 */
void queue_destroy(Queue* q);

/**
 * @brief Adds an int item to the rear of the queue.
 *
 * If the queue's current capacity is insufficient (i.e., size == capacity),
 * the queue will attempt to resize its internal storage (typically by
 * reallocating to a larger capacity). During resize, elements are "unrolled"
 * from their circular positions into a linear order in the new array.
 *
 * @param q A pointer to the Queue. Must not be NULL.
 * @param item The int value to be enqueued.
 * @return bool true if the item was successfully enqueued, false if memory
 *              allocation failed during a potential resize operation.
 * @pre 'q' must be a valid, non-NULL pointer to a Queue.
 * @post If successful, the 'item' is added to the rear of the queue, 'size' is
 *       incremented, and 'rear' index is updated (circularly). The queue's
 *       'capacity' might increase if a resize was necessary.
 */
bool queue_enqueue(Queue* q, int item);

/**
 * @brief Removes and returns the int item from the front of the queue.
 *
 * The 'success' output parameter is used to indicate whether the dequeue operation
 * was successful. If the queue is empty, 'success' will be set to false, and
 * the returned int value is undefined and should not be used.
 *
 * @param q A pointer to the Queue. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this variable will
 *                be set to true if an item was successfully dequeued (queue not empty),
 *                or false if the queue was empty. Must not be NULL.
 * @return int The int item removed from the front of the queue. This value is only
 *             meaningful if '*success' is true upon function return.
 * @pre 'q' must be a valid, non-NULL pointer to a Queue.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @post If successful (queue was not empty), 'size' is decremented, and the 'front'
 *       index is updated (circularly). Capacity remains unchanged.
 */
int queue_dequeue(Queue* q, bool* success);

/**
 * @brief Returns the int item at the front of the queue without removing it.
 *
 * The 'success' output parameter is used to indicate whether the peek operation
 * was successful. If the queue is empty, 'success' will be set to false, and
 * the returned int value is undefined and should not be used.
 *
 * @param q A pointer to a constant Queue. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this variable will
 *                be set to true if an item was successfully peeked (queue not empty),
 *                or false if the queue was empty. Must not be NULL.
 * @return int The int item at the front of the queue. This value is only meaningful
 *             if '*success' is true upon function return.
 * @pre 'q' must be a valid, non-NULL pointer to a Queue.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 */
int queue_peek(const Queue* q, bool* success);

/**
 * @brief Checks if the queue is empty.
 *
 * @param q A pointer to a constant Queue. Must not be NULL.
 * @return bool true if the queue's size is 0, false otherwise.
 * @pre 'q' must be a valid, non-NULL pointer to a Queue.
 */
bool queue_is_empty(const Queue* q);

/**
 * @brief Returns the current number of int elements stored in the queue.
 *
 * @param q A pointer to a constant Queue. Must not be NULL.
 * @return int The number of int elements in the queue.
 * @pre 'q'must be a valid, non-NULL pointer to a Queue.
 */
int queue_size(const Queue* q);

/**
 * @brief Returns the current storage capacity of the queue's underlying array.
 *
 * @param q A pointer to a constant Queue. Must not be NULL.
 * @return int The current capacity of the queue.
 * @pre 'q' must be a valid, non-NULL pointer to a Queue.
 */
int queue_capacity(const Queue* q);

/**
 * @brief Removes all int elements from the queue, effectively making it empty.
 *
 * This operation resets 'front', 'rear', and 'size' to their initial empty state values
 * (typically front=0, rear=0, size=0). It does not change the queue's capacity;
 * the allocated memory is retained for potential future use.
 *
 * @param q A pointer to the Queue. Must not be NULL.
 * @pre 'q' must be a valid, non-NULL pointer to a Queue.
 * @post The queue's 'size' becomes 0. 'front' and 'rear' are reset. Its 'capacity'
 *       remains unchanged.
 */
void queue_clear(Queue* q);

/**
 * @brief Requests that the queue capacity be at least 'new_capacity'.
 *
 * If 'new_capacity' is greater than the current queue capacity, the function
 * attempts to reallocate the internal storage to 'new_capacity'. During this
 * process, the elements in the circular buffer are "unrolled" and copied
 * linearly into the new, larger array, resetting 'front' to 0 and 'rear' to 'size'.
 * If 'new_capacity' is less than or equal to the current capacity, this function
 * typically does nothing and is considered successful, provided 'new_capacity'
 * is not less than the current 'size'.
 *
 * @param q A pointer to the Queue. Must not be NULL.
 * @param new_capacity The desired minimum capacity. Must be non-negative.
 *                     If new_capacity is less than current queue size, the operation will fail
 *                     to prevent data loss (returns false).
 * @return bool true if the capacity is successfully ensured (either by reallocation,
 *              or because it was already sufficient/no change needed as per rules),
 *              or false if 'new_capacity' is negative, less than current size, or if
 *              memory allocation fails.
 * @pre 'q' must be a valid, non-NULL pointer to a Queue.
 * @post If successful and 'new_capacity' was greater than original capacity (and also
 *       greater or equal to current size), the queue's 'capacity' is at least
 *       'new_capacity'. 'front' is set to 0, 'rear' is set to 'size', and elements
 *       are linearly arranged in the new buffer.
 */
bool queue_reserve(Queue* q, int new_capacity);

/**
 * @brief Prints the elements of the queue to standard output.
 *        (Primarily for debugging and testing purposes).
 *
 * Prints from front to rear, respecting circularity.
 * Format: Queue (Front to Rear): [front_val, ..., rear_val] or [empty]
 *
 * @param q A pointer to a constant Queue. Can be NULL.
 */
void queue_print(const Queue* q);

#endif // QUEUE_H