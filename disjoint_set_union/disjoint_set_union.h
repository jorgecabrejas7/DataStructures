/**
 * @file disjoint_set_union.h
 * @brief Defines the interface for a Disjoint Set Union (DSU) data structure,
 *        also known as Union-Find, for 'int' elements (0 to N-1).
 *        This implementation uses Path Compression and Union by Size optimizations.
 *
 * == Clear Definition ==
 * A Disjoint Set Union (DSU) data structure, often called Union-Find, manages a
 * collection of disjoint (non-overlapping) sets. It is typically used to keep
 * track of the connectivity between elements. Each set is identified by a
 * representative element (also called the root or parent) from that set.
 *
 * The 'int' elements managed by this DSU will be in the range [0, N-1], where N
 * is the total number of elements specified at creation time.
 *
 * Key Operations:
 * 1. `make_set(i)`: (Implicitly done at creation) Creates a new set containing only element `i`.
 * 2. `find(i)`: Returns the representative (root) of the set containing element `i`.
 *    This operation often includes Path Compression for optimization.
 * 3. `union_sets(i, j)`: Merges the two sets containing elements `i` and `j` into a
 *    single set. If `i` and `j` are already in the same set, no change occurs.
 *    This operation often includes Union by Size (or Rank) for optimization.
 *
 * == Key Properties and Characteristics ==
 * - Manages 'int' elements, typically treated as IDs from 0 to N-1.
 * - Partitioning: Elements are partitioned into disjoint sets.
 * - Representative: Each set has a unique representative.
 * - Forest of Trees: The sets are often represented as a forest of trees, where
 *   each tree corresponds to a set, and the root of the tree is the representative.
 *   An array `parent[i]` stores the parent of element `i`. If `parent[i] == i`, then
 *   `i` is a root (representative).
 * - Path Compression (Optimization for `find`): During a `find(i)` operation,
 *   after finding the root `r` of `i`, all nodes on the path from `i` to `r` are
 *   made direct children of `r`. This flattens the tree, speeding up future `find`
 *   operations.
 * - Union by Size (Optimization for `union_sets`): When merging two sets, the root of
 *   the smaller tree (in terms of number of nodes/size) is made a child of the root
 *   of the larger tree. This helps keep the trees shallower. An array `size[i]`
 *   stores the size of the set rooted at `i` (only meaningful if `i` is a root).
 *
 * == Common Operations ==
 * - Creation: Initializes the DSU structure for a given number of 'int' elements,
 *   where each element initially forms its own set.
 * - Find: Determines the representative of the set an 'int' element belongs to.
 * - Union: Merges two sets.
 * - Is Connected (or same_set): Checks if two 'int' elements belong to the same set.
 * - Get Number of Sets: Counts the current number of disjoint sets.
 * - Destroy: Frees allocated resources.
 *
 * == Typical Use Cases ==
 * - Kruskal's algorithm for finding Minimum Spanning Trees in a graph.
 * - Detecting cycles in an undirected graph.
 * - Determining connected components in a graph.
 * - Equivalence class problems.
 * - Network connectivity analysis.
 *
 * == Advantages ==
 * - Extremely Fast Operations: With path compression and union by size/rank,
 *   the amortized time complexity for `find` and `union_sets` operations is nearly
 *   constant, specifically O(α(N)), where α(N) is the inverse Ackermann function,
 *   which grows extremely slowly (α(N) < 5 for any practical N).
 * - Simple conceptual model once optimizations are understood.
 *
 * == Disadvantages ==
 * - Does not easily allow for "un-unioning" or splitting sets.
 * - The elements must usually be known beforehand (0 to N-1 mapping). Adding new
 *   elements dynamically after creation is not standard (though extendable).
 * - The internal structure (the trees) can be complex and not easily visualized
 *   or directly useful beyond the set memberships.
 */

#ifndef DISJOINT_SET_UNION_H
#define DISJOINT_SET_UNION_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, free
#include <stdio.h>   // For printf (and NULL)

// Forward declaration
typedef struct DSU DSU;

/**
 * @brief Structure representing the Disjoint Set Union data structure.
 *
 * @param parent An array where `parent[i]` stores the parent of element `i`.
 *               If `parent[i] == i`, then `i` is the representative (root) of its set.
 * @param set_size An array where `set_size[i]` stores the number of elements in the set
 *                 if `i` is a representative (root). Otherwise, its value is not strictly defined
 *                 but often unused for non-root nodes (or can store other info if needed).
 *                 Used for the "Union by Size" optimization.
 * @param num_elements The total number of elements (0 to num_elements-1) managed by the DSU.
 * @param num_sets The current number of disjoint sets.
 */
struct DSU {
    int* parent;
    int* set_size; // Stores the size of the set if the index is a root
    int num_elements;
    int num_sets;
};

// === Function Prototypes ===

