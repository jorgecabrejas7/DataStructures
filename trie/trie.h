/**
 * @file trie.h
 * @brief Defines the interface for a Bitwise Trie (Binary Trie) for storing
 *        non-negative integers and performing bitwise operations.
 *
 * == Clear Definition ==
 * A Trie, also known as a prefix tree, is a tree-like data structure that stores
 * a dynamic set of elements, where the keys are usually sequences (like strings).
 * This implementation is a "Bitwise Trie" or "Binary Trie" specifically designed
 * to store non-negative 'int' values.
 *
 * Each level in the trie corresponds to a bit position in the binary representation
 * of the integers (e.g., from the most significant bit (MSB) down to the least
 * significant bit (LSB)). Each node in the trie can have up to two children,
 * representing the bit '0' and the bit '1' for the current bit position.
 * A path from the root to a certain node or a marked leaf represents an integer.
 *
 * == Key Properties and Characteristics ==
 * - Stores non-negative 'int' data types.
 * - Bitwise Structure: Tree structure is based on the binary representation of integers.
 * - Path Represents Number: A path from the root to a node where `is_end_of_number`
 *   is true (or a leaf node in simpler variants) corresponds to an inserted integer.
 * - Fixed Depth (usually): The maximum depth of the trie is determined by the
 *   number of bits considered for the integers (e.g., 31 or 32 for standard ints).
 * - Nodes typically contain pointers to children (for bit 0 and bit 1) and
 *   potentially a flag to mark the end of a number or store a count.
 *
 * == Common Operations ==
 * - Insertion: Adds a non-negative 'int' to the trie. This involves traversing
 *   the trie bit by bit (e.g., MSB to LSB) and creating nodes if they don't exist.
 * - Search (Contains): Checks if a non-negative 'int' is present in the trie.
 * - Deletion: Removes a non-negative 'int' from the trie. This might involve
 *   removing nodes if they are no longer part of any other number's path and
 *   are not an end_of_number themselves. (Deletion can be complex).
 * - Find Minimum/Maximum XOR Pair: Given a set of numbers, find two numbers
 *   whose XOR sum is maximized or minimized (a common trie application).
 * - Find Number with Max XOR with a Given Value: Given a query integer, find a
 *   number in the trie that produces the maximum XOR value with the query integer.
 *
 * == Typical Use Cases (Bitwise Tries for Integers) ==
 * - Maximizing/Minimizing XOR sums between pairs of integers.
 * - IP routing (though usually for string-like IP addresses, concepts are similar).
 * - Searching for integers with specific bit patterns or prefixes.
 * - Efficiently storing sets of integers where bitwise properties are important.
 *
 * == Advantages ==
 * - Efficient for certain bitwise operations: Search, insert, delete can be O(K)
 *   where K is the number of bits in the integer.
 * - Max/Min XOR queries can be very efficient (O(K)).
 * - Can implicitly store numbers in a way that reveals shared bit prefixes.
 *
 * == Disadvantages ==
 * - Space Complexity: Can be high if numbers are sparse and paths don't overlap much.
 *   Each node stores pointers, and K levels of nodes might be needed.
 * - Typically limited to non-negative integers or requires handling of sign bits.
 * - Deletion can be complex, requiring careful pruning of nodes. For this initial
 *   version, we might simplify deletion or mark nodes as "deleted" rather than
 *   physically removing them to keep it simpler, or focus on insert/search.
 *   Let's include a proper deletion.
 * - Fixed number of bits: Usually designed for integers of a specific bit width.
 *
 * For this implementation:
 * - We will consider a fixed number of bits (e.g., 31 for positive `int`s).
 * - Each node will have two children: `children[0]` for bit 0, `children[1]` for bit 1.
 * - A node can also store a count of how many numbers pass through it or end at it,
 *   which helps in deletion and in problems requiring counts.
 *   For simplicity, we'll use `is_end_of_number` and a `count_pass_through`
 *   (or `subtree_elements_count`). Let's use `count_pass_through` to track how many
 *   numbers have this node in their path, useful for deletion. And `is_end_of_number`
 *   to specifically mark if a number *ends* at this node.
 */

#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, free
#include <stdio.h>   // For NULL

// Define the number of bits to consider for integers.
// For a 32-bit signed int, we might use 31 bits for the magnitude if dealing with non-negatives,
// or 32 if we have a scheme for signs (e.g. MSB for sign).
// Let's use 31 bits, assuming positive integers primarily, MSB first.
#define INT_BITS 31 // Max value approx 2*10^9

// Forward declarations
typedef struct TrieNode TrieNode;
typedef struct Trie Trie;

/**
 * @brief Structure representing a single node in the Bitwise Trie.
 *
 * @param children An array of two pointers to TrieNode, where children[0]
 *                 corresponds to the bit '0' and children[1] to the bit '1'.
 * @param is_end_of_number A flag that is true if a number inserted into the trie
 *                         ends at this node.
 * @param count_pass_through (Optional, but useful for deletion and some queries)
 *                           Number of distinct numbers whose paths pass through or end at this node.
 *                           Incremented when a new path through this node is created.
 *                           Decremented when a path is removed.
 */
struct TrieNode {
    TrieNode* children[2];
    bool is_end_of_number;
    int count_pass_through; // Number of numbers that use this node in their path
};

/**
 * @brief Structure representing the Bitwise Trie.
 *
 * @param root A pointer to the root TrieNode of the trie.
 *             The root itself doesn't correspond to any bit, its children do.
 */
struct Trie {
    TrieNode* root;
};

// === Function Prototypes ===

