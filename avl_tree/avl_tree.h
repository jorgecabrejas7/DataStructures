/**
 * @file avl_tree.h
 * @brief Defines the interface for an AVL Tree (Adelson-Velsky and Landis Tree)
 *        storing unique, sorted integers.
 *
 * == Clear Definition ==
 * An AVL Tree is a self-balancing Binary Search Tree (BST). It maintains its balance
 * by ensuring that for every node, the heights of its left and right subtrees
 * differ by at most one. This difference is called the "balance factor" of the node
 * (Balance Factor = Height(Right Subtree) - Height(Left Subtree)).
 * The balance factor must always be -1, 0, or 1.
 *
 * If an insertion or deletion causes any node's balance factor to become -2 or +2,
 * the tree is rebalanced at that node using "rotations" (single or double rotations)
 * to restore the AVL property. This guarantees that the height of the tree remains
 * O(log N), where N is the number of nodes, thus ensuring O(log N) worst-case
 * time complexity for search, insertion, and deletion operations.
 *
 * == Key Properties and Characteristics ==
 * - Stores unique 'int' data types, maintained in BST order.
 * - Self-Balancing: Strict height balance is maintained.
 * - Balance Factor: Each node effectively has a balance factor of -1, 0, or 1.
 * - Rotations: LL, RR, LR, RL rotations are used to rebalance the tree.
 * - BST Properties: All standard BST properties (left child < parent < right child) hold.
 * - Height Information: Nodes often store their height to efficiently calculate
 *   balance factors.
 *
 * == Common Operations ==
 * - Insertion: Adds a new unique 'int' key, then rebalances up the tree if needed. (O(log N))
 * - Deletion: Removes an 'int' key (similar to BST deletion), then rebalances up the
 *   tree from the parent of the physically removed/replaced node if needed. (O(log N))
 * - Search (Contains): Same as BST search. (O(log N))
 * - Traversal (In-order, Pre-order, Post-order): Same as BST.
 * - Find Minimum/Maximum: Same as BST. (O(log N))
 * - Get Size, Get Height.
 * - Create/Destroy.
 *
 * == Typical Use Cases ==
 * - Applications requiring guaranteed O(log N) performance for search, insert, delete,
 *   and where the strict balance is preferred (e.g., databases, symbol tables where
 *   worst-case performance is critical).
 * - Often used when insertions and deletions are intermingled with searches, and
 *   predictable performance is key.
 *
 * == Advantages ==
 * - Guaranteed O(log N) worst-case time complexity for all major operations.
 * - Conceptually simpler balance condition (height difference) than Red-Black Trees,
 *   though rotations are similar.
 * - Search can be slightly faster on average than Red-Black Trees because AVL trees
 *   are more strictly balanced (tend to be shallower).
 *
 * == Disadvantages ==
 * - More rigid balancing can lead to more rotations during insert/delete operations
 *   compared to Red-Black Trees, making insertions/deletions potentially slower
 *   on average, even if both are O(log N).
 * - Implementation of rotations and rebalancing logic is complex and error-prone.
 * - Each node needs to store height or balance factor, adding a small space overhead.
 *
 * Node structure will include value, left/right children, and height.
 * Parent pointers are optional but can simplify some aspects of rebalancing or deletion.
 * For this interface, let's include height and omit explicit parent pointers in the node,
 * managing parentage through recursion or by passing parent nodes during operations.
 */

#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, free
#include <stdio.h>   // For NULL and printf in traversal functions

// Forward declarations
typedef struct AVLNode AVLNode;
typedef struct AVLTree AVLTree;

/**
 * @brief Structure representing a single node in the AVL Tree.
 *
 * @param value The integer value (key) stored in this node.
 * @param left A pointer to the left child AVLNode, or NULL if no left child.
 * @param right A pointer to the right child AVLNode, or NULL if no right child.
 * @param height The height of the subtree rooted at this node.
 *               Height of a leaf node is 0. Height of NULL is -1.
 */
struct AVLNode {
    int value;
    AVLNode* left;
    AVLNode* right;
    int height;
};

/**
 * @brief Structure representing the AVL Tree.
 *
 * @param root A pointer to the root AVLNode of the tree. NULL if the tree is empty.
 * @param size The current number of nodes (and thus unique int elements) in the tree.
 */
struct AVLTree {
    AVLNode* root;
    int size;
};

// === Function Prototypes ===

/**
 * @brief Creates a new, empty AVL tree.
 *
 * Initializes the root pointer to NULL and size to 0.
 *
 * @return AVLTree* A pointer to the newly created AVLTree structure,
 *                  or NULL if memory allocation fails.
 * @note The caller is responsible for eventually calling avl_tree_destroy().
 */
AVLTree* avl_tree_create();

/**
 * @brief Destroys the AVL tree, freeing all its nodes and the tree structure itself.
 *
 * Uses a post-order traversal to recursively free all nodes.
 * If 'tree' is NULL, no operation is performed.
 *
 * @param tree A pointer to the AVLTree to be destroyed. Can be NULL.
 * @post All nodes are freed. The AVLTree structure is freed. 'tree' becomes invalid.
 */
