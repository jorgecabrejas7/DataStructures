/* Placeholder for rope.h */
/**
 * @file rope.h
 * @brief Defines the interface for a Rope data structure adapted for storing
 *        sequences of integers.
 *
 * == Clear Definition ==
 * A Rope is a tree-based data structure used for efficiently storing and
 * manipulating long sequences, traditionally strings. This adaptation applies
 * the Rope concept to sequences of 'int' values.
 *
 * It is a binary tree where:
 * - Leaf Nodes: Store actual 'int' data, typically in small arrays or "chunks".
 * - Internal Nodes: Represent the concatenation of the sequences in their children.
 *   Each internal node stores a 'weight' or 'length', which is the total count
 *   of 'int' elements in its left subtree. This weight is crucial for efficient
 *   indexing and splitting operations.
 *
 * This version will use a simple binary tree structure (not necessarily self-balancing).
 *
 * == Key Properties and Characteristics ==
 * - Stores sequences of 'int' data types.
 * - Tree-based Concatenation: The overall sequence is formed by the concatenation
 *   of sequences in the leaf nodes, as ordered by an in-order traversal of the tree.
 * - Weight/Length in Internal Nodes: Enables O(log N) indexing if the tree is balanced
 *   (where N is the number of nodes, or total length if leaves are small). For an
 *   unbalanced tree, it can be O(height).
 * - Leaf Chunks: Integers are stored in contiguous blocks (arrays) in the leaf nodes.
 *   The size of these chunks can affect performance.
 *
 * == Common Operations (adapted for int sequences) ==
 * - Create: Creates an empty rope or a rope from an initial array of 'int's.
 * - Destroy: Frees all nodes and data.
 * - Get Length: Returns the total number of 'int's in the rope.
 * - Get Element at Index (Indexing): Retrieves the 'int' at a specific 0-based index.
 * - Concatenate: Joins two ropes to form a new rope.
 * - Split: Divides a rope into two new ropes at a given index.
 * - Insert Sequence: Inserts a sequence of 'int's (or another rope) at a given index.
 * - Delete Subsequence: Deletes a range of 'int's from the rope.
 *
 * For this initial interface, we will focus on:
 * Create, Destroy, Get Length, Get Element at Index, Concatenate, and Split.
 * Insertion/Deletion of subsequences can be built upon split and concatenate.
 *
 * == Typical Use Cases ==
 * - Text editors (for long strings).
 * - Storing and manipulating large genomic sequences.
 * - Any application needing efficient operations on very long dynamic sequences
 *   where insertions/deletions/splits in the middle are common and moving
 *   large contiguous blocks of memory (as in a flat array) is too slow.
 *
 * == Advantages ==
 * - Faster concatenation and splitting than flat arrays (often O(1) or O(log N)
 *   to create a new root, versus O(N) for copying arrays).
 * - Indexing is relatively efficient (O(height)).
 * - Insertions/deletions in the middle can be faster than with flat arrays if
 *   they involve splits and concatenations near the modification point.
 * - Shares substructures (if ropes are immutable or use copy-on-write, leading to
 *   memory savings when versions are created). For our mutable C version, this is less direct.
 *
 * == Disadvantages ==
 * - More complex than simple arrays or linked lists.
 * - Higher overhead per element due to tree structure and pointers, especially if
 *   leaf chunks are very small.
 * - Random access is slower than a flat array (O(height) vs O(1)).
 * - If the tree becomes unbalanced, performance can degrade towards O(N) for
 *   some operations. Self-balancing mechanisms (like in B-trees or AVL trees)
 *   are often used in production Ropes but add significant complexity.
 * - Operations like iterating through all elements sequentially might be slightly
 *   slower due to tree traversal and jumping between leaf chunks.
 *
 * Leaf Node Data: For simplicity, leaf nodes will contain a pointer to a dynamically
 * allocated array of ints and the count of ints in that array.
 */

#ifndef ROPE_H
#define ROPE_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, realloc, free
#include <stdio.h>   // For printf in rope_print (and NULL)

// Max number of ints a leaf node can hold directly.
// This is a design choice. Smaller values mean more tree overhead, larger values
// mean more array-like behavior within leaves.
#define ROPE_LEAF_MAX_INTS 10

