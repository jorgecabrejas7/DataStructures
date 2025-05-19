/**
 * @file doubly_linked_list.h
 * @brief Defines the interface for a Doubly Linked List storing integers.
 *
 * == Clear Definition ==
 * A Doubly Linked List is a linear data structure consisting of a sequence of
 * nodes. Each node stores an 'int' data element, a pointer (or link) to the
 * next node in the sequence, and a pointer to the previous node in the sequence.
 * This bidirectional linking allows for traversal in both forward and reverse
 * directions. The list is accessed starting from the first node ('head') or
 * last node ('tail'). This implementation maintains both 'head' and 'tail'
 * pointers and a 'size' member for O(1) size queries and efficient additions/
 * deletions at both ends.
 *
 * == Key Properties and Characteristics ==
 * - Stores 'int' data type exclusively in each node.
 * - Bidirectionally linked nodes: Elements are not stored in contiguous memory.
 *   Each node contains a pointer to the next element and a pointer to the
 *   previous element.
 * - Dynamic sizing: The list can grow or shrink dynamically as int elements
 *   are added or removed. Memory for each node is allocated individually.
 * - Sequential access: Elements are typically accessed by traversing from either
 *   the head or the tail. Random access by index is O(N).
 * - Ordered: The order of elements as they are inserted is preserved.
 * - Head pointer: Points to the first node in the list. NULL if empty.
 * - Tail pointer: Points to the last node in the list. NULL if empty.
 * - Size: Keeps track of the number of int elements currently in the list.
 *
 * == Common Operations ==
 * - Creation and destruction of the list.
 * - Adding an integer element to the beginning (head).
 * - Adding an integer element to the end (tail).
 * - Inserting an integer element at a specific position (index) or before/after a given node.
 * - Removing an integer element from the beginning.
 * - Removing an integer element from the end.
 * - Removing an integer element from a specific position or a specific node.
 * - Accessing (getting) an integer element at a specific position.
 * - Traversing the list forwards or backwards.
 * - Querying the current number of integer elements (size).
 * - Clearing all integer elements from the list.
 *
 * == Typical Use Cases ==
 * - When frequent insertions or deletions of integers are needed at various points in the list.
 * - Implementing other data structures like Deques (Double-Ended Queues), or LRU caches.
 * - Scenarios requiring traversal in both directions (e.g., navigating browser history).
 * - Maintaining lists where operations on both ends are common.
 *
 * == Advantages ==
 * - Dynamic size: Allocates memory as needed.
 * - Efficient insertions/deletions: O(1) at both ends (head and tail).
 *   O(1) for insertion/deletion if a pointer to the node is already known.
 * - Bidirectional traversal: Can iterate through elements forwards and backwards easily.
 * - Deletion of a node is simpler if you have a pointer to the node itself, as you
 *   can access its neighbors directly.
 *
 * == Disadvantages ==
 * - Extra memory for pointers: Each node requires two pointers (next and prev),
 *   increasing memory overhead per element compared to singly linked lists or arrays.
 * - Slow random access: Accessing an element by index takes O(N) time.
 * - Cache performance: Nodes are typically scattered in memory, leading to poorer
 *   cache locality compared to arrays.
 * - More complex pointer management during insertion/deletion operations compared to
 *   singly linked lists.
 */

#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, free
#include <stdio.h>   // For NULL (though stdlib.h usually provides it)

// Forward declarations
typedef struct DLLNode DLLNode;
typedef struct DoublyLinkedList DoublyLinkedList;

/**
 * @brief Structure representing a single node in the Doubly Linked List.
 *
 * @param data The integer value stored in this node.
 * @param prev A pointer to the previous DLLNode in the list, or NULL if this is the head.
 * @param next A pointer to the next DLLNode in the list, or NULL if this is the tail.
 */
struct DLLNode {
    int data;
    DLLNode* prev;
    DLLNode* next;
};

