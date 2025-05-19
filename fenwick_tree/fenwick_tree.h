/**
 * @file fenwick_tree.h
 * @brief Defines the interface for a Fenwick Tree (Binary Indexed Tree - BIT)
 *        for storing and querying prefix sums of integers.
 *
 * == Clear Definition ==
 * A Fenwick Tree, also known as a Binary Indexed Tree (BIT), is a data structure
 * that can efficiently update 'int' element values and calculate prefix sums
 * (or other associative and invertible operations like prefix XORs, products)
 * in an array of 'int's.
 *
 * It achieves O(log N) time complexity for both point updates and prefix sum queries,
 * where N is the size of the array (or number of elements). The space complexity is O(N).
 *
 * The structure is "implicit": an array (let's call it `bit_array`) is used, where
 * each index `i` in `bit_array` is responsible for storing the sum of a specific
 * range of elements from the original conceptual array. The mapping of these ranges
 * is determined by the bitwise properties of the index `i`.
 * - `bit_array[i]` stores the sum of elements in the range `[i - (i & -i) + 1, i]`
 *   (using 1-based indexing for the conceptual ranges for easier bit logic understanding,
 *   though the array `bit_array` itself can be 0-indexed or 1-indexed in implementation).
 *   The term `(i & -i)` extracts the least significant set bit of `i`.
 *
 * == Key Properties and Characteristics ==
 * - Stores cumulative sums (or other associative values) of 'int's.
 * - Implicit Tree Structure: The tree relationships are defined by bitwise
 *   operations on indices, not by explicit pointers.
 * - Efficient Updates: Updating an element in the conceptual array requires
 *   updating O(log N) entries in the `bit_array`.
 * - Efficient Prefix Queries: Calculating a prefix sum up to an index requires
 *   accessing O(log N) entries in the `bit_array`.
 * - 1-Based Indexing Convention: The bitwise logic for Fenwick trees is often
 *   explained and implemented most easily using 1-based indexing for the conceptual
 *   array and the `bit_array`. We will adopt this for the operations, though the
 *   underlying C array for `bit_array` will be 0-indexed (e.g., `bit_array[0]` maps
 *   to conceptual index 1).
 *
 * == Common Operations ==
 * - Create: Initializes a Fenwick tree of a given size, typically with all values as 0.
 *   Can also be built from an existing array of 'int's.
 * - Update (add value at index): Adds a `delta` value to the element at a specific
 *   index in the conceptual array. This involves updating all `bit_array` entries
 *   responsible for ranges that include this index.
 * - Query (get prefix sum): Calculates the sum of elements from the beginning
 *   of the conceptual array up to a given index.
 * - Get Value at Index (less common directly, usually built from prefix sums):
 *   `value[i] = prefix_sum[i] - prefix_sum[i-1]`.
 * - Get Range Sum (from index L to R): `range_sum(L,R) = prefix_sum(R) - prefix_sum(L-1)`.
 * - Destroy: Frees allocated resources.
 *
 * == Typical Use Cases ==
 * - Dynamic prefix sum problems where array elements are frequently updated.
 * - Problems requiring cumulative frequency counts.
 * - Can be extended to 2D Fenwick trees for 2D prefix sums/updates.
 * - Competitive programming problems involving range queries and point updates.
 *
 * == Advantages ==
 * - Fast updates and prefix queries: O(log N).
 * - Space efficient: O(N), often just a single array.
 * - Simpler to implement than Segment Trees for basic prefix sum/point update tasks.
 *
 * == Disadvantages ==
 * - Less versatile than Segment Trees: Not as straightforward for general range
 *   queries like range minimum/maximum query (RMQ) or range updates without extensions.
 * - The bitwise logic (`i & -i`, `i += (i & -i)`, `i -= (i & -i)`) can be non-intuitive initially.
 * - Typically uses 1-based indexing conceptually, which requires careful mapping
 *   if the underlying array is 0-indexed.
 *
 * For this implementation:
 * - The Fenwick tree will operate on a conceptual 1-indexed array of size `n`.
 * - The internal `bit_array` will also be of size `n+1` (0-indexed, but `bit_array[0]` unused,
 *   `bit_array[1]` to `bit_array[n]` store the tree data).
 */

#ifndef FENWICK_TREE_H
#define FENWICK_TREE_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, free
#include <stdio.h>   // For printf (and NULL)

// Forward declaration
typedef struct FenwickTree FenwickTree;

/**
 * @brief Structure representing the Fenwick Tree (Binary Indexed Tree).
 *
 * @param bit_array A pointer to the dynamically allocated array that stores the BIT.
 *                  It will be of size `max_val + 1` to support 1-based indexing
 *                  from 1 to `max_val`. `bit_array[0]` is typically unused.
 * @param size The logical size of the Fenwick tree (max index it can handle,
 *             corresponding to the size of the conceptual array it represents).
 */