/**
 * @brief Creates and initializes a DSU structure for a given number of integer elements.
 *
 * Each element from 0 to `num_elements - 1` will initially be in its own set.
 *
 * @param num_elements The total number of distinct elements to manage. Must be non-negative.
 *                     If 0, a valid DSU for 0 elements is created (though mostly trivial).
 * @return DSU* A pointer to the newly created DSU structure, or NULL if
 *              memory allocation fails or if `num_elements` is negative.
 * @note The caller is responsible for eventually calling dsu_destroy() on the
 *       returned structure.
 */
DSU* dsu_create(int num_elements);

/**
 * @brief Destroys the DSU structure, freeing all associated memory.
 *
 * Deallocates the `parent` and `set_size` arrays, and the DSU structure itself.
 * If `dsu` is NULL, the function performs no operation.
 *
 * @param dsu A pointer to the DSU to be destroyed. Can be NULL.
 * @post All memory associated with `dsu` is freed. `dsu` becomes invalid.
 */
void dsu_destroy(DSU* dsu);

/**
 * @brief Finds the representative (root) of the set containing element `element_id`.
 *
 * Implements Path Compression: During the find operation, all nodes on the path
 * from `element_id` to its root are made direct children of the root.
 *
 * @param dsu A pointer to the DSU. Must not be NULL.
 * @param element_id The integer ID of the element (0 to num_elements-1).
 * @return int The representative (root) of the set containing `element_id`.
 *             Returns -1 if `element_id` is out of bounds or `dsu` is NULL
 *             (though preconditions should prevent NULL dsu).
 * @pre `dsu` must be a valid, non-NULL pointer to a DSU.
 * @pre `element_id` must be in the range [0, dsu->num_elements - 1].
 */
int dsu_find(DSU* dsu, int element_id);

/**
 * @brief Unites the sets containing elements `element_id1` and `element_id2`.
 *
 * Implements Union by Size: The root of the smaller set (by number of elements)
 * is attached to the root of the larger set. If the elements are already in
 * the same set, no operation is performed, and the function returns false.
 * If a union occurs, `num_sets` is decremented.
 *
 * @param dsu A pointer to the DSU. Must not be NULL.
 * @param element_id1 The ID of the first element.
 * @param element_id2 The ID of the second element.
 * @return bool true if a union occurred (i.e., the elements were in different sets),
 *              false if the elements were already in the same set or if either ID
 *              is out of bounds.
 * @pre `dsu` must be a valid, non-NULL pointer to a DSU.
 * @pre `element_id1` and `element_id2` must be in the range [0, dsu->num_elements - 1].
 * @post If a union occurs, the two sets are merged, and `num_sets` is decremented.
 */
bool dsu_union_sets(DSU* dsu, int element_id1, int element_id2);

/**
 * @brief Checks if two elements `element_id1` and `element_id2` are in the same set.
 *
 * This is equivalent to checking if `dsu_find(dsu, element_id1) == dsu_find(dsu, element_id2)`.
 *
 * @param dsu A pointer to the DSU. Must not be NULL.
 * @param element_id1 The ID of the first element.
 * @param element_id2 The ID of the second element.
 * @return bool true if both elements are in the same set, false otherwise (including
 *              if an ID is out of bounds).
 * @pre `dsu` must be a valid, non-NULL pointer to a DSU.
 * @pre `element_id1` and `element_id2` must be in the range [0, dsu->num_elements - 1] for valid check.
 */
bool dsu_are_in_same_set(DSU* dsu, int element_id1, int element_id2);

/**
 * @brief Returns the current number of disjoint sets.
 *
 * @param dsu A pointer to a constant DSU. Must not be NULL.
 * @return int The number of disjoint sets.
 * @pre `dsu` must be a valid, non-NULL pointer to a DSU.
 */
int dsu_get_num_sets(const DSU* dsu);

/**
 * @brief Returns the size of the set that `element_id` belongs to.
 *
 * This involves finding the representative of `element_id` and then returning
 * the stored size for that representative.
 *
 * @param dsu A pointer to the DSU. Must not be NULL.
 * @param element_id The ID of the element.
 * @return int The size of the set containing `element_id`. Returns 0 or -1 if
 *             `element_id` is out of bounds (implementation specific for error). Let's say 0.
 * @pre `dsu` must be a valid, non-NULL pointer to a DSU.
 * @pre `element_id` must be in the range [0, dsu->num_elements - 1].
 */
int dsu_get_set_size(DSU* dsu, int element_id);

/**
 * @brief (Optional helper for testing/debugging) Prints the parent array of the DSU.
 *
 * Format: Parents: [p0, p1, ..., pN-1]
 *
 * @param dsu A pointer to a constant DSU. Can be NULL.
 */
void dsu_print_parents(const DSU* dsu);


#endif // DISJOINT_SET_UNION_H