/**
 * @file segment_tree.h
 * @brief Defines the interface for a Segment Tree supporting range sum queries
 *        and point updates on an array of integers.
 *
 * == Clear Definition ==
 * A Segment Tree is a versatile tree-based data structure used for storing information
 * about intervals or segments. It allows for efficient querying of aggregate values
 * over a range (e.g., sum, minimum, maximum) and for updating individual elements
 * of an underlying array.
 *
 * It's typically a (full or complete) binary tree where:
 * - Each Leaf Node: Represents a single element from the original input array of 'int's.
 * - Each Internal Node: Represents an interval (a segment) that is the union of the
 *   intervals of its children. It stores an aggregate value for that interval
 *   (e.g., the sum of all 'int' elements within its range).
 *
 * For a Segment Tree built on an array of N 'int's:
 * - The root represents the entire range [0, N-1].
 * - If a node represents range [L, R], its left child represents [L, (L+R)/2]
 *   and its right child represents [(L+R)/2 + 1, R].
 * - Leaf nodes represent ranges [i, i].
 *
 * This implementation will focus on:
 * 1. Building the Segment Tree from an initial array of 'int's.
 * 2. Performing range sum queries: `query(L, R)` returns sum of elements from index L to R.
 * 3. Performing point updates: `update(index, newValue)` changes the value of an
 *    element at a specific index and propagates this change up the tree.
 *
 * == Key Properties and Characteristics ==
 * - Stores aggregate information (e.g., sum) for 'int' array segments.
 * - Tree Structure: Typically a binary tree, often implemented using an array for
 *   implicit parent-child relationships similar to a heap, though explicit node
 *   structs can also be used. Array implementation is common for fixed-size input.
 *   Let's use an array for the tree nodes.
 * - Recursive Operations: Build, query, and update operations are naturally recursive.
 * - Range Coverage: Each node covers a specific range of the original array.
 * - Overlapping Subproblems: Efficiently answers range queries by combining results
 *   from a small number of tree nodes that cover the query range.
 *
 * == Common Operations ==
 * - Build: Constructs the segment tree from an initial array of 'int's. (O(N))
 * - Query (Range Query): Computes an aggregate value (e.g., sum) over a given range [L,R]. (O(log N))
 * - Update (Point Update): Modifies the value of an element at a specific index in
 *   the original array and updates the corresponding tree nodes. (O(log N))
 * - (Advanced: Range Update with Lazy Propagation - not covered in this basic version)
 * - Create/Destroy.
 *
 * == Typical Use Cases ==
 * - Range Sum Queries (RSQ), Range Minimum/Maximum Queries (RMQ).
 * - Computational geometry problems.
 * - Dynamic programming problems where range queries on intermediate results are needed.
 * - Any scenario requiring fast aggregation over sub-segments of an array with updates.
 *
 * == Advantages ==
 * - Efficient range queries and point updates: O(log N) time complexity.
 * - Versatile: Can be adapted for various aggregate functions (sum, min, max, GCD, etc.).
 * - Can handle range updates with lazy propagation (more advanced).
 *
 * == Disadvantages ==
 * - Space Complexity: Typically O(N) or O(2N) to O(4N) for the tree array,
 *   depending on implementation (e.g., array size for a complete binary tree).
 * - More complex to implement than simpler structures like Fenwick Trees for
 *   basic prefix sum tasks.
 * - The recursive nature can be a bit tricky to get right initially.
 *
 * Implementation Detail:
 * The segment tree itself will be stored in an array. If the original array has N elements,
 * the segment tree array might need up to `2*N` or `4*N` space depending on whether it's
 * a complete binary tree and how indexing is handled (1-based vs 0-based for tree nodes).
 * A common safe upper bound for array size is `4*N` for N leaves.
 * The root of the tree is usually at index 0 or 1 of this array.
 */

#ifndef SEGMENT_TREE_H
#define SEGMENT_TREE_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, free
#include <stdio.h>   // For printf (and NULL)
#include <limits.h>  // For INT_MIN/INT_MAX if doing range min/max

// Forward declaration
typedef struct SegmentTree SegmentTree;

