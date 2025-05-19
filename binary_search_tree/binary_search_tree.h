/**
 * @file binary_search_tree.h
 * @brief Defines the interface for a Binary Search Tree (BST) storing unique integers.
 *
 * == Clear Definition ==
 * A Binary Search Tree is a rooted binary tree data structure whose internal nodes
 * each store an 'int' key. Each node has at most two children, referred to as the
 * left child and the right child. For any given node 'N' in the tree:
 * - All 'int' keys in N's left subtree are less than N's key.
 * - All 'int' keys in N's right subtree are greater than N's key.
 * - Both the left and right subtrees must also be binary search trees.
 * - This implementation stores unique 'int' keys. Duplicate keys are not allowed.
 *
 * The tree structure allows for efficient searching, insertion, and deletion
 * operations, with an average time complexity of O(log N) where N is the
 * number of nodes. However, in the worst-case (e.g., a skewed tree resulting
 * from inserting elements in sorted order), these operations can degrade to O(N).
 *
 * == Key Properties and Characteristics ==
 * - Stores unique 'int' data type exclusively in each node.
 * - Hierarchical Structure: Node-based, with parent-child relationships.
 * - Ordered Property: Keys are ordered in a way that allows for binary search.
 * - Recursive Definition: Both left and right subtrees are themselves BSTs.
 * - No Duplicates: This implementation will not store duplicate integer values.
 *   Attempting to insert a duplicate will typically be a no-op or return failure.
 * - Root: The topmost node of the tree. An empty tree has a NULL root.
 *
 * == Common Operations ==
 * - Insertion: Adds a new unique 'int' key to the tree, maintaining BST properties.
 * - Deletion: Removes an 'int' key from the tree, restructuring as needed to
 *   maintain BST properties. Deletion can be complex, especially for nodes
 *   with two children.
 * - Search (Contains): Efficiently checks if an 'int' key exists in the tree.
 * - Traversal: Visiting all nodes in a specific order:
 *   - In-order: Visits nodes in ascending sorted order of keys.
 *   - Pre-order: Visits the current node before its children.
 *   - Post-order: Visits the current node after its children.
 * - Find Minimum/Maximum: Finds the smallest or largest 'int' key in the tree.
 * - Get Size: Counts the number of nodes (keys) in the tree.
 * - Get Height: Calculates the height (or depth) of the tree.
 * - Create/Destroy: Manages the lifecycle of the tree.
 *
 * == Typical Use Cases ==
 * - Implementing dynamic sets of 'int's that require efficient search, insert, delete.
 * - Used in database indexing.
 * - Symbol tables in compilers.
 * - Sorting (e.g., TreeSort, though not always the most efficient general sort).
 * - As a basis for more advanced self-balancing trees (AVL, Red-Black trees)
 *   that guarantee O(log N) worst-case performance.
 *
 * == Advantages ==
 * - Efficient search, insert, delete: O(log N) on average for 'int' keys.
 * - In-order traversal yields 'int' keys in sorted order.
 * - Dynamic: Can grow and shrink as needed.
 *
 * == Disadvantages ==
 * - Worst-case performance: O(N) for operations if the tree becomes unbalanced
 *   (skewed).
 * - Deletion can be tricky to implement correctly, especially for nodes with two children.
 * - No O(1) random access by index like an array.
 * - Recursive implementations can lead to stack overflow for very deep (skewed) trees.
 */

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, free
#include <stdio.h>   // For NULL and printf in traversal functions

// Forward declarations
typedef struct BSTNode BSTNode;
typedef struct BinarySearchTree BinarySearchTree;

/**
 * @brief Structure representing a single node in the Binary Search Tree.
 *
 * @param data The integer value (key) stored in this node.
 * @param left A pointer to the left child BSTNode, or NULL if no left child.
 *             Stores keys less than this node's data.
 * @param right A pointer to the right child BSTNode, or NULL if no right child.
 *              Stores keys greater than this node's data.
 * @param parent (Optional, but very helpful for deletion and other operations.
 *                Included here for a more robust implementation).
 *                A pointer to the parent BSTNode, or NULL if this is the root.
 */
struct BSTNode {
    int data;
    BSTNode* left;
    BSTNode* right;
    BSTNode* parent; // Optional, but recommended
};

/**
 * @brief Structure representing the Binary Search Tree.
 *
 * @param root A pointer to the root BSTNode of the tree. NULL if the tree is empty.
 * @param size The current number of nodes (and thus unique int elements) in the tree.
 */