/**
 * @brief Structure representing the Doubly Linked List.
 *
 * @param head A pointer to the first DLLNode in the list. NULL if the list is empty.
 * @param tail A pointer to the last DLLNode in the list. NULL if the list is empty.
 * @param size The current number of DLLNodes (and thus int elements) in the list.
 */
struct DoublyLinkedList {
    DLLNode* head;
    DLLNode* tail;
    int size;
};

// === Function Prototypes ===

/**
 * @brief Creates a new, empty doubly linked list.
 *
 * Initializes the head and tail pointers to NULL and size to 0.
 *
 * @return DoublyLinkedList* A pointer to the newly created DoublyLinkedList structure,
 *                           or NULL if memory allocation fails.
 * @note The caller is responsible for eventually calling dll_destroy() on the
 *       returned list to free its resources.
 */
DoublyLinkedList* dll_create();

/**
 * @brief Destroys the doubly linked list, freeing all its nodes and the list structure itself.
 *
 * Iterates through the list, freeing each DLLNode. Finally, frees the
 * DoublyLinkedList structure. If 'list' is NULL, the function performs no operation.
 *
 * @param list A pointer to the DoublyLinkedList to be destroyed. Can be NULL.
 * @post All nodes in the list are freed. The DoublyLinkedList structure itself is freed.
 *       The pointer 'list' becomes invalid and should not be used subsequently.
 */
void dll_destroy(DoublyLinkedList* list);

/**
 * @brief Returns the current number of int elements in the list.
 *
 * @param list A pointer to a constant DoublyLinkedList. Must not be NULL.
 * @return int The number of int elements in the list.
 * @pre 'list' must be a valid, non-NULL pointer to a DoublyLinkedList.
 */
int dll_size(const DoublyLinkedList* list);

/**
 * @brief Checks if the list is empty.
 *
 * @param list A pointer to a constant DoublyLinkedList. Must not be NULL.
 * @return bool true if the list contains no int elements (size is 0), false otherwise.
 * @pre 'list' must be a valid, non-NULL pointer to a DoublyLinkedList.
 */
bool dll_is_empty(const DoublyLinkedList* list);

/**
 * @brief Adds an int item to the beginning (head) of the list.
 *
 * Creates a new node with the given 'item' and makes it the new head of the list.
 * Updates pointers accordingly (new node's next, old head's prev, list's head,
 * and list's tail if list was empty).
 *
 * @param list A pointer to the DoublyLinkedList. Must not be NULL.
 * @param item The int value to be added.
 * @return bool true if the item was successfully added, false if memory allocation
 *              for the new node failed.
 * @pre 'list' must be a valid, non-NULL pointer to a DoublyLinkedList.
 * @post If successful, the list's size is incremented by 1. The new 'item' becomes
 *       the first element. 'head' (and 'tail' if list was empty) pointers are updated.
 */
bool dll_add_first(DoublyLinkedList* list, int item);

/**
 * @brief Adds an int item to the end (tail) of the list.
 *
 * Creates a new node with the given 'item' and appends it to the end of the list.
 * Updates pointers accordingly (new node's prev, old tail's next, list's tail,
 * and list's head if list was empty). This operation is O(1).
 *
 * @param list A pointer to the DoublyLinkedList. Must not be NULL.
 * @param item The int value to be added.
 * @return bool true if the item was successfully added, false if memory allocation
 *              for the new node failed.
 * @pre 'list' must be a valid, non-NULL pointer to a DoublyLinkedList.
 * @post If successful, the list's size is incremented by 1. The new 'item' becomes
 *       the last element. 'tail' (and 'head' if list was empty) pointers are updated.
 */
bool dll_add_last(DoublyLinkedList* list, int item);