struct FenwickTree {
    int* bit_array;
    int size; // Maximum index (1-based) the tree can handle
};

// === Function Prototypes ===

/**
 * @brief Creates and initializes a Fenwick Tree of a given logical size.
 *
 * All elements in the conceptual array are initialized to 0.
 * The internal `bit_array` will be allocated to `logical_size + 1` and initialized to zeros.
 *
 * @param logical_size The maximum 1-based index the Fenwick Tree will support.
 *                     This corresponds to the size of the conceptual array.
 *                     Must be non-negative. If 0, a trivial tree is made.
 * @return FenwickTree* A pointer to the newly created FenwickTree, or NULL if
 *                      memory allocation fails or `logical_size` is negative.
 * @note The caller is responsible for eventually calling fenwick_tree_destroy().
 */
FenwickTree* fenwick_tree_create(int logical_size);

/**
 * @brief Destroys the Fenwick Tree, freeing its internal array and the structure itself.
 *
 * If `ft` is NULL, no operation is performed.
 *
 * @param ft A pointer to the FenwickTree to be destroyed. Can be NULL.
 * @post All memory associated with `ft` is freed. `ft` becomes invalid.
 */
void fenwick_tree_destroy(FenwickTree* ft);

/**
 * @brief Adds a `delta` value to the element at the specified 1-based `index`
 *        in the conceptual array represented by the Fenwick Tree.
 *
 * This operation updates all necessary entries in the `bit_array` by traversing
 * upwards in the implicit tree structure.
 *
 * @param ft A pointer to the FenwickTree. Must not be NULL.
 * @param index The 1-based index of the element to update (1 to ft->size).
 * @param delta The integer value to add to the element at `index`.
 * @return bool true if the update was successful, false if `index` is out of bounds
 *              [1, ft->size].
 * @pre `ft` must be a valid, non-NULL pointer.
 * @pre `index` must be in the range [1, ft->size].
 * @post The conceptual element at `index` is incremented by `delta`, and the
 *       Fenwick tree structure is updated to reflect this change.
 */
bool fenwick_tree_update(FenwickTree* ft, int index, int delta);

/**
 * @brief Queries the prefix sum of elements from 1 up to the specified 1-based `index`
 *        in the conceptual array.
 *
 * This operation sums relevant entries in the `bit_array` by traversing
 * downwards (towards index 0) in the implicit tree structure.
 *
 * @param ft A pointer to a constant FenwickTree. Must not be NULL.
 * @param index The 1-based index up to which the prefix sum is required (1 to ft->size).
 *              If index is 0, the sum is 0. If index > ft->size, behavior might be
 *              to sum up to ft->size or return error. Let's specify sum up to ft->size.
 * @return int The prefix sum up to `index`. Returns 0 if `index` is 0 or ft is empty.
 *             If `index` is out of bounds (> ft->size), it effectively queries up to `ft->size`.
 *             If `index` < 0, behavior is undefined, should return 0 or error. Let's say 0.
 * @pre `ft` must be a valid, non-NULL pointer.
 */
int fenwick_tree_query_prefix_sum(const FenwickTree* ft, int index);

/**
 * @brief Queries the sum of elements in a given 1-based range [range_start, range_end].
 *
 * Calculated as `query_prefix_sum(range_end) - query_prefix_sum(range_start - 1)`.
 *
 * @param ft A pointer to a constant FenwickTree. Must not be NULL.
 * @param range_start The 1-based starting index of the range.
 * @param range_end The 1-based ending index of the range.
 * @return int The sum of elements in the specified range. Returns 0 if the range
 *             is invalid (e.g., range_start > range_end, or indices out of bounds
 *             leading to prefix sums that cancel out or are zero).
 * @pre `ft` must be a valid, non-NULL pointer.
 * @pre `1 <= range_start <= range_end <= ft->size` for a typical valid range.
 */
int fenwick_tree_query_range_sum(const FenwickTree* ft, int range_start, int range_end);

/**
 * @brief Gets the current logical size (maximum 1-based index) of the Fenwick tree.
 *
 * @param ft A pointer to a constant FenwickTree. Must not be NULL.
 * @return int The logical size of the tree.
 * @pre `ft` must be a valid, non-NULL pointer.
 */
int fenwick_tree_get_size(const FenwickTree* ft);

/**
 * @brief (Optional helper for testing/debugging) Prints the internal `bit_array`.
 *
 * @param ft A pointer to a constant FenwickTree. Can be NULL.
 */
void fenwick_tree_print_internal_array(const FenwickTree* ft);

#endif // FENWICK_TREE_H