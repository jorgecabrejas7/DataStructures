/**
 * @file singly_linked_list.h
 * @brief Defines the interface for a Singly Linked List storing integers.
 *
 * == Clear Definition ==
 * A Singly Linked List is a linear data structure consisting of a sequence of
 * nodes. Each node stores an 'int' data element and a pointer (or link) to
 * the next node in the sequence. The list is accessed starting from the first
 * node, known as the 'head'. This implementation also maintains a 'tail' pointer
 * for efficient O(1) appends and a 'size' member for O(1) size queries.
 *
 * == Key Properties and Characteristics ==
 * - Stores 'int' data type exclusively in each node.
 * - Linked nodes: Elements are not stored in contiguous memory locations.
 *   Instead, each element (node) contains a pointer to the next element.
 * - Dynamic sizing: The list can grow or shrink dynamically as int elements
 *   are added or removed. Memory for each node is allocated individually.
 * - Sequential access: Elements are accessed sequentially starting from the head.
 *   Random access by index is not efficient (O(N)).
 * - Ordered: The order of elements as they are inserted is preserved.
 * - Head pointer: Points to the first node in the list. If the list is empty,
 *   the head (and tail) pointer is NULL.
 * - Tail pointer: Points to the last node in the list, allowing for O(1)
 *   additions to the end of the list (add_last).
 * - Size: Keeps track of the number of int elements currently in the list.
 *
 * == Common Operations ==
 * - Creation and destruction of the list.
 * - Adding an integer element to the beginning (head) of the list.
 * - Adding an integer element to the end (tail) of the list.
 * - Inserting an integer element at a specific position (index).
 * - Removing an integer element from the beginning (head).
 * - Removing an integer element from the end (tail) - this is O(N) for SLL.
 * - Removing an integer element from a specific position (index).
 * - Accessing (getting) an integer element at a specific position.
 * - Checking if the list contains a specific integer element.
 * - Querying the current number of integer elements (size).
 * - Clearing all integer elements from the list.
 *
 * == Typical Use Cases ==
 * - When the number of integer elements is unknown beforehand and can change frequently.
 * - Situations requiring frequent insertions or deletions of integers, especially at
 *   the beginning of the list (O(1)). Adding to the end is also O(1) with a tail pointer.
 * - Implementing other data structures like Stacks and Queues.
 * - Scenarios where memory for integers should be allocated on-demand.
 *
 * == Advantages ==
 * - Dynamic size: Allocates memory as needed, can grow and shrink easily.
 * - Efficient insertions/deletions at the head: O(1) time complexity.
 * - Efficient insertions at the tail (with a tail pointer): O(1) time complexity.
 * - Memory efficiency: Only allocates memory for the nodes actually in use (plus
 *   pointers), unlike arrays which might have unused reserved capacity.
 *
 * == Disadvantages ==
 * - Slow random access: Accessing an element by index takes O(N) time as it
 *   requires traversing the list from the head.
 * - Extra memory for pointers: Each node requires additional memory to store
 *   the 'next' pointer.
 * - Cache performance: Nodes are typically scattered in memory, which can lead to
 *   poorer cache locality compared to contiguous arrays during traversal.
 * - Deletion from the tail is O(N) because the predecessor of the tail node needs
 *   to be found to update its 'next' pointer and become the new tail.
 */

#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, free
#include <stdio.h>   // For NULL (though stdlib.h usually provides it)

// Forward declarations
typedef struct SLLNode SLLNode;
typedef struct SinglyLinkedList SinglyLinkedList;

/**
 * @brief Structure representing a single node in the Singly Linked List.
 *
 * @param data The integer value stored in this node.
 * @param next A pointer to the next SLLNode in the list, or NULL if this is the
 *             last node.
 */
struct SLLNode {
    int data;
    SLLNode* next;
};

/**
 * @brief Structure representing the Singly Linked List.
 *
 * @param head A pointer to the first SLLNode in the list. NULL if the list is empty.
 * @param tail A pointer to the last SLLNode in the list. NULL if the list is empty.
 *             Maintained for O(1) appends.
 * @param size The current number of SLLNodes (and thus int elements) in the list.
 */
struct SinglyLinkedList {
    SLLNode* head;
    SLLNode* tail;
    int size;
};

// === Function Prototypes ===

/**
 * @brief Creates a new, empty singly linked list.
 *
 * Initializes the head and tail pointers to NULL and size to 0.
 *
 * @return SinglyLinkedList* A pointer to the newly created SinglyLinkedList structure,
 *                           or NULL if memory allocation fails.
 * @note The caller is responsible for eventually calling sll_destroy() on the
 *       returned list to free its resources.
 */
SinglyLinkedList* sll_create();

/**
 * @brief Destroys the singly linked list, freeing all its nodes and the list structure itself.
 *
 * Iterates through the list, freeing each SLLNode. Finally, frees the
 * SinglyLinkedList structure. If 'list' is NULL, the function performs no operation.
 *
 * @param list A pointer to the SinglyLinkedList to be destroyed. Can be NULL.
 * @post All nodes in the list are freed. The SinglyLinkedList structure itself is freed.
 *       The pointer 'list' becomes invalid and should not be used subsequently.
 */
