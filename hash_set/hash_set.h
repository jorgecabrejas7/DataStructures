/**
 * @file hash_set.h
 * @brief Defines the interface for a Hash Set storing unique integers,
 *        implemented with chaining using singly linked lists for collision resolution.
 *
 * == Clear Definition ==
 * A Hash Set is a data structure that stores a collection of unique 'int' elements,
 * providing very fast average-time complexity for insertion, deletion, and lookup
 * (checking for presence). It is a specialized form of a Hash Table where only
 * keys (our 'int' values) are stored, and their presence is what matters.
 *
 * This implementation uses:
 * 1. A dynamic array (the "table") where each element is a "bucket".
 * 2. A hash function to map an 'int' value to an index in this array.
 *    A simple hash function for an integer 'value' and a table of 'table_size'
 *    could be 'value % table_size'. Care must be taken with negative numbers to
 *    ensure a non-negative index (e.g., (value % table_size + table_size) % table_size).
 * 3. Chaining with singly linked lists for collision resolution: Each bucket in the
 *    table is a pointer to the head of a singly linked list. If multiple 'int' values
 *    hash to the same bucket index, they are all stored in the linked list at that index.
 *
 * == Key Properties and Characteristics ==
 * - Stores unique 'int' data types exclusively.
 * - Unordered: The set does not maintain any specific order of elements.
 * - Hash Function: Maps 'int' values to bucket indices in the internal array.
 *   The quality of the hash function is crucial for good performance.
 * - Collision Resolution: Chaining is used. Each bucket can hold multiple 'int'
 *   values in a linked list if they hash to the same index.
 * - Dynamic Sizing (Rehashing): The internal array (table) can be resized
 *   (usually doubled) when the number of elements exceeds a certain threshold
 *   relative to the table size (this ratio is called the "load factor").
 *   When resizing, a new table is allocated, and all existing 'int' elements
 *   must be "rehashed" into the new, larger table because their bucket indices
 *   might change with the new table size. A common load factor threshold to
 *   trigger resizing is around 0.7 to 0.75.
 * - Table Size: It's often beneficial for the table size to be a prime number to
 *   help distribute elements more uniformly, especially with simple modulo hash functions.
 *
 * == Common Operations ==
 * - Insertion (add): Adds an 'int' to the set if not already present.
 * - Deletion (remove): Removes an 'int' from the set if present.
 * - Lookup (contains): Checks if an 'int' is present in the set.
 * - Size: Gets the number of unique 'int' elements in the set.
 * - Clear: Removes all elements from the set.
 * - Create/Destroy: Manages the lifecycle.
 *
 * == Typical Use Cases ==
 * - Efficiently checking for the existence of an 'int' in a collection.
 * - Storing and managing collections of unique 'int' items (e.g., unique IDs).
 * - Removing duplicate 'int's from a list.
 * - As a building block for more complex data structures.
 *
 * == Advantages ==
 * - Fast average-case performance: O(1) on average for insertion, deletion, and
 *   lookup, assuming a good hash function and manageable load factor.
 * - Flexible size: Can grow dynamically through rehashing.
 *
 * == Disadvantages ==
 * - Worst-case performance: O(N) for operations if many elements hash to the
 *   same bucket (poor hash function or extreme collisions).
 * - Space overhead: Uses an array for the table and additional memory for linked
 *   list nodes (data + next pointer) in chaining.
 * - Rehashing can be expensive: When the table resizes, all elements must be
 *   re-inserted into the new table, which is an O(N) operation (where N is the
 *   number of elements, plus the size of the old and new tables). However, this
 *   is amortized over many operations.
 * - Performance depends on hash function and load factor management.
 * - Unordered: Does not maintain elements in any sorted sequence.
 */

#ifndef HASH_SET_H
#define HASH_SET_H

#include <stdbool.h> // For bool type
#include <stdlib.h>  // For malloc, realloc, free
#include <stdio.h>   // For NULL and printf in hash_set_print

// Forward declarations
typedef struct HSNode HSNode;
typedef struct HashSet HashSet;

/**
 * @brief Structure representing a node in the singly linked list used for chaining.
 *
 * @param data The integer value stored in this node.
 * @param next A pointer to the next HSNode in the chain, or NULL if this is the
 *             last node in the chain for this bucket.
 */
struct HSNode {
    int data;
    HSNode* next;
};

/**
 * @brief Structure representing the Hash Set.
 *
 * @param table An array of pointers to HSNode. Each element `table[i]` is the
 *              head of a singly linked list for bucket `i`.
 * @param table_capacity The current number of buckets in the hash table (size of the array `table`).
 * @param num_elements The current number of unique int elements stored in the hash set.
 */
struct HashSet {
    HSNode** table;        // Array of HSNode pointers (the buckets)
    int table_capacity;  // Number of buckets in the table
    int num_elements;    // Total number of unique int elements stored
};

// === Function Prototypes ===

/**
 * @brief Creates a new, empty hash set with a specified initial table capacity (number of buckets).
 *
 * A small, non-zero prime number is often a good choice for initial_capacity.
 * If initial_capacity is 0 or less, a default capacity might be used or an error returned
 * (behavior to be defined by implementation, for this spec, let's say it fails for <=0).
 *
 * @param initial_table_capacity The initial number of buckets for the hash table.
 *                               Must be greater than 0.
 * @return HashSet* A pointer to the newly created HashSet structure, or NULL if
 *                  memory allocation fails or if initial_table_capacity is not positive.
 * @note The caller is responsible for eventually calling hash_set_destroy() on the
 *       returned set to free its resources.
 */
