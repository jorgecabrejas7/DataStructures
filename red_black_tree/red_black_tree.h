/*
 * @file red_black_tree.h
 * @brief Defines the interface for a Red-Black Tree storing unique, sorted integers.
 *
 * == Clear Definition ==
 * A Red-Black Tree is a self-balancing Binary Search Tree (BST) where each node
 * has an extra bit for storing a color ("red" or "black"). By constraining the
 * way nodes can be colored on any path from the root to a leaf, Red-Black Trees
 * ensure that no path is more than twice as long as any other, meaning the tree
 * remains approximately balanced. This balance ensures O(log N) worst-case
 * time complexity for search, insertion, and deletion.
 *
 * Red-Black Properties:
 * 1. Every node is either red or black.
 * 2. The root is always black.
 * 3. All leaves (NIL nodes, conceptual null children) are black.
 *    (In many implementations, actual NULL pointers are treated as black NIL leaves).
 * 4. If a node is red, then both its children must be black. (No two red nodes
 *    can be adjacent on a path, though a red node can have a black parent).
 * 5. Every simple path from a given node to any of its descendant NIL leaves
 *    contains the same number of black nodes (this is the "black-height").
 *
 * Insertions and deletions may violate these properties. The tree is then
 * rebalanced and recolored through a series of "fixup" operations, which involve
 * recolorings and rotations (similar to AVL tree rotations).
 *
 * == Key Properties and Characteristics ==
 * - Stores unique 'int' data types, maintained in BST order.
 * - Self-Balancing: Uses color properties and rotations to maintain balance.
 * - Node Colors: Each node is red or black.
 * - BST Properties: Standard BST ordering holds.
 * - Guaranteed Logarithmic Height: The path from root to farthest leaf is no more
 *   than twice the path to the nearest leaf. Height is O(log N).
 *
 * == Common Operations ==
 * - Insertion: Adds a new unique 'int' key (initially colored red), then performs
 *   fixup operations (recoloring, rotations) if RB properties are violated. (O(log N))
 * - Deletion: Removes an 'int' key (more complex than BST deletion due to property
 *   maintenance), then performs fixup operations. (O(log N))
 * - Search (Contains): Same as BST search. (O(log N))
 * - Traversal (In-order, Pre-order, Post-order): Same as BST.
 * - Find Minimum/Maximum: Same as BST. (O(log N))
 * - Get Size.
 * - Create/Destroy.
 *
 * == Typical Use Cases ==
 * - Widely used in system software for associative arrays, symbol tables.
 * - Implementations of `std::map` and `std::set` in C++, `TreeMap` and `TreeSet` in Java.
 * - When O(log N) worst-case is required, and slightly more complex constant factors
 *   for balancing (compared to AVL's stricter balancing) are acceptable for potentially
 *   faster average insert/delete due to fewer rotations.
 *
 * == Advantages ==
 * - Guaranteed O(log N) worst-case time complexity for all major operations.
 * - Generally performs fewer rotations on average for insertions/deletions than AVL trees,
 *   though recolorings are more frequent. This can make insert/delete faster in practice
 *   if rotations are more expensive than recolorings.
 *
 * == Disadvantages ==
 * - More complex to implement than standard BSTs or even AVL trees due to the
 *   number of cases and rules for recoloring and rotations during fixup operations.
 * - The rules and proofs of correctness are non-trivial.
 * - Can be slightly less balanced than AVL trees (height can be up to 2*log(N+1)),
 *   so searches might be marginally slower in some cases, though still O(log N).
 *
 * Node structure will include value, color, left, right, and parent pointers.
 * Parent pointers are almost essential for efficient fixup operations in Red-Black Trees.
 */

#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, free
#include <stdio.h>   // For NULL and printf in traversal functions

// Define node colors
typedef enum { RBT_COLOR_RED, RBT_COLOR_BLACK } RBTColor;

// Forward declarations
typedef struct RBTNode RBTNode;
typedef struct RedBlackTree RedBlackTree;

/**
 * @brief Structure representing a single node in the Red-Black Tree.
 *
 * @param value The integer value (key) stored in this node.
 * @param color The color of the node (RBT_COLOR_RED or RBT_COLOR_BLACK).
 * @param left A pointer to the left child RBTNode.
 * @param right A pointer to the right child RBTNode.
 * @param parent A pointer to the parent RBTNode. Crucial for fixup operations.
 *               The root's parent is NULL. NIL leaf's parent points to actual parent.
 */
struct RBTNode {
    int value;
    RBTColor color;
    RBTNode* left;
    RBTNode* right;
    RBTNode* parent;
};

/**
 * @brief Structure representing the Red-Black Tree.
 *
 * @param root A pointer to the root RBTNode of the tree.
 *             The root is always black. If tree is empty, root is NULL.
 * @param nil A special sentinel NIL node. All leaves (conceptual null children)
 *            point to this single NIL node. The NIL node is always black.
 *            This simplifies boundary conditions in algorithms.
 *            The root's parent can also point to this NIL node.
 * @param size The current number of actual data nodes in the tree (excluding NIL sentinel).
 */