void sll_destroy(SinglyLinkedList* list);

/**
 * @brief Returns the current number of int elements in the list.
 *
 * @param list A pointer to a constant SinglyLinkedList. Must not be NULL.
 * @return int The number of int elements in the list.
 * @pre 'list' must be a valid, non-NULL pointer to a SinglyLinkedList.
 */
int sll_size(const SinglyLinkedList* list);

/**
 * @brief Checks if the list is empty.
 *
 * @param list A pointer to a constant SinglyLinkedList. Must not be NULL.
 * @return bool true if the list contains no int elements (size is 0), false otherwise.
 * @pre 'list' must be a valid, non-NULL pointer to a SinglyLinkedList.
 */
bool sll_is_empty(const SinglyLinkedList* list);

/**
 * @brief Adds an int item to the beginning (head) of the list.
 *
 * Creates a new node with the given 'item' and makes it the new head of the list.
 * Updates tail if the list was previously empty.
 *
 * @param list A pointer to the SinglyLinkedList. Must not be NULL.
 * @param item The int value to be added.
 * @return bool true if the item was successfully added, false if memory allocation
 *              for the new node failed.
 * @pre 'list' must be a valid, non-NULL pointer to a SinglyLinkedList.
 * @post If successful, the list's size is incremented by 1. The new 'item' becomes
 *       the first element. 'head' (and 'tail' if list was empty) pointers are updated.
 */
bool sll_add_first(SinglyLinkedList* list, int item);

/**
 * @brief Adds an int item to the end (tail) of the list.
 *
 * Creates a new node with the given 'item' and appends it to the end of the list.
 * Updates head if the list was previously empty. This operation is O(1) due to
 * the tail pointer.
 *
 * @param list A pointer to the SinglyLinkedList. Must not be NULL.
 * @param item The int value to be added.
 * @return bool true if the item was successfully added, false if memory allocation
 *              for the new node failed.
 * @pre 'list' must be a valid, non-NULL pointer to a SinglyLinkedList.
 * @post If successful, the list's size is incremented by 1. The new 'item' becomes
 *       the last element. 'tail' (and 'head' if list was empty) pointers are updated.
 */
bool sll_add_last(SinglyLinkedList* list, int item);

/**
 * @brief Inserts an int item at the specified zero-based index in the list.
 *
 * If index is 0, it's equivalent to sll_add_first().
 * If index is equal to the current list size, it's equivalent to sll_add_last().
 * Otherwise, the item is inserted before the element currently at 'index'.
 *
 * @param list A pointer to the SinglyLinkedList. Must not be NULL.
 * @param index The zero-based index at which the 'item' should be inserted.
 *              Valid range for 'index' is [0, sll_size(list)].
 * @param item The int value to insert.
 * @return bool true if the item was successfully inserted, false if memory allocation
 *              failed or if 'index' is out of the valid range.
 * @pre 'list' must be a valid, non-NULL pointer to a SinglyLinkedList.
 * @pre 'index' must be in the range [0, sll_size(list)].
 * @post If successful, the list's size is incremented by 1. The 'item' is placed at
 *       the specified 'index'. Pointers ('head', 'tail', 'next' of preceding node)
 *       are updated as necessary.
 */
bool sll_insert_at(SinglyLinkedList* list, int index, int item);

/**
 * @brief Retrieves the int item from the beginning (head) of the list without removing it.
 *
 * The 'success' output parameter indicates if retrieval was possible (i.e., list not empty).
 *
 * @param list A pointer to a constant SinglyLinkedList. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this will be set to true
 *                if an item was retrieved (list not empty), or false if the list was empty.
 *                Must not be NULL.
 * @return int The int item at the head of the list. Value is meaningful only if '*success' is true.
 * @pre 'list' must be a valid, non-NULL pointer to a SinglyLinkedList.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 */
int sll_get_first(const SinglyLinkedList* list, bool* success);

/**
 * @brief Retrieves the int item from the end (tail) of the list without removing it.
 *
 * The 'success' output parameter indicates if retrieval was possible (i.e., list not empty).
 * This operation is O(1) due to the tail pointer.
 *
 * @param list A pointer to a constant SinglyLinkedList. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this will be set to true
 *                if an item was retrieved (list not empty), or false if the list was empty.
 *                Must not be NULL.
 * @return int The int item at the tail of the list. Value is meaningful only if '*success' is true.
 * @pre 'list' must be a valid, non-NULL pointer to a SinglyLinkedList.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 */
int sll_get_last(const SinglyLinkedList* list, bool* success);