void avl_tree_destroy(AVLTree* tree);

/**
 * @brief Inserts a unique integer value into the AVL tree.
 *
 * If the value already exists, the tree remains unchanged (returns false).
 * Otherwise, inserts like a standard BST, then updates heights and performs
 * rotations if necessary to restore the AVL property.
 *
 * @param tree A pointer to the AVLTree. Must not be NULL.
 * @param value The int value to insert.
 * @return bool true if value was inserted, false if value already exists or alloc failed.
 * @pre 'tree' must be a valid, non-NULL pointer.
 * @post If successful and value new, 'size' incremented, value added, AVL properties maintained.
 */
bool avl_tree_insert(AVLTree* tree, int value);

/**
 * @brief Checks if an integer value is present in the AVL tree.
 *
 * Performs a standard BST search.
 *
 * @param tree A pointer to a constant AVLTree. Must not be NULL.
 * @param value The int value to search for.
 * @return bool true if value found, false otherwise.
 * @pre 'tree' must be a valid, non-NULL pointer.
 */
bool avl_tree_contains(const AVLTree* tree, int value);

/**
 * @brief Removes an integer value from the AVL tree if it is present.
 *
 * Removes like a standard BST, then updates heights and performs rotations
 * if necessary, moving up from the point of deletion/replacement, to restore
 * the AVL property.
 *
 * @param tree A pointer to the AVLTree. Must not be NULL.
 * @param value The int value to remove.
 * @return bool true if value was found and removed, false if not found.
 * @pre 'tree' must be a valid, non-NULL pointer.
 * @post If successful, 'size' decremented, value removed, AVL properties maintained.
 */
bool avl_tree_remove(AVLTree* tree, int value);

/**
 * @brief Returns the current number of nodes in the AVL tree.
 *
 * @param tree A pointer to a constant AVLTree. Must not be NULL.
 * @return int The number of nodes.
 * @pre 'tree' must be a valid, non-NULL pointer.
 */
int avl_tree_size(const AVLTree* tree);

/**
 * @brief Checks if the AVL tree is empty.
 *
 * @param tree A pointer to a constant AVLTree. Must not be NULL.
 * @return bool true if tree's root is NULL (or size is 0), false otherwise.
 * @pre 'tree' must be a valid, non-NULL pointer.
 */
bool avl_tree_is_empty(const AVLTree* tree);

/**
 * @brief Calculates the height of the AVL tree.
 *        Height of empty tree = -1. Height of tree with one node = 0.
 *
 * @param tree A pointer to a constant AVLTree. Must not be NULL.
 * @return int The height of the tree (derived from root's height).
 * @pre 'tree' must be a valid, non-NULL pointer.
 */
int avl_tree_get_height(const AVLTree* tree); // Note: distinct from internal node height field

/**
 * @brief Performs an in-order traversal and calls visitor for each node's value.
 *
 * @param tree A pointer to a constant AVLTree. Must not be NULL.
 * @param visitor Function pointer: void (*visitor)(int value, void* user_data).
 * @param user_data User-defined data passed to visitor.
 * @pre 'tree' and 'visitor' must not be NULL.
 */
void avl_tree_in_order_traversal(const AVLTree* tree, void (*visitor)(int value, void* user_data), void* user_data);

/**
 * @brief Performs a pre-order traversal and calls visitor for each node's value.
 *
 * @param tree A pointer to a constant AVLTree. Must not be NULL.
 * @param visitor Function pointer: void (*visitor)(int value, void* user_data).
 * @param user_data User-defined data passed to visitor.
 * @pre 'tree' and 'visitor' must not be NULL.
 */
void avl_tree_pre_order_traversal(const AVLTree* tree, void (*visitor)(int value, void* user_data), void* user_data);

/**
 * @brief Performs a post-order traversal and calls visitor for each node's value.
 *
 * @param tree A pointer to a constant AVLTree. Must not be NULL.
 * @param visitor Function pointer: void (*visitor)(int value, void* user_data).
 * @param user_data User-defined data passed to visitor.
 * @pre 'tree' and 'visitor' must not be NULL.
 */
void avl_tree_post_order_traversal(const AVLTree* tree, void (*visitor)(int value, void* user_data), void* user_data);


// Helper functions that might be useful internally but not necessarily public API
// (or could be static in avl_tree.c)
// - int node_height(AVLNode* node);
// - int balance_factor(AVLNode* node);
// - AVLNode* rotate_left(AVLNode* y);
// - AVLNode* rotate_right(AVLNode* x);
// - void update_node_height(AVLNode* node);
// - AVLNode* rebalance(AVLNode* node);
// - AVLNode* insert_recursive_helper(AVLNode* node, int value, bool* inserted_flag, int* tree_size_ptr);
// - AVLNode* remove_recursive_helper(AVLNode* node, int value, bool* removed_flag, int* tree_size_ptr);
// - AVLNode* find_min_node(AVLNode* node);


#endif // AVL_TREE_H