/**
 * @brief Inserts an int item at the specified zero-based index in the list.
 *
 * If index is 0, it's equivalent to dll_add_first().
 * If index is equal to the current list size, it's equivalent to dll_add_last().
 * Otherwise, the item is inserted before the element currently at 'index'.
 * Traversal to the insertion point is optimized by starting from head or tail
 * depending on which is closer to the index.
 *
 * @param list A pointer to the DoublyLinkedList. Must not be NULL.
 * @param index The zero-based index at which the 'item' should be inserted.
 *              Valid range for 'index' is [0, dll_size(list)].
 * @param item The int value to insert.
 * @return bool true if the item was successfully inserted, false if memory allocation
 *              failed or if 'index' is out of the valid range.
 * @pre 'list' must be a valid, non-NULL pointer to a DoublyLinkedList.
 * @pre 'index' must be in the range [0, dll_size(list)].
 * @post If successful, the list's size is incremented by 1. The 'item' is placed at
 *       the specified 'index'. Pointers ('head', 'tail', 'next'/'prev' of surrounding
 *       nodes) are updated as necessary.
 */
bool dll_insert_at(DoublyLinkedList* list, int index, int item);

/**
 * @brief Retrieves the int item from the beginning (head) of the list without removing it.
 *
 * The 'success' output parameter indicates if retrieval was possible (i.e., list not empty).
 *
 * @param list A pointer to a constant DoublyLinkedList. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this will be set to true
 *                if an item was retrieved (list not empty), or false if the list was empty.
 *                Must not be NULL.
 * @return int The int item at the head of the list. Value is meaningful only if '*success' is true.
 * @pre 'list' must be a valid, non-NULL pointer to a DoublyLinkedList.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 */
int dll_get_first(const DoublyLinkedList* list, bool* success);

/**
 * @brief Retrieves the int item from the end (tail) of the list without removing it.
 *
 * The 'success' output parameter indicates if retrieval was possible (i.e., list not empty).
 * This operation is O(1).
 *
 * @param list A pointer to a constant DoublyLinkedList. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this will be set to true
 *                if an item was retrieved (list not empty), or false if the list was empty.
 *                Must not be NULL.
 * @return int The int item at the tail of the list. Value is meaningful only if '*success' is true.
 * @pre 'list' must be a valid, non-NULL pointer to a DoublyLinkedList.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 */
int dll_get_last(const DoublyLinkedList* list, bool* success);

/**
 * @brief Retrieves the int item at the specified zero-based index in the list without removing it.
 *
 * The 'success' output parameter indicates if retrieval was possible (i.e., index valid).
 * Traversal to the item is optimized by starting from head or tail depending on
 * which is closer to the index.
 *
 * @param list A pointer to a constant DoublyLinkedList. Must not be NULL.
 * @param index The zero-based index of the int item to retrieve.
 * @param success A pointer to a boolean variable. On return, this will be set to true
 *                if 'index' was valid and the item was retrieved, or false if 'index'
 *                was out of bounds [0, dll_size(list)-1]. Must not be NULL.
 * @return int The int item at the specified 'index'. Value is meaningful only if '*success' is true.
 * @pre 'list' must be a valid, non-NULL pointer to a DoublyLinkedList.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @pre For successful retrieval, 'index' must be in the range [0, dll_size(list) - 1].
 */
int dll_get_at(const DoublyLinkedList* list, int index, bool* success);

/**
 * @brief Removes and returns the int item from the beginning (head) of the list.
 *
 * The 'success' output parameter indicates if an item was successfully removed.
 * Updates head (and tail if list becomes empty or had only one element). This is O(1).
 *
 * @param list A pointer to the DoublyLinkedList. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this will be set to true
 *                if an item was removed (list not empty), or false if the list was empty.
 *                Must not be NULL.
 * @return int The int item removed from the head. Value is meaningful only if '*success' is true.
 * @pre 'list' must be a valid, non-NULL pointer to a DoublyLinkedList.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @post If successful (list was not empty), the list's size is decremented by 1.
 *       The head pointer is updated to the next node (or NULL if list becomes empty).
 *       The new head's 'prev' pointer is set to NULL. If the list becomes empty,
 *       the tail pointer is also set to NULL. The removed node is freed.
 */
