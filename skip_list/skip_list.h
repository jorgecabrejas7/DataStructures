/*
 * @file skip_list.h
 * @brief Defines the interface for a Skip List storing unique, sorted integers.
 *
 * == Clear Definition ==
 * A Skip List is a probabilistic data structure that allows for efficient search,
 * insertion, and deletion of elements from an ordered sequence, achieving
 * O(log N) average time complexity, similar to balanced trees (like AVL or
 * Red-Black trees) but often with simpler implementation logic.
 *
 * It consists of multiple levels of sorted linked lists.
 * - Level 0: A standard sorted singly linked list containing all 'int' elements.
 * - Higher Levels (Level 1, Level 2, ...): Each of these is also a sorted linked
 *   list, but acts as an "express lane" by containing a sub-sequence of the elements
 *   from the level below it.
 * - An element present at Level `k` is also present at all levels below `k` (i.e., 0 to `k-1`).
 * - The number of levels an element participates in is determined probabilistically
 *   during insertion (e.g., flipping a coin until tails, or a fixed probability `p`).
 * - A special `header` node (or sentinel) is often used at the beginning of each level
 *   to simplify search and insertion logic.
 *
 * Search starts at the highest level, moving forward as long as the next node's
 * value is less than the target. If the next node is too large or end of list is
 * reached, search drops down one level and continues from the current node.
 *
 * == Key Properties and Characteristics ==
 * - Stores unique 'int' data types, maintained in sorted order.
 * - Probabilistic Balancing: Achieves good performance on average due to the
 *   randomized level assignment for nodes. Not strictly balanced like AVL/RBT.
 * - Multiple Levels of Linked Lists: Forms "express lanes" for faster traversal.
 * - Node Structure: Each node stores an 'int' value and an array of 'forward'
 *   pointers, one for each level the node participates in. The size of this
 *   array corresponds to the node's level.
 * - Max Level: The skip list has a maximum possible level, which can be fixed
 *   or determined based on the expected number of elements (e.g., log_1/p (N)).
 *
 * == Common Operations ==
 * - Insertion: Finds the correct position, determines a random level for the new
 *   node, and links it into all lists up to that level. (O(log N) average)
 * - Deletion: Finds the node and unlinks it from all levels it participates in. (O(log N) average)
 * - Search (Contains): Searches for an 'int' value. (O(log N) average)
 * - Create/Destroy.
 *
 * == Typical Use Cases ==
 * - As an alternative to balanced binary search trees when simpler implementation
 *   is desired, and average-case O(log N) is acceptable.
 * - In databases and concurrent data structures (though concurrency adds complexity).
 * - Implementing ordered sets or maps.
 *
 * == Advantages ==
 * - Simpler insertion/deletion logic (especially rebalancing) compared to complex
 *   rotations in AVL/Red-Black trees.
 * - Good average-case performance: O(log N) for search, insert, delete.
 * - Probabilistic approach can be easier to analyze for average case than some
 *   deterministic balancing schemes.
 *
 * == Disadvantages ==
 * - Worst-case performance can be O(N) if, by chance, the levels are very poorly
 *   distributed (though highly improbable for a reasonable number of elements and
 *   probability `p`).
 * - Space overhead: Nodes store multiple forward pointers (an array of them),
 *   which can be more than the two child pointers in a BST node. Average number
 *   of pointers per node is `1/(1-p)`. For p=0.5, this is 2 pointers on average.
 * - Random number generation adds a small overhead to insertions.
 *
 * For this implementation:
 * - We will use a probability `P_FACTOR` (e.g., 0.5 or 0.25) for determining node levels.
 * - A `MAX_LEVEL` will be defined to cap the height of the skip list.
 */

#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, realloc, free
#include <stdio.h>   // For printf (and NULL)
#include <limits.h>  // For INT_MIN in header node (or other sentinel value)

// Maximum number of levels in the skip list.
// This affects the maximum number of elements that can be efficiently stored.
// log_1/P (N) = MAX_LEVEL. If P=0.5, N = 2^MAX_LEVEL.
// For MAX_LEVEL = 16, N can be up to 2^16 = 65536.
// For MAX_LEVEL = 32, N can be up to 2^32.
// Let's choose a reasonable default for typical int ranges.
#define SKIP_LIST_MAX_LEVEL 16
#define P_FACTOR 0.5 // Probability of a node increasing its level

// Forward declarations
typedef struct SLNode SLNode;
typedef struct SkipList SkipList;

/**
 * @brief Structure representing a node in the Skip List.
 *
 * @param value The integer value stored in this node.
 * @param forward An array of pointers to the next SLNode at each level.
 *                `forward[i]` points to the next node at level `i`.
 *                The size of this array is `level + 1` (for levels 0 to `level`).
 *                Dynamically allocated based on the node's randomly determined level.
 * @param level The highest level this node participates in (0-indexed).
 *              A node with level `k` has `k+1` forward pointers (forward[0] to forward[k]).
 */