HashSet* hash_set_create(int initial_table_capacity);

/**
 * @brief Destroys the hash set, freeing all its nodes, the table array, and the set structure itself.
 *
 * Iterates through each bucket, frees all nodes in its chain, then frees the table array,
 * and finally frees the HashSet structure. If 'set' is NULL, no operation is performed.
 *
 * @param set A pointer to the HashSet to be destroyed. Can be NULL.
 * @post All memory associated with 'set' is freed. The pointer 'set' becomes invalid.
 */
void hash_set_destroy(HashSet* set);

/**
 * @brief Inserts an integer value into the hash set if it's not already present.
 *
 * If the insertion causes the load factor (num_elements / table_capacity) to exceed
 * a predefined threshold (e.g., 0.75), the hash table should be resized (rehashed)
 * to maintain performance. This function should handle that resizing internally.
 *
 * @param set A pointer to the HashSet. Must not be NULL.
 * @param value The int value to insert.
 * @return bool true if the value was successfully inserted (i.e., it was not already
 *              present and memory allocation for a new node succeeded),
 *              false if the value was already present in the set or if memory
 *              allocation failed (either for a new node or during a resize).
 * @pre 'set' must be a valid, non-NULL pointer to a HashSet.
 * @post If successful and value was not present, 'num_elements' is incremented.
 *       The 'value' is added to the appropriate chain. The table might be resized.
 */
bool hash_set_insert(HashSet* set, int value);

/**
 * @brief Checks if an integer value is present in the hash set.
 *
 * @param set A pointer to a constant HashSet. Must not be NULL.
 * @param value The int value to search for.
 * @return bool true if the value is found in the set, false otherwise.
 * @pre 'set' must be a valid, non-NULL pointer to a HashSet.
 */
bool hash_set_contains(const HashSet* set, int value);

/**
 * @brief Removes an integer value from the hash set if it is present.
 *
 * @param set A pointer to the HashSet. Must not be NULL.
 * @param value The int value to remove.
 * @return bool true if the value was found and successfully removed,
 *              false if the value was not found in the set.
 * @pre 'set' must be a valid, non-NULL pointer to a HashSet.
 * @post If successful, 'num_elements' is decremented. The node containing 'value'
 *       is removed from its chain and freed.
 */
bool hash_set_remove(HashSet* set, int value);

/**
 * @brief Returns the current number of unique integer elements stored in the hash set.
 *
 * @param set A pointer to a constant HashSet. Must not be NULL.
 * @return int The number of unique elements in the set.
 * @pre 'set' must be a valid, non-NULL pointer to a HashSet.
 */
int hash_set_size(const HashSet* set);

/**
 * @brief Returns the current capacity of the hash table (number of buckets).
 *
 * @param set A pointer to a constant HashSet. Must not be NULL.
 * @return int The number of buckets in the hash table.
 * @pre 'set' must be a valid, non-NULL pointer to a HashSet.
 */
int hash_set_table_capacity(const HashSet* set);

/**
 * @brief Checks if the hash set is empty.
 *
 * @param set A pointer to a constant HashSet. Must not be NULL.
 * @return bool true if the set contains no elements, false otherwise.
 * @pre 'set' must be a valid, non-NULL pointer to a HashSet.
 */
bool hash_set_is_empty(const HashSet* set);

/**
 * @brief Removes all elements from the hash set, making it empty.
 *
 * This operation frees all HSNode elements in all chains but retains the
 * underlying table array (at its current capacity). num_elements is set to 0.
 *
 * @param set A pointer to the HashSet. Must not be NULL.
 * @pre 'set' must be a valid, non-NULL pointer to a HashSet.
 * @post The set's 'num_elements' becomes 0. All chains are emptied, and their
 *       nodes freed. The 'table_capacity' remains unchanged.
 */
void hash_set_clear(HashSet* set);

/**
 * @brief Resizes the hash table to a new capacity and rehashes all existing elements.
 *
 * This is typically called internally when the load factor is too high, but can
 * also be exposed for manual control if desired (e.g., to pre-allocate or shrink).
 * If `new_table_capacity` is less than the current number of elements, the behavior
 * is undefined or should ideally fail (this spec: fail if new_table_capacity is too small, e.g. 0 or less).
 *
 * @param set A pointer to the HashSet. Must not be NULL.
 * @param new_table_capacity The new number of buckets for the hash table. Must be positive.
 * @return bool true if resizing was successful (or not needed if new_table_capacity
 *              is not substantially different or smaller than current num_elements),
 *              false if memory allocation failed or if new_table_capacity is invalid.
 * @pre 'set' must be a valid, non-NULL pointer to a HashSet.
 * @pre 'new_table_capacity' should be a positive value.
 * @post If successful, the hash set's 'table' points to a new array of buckets of
 *       size 'new_table_capacity'. All original elements are rehashed and inserted
 *       into this new table. The old table is freed. 'table_capacity' is updated.
 */
bool hash_set_resize(HashSet* set, int new_table_capacity);

/**
 * @brief Prints the contents of the hash set to standard output.
 *        (Primarily for debugging and testing purposes).
 *
 * Shows each bucket and the elements in its chain.
 *
 * @param set A pointer to a constant HashSet. Can be NULL.
 */
void hash_set_print(const HashSet* set);


#endif // HASH_SET_H