struct RedBlackTree {
    RBTNode* root;
    RBTNode* nil; // Sentinel NIL leaf node (black)
    int size;
};

// === Function Prototypes ===

/**
 * @brief Creates a new, empty Red-Black tree.
 *
 * Initializes the NIL sentinel node and sets the root to point to NIL.
 * Size is initialized to 0.
 *
 * @return RedBlackTree* A pointer to the newly created RedBlackTree structure,
 *                       or NULL if memory allocation fails (e.g., for NIL node).
 * @note The caller is responsible for eventually calling rbt_destroy().
 */
RedBlackTree* rbt_create();

/**
 * @brief Destroys the Red-Black tree, freeing all its nodes (including NIL if managed)
 *        and the tree structure itself.
 *
 * If 'tree' is NULL, no operation is performed.
 *
 * @param tree A pointer to the RedBlackTree to be destroyed. Can be NULL.
 * @post All data nodes and the NIL sentinel are freed. The RedBlackTree structure is freed.
 *       'tree' becomes invalid.
 */
void rbt_destroy(RedBlackTree* tree);

/**
 * @brief Inserts a unique integer value into the Red-Black tree.
 *
 * If the value already exists, the tree remains unchanged (returns false).
 * Otherwise, inserts as a standard BST, colors the new node RED, and then
 * performs `rbt_insert_fixup` to restore Red-Black properties if violated.
 *
 * @param tree A pointer to the RedBlackTree. Must not be NULL.
 * @param value The int value to insert.
 * @return bool true if value was newly inserted, false if value already exists or alloc failed.
 * @pre 'tree' must be a valid, non-NULL pointer.
 * @post If successful and value new, 'size' incremented, value added, R-B properties maintained.
 */
bool rbt_insert(RedBlackTree* tree, int value);

/**
 * @brief Checks if an integer value is present in the Red-Black tree.
 *
 * Performs a standard BST search, ignoring colors.
 *
 * @param tree A pointer to a constant RedBlackTree. Must not be NULL.
 * @param value The int value to search for.
 * @return bool true if value found, false otherwise.
 * @pre 'tree' must be a valid, non-NULL pointer.
 */
bool rbt_contains(const RedBlackTree* tree, int value);

/**
 * @brief Removes an integer value from the Red-Black tree if it is present.
 *
 * This is the most complex operation. It involves standard BST deletion logic,
 * followed by `rbt_delete_fixup` to restore Red-Black properties. The color of
 * the node that replaces the deleted node (or the deleted node itself if it was
 * a leaf) and its position determine the fixup cases.
 *
 * @param tree A pointer to the RedBlackTree. Must not be NULL.
 * @param value The int value to remove.
 * @return bool true if value was found and removed, false if not found.
 * @pre 'tree' must be a valid, non-NULL pointer.
 * @post If successful, 'size' decremented, value removed, R-B properties maintained.
 */
bool rbt_remove(RedBlackTree* tree, int value);

/**
 * @brief Returns the current number of actual data nodes in the Red-Black tree.
 *
 * @param tree A pointer to a constant RedBlackTree. Must not be NULL.
 * @return int The number of data nodes.
 * @pre 'tree' must be a valid, non-NULL pointer.
 */
int rbt_size(const RedBlackTree* tree);

/**
 * @brief Checks if the Red-Black tree is empty (contains no data nodes).
 *
 * @param tree A pointer to a constant RedBlackTree. Must not be NULL.
 * @return bool true if tree's root is the NIL sentinel (or size is 0), false otherwise.
 * @pre 'tree' must be a valid, non-NULL pointer.
 */
bool rbt_is_empty(const RedBlackTree* tree);

/**
 * @brief Performs an in-order traversal and calls visitor for each node's value.
 *
 * @param tree A pointer to a constant RedBlackTree. Must not be NULL.
 * @param visitor Function pointer: void (*visitor)(int value, void* user_data).
 * @param user_data User-defined data passed to visitor.
 * @pre 'tree' and 'visitor' must not be NULL.
 */
void rbt_in_order_traversal(const RedBlackTree* tree, void (*visitor)(int value, void* user_data), void* user_data);

// Other traversals (pre-order, post-order) can be added similarly if needed.

// Helper functions typically static in rbt.c (not part of public API but crucial):
// - rbt_rotate_left(RedBlackTree* tree, RBTNode* x)
// - rbt_rotate_right(RedBlackTree* tree, RBTNode* y)
// - rbt_insert_fixup(RedBlackTree* tree, RBTNode* z)
// - rbt_transplant(RedBlackTree* tree, RBTNode* u, RBTNode* v) // Replaces subtree u with v
// - rbt_delete_fixup(RedBlackTree* tree, RBTNode* x) // x is child that may have extra blackness
// - RBTNode* rbt_minimum(RedBlackTree* tree, RBTNode* x) // Finds minimum node in subtree x


#endif // RED_BLACK_TREE_H