// Forward declarations
typedef struct RopeNode RopeNode;

/**
 * @brief Structure representing a node in the Rope.
 *
 * If `is_leaf` is true:
 *   - `data.leaf.elements` points to an array of integers.
 *   - `data.leaf.count` is the number of integers in this leaf's array.
 *   - `weight_or_length` stores `data.leaf.count`.
 *   - `left` and `right` children are NULL.
 * If `is_leaf` is false (internal node):
 *   - `weight_or_length` stores the total number of integers in the left subtree.
 *   - `left` points to the left child RopeNode.
 *   - `right` points to the right child RopeNode.
 *   - `data.leaf.elements` and `data.leaf.count` are unused.
 */
struct RopeNode {
    bool is_leaf;
    int weight_or_length; // If internal: weight of left subtree. If leaf: number of ints in this leaf.
    RopeNode* left;
    RopeNode* right;
    RopeNode* parent; // Optional, but can simplify some operations like rebalancing or complex splits.
                      // For this version, let's include it.

    union {
        struct {
            int* elements; // Array of integers for this leaf
            int count;     // Number of actual integers in this leaf's array
        } leaf;
        // No specific data for internal nodes other than weight and children
    } data;
};

/**
 * @brief Structure representing the Rope itself.
 *        Essentially, it's just a pointer to the root node.
 *        We might also store the total length here for O(1) access,
 *        though it can also be derived from the root if it's an internal node
 *        (root->weight + length(root->right_child)).
 *
 * @param root A pointer to the root RopeNode of the rope. NULL if the rope is empty.
 * @param total_length The total number of integers stored in the rope.
 */
typedef struct {
    RopeNode* root;
    int total_length;
} Rope;


// === Function Prototypes ===

/**
 * @brief Creates a new, empty rope.
 *
 * Initializes the root to NULL and total_length to 0.
 *
 * @return Rope* A pointer to the newly created Rope structure, or NULL if
 *               memory allocation for the Rope structure itself fails.
 * @note The caller is responsible for eventually calling rope_destroy() on the
 *       returned rope.
 */
Rope* rope_create();

/**
 * @brief Creates a new rope from an array of integers.
 *
 * This might involve recursively splitting the array and creating leaf nodes
 * for chunks of it, then internal nodes to combine them.
 * A simple initial implementation might create a single leaf node if the array
 * is small, or a chain/balanced tree of leaves.
 * For this version, let's aim for a simple build that might not be perfectly balanced.
 *
 * @param initial_elements An array of integers to initialize the rope with.
 * @param count The number of integers in `initial_elements`.
 * @return Rope* A pointer to the newly created Rope, or NULL on failure.
 *               If count is 0, an empty rope is returned.
 * @pre `initial_elements` can be NULL if `count` is 0.
 */
Rope* rope_create_from_array(const int* initial_elements, int count);

/**
 * @brief Destroys the rope, freeing all its nodes and any data stored in leaves.
 *
 * Uses a recursive approach (e.g., post-order traversal) to free nodes
 * and leaf data arrays. If 'rope' is NULL, no operation is performed.
 *
 * @param rope A pointer to the Rope to be destroyed. Can be NULL.
 * @post All nodes and leaf data arrays are freed. The Rope structure itself is freed.
 */
void rope_destroy(Rope* rope);

/**
 * @brief Returns the total number of integers stored in the rope.
 *
 * @param rope A pointer to a constant Rope. Must not be NULL.
 * @return int The total length of the sequence of integers.
 * @pre 'rope' must be a valid, non-NULL pointer to a Rope.
 */
int rope_get_length(const Rope* rope);

/**
 * @brief Retrieves the integer at the specified 0-based index in the rope.
 *
 * Traverses the tree using the `weight_or_length` fields in internal nodes to
 * navigate to the correct leaf node and then accesses the integer within that leaf's array.
 *
 * @param rope A pointer to a constant Rope. Must not be NULL.
 * @param index The 0-based index of the integer to retrieve.
 * @param success A pointer to a boolean variable. On return, set to true if the
 *                index was valid and the integer was retrieved, false otherwise.
 *                Must not be NULL.
 * @return int The integer at the specified 'index'. Meaningful only if '*success' is true.
 * @pre 'rope' must be a valid, non-NULL pointer to a Rope.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 * @pre 'index' must be in the range [0, rope_get_length(rope) - 1].
 */