struct BinarySearchTree {
    BSTNode* root;
    int size;
};

// === Function Prototypes ===

/**
 * @brief Creates a new, empty binary search tree.
 *
 * Initializes the root pointer to NULL and size to 0.
 *
 * @return BinarySearchTree* A pointer to the newly created BinarySearchTree structure,
 *                           or NULL if memory allocation fails.
 * @note The caller is responsible for eventually calling bst_destroy() on the
 *       returned tree to free its resources.
 */
BinarySearchTree* bst_create();

/**
 * @brief Destroys the binary search tree, freeing all its nodes and the tree structure itself.
 *
 * Uses a post-order traversal to recursively free all nodes.
 * If 'tree' is NULL, the function performs no operation.
 *
 * @param tree A pointer to the BinarySearchTree to be destroyed. Can be NULL.
 * @post All nodes in the tree are freed. The BinarySearchTree structure itself is freed.
 *       The pointer 'tree' becomes invalid and should not be used subsequently.
 */
void bst_destroy(BinarySearchTree* tree);

/**
 * @brief Inserts a unique integer value into the binary search tree.
 *
 * If the value already exists in the tree, the tree remains unchanged, and the
 * function returns false. Otherwise, a new node is created for the value and
 * inserted at the appropriate position to maintain BST properties.
 * The parent pointers of affected nodes should also be updated.
 *
 * @param tree A pointer to the BinarySearchTree. Must not be NULL.
 * @param value The int value to insert.
 * @return bool true if the value was successfully inserted (i.e., it was not
 *              already present and memory allocation for the new node succeeded),
 *              false if the value was already present or if memory allocation failed.
 * @pre 'tree' must be a valid, non-NULL pointer to a BinarySearchTree.
 * @post If successful and value was not present, 'size' is incremented. The new
 *       'value' is added as a new node, maintaining BST properties.
 */
bool bst_insert(BinarySearchTree* tree, int value);

/**
 * @brief Checks if an integer value is present in the binary search tree.
 *
 * @param tree A pointer to a constant BinarySearchTree. Must not be NULL.
 * @param value The int value to search for.
 * @return bool true if the value is found in the tree, false otherwise.
 * @pre 'tree' must be a valid, non-NULL pointer to a BinarySearchTree.
 */
bool bst_contains(const BinarySearchTree* tree, int value);

/**
 * @brief Removes an integer value from the binary search tree if it is present.
 *
 * Handles three cases for the node to be deleted:
 * 1. Node is a leaf (no children).
 * 2. Node has one child.
 * 3. Node has two children (requires finding in-order successor or predecessor).
 * Parent pointers must be correctly updated.
 *
 * @param tree A pointer to the BinarySearchTree. Must not be NULL.
 * @param value The int value to remove.
 * @return bool true if the value was found and successfully removed,
 *              false if the value was not found in the tree.
 * @pre 'tree' must be a valid, non-NULL pointer to a BinarySearchTree.
 * @post If successful, 'size' is decremented. The node containing 'value'
 *       is removed, and its memory freed. BST properties are maintained.
 */
bool bst_remove(BinarySearchTree* tree, int value);

/**
 * @brief Returns the current number of unique integer elements (nodes) in the tree.
 *
 * @param tree A pointer to a constant BinarySearchTree. Must not be NULL.
 * @return int The number of nodes in the tree.
 * @pre 'tree' must be a valid, non-NULL pointer to a BinarySearchTree.
 */
int bst_size(const BinarySearchTree* tree);

/**
 * @brief Checks if the binary search tree is empty.
 *
 * @param tree A pointer to a constant BinarySearchTree. Must not be NULL.
 * @return bool true if the tree's root is NULL (or size is 0), false otherwise.
 * @pre 'tree' must be a valid, non-NULL pointer to a BinarySearchTree.
 */
bool bst_is_empty(const BinarySearchTree* tree);

/**
 * @brief Removes all nodes from the binary search tree, making it empty.
 *
 * This operation frees all BSTNode elements. The root is set to NULL, and size to 0.
 *
 * @param tree A pointer to the BinarySearchTree. Must not be NULL.
 * @pre 'tree' must be a valid, non-NULL pointer to a BinarySearchTree.
 * @post The tree's 'size' becomes 0, and 'root' becomes NULL. All nodes are freed.
 */