/**
 * @brief Creates a new, empty bitwise trie.
 *
 * Initializes the root node.
 *
 * @return Trie* A pointer to the newly created Trie structure, or NULL if
 *               memory allocation for the root node fails.
 * @note The caller is responsible for eventually calling trie_destroy() on the
 *       returned trie to free all its resources.
 */
Trie* trie_create();

/**
 * @brief Destroys the bitwise trie, freeing all its nodes and the trie structure itself.
 *
 * Uses a recursive approach (e.g., post-order traversal) to free nodes.
 * If 'trie_ptr' is NULL, the function performs no operation.
 *
 * @param trie_ptr A pointer to the Trie to be destroyed. Can be NULL.
 * @post All nodes in the trie are freed. The Trie structure itself is freed.
 *       The pointer 'trie_ptr' becomes invalid.
 */
void trie_destroy(Trie* trie_ptr);

/**
 * @brief Inserts a non-negative integer value into the bitwise trie.
 *
 * Traverses the trie from MSB to LSB according to the bits of 'value'.
 * Creates nodes as needed. Marks the final node as `is_end_of_number = true`.
 * Updates `count_pass_through` for all nodes in the path.
 * If the value already exists, `is_end_of_number` for the final node is ensured
 * to be true, and `count_pass_through` might not change if no new nodes were created
 * but this specific number was not previously marked as ending.
 * For simplicity in this version: if value exists, no change to counts if already marked as end.
 * If it exists but wasn't marked as an end, mark it and potentially adjust counts.
 * Let's define that inserting an existing number is a no-op that returns false.
 *
 * @param trie_ptr A pointer to the Trie. Must not be NULL.
 * @param value The non-negative int value to insert. Values outside the representable
 *              range (e.g. negative, or too large for INT_BITS) should be handled
 *              (e.g., return false or assert). For now, assume valid non-negative.
 * @return bool true if the value was newly inserted (or if it was inserted and
 *              wasn't previously marked as an end-of-number and now is),
 *              false if the value was already present and marked as an end-of-number,
 *              or if memory allocation failed, or value is invalid (e.g. negative).
 * @pre 'trie_ptr' must be a valid, non-NULL pointer to a Trie.
 * @pre 'value' must be non-negative and fit within INT_BITS.
 * @post If successful and value was new, 'value' is represented in the trie.
 */
bool trie_insert(Trie* trie_ptr, int value);

/**
 * @brief Checks if a non-negative integer value is present in the bitwise trie.
 *
 * Traverses the trie bit by bit. The value is present if a path exists and
 * the final node in that path has `is_end_of_number` set to true.
 *
 * @param trie_ptr A pointer to a constant Trie. Must not be NULL.
 * @param value The non-negative int value to search for.
 * @return bool true if the value is found in the trie and marked as an end of number,
 *              false otherwise or if value is invalid (e.g. negative).
 * @pre 'trie_ptr' must be a valid, non-NULL pointer to a Trie.
 * @pre 'value' must be non-negative.
 */
bool trie_contains(const Trie* trie_ptr, int value);

/**
 * @brief Removes a non-negative integer value from the bitwise trie if it is present.
 *
 * This operation involves:
 * 1. Finding the path for 'value'.
 * 2. If found and `is_end_of_number` is true at the end node, set it to false.
 * 3. Decrement `count_pass_through` for all nodes along the path.
 * 4. If a node's `count_pass_through` becomes 0 (and it's not `is_end_of_number`
 *    for some other shorter number), it can be physically removed from the tree.
 *    This pruning should be done from the leaf upwards along the path.
 *
 * @param trie_ptr A pointer to the Trie. Must not be NULL.
 * @param value The non-negative int value to remove.
 * @return bool true if the value was found, marked as an end-of-number, and successfully
 *              processed for removal (is_end_of_number potentially unset, counts updated,
 *              nodes possibly pruned), false if the value was not found as an
 *              end-of-number or if value is invalid.
 * @pre 'trie_ptr' must be a valid, non-NULL pointer to a Trie.
 * @pre 'value' must be non-negative.
 * @post If successful, the 'value' is no longer marked as an end-of-number in the trie.
 *       Nodes that are no longer part of any number path might be freed.
 */
bool trie_remove(Trie* trie_ptr, int value);

/**
 * @brief (Advanced Query Example) Finds the integer in the trie that has the
 *        maximum XOR value with the given `query_value`.
 *
 * Traverses the trie bit by bit from MSB to LSB. At each bit position of
 * `query_value`, it tries to take the opposite bit path in the trie to maximize
 * the XOR sum. If the opposite bit path doesn't exist, it must take the same
 * bit path.
 *
 * @param trie_ptr A pointer to a constant Trie. Must not be NULL.
 * @param query_value The non-negative integer to XOR with numbers in the trie.
 * @param success A pointer to a boolean variable. On return, set to true if a
 *                number was found in the trie to XOR with (i.e., trie not empty),
 *                false otherwise. Must not be NULL.
 * @return int The integer from the trie that yields the maximum XOR with `query_value`.
 *             Meaningful only if '*success' is true. If trie is empty, behavior is
 *             undefined or returns 0 with success=false.
 * @pre 'trie_ptr' must be a valid, non-NULL pointer to a Trie and not empty for success.
 * @pre 'query_value' must be non-negative.
 * @pre 'success' must be a valid, non-NULL pointer to a bool.
 */
int trie_find_max_xor(const Trie* trie_ptr, int query_value, bool* success);

// It might be useful to have a function to count total distinct numbers in the trie,
// but this can be complex if is_end_of_number is the only indicator without a global size.
// For now, we focus on the core insert/contains/remove/max_xor.

#endif // TRIE_H