struct SLNode {
    int value;
    SLNode** forward; // Array of forward pointers
    int level;        // Highest level this node reaches (0 to MAX_LEVEL-1)
};

/**
 * @brief Structure representing the Skip List.
 *
 * @param header A pointer to a special header (or sentinel) node.
 *               The header node typically has a value smaller than any possible
 *               element (e.g., INT_MIN) and has forward pointers at all MAX_LEVEL levels,
 *               initially pointing to NULL (or a tail sentinel if used).
 *               This simplifies search and insertion logic.
 * @param current_max_level The current highest level actually in use by any node
 *                          in the skip list (0 to MAX_LEVEL-1).
 * @param size The number of actual data elements in the skip list (excluding header).
 */
struct SkipList {
    SLNode* header;
    int current_max_level; // Highest level currently active in the list
    int size;              // Number of elements
};

// === Function Prototypes ===

/**
 * @brief Creates a new, empty skip list.
 *
 * Initializes the header node and sets the current max level to 0.
 *
 * @return SkipList* A pointer to the newly created SkipList structure, or NULL if
 *                   memory allocation fails.
 * @note The caller is responsible for eventually calling skip_list_destroy().
 */
SkipList* skip_list_create();

/**
 * @brief Destroys the skip list, freeing all its nodes (including the header)
 *        and the skip list structure itself.
 *
 * If `sl` is NULL, no operation is performed.
 *
 * @param sl A pointer to the SkipList to be destroyed. Can be NULL.
 * @post All memory associated with `sl` is freed. `sl` becomes invalid.
 */
void skip_list_destroy(SkipList* sl);

/**
 * @brief Inserts a unique integer value into the skip list.
 *
 * If the value already exists, the list remains unchanged, and the function returns false.
 * Otherwise, a new node is created. Its level is determined probabilistically.
 * The node is then inserted into the appropriate positions at all its levels.
 * Updates `current_max_level` if the new node's level exceeds it.
 *
 * @param sl A pointer to the SkipList. Must not be NULL.
 * @param value The int value to insert.
 * @return bool true if the value was successfully inserted (i.e., it was not
 *              already present and memory allocation succeeded),
 *              false if the value was already present or if memory allocation failed.
 * @pre `sl` must be a valid, non-NULL pointer.
 * @post If successful and value was new, 'size' is incremented. The 'value' is
 *       added, maintaining sorted order at all levels. `current_max_level` may be updated.
 */
bool skip_list_insert(SkipList* sl, int value);

/**
 * @brief Checks if an integer value is present in the skip list.
 *
 * Searches from the highest current level downwards.
 *
 * @param sl A pointer to a constant SkipList. Must not be NULL.
 * @param value The int value to search for.
 * @return bool true if the value is found in the skip list, false otherwise.
 * @pre `sl` must be a valid, non-NULL pointer.
 */
bool skip_list_contains(const SkipList* sl, int value);

/**
 * @brief Removes an integer value from the skip list if it is present.
 *
 * Finds the node containing the value and unlinks it from all levels it
 * participates in. Adjusts `current_max_level` if necessary (if the removed
 * node was the only one at the highest level).
 *
 * @param sl A pointer to the SkipList. Must not be NULL.
 * @param value The int value to remove.
 * @return bool true if the value was found and successfully removed,
 *              false if the value was not found.
 * @pre `sl` must be a valid, non-NULL pointer.
 * @post If successful, 'size' is decremented. The node containing 'value'
 *       is removed and freed. `current_max_level` may be updated.
 */
bool skip_list_remove(SkipList* sl, int value);

/**
 * @brief Returns the current number of unique integer elements stored in the skip list.
 *
 * @param sl A pointer to a constant SkipList. Must not be NULL.
 * @return int The number of elements in the skip list.
 * @pre `sl` must be a valid, non-NULL pointer.
 */
int skip_list_size(const SkipList* sl);

/**
 * @brief Checks if the skip list is empty.
 *
 * @param sl A pointer to a constant SkipList. Must not be NULL.
 * @return bool true if the skip list's size is 0, false otherwise.
 * @pre `sl` must be a valid, non-NULL pointer.
 */
bool skip_list_is_empty(const SkipList* sl);

/**
 * @brief (Optional helper for testing/debugging) Prints the skip list level by level.
 *
 * For each level, prints the sequence of values in that level's linked list.
 *
 * @param sl A pointer to a constant SkipList. Can be NULL.
 */
void skip_list_print(const SkipList* sl);


#endif // SKIP_LIST_H