void bst_clear(BinarySearchTree* tree);

/**
 * @brief Finds and returns the minimum integer value stored in the tree.
 *
 * The 'success' output parameter indicates if a minimum value was found (i.e., tree not empty).
 *
 * @param tree A pointer to a constant BinarySearchTree. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this will be set to true
 *                if a minimum value was found (tree not empty), or false if the tree was empty.
 *                Must not be NULL.
 * @return int The minimum int value in the tree. Value is meaningful only if '*success' is true.
 * @pre 'tree' must be a valid, non-NULL pointer to a BinarySearchTree.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 */
int bst_find_min(const BinarySearchTree* tree, bool* success);

/**
 * @brief Finds and returns the maximum integer value stored in the tree.
 *
 * The 'success' output parameter indicates if a maximum value was found (i.e., tree not empty).
 *
 * @param tree A pointer to a constant BinarySearchTree. Must not be NULL.
 * @param success A pointer to a boolean variable. On return, this will be set to true
 *                if a maximum value was found (tree not empty), or false if the tree was empty.
 *                Must not be NULL.
 * @return int The maximum int value in the tree. Value is meaningful only if '*success' is true.
 * @pre 'tree' must be a valid, non-NULL pointer to a BinarySearchTree.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 */
int bst_find_max(const BinarySearchTree* tree, bool* success);

/**
 * @brief Calculates the height of the binary search tree.
 *
 * The height of an empty tree is often defined as -1 or 0.
 * The height of a tree with a single node is 0.
 * Height is the length of the longest path from the root to a leaf node.
 * This specification will use: height of empty tree = -1, height of tree with one node = 0.
 *
 * @param tree A pointer to a constant BinarySearchTree. Must not be NULL.
 * @return int The height of the tree.
 * @pre 'tree' must be a valid, non-NULL pointer to a BinarySearchTree.
 */
int bst_height(const BinarySearchTree* tree);

/**
 * @brief Performs an in-order traversal of the BST and calls the provided
 *        visitor function for each node's data.
 * In-order traversal visits nodes in Left-Root-Right order, resulting in
 * processing the data in ascending sorted order.
 *
 * @param tree A pointer to a constant BinarySearchTree. Must not be NULL.
 * @param visitor A function pointer that takes an int (the node's data) and
 *                void* user_data. It's called for each node.
 * @param user_data A pointer to user-defined data that will be passed to each
 *                  call of the visitor function. Can be NULL if not needed.
 * @pre 'tree' must be a valid, non-NULL pointer to a BinarySearchTree.
 * @pre 'visitor' function pointer must not be NULL.
 */
void bst_in_order_traversal(const BinarySearchTree* tree, void (*visitor)(int data, void* user_data), void* user_data);

/**
 * @brief Performs a pre-order traversal of the BST and calls the provided
 *        visitor function for each node's data.
 * Pre-order traversal visits nodes in Root-Left-Right order.
 *
 * @param tree A pointer to a constant BinarySearchTree. Must not be NULL.
 * @param visitor A function pointer that takes an int (the node's data) and
 *                void* user_data. It's called for each node.
 * @param user_data A pointer to user-defined data that will be passed to each
 *                  call of the visitor function. Can be NULL if not needed.
 * @pre 'tree' must be a valid, non-NULL pointer to a BinarySearchTree.
 * @pre 'visitor' function pointer must not be NULL.
 */
void bst_pre_order_traversal(const BinarySearchTree* tree, void (*visitor)(int data, void* user_data), void* user_data);

/**
 * @brief Performs a post-order traversal of the BST and calls the provided
 *        visitor function for each node's data.
 * Post-order traversal visits nodes in Left-Right-Root order. Useful for deletion.
 *
 * @param tree A pointer to a constant BinarySearchTree. Must not be NULL.
 * @param visitor A function pointer that takes an int (the node's data) and
 *                void* user_data. It's called for each node.
 * @param user_data A pointer to user-defined data that will be passed to each
 *                  call of the visitor function. Can be NULL if not needed.
 * @pre 'tree' must be a valid, non-NULL pointer to a BinarySearchTree.
 * @pre 'visitor' function pointer must not be NULL.
 */
void bst_post_order_traversal(const BinarySearchTree* tree, void (*visitor)(int data, void* user_data), void* user_data);


#endif // BINARY_SEARCH_TREE_H