int dll_remove_first(DoublyLinkedList* list, bool* success);

/**
 * @brief Removes and returns the int item from the end (tail) of the list.
 *
 * The 'success' output parameter indicates if an item was successfully removed.
 * This operation is O(1).
 *
 * @param list A pointer to the DoublyLinkedList. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this will be set to true
 *                if an item was removed (list not empty), or false if the list was empty.
 *                Must not be NULL.
 * @return int The int item removed from the tail. Value is meaningful only if '*success' is true.
 * @pre 'list' must be a valid, non-NULL pointer to a DoublyLinkedList.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @post If successful, the list's size is decremented by 1. The 'tail' pointer is
 *       updated to the previous node (or NULL if list becomes empty). The new tail's
 *       'next' pointer is set to NULL. If the list becomes empty, the 'head' pointer
 *       is also set to NULL. The removed node is freed.
 */
int dll_remove_last(DoublyLinkedList* list, bool* success);

/**
 * @brief Removes and returns the int item at the specified zero-based index in the list.
 *
 * The 'success' output parameter indicates if an item was successfully removed.
 * If index is 0, it's equivalent to dll_remove_first().
 * If index is dll_size(list)-1, it's equivalent to dll_remove_last().
 * Traversal to the node is optimized.
 *
 * @param list A pointer to the DoublyLinkedList. Must not be NULL.
 * @param index The zero-based index of the int item to remove.
 * @param success A pointer to a boolean variable. On return, this will be set to true
 *                if 'index' was valid and the item was removed, or false if 'index'
 *                was out of bounds [0, dll_size(list)-1] or list was empty. Must not be NULL.
 * @return int The int item removed from the specified 'index'. Value is meaningful only
 *             if '*success' is true.
 * @pre 'list' must be a valid, non-NULL pointer to a DoublyLinkedList.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @pre For successful removal, 'index' must be in the range [0, dll_size(list) - 1].
 * @post If successful, the list's size is decremented by 1. Pointers ('head', 'tail',
 *       'next'/'prev' of surrounding nodes) are updated as necessary. The removed node is freed.
 */
int dll_remove_at(DoublyLinkedList* list, int index, bool* success);

/**
 * @brief Checks if the list contains the specified int item.
 *
 * Traverses the list to find if any node holds the 'item'.
 *
 * @param list A pointer to a constant DoublyLinkedList. Must not be NULL.
 * @param item The int value to search for.
 * @return bool true if the item is found in the list, false otherwise.
 * @pre 'list' must be a valid, non-NULL pointer to a DoublyLinkedList.
 */
bool dll_contains(const DoublyLinkedList* list, int item);

/**
 * @brief Removes all int elements (nodes) from the list, making it empty.
 *
 * Iterates through the list, freeing each DLLNode. Sets head and tail to NULL
 * and size to 0.
 *
 * @param list A pointer to the DoublyLinkedList. Must not be NULL.
 * @pre 'list' must be a valid, non-NULL pointer to a DoublyLinkedList.
 * @post The list becomes empty (size is 0, head and tail are NULL). All previously
 *       held nodes are freed.
 */
void dll_clear(DoublyLinkedList* list);

/**
 * @brief Prints the elements of the doubly linked list to standard output from head to tail.
 *        (Primarily for debugging and testing purposes).
 *
 * Format: List (H->T): [element1, element2, ..., elementN] or [empty]
 *
 * @param list A pointer to a constant DoublyLinkedList. Can be NULL.
 */
void dll_print_forward(const DoublyLinkedList* list);

/**
 * @brief Prints the elements of the doubly linked list to standard output from tail to head.
 *        (Primarily for debugging and testing purposes).
 *
 * Format: List (T->H): [elementN, ..., element2, element1] or [empty]
 *
 * @param list A pointer to a constant DoublyLinkedList. Can be NULL.
 */
void dll_print_backward(const DoublyLinkedList* list);


#endif // DOUBLY_LINKED_LIST_H