/**
 * @brief Structure representing the Segment Tree.
 *
 * @param tree_array A pointer to the dynamically allocated array storing the segment tree nodes.
 *                   Each node stores the sum of its corresponding range.
 * @param original_array_size The size of the original input array of integers upon which
 *                            this segment tree is built.
 * @param tree_array_capacity The allocated capacity of `tree_array`.
 *                            Typically around 2*N or 4*N where N is original_array_size.
 */
struct SegmentTree {
    int* tree_array;          // Stores sums (or other aggregates)
    int original_array_size;  // Number of elements in the conceptual base array
    int tree_array_capacity;  // Actual allocated size of tree_array
};

// === Function Prototypes ===

/**
 * @brief Creates and builds a Segment Tree from an initial array of integers.
 *
 * The tree will be constructed to support range sum queries.
 *
 * @param input_array A pointer to the array of integers to build the tree from.
 *                    Cannot be NULL if `array_size` > 0.
 * @param array_size The number of elements in `input_array`. Must be non-negative.
 *                   If 0, a valid but empty/trivial segment tree is created.
 * @return SegmentTree* A pointer to the newly created SegmentTree, or NULL if
 *                      `input_array` is NULL (and size > 0), `array_size` is negative,
 *                      or memory allocation fails.
 * @note The caller is responsible for eventually calling segment_tree_destroy().
 */
SegmentTree* segment_tree_build(const int* input_array, int array_size);

/**
 * @brief Destroys the Segment Tree, freeing its internal tree array and the structure itself.
 *
 * If `st` is NULL, no operation is performed.
 *
 * @param st A pointer to the SegmentTree to be destroyed. Can be NULL.
 * @post All memory associated with `st` is freed. `st` becomes invalid.
 */
void segment_tree_destroy(SegmentTree* st);

/**
 * @brief Queries the sum of elements in the original array within the given
 *        0-based range [query_left, query_right].
 *
 * @param st A pointer to a constant SegmentTree. Must not be NULL.
 * @param query_left The 0-based starting index of the query range.
 * @param query_right The 0-based ending index of the query range.
 * @param success Pointer to a boolean that will be set to true if query is valid and successful,
 *                false otherwise (e.g. invalid range, empty tree).
 * @return int The sum of elements in the specified range. Value is meaningful only if *success is true.
 *             If range is invalid or tree is empty, behavior might be to return 0 and set success=false.
 * @pre `st` must be a valid, non-NULL pointer.
 * @pre `0 <= query_left <= query_right < st->original_array_size`.
 * @pre `success` must not be NULL.
 */
int segment_tree_query_range_sum(const SegmentTree* st, int query_left, int query_right, bool* success);

/**
 * @brief Updates the value of an element at a specific 0-based `array_index` in the
 *        original conceptual array to `new_value`.
 *
 * This operation also updates all affected nodes in the Segment Tree to reflect this change.
 *
 * @param st A pointer to the SegmentTree. Must not be NULL.
 * @param array_index The 0-based index in the original array whose value is to be updated.
 * @param new_value The new integer value for the element at `array_index`.
 * @return bool true if the update was successful, false if `array_index` is out of bounds.
 * @pre `st` must be a valid, non-NULL pointer.
 * @pre `0 <= array_index < st->original_array_size`.
 * @post The value at `array_index` in the conceptual array is `new_value`, and the
 *       Segment Tree is updated consistently.
 */
bool segment_tree_update_point(SegmentTree* st, int array_index, int new_value);

/**
 * @brief Gets the size of the original array for which the segment tree was built.
 *
 * @param st A pointer to a constant SegmentTree. Must not be NULL.
 * @return int The size of the original array.
 * @pre `st` must be a valid, non-NULL pointer.
 */
int segment_tree_get_original_size(const SegmentTree* st);

/**
 * @brief (Optional helper for testing/debugging) Prints the internal `tree_array`
 *        up to a reasonable limit or based on actual used part of tree.
 *
 * @param st A pointer to a constant SegmentTree. Can be NULL.
 */
void segment_tree_print_internal_array(const SegmentTree* st);


#endif // SEGMENT_TREE_H