/**
 * @brief Retrieves the int item at the specified zero-based index in the list without removing it.
 *
 * The 'success' output parameter indicates if retrieval was possible (i.e., index valid).
 *
 * @param list A pointer to a constant SinglyLinkedList. Must not be NULL.
 * @param index The zero-based index of the int item to retrieve.
 * @param success A pointer to a boolean variable. On return, this will be set to true
 *                if 'index' was valid and the item was retrieved, or false if 'index'
 *                was out of bounds [0, sll_size(list)-1]. Must not be NULL.
 * @return int The int item at the specified 'index'. Value is meaningful only if '*success' is true.
 * @pre 'list' must be a valid, non-NULL pointer to a SinglyLinkedList.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @pre For successful retrieval, 'index' must be in the range [0, sll_size(list) - 1].
 */
int sll_get_at(const SinglyLinkedList* list, int index, bool* success);

/**
 * @brief Removes and returns the int item from the beginning (head) of the list.
 *
 * The 'success' output parameter indicates if an item was successfully removed.
 * Updates head (and tail if list becomes empty).
 *
 * @param list A pointer to the SinglyLinkedList. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this will be set to true
 *                if an item was removed (list not empty), or false if the list was empty.
 *                Must not be NULL.
 * @return int The int item removed from the head. Value is meaningful only if '*success' is true.
 * @pre 'list' must be a valid, non-NULL pointer to a SinglyLinkedList.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @post If successful (list was not empty), the list's size is decremented by 1.
 *       The head pointer is updated to the next node (or NULL if list becomes empty).
 *       If the list becomes empty, the tail pointer is also set to NULL. The removed
 *       node is freed.
 */
int sll_remove_first(SinglyLinkedList* list, bool* success);

/**
 * @brief Removes and returns the int item from the end (tail) of the list.
 *
 * The 'success' output parameter indicates if an item was successfully removed.
 * This operation is O(N) for a singly linked list because it requires traversing
 * to find the node before the tail.
 * Updates tail (and head if list becomes empty or had only one element).
 *
 * @param list A pointer to the SinglyLinkedList. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this will be set to true
 *                if an item was removed (list not empty), or false if the list was empty.
 *                Must not be NULL.
 * @return int The int item removed from the tail. Value is meaningful only if '*success' is true.
 * @pre 'list' must be a valid, non-NULL pointer to a SinglyLinkedList.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @post If successful, the list's size is decremented by 1. The 'tail' pointer is
 *       updated to the new last node (or NULL if list becomes empty). The 'head'
 *       pointer is also updated to NULL if the list becomes empty. The removed node is freed.
 */
int sll_remove_last(SinglyLinkedList* list, bool* success);

/**
 * @brief Removes and returns the int item at the specified zero-based index in the list.
 *
 * The 'success' output parameter indicates if an item was successfully removed.
 * If index is 0, it's equivalent to sll_remove_first().
 * If index is sll_size(list)-1, it's equivalent to sll_remove_last().
 *
 * @param list A pointer to the SinglyLinkedList. Must not be NULL.
 * @param index The zero-based index of the int item to remove.
 * @param success A pointer to a boolean variable. On return, this will be set to true
 *                if 'index' was valid and the item was removed, or false if 'index'
 *                was out of bounds [0, sll_size(list)-1] or list was empty. Must not be NULL.
 * @return int The int item removed from the specified 'index'. Value is meaningful only
 *             if '*success' is true.
 * @pre 'list' must be a valid, non-NULL pointer to a SinglyLinkedList.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @pre For successful removal, 'index' must be in the range [0, sll_size(list) - 1].
 * @post If successful, the list's size is decremented by 1. Pointers ('head', 'tail',
 *       'next' of preceding node) are updated as necessary. The removed node is freed.
 */
int sll_remove_at(SinglyLinkedList* list, int index, bool* success);

/**
 * @brief Checks if the list contains the specified int item.
 *
 * Traverses the list to find if any node holds the 'item'.
 *
 * @param list A pointer to a constant SinglyLinkedList. Must not be NULL.
 * @param item The int value to search for.
 * @return bool true if the item is found in the list, false otherwise.
 * @pre 'list' must be a valid, non-NULL pointer to a SinglyLinkedList.
 */
bool sll_contains(const SinglyLinkedList* list, int item);

/**
 * @brief Removes all int elements (nodes) from the list, making it empty.
 *
 * Iterates through the list, freeing each SLLNode. Sets head and tail to NULL
 * and size to 0.
 *
 * @param list A pointer to the SinglyLinkedList. Must not be NULL.
 * @pre 'list' must be a valid, non-NULL pointer to a SinglyLinkedList.
 * @post The list becomes empty (size is 0, head and tail are NULL). All previously
 *       held nodes are freed.
 */
void sll_clear(SinglyLinkedList* list);

/**
 * @brief Prints the elements of the singly linked list to standard output.
 *        (Primarily for debugging and testing purposes).
 *
 * Format: [element1, element2, ..., elementN] or [empty]
 *
 * @param list A pointer to a constant SinglyLinkedList. Can be NULL.
 */
void sll_print(const SinglyLinkedList* list);


#endif // SINGLY_LINKED_LIST_H