int rope_get_element_at(const Rope* rope, int index, bool* success);

/**
 * @brief Concatenates two ropes, `r1` and `r2`, into a new rope.
 *
 * The original `r1` and `r2` should ideally be preserved if they are to be reused,
 * meaning this function might create new nodes or copy parts.
 * A simple concatenation creates a new root node whose left child is `r1->root`
 * and right child is `r2->root`. The weight of the new root is `rope_get_length(r1)`.
 *
 * For this interface, let's define that `r1` and `r2` are "consumed" or become
 * invalid after this operation, and a new Rope* is returned.
 * (Alternatively, `r1` could be modified to append `r2`, or a completely new
 * rope copying all data could be made. "Consuming" is common for efficiency
 * if the originals are not needed).
 *
 * Let's refine: this function creates a NEW rope. `r1` and `r2` remain valid
 * but their nodes are *not* deep copied, they are reused. The caller must be
 * careful not to destroy `r1` or `r2` if their nodes are now part of the new rope,
 * unless a deep copy mechanism is implemented (which is more complex).
 *
 * Simplest approach for now: Create a new root, making `r1->root` its left child and `r2->root`
 * its right child. The new rope "owns" these subtrees. `r1` and `r2` structs can be
 * considered empty or invalid after this, as their roots are taken.
 * The `Rope` structs `r1` and `r2` themselves should be freed by the caller if dynamically allocated,
 * after their roots have been transferred.
 *
 * @param r1 A pointer to the first Rope. Becomes invalid after this call (its root is used).
 * @param r2 A pointer to the second Rope. Becomes invalid after this call (its root is used).
 * @return Rope* A new Rope representing the concatenation of r1 then r2, or NULL on failure.
 * @pre `r1` and `r2` can be NULL (representing empty ropes).
 * @post A new Rope is returned. The root nodes of `r1` and `r2` become children
 *       of the new rope's root. `r1` and `r2` Rope structs should be considered unusable.
 */
Rope* rope_concatenate(Rope* r1, Rope* r2);

/**
 * @brief Splits the given rope `r` at the specified 0-based index `k`.
 *
 * Produces two new ropes:
 * - `left_rope_ptr`: A pointer to a new Rope containing elements from index 0 to `k-1` of `r`.
 * - `right_rope_ptr`: A pointer to a new Rope containing elements from index `k` to end of `r`.
 *
 * The original rope `r` is modified or effectively consumed by this operation.
 * The nodes of the original rope `r` are reused and rearranged to form the two new ropes.
 * The original `r` Rope struct should be considered unusable and potentially freed by the caller.
 *
 * @param r A pointer to the Rope to be split. Becomes invalid after this call.
 * @param k The 0-based index at which to split. `0 <= k <= rope_get_length(r)`.
 *          If k=0, left_rope is empty, right_rope is `r`.
 *          If k=length, left_rope is `r`, right_rope is empty.
 * @param left_rope_ptr A pointer to a Rope* variable where the new left rope will be stored.
 * @param right_rope_ptr A pointer to a Rope* variable where the new right rope will be stored.
 * @return bool true if the split was successful, false on failure (e.g., memory error, invalid k).
 * @pre `r` must not be NULL (unless its length is 0).
 * @pre `left_rope_ptr` and `right_rope_ptr` must not be NULL.
 * @pre `k` must be a valid split index.
 * @post `*left_rope_ptr` and `*right_rope_ptr` point to new Rope structures.
 *       The original `r` Rope struct is effectively invalid.
 */
bool rope_split(Rope* r, int k, Rope** left_rope_ptr, Rope** right_rope_ptr);

/**
 * @brief (Optional helper for testing/debugging) Prints the structure of the rope
 *        and its contents. This can be a complex function involving recursive traversal.
 *
 * @param rope A pointer to a constant Rope. Can be NULL.
 * @param mode 0 for concise summary, 1 for detailed structure.
 */
void rope_print_debug(const Rope* rope, int mode);


#endif // ROPE_H