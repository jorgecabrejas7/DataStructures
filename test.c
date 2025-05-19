#include <stdio.h>
#include <stdlib.h> // For srand, malloc, free
#include <stdbool.h>
#include <string.h> // For memcmp, etc.
#include <time.h>   // For srand
#include <limits.h> // For INT_MIN, INT_MAX (used in some tests/DS)


// Include all data structure headers
#include "vector/vector.h"
#include "singly_linked_list/singly_linked_list.h"
#include "stack/stack.h"
#include "queue/queue.h"
#include "doubly_linked_list/doubly_linked_list.h"
#include "hash_set/hash_set.h"
#include "binary_search_tree/binary_search_tree.h"
#include "rope/rope.h"
#include "deque/deque.h"
#include "binary_heap/binary_heap.h"
#include "disjoint_set_union/disjoint_set_union.h"
#include "trie/trie.h"
#include "graph_adj_list/graph_adj_list.h"
#include "graph_adj_matrix/graph_adj_matrix.h"
#include "fenwick_tree/fenwick_tree.h"
#include "segment_tree/segment_tree.h"
#include "skip_list/skip_list.h"
#include "avl_tree/avl_tree.h"
#include "red_black_tree/red_black_tree.h"

// --- Forward declarations of all test functions ---
void test_vector();
void test_singly_linked_list();
void test_stack();
void test_queue();
void test_doubly_linked_list();
void test_hash_set();
void test_binary_search_tree();
void test_rope();
void test_deque();
void test_binary_heap();
void test_disjoint_set_union();
void test_trie();
void test_graph_adj_list();
void test_graph_adj_matrix();
void test_fenwick_tree();
void test_segment_tree();
void test_skip_list();
void test_avl_tree();
void test_red_black_tree();


// --- Visitor Data Structs and Functions (consolidated and guarded) ---

#ifndef TREE_VISIT_DATA_DEFINED // For BST, AVL, RBT traversals
#define TREE_VISIT_DATA_DEFINED
typedef struct {
    int count;
    int visited_order[100]; 
    bool first_print;
} TreeVisitData; 

void tree_node_visit_printer(int value, void* user_data) { // Generic name
    TreeVisitData* data = (TreeVisitData*)user_data;
    if (data->first_print) {
        data->first_print = false;
    } else {
        printf(", ");
    }
    printf("%d", value);
    if (data->count < 100) {
        data->visited_order[data->count] = value;
    }
    data->count++;
}
#endif

#ifndef GRAPH_VISIT_DATA_DEFINED // For Graph traversals
#define GRAPH_VISIT_DATA_DEFINED
typedef struct {
    int count;
    int visited_order[100]; 
} GraphVisitData;

void graph_node_visit_printer(int vertex_id, void* user_data) { // Generic name
    GraphVisitData* data = (GraphVisitData*)user_data;
    if (data->count > 0) {
        printf(", ");
    }
    printf("%d", vertex_id);
    if (data->count < 100) {
        data->visited_order[data->count] = vertex_id;
    }
    data->count++;
}
#endif


// --- Test Function Implementations ---

// Helper function to print vector status and elements for easy verification
void print_vector_status(const Vector* vec, const char* label) {
    if (!label) label = "Current Vector Status";
    printf("\n--- %s ---\n", label);
    if (!vec) {
        printf("Vector is NULL.\n");
        return;
    }
    printf("Size:     %d\n", vector_size(vec));
    printf("Capacity: %d\n", vector_capacity(vec));
    printf("Is Empty: %s\n", vector_is_empty(vec) ? "Yes" : "No");
    printf("Elements: [");
    bool success_get;
    for (int i = 0; i < vector_size(vec); ++i) {
        int item = vector_get_item(vec, i, &success_get);
        if (success_get) {
            printf("%d", item);
        } else {
            printf("ERR_GET_ITEM_AT_%d", i);
        }
        if (i < vector_size(vec) - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    printf("---------------\n");
}
void test_vector() {
    printf("===== Starting Vector Test Suite =====\n");
    Vector* my_vec = NULL;
    bool success_op; 
    int item_val;   
    printf("\n[Test 1: Creation]\n");
    my_vec = vector_create(4); 
    if (my_vec) {
        printf("vector_create(4) successful.\n");
    } else {
        printf("vector_create(4) FAILED. Aborting tests.\n");
        return;
    }
    print_vector_status(my_vec, "After creation with capacity 4");
    Vector* zero_cap_vec = vector_create(0);
    if (zero_cap_vec) {
        printf("vector_create(0) successful.\n");
        print_vector_status(zero_cap_vec, "Vector with 0 initial capacity");
        vector_destroy(zero_cap_vec); 
    } else {
        printf("vector_create(0) FAILED.\n");
    }
    Vector* neg_cap_vec = vector_create(-1);
    if (neg_cap_vec == NULL) {
        printf("vector_create(-1) correctly returned NULL.\n");
    } else {
        printf("vector_create(-1) FAILED to return NULL.\n");
        vector_destroy(neg_cap_vec);
    }
    printf("\n[Test 2: Push Back (no resize)]\n");
    success_op = vector_push_back(my_vec, 10); printf("Pushed 10: %s\n", success_op ? "OK" : "Fail");
    success_op = vector_push_back(my_vec, 20); printf("Pushed 20: %s\n", success_op ? "OK" : "Fail");
    success_op = vector_push_back(my_vec, 30); printf("Pushed 30: %s\n", success_op ? "OK" : "Fail");
    print_vector_status(my_vec, "After pushing 10, 20, 30");
    printf("\n[Test 3: Push Back (with resize)]\n");
    success_op = vector_push_back(my_vec, 40); 
    printf("Pushed 40 (at capacity): %s\n", success_op ? "OK" : "Fail");
    print_vector_status(my_vec, "After pushing 40 (size should be 4, cap 4)");
    success_op = vector_push_back(my_vec, 50); 
    printf("Pushed 50 (triggers resize): %s\n", success_op ? "OK" : "Fail");
    print_vector_status(my_vec, "After pushing 50 (resized)");
    printf("\n[Test 4: Get Item]\n");
    item_val = vector_get_item(my_vec, 1, &success_op);
    if (success_op) printf("Item at index 1: %d (Expected 20)\n", item_val);
    else printf("Failed to get item at index 1.\n");
    item_val = vector_get_item(my_vec, vector_size(my_vec) -1, &success_op); 
    if (success_op) printf("Last item (index %d): %d (Expected 50)\n", vector_size(my_vec)-1, item_val);
    else printf("Failed to get last item.\n");
    item_val = vector_get_item(my_vec, 10, &success_op); 
    if (!success_op) printf("Correctly failed to get item at out-of-bounds index 10.\n");
    else printf("ERROR: Incorrectly got item %d at index 10.\n", item_val);
    printf("\n[Test 5: Set Item]\n");
    success_op = vector_set_item(my_vec, 0, 100); 
    if (success_op) printf("Set item at index 0 to 100: OK\n");
    else printf("Set item at index 0 FAILED.\n");
    print_vector_status(my_vec, "After setting item at index 0 to 100");
    success_op = vector_set_item(my_vec, 10, 999); 
    if (!success_op) printf("Correctly failed to set item at out-of-bounds index 10.\n");
    else printf("ERROR: Incorrectly set item at index 10.\n");
    printf("\n[Test 6: Insert Item]\n");
    success_op = vector_insert_item(my_vec, 2, 250); 
    if (success_op) printf("Inserted 250 at index 2: OK\n");
    else printf("Insert 250 at index 2 FAILED.\n");
    print_vector_status(my_vec, "After inserting 250 at index 2");
    success_op = vector_insert_item(my_vec, 0, 5); 
    if (success_op) printf("Inserted 5 at index 0: OK\n");
    else printf("Insert 5 at index 0 FAILED.\n");
    print_vector_status(my_vec, "After inserting 5 at index 0");
    int current_size_vec = vector_size(my_vec); // Renamed
    success_op = vector_insert_item(my_vec, current_size_vec, 600); 
    if (success_op) printf("Inserted 600 at index %d (end): OK\n", current_size_vec);
    else printf("Insert 600 at end FAILED.\n");
    print_vector_status(my_vec, "After inserting 600 at end");
    success_op = vector_insert_item(my_vec, vector_size(my_vec) + 1, 999); 
    if (!success_op) printf("Correctly failed to insert at out-of-bounds index.\n");
    else printf("ERROR: Incorrectly inserted at out-of-bounds index.\n");
    printf("\n[Test 7: Pop Back]\n");
    item_val = vector_pop_back(my_vec, &success_op);
    if (success_op) printf("Popped item: %d (Expected 600)\n", item_val);
    else printf("Pop_back FAILED.\n");
    print_vector_status(my_vec, "After one pop_back");
    printf("\n[Test 8: Remove Item]\n");
    success_op = vector_remove_item(my_vec, 1); 
    if (success_op) printf("Removed item at index 1 (value 100): OK\n");
    else printf("Remove item at index 1 FAILED.\n");
    print_vector_status(my_vec, "After removing item at index 1");
    success_op = vector_remove_item(my_vec, 0); 
    if (success_op) printf("Removed item at index 0 (value 5): OK\n");
    else printf("Remove item at index 0 FAILED.\n");
    print_vector_status(my_vec, "After removing item at index 0");
    success_op = vector_remove_item(my_vec, vector_size(my_vec) - 1); 
    if (success_op) printf("Removed item at last index (value 50): OK\n");
    else printf("Remove item at last index FAILED.\n");
    print_vector_status(my_vec, "After removing last item");
    success_op = vector_remove_item(my_vec, 10); 
    if (!success_op) printf("Correctly failed to remove item at out-of-bounds index 10.\n");
    else printf("ERROR: Incorrectly removed item at out-of-bounds index.\n");
    printf("\n[Test 9: Reserve Capacity]\n");
    printf("Current capacity: %d\n", vector_capacity(my_vec));
    success_op = vector_reserve(my_vec, 20);
    if (success_op) printf("vector_reserve(20) successful. New capacity: %d\n", vector_capacity(my_vec));
    else printf("vector_reserve(20) FAILED.\n");
    print_vector_status(my_vec, "After reserving capacity for 20");
    success_op = vector_reserve(my_vec, 10); 
    if (success_op) printf("vector_reserve(10) successful (no change expected). Capacity: %d\n", vector_capacity(my_vec));
    else printf("vector_reserve(10) FAILED (should be no-op success).\n");
    success_op = vector_reserve(my_vec, 1); 
    if (!success_op) printf("vector_reserve(1) correctly FAILED (new_capacity < size). Capacity: %d\n", vector_capacity(my_vec));
    else printf("vector_reserve(1) ERROR: should have failed. Capacity: %d\n", vector_capacity(my_vec));
    printf("\n[Test 10: Shrink to Fit]\n");
    vector_reserve(my_vec, vector_size(my_vec) + 10); 
    print_vector_status(my_vec, "Before shrink_to_fit (capacity intentionally made larger)");
    success_op = vector_shrink_to_fit(my_vec);
    if (success_op) printf("vector_shrink_to_fit() successful.\n");
    else printf("vector_shrink_to_fit() FAILED.\n");
    print_vector_status(my_vec, "After shrink_to_fit");
    printf("\n[Test 11: Clear Vector]\n");
    vector_clear(my_vec);
    print_vector_status(my_vec, "After clear (size 0, capacity retained)");
    printf("\n[Test 12: Operations on cleared vector]\n");
    item_val = vector_pop_back(my_vec, &success_op);
    if (!success_op) printf("Correctly failed to pop_back from empty vector.\n");
    else printf("ERROR: Incorrectly popped %d from empty vector.\n", item_val);
    success_op = vector_push_back(my_vec, 777); 
    printf("Pushed 777 to cleared vector: %s\n", success_op ? "OK" : "Fail");
    print_vector_status(my_vec, "After push_back to cleared vector");
    printf("\n[Test 13: Shrink to fit on empty vector]\n"); 
    vector_clear(my_vec);
    print_vector_status(my_vec, "After clear, before shrink on empty");
    success_op = vector_shrink_to_fit(my_vec);
    if (success_op) printf("vector_shrink_to_fit() on empty vector successful.\n");
    else printf("vector_shrink_to_fit() on empty vector FAILED.\n");
    print_vector_status(my_vec, "After shrink_to_fit on empty vector (cap 0, data NULL)");
    printf("\n[Test 14: Destruction]\n");
    vector_destroy(my_vec);
    my_vec = NULL; 
    printf("Vector destroyed.\n");
    vector_destroy(NULL);
    printf("vector_destroy(NULL) called, should not crash.\n");
    printf("\n===== Vector Test Suite Complete =====\n\n");
}

void print_sll_status(const SinglyLinkedList* list, const char* label) {
    if (!label) label = "Current SLL Status";
    printf("\n--- %s ---\n", label);
    if (!list) {
        printf("List is NULL.\n");
        return;
    }
    printf("Size:     %d\n", sll_size(list));
    printf("Is Empty: %s\n", sll_is_empty(list) ? "Yes" : "No");
    bool success_get;
    int first_val = sll_get_first(list, &success_get);
    if(success_get) printf("First:    %d\n", first_val); else printf("First:    (empty)\n");
    int last_val = sll_get_last(list, &success_get);
    if(success_get) printf("Last:     %d\n", last_val); else printf("Last:     (empty)\n");
    printf("Elements: ");
    sll_print(list); 
    printf("---------------\n");
}
void test_singly_linked_list() {
    printf("===== Starting Singly Linked List Test Suite =====\n");
    SinglyLinkedList* my_list = NULL;
    bool success_op;
    int item_val;
    printf("\n[Test 1: Creation]\n");
    my_list = sll_create();
    if (my_list) {
        printf("sll_create() successful.\n");
    } else {
        printf("sll_create() FAILED. Aborting tests.\n");
        return;
    }
    print_sll_status(my_list, "After creation");
    printf("\n[Test 2: Add First]\n");
    success_op = sll_add_first(my_list, 10); printf("Added 10 first: %s\n", success_op ? "OK" : "Fail");
    print_sll_status(my_list, "After adding 10 first");
    success_op = sll_add_first(my_list, 5);  printf("Added 5 first: %s\n", success_op ? "OK" : "Fail");
    print_sll_status(my_list, "After adding 5 first"); 
    printf("\n[Test 3: Add Last]\n");
    success_op = sll_add_last(my_list, 20); printf("Added 20 last: %s\n", success_op ? "OK" : "Fail");
    print_sll_status(my_list, "After adding 20 last"); 
    success_op = sll_add_last(my_list, 30); printf("Added 30 last: %s\n", success_op ? "OK" : "Fail");
    print_sll_status(my_list, "After adding 30 last"); 
    printf("\n[Test 4: Get Operations]\n");
    item_val = sll_get_first(my_list, &success_op);
    if (success_op) printf("First item: %d (Expected 5)\n", item_val); else printf("Get first FAILED.\n");
    item_val = sll_get_last(my_list, &success_op);
    if (success_op) printf("Last item: %d (Expected 30)\n", item_val); else printf("Get last FAILED.\n");
    item_val = sll_get_at(my_list, 1, &success_op);
    if (success_op) printf("Item at index 1: %d (Expected 10)\n", item_val); else printf("Get at index 1 FAILED.\n");
    item_val = sll_get_at(my_list, 3, &success_op); 
    if (success_op) printf("Item at index 3: %d (Expected 30)\n", item_val); else printf("Get at index 3 FAILED.\n");
    item_val = sll_get_at(my_list, 10, &success_op); 
    if (!success_op) printf("Correctly failed to get item at out-of-bounds index 10.\n");
    else printf("ERROR: Incorrectly got item %d at index 10.\n", item_val);
    printf("\n[Test 5: Insert At]\n");
    success_op = sll_insert_at(my_list, 2, 15); printf("Inserted 15 at index 2: %s\n", success_op ? "OK" : "Fail");
    print_sll_status(my_list, "After inserting 15 at index 2"); 
    success_op = sll_insert_at(my_list, 0, 0); printf("Inserted 0 at index 0: %s\n", success_op ? "OK" : "Fail");
    print_sll_status(my_list, "After inserting 0 at index 0"); 
    int current_size_sll = sll_size(my_list);
    success_op = sll_insert_at(my_list, current_size_sll, 40); printf("Inserted 40 at index %d (end): %s\n", current_size_sll, success_op ? "OK" : "Fail");
    print_sll_status(my_list, "After inserting 40 at end"); 
    success_op = sll_insert_at(my_list, sll_size(my_list) + 1, 999); 
    if (!success_op) printf("Correctly failed to insert at out-of-bounds index.\n");
    else printf("ERROR: Incorrectly inserted at out-of-bounds index.\n");
    printf("\n[Test 6: Contains]\n");
    printf("List contains 15: %s (Expected true)\n", sll_contains(my_list, 15) ? "true" : "false");
    printf("List contains 0: %s (Expected true)\n", sll_contains(my_list, 0) ? "true" : "false");
    printf("List contains 40: %s (Expected true)\n", sll_contains(my_list, 40) ? "true" : "false");
    printf("List contains 99: %s (Expected false)\n", sll_contains(my_list, 99) ? "true" : "false");
    printf("\n[Test 7: Remove First]\n");
    item_val = sll_remove_first(my_list, &success_op);
    if (success_op) printf("Removed first: %d (Expected 0)\n", item_val); else printf("Remove first FAILED.\n");
    print_sll_status(my_list, "After removing first"); 
    printf("\n[Test 8: Remove Last]\n");
    item_val = sll_remove_last(my_list, &success_op);
    if (success_op) printf("Removed last: %d (Expected 40)\n", item_val); else printf("Remove last FAILED.\n");
    print_sll_status(my_list, "After removing last"); 
    printf("\n[Test 9: Remove At]\n");
    item_val = sll_remove_at(my_list, 2, &success_op); 
    if (success_op) printf("Removed item at index 2: %d (Expected 15)\n", item_val); else printf("Remove at index 2 FAILED.\n");
    print_sll_status(my_list, "After removing at index 2"); 
    item_val = sll_remove_at(my_list, 0, &success_op); 
    if (success_op) printf("Removed item at index 0: %d (Expected 5)\n", item_val); else printf("Remove at index 0 FAILED.\n");
    print_sll_status(my_list, "After removing at index 0"); 
    item_val = sll_remove_at(my_list, sll_size(my_list) - 1, &success_op); 
    if (success_op) printf("Removed item at last index: %d (Expected 30)\n", item_val); else printf("Remove at last index FAILED.\n");
    print_sll_status(my_list, "After removing at last index"); 
    item_val = sll_remove_at(my_list, 5, &success_op); 
    if (!success_op) printf("Correctly failed to remove at out-of-bounds index 5.\n");
    else printf("ERROR: Incorrectly removed item at index 5.\n");
    printf("\n[Test 10: Clear List]\n");
    sll_clear(my_list);
    print_sll_status(my_list, "After clear");
    printf("List contains 10 after clear: %s (Expected false)\n", sll_contains(my_list, 10) ? "true" : "false");
    printf("\n[Test 11: Operations on cleared list]\n");
    item_val = sll_get_first(my_list, &success_op);
    if (!success_op) printf("Correctly failed to get_first from empty list.\n");
    else printf("ERROR: Incorrectly got %d from empty list (get_first).\n", item_val);
    item_val = sll_remove_last(my_list, &success_op);
    if (!success_op) printf("Correctly failed to remove_last from empty list.\n");
    else printf("ERROR: Incorrectly removed %d from empty list (remove_last).\n", item_val);
    success_op = sll_add_last(my_list, 100); printf("Added 100 last to cleared list: %s\n", success_op ? "OK" : "Fail");
    print_sll_status(my_list, "After adding 100 to cleared list");
    item_val = sll_remove_first(my_list, &success_op);
    if (success_op && item_val == 100) printf("Removed 100 (first) successfully. List should be empty.\n");
    else printf("Failed to remove 100 or incorrect value.\n");
    print_sll_status(my_list, "After removing the only element");
    printf("\n[Test 12: Removing all elements]\n");
    sll_add_last(my_list, 1); sll_add_last(my_list, 2); sll_add_last(my_list, 3);
    print_sll_status(my_list, "List with 3 elements [1,2,3]");
    item_val = sll_remove_last(my_list, &success_op); printf("Removed last: %d (Exp 3)\n", item_val);
    item_val = sll_remove_last(my_list, &success_op); printf("Removed last: %d (Exp 2)\n", item_val);
    item_val = sll_remove_last(my_list, &success_op); printf("Removed last: %d (Exp 1)\n", item_val);
    print_sll_status(my_list, "After removing all via remove_last");
    if (sll_is_empty(my_list) && my_list->head == NULL && my_list->tail == NULL) {
        printf("List is correctly empty, head and tail are NULL.\n");
    } else {
        printf("ERROR: List not correctly empty or head/tail not NULL after removing all.\n");
    }
    sll_add_last(my_list, 1); sll_add_last(my_list, 2); sll_add_last(my_list, 3);
    print_sll_status(my_list, "List with 3 elements [1,2,3] again");
    item_val = sll_remove_first(my_list, &success_op); printf("Removed first: %d (Exp 1)\n", item_val);
    item_val = sll_remove_first(my_list, &success_op); printf("Removed first: %d (Exp 2)\n", item_val);
    item_val = sll_remove_first(my_list, &success_op); printf("Removed first: %d (Exp 3)\n", item_val);
    print_sll_status(my_list, "After removing all via remove_first");
    if (sll_is_empty(my_list) && my_list->head == NULL && my_list->tail == NULL) {
        printf("List is correctly empty, head and tail are NULL.\n");
    } else {
        printf("ERROR: List not correctly empty or head/tail not NULL after removing all.\n");
    }
    printf("\n[Test 13: Destruction]\n");
    sll_destroy(my_list);
    my_list = NULL; 
    printf("Singly Linked List destroyed.\n");
    sll_destroy(NULL);
    printf("sll_destroy(NULL) called, should not crash.\n");
    printf("\n===== Singly Linked List Test Suite Complete =====\n\n");
}

void print_stack_status(const Stack* s, const char* label) {
    if (!label) label = "Current Stack Status";
    printf("\n--- %s ---\n", label);
    if (!s) {
        printf("Stack is NULL.\n");
        return;
    }
    printf("Size:     %d\n", stack_size(s));
    printf("Capacity: %d\n", stack_capacity(s));
    printf("Is Empty: %s\n", stack_is_empty(s) ? "Yes" : "No");
    bool success_peek;
    int top_item = stack_peek(s, &success_peek);
    if (success_peek) {
        printf("Top item: %d\n", top_item);
    } else {
        printf("Top item: (empty stack)\n");
    }
    stack_print(s); 
    printf("---------------\n");
}
void test_stack() {
    printf("===== Starting Stack Test Suite =====\n");
    Stack* my_stack = NULL;
    bool success_op;
    int item_val;
    printf("\n[Test 1: Creation]\n");
    my_stack = stack_create(2); 
    if (my_stack) {
        printf("stack_create(2) successful.\n");
    } else {
        printf("stack_create(2) FAILED. Aborting tests.\n");
        return;
    }
    print_stack_status(my_stack, "After creation with capacity 2");
    Stack* zero_cap_stack = stack_create(0);
    if (zero_cap_stack) {
        printf("stack_create(0) successful.\n");
        print_stack_status(zero_cap_stack, "Stack with 0 initial capacity");
        stack_destroy(zero_cap_stack);
    } else {
        printf("stack_create(0) FAILED.\n");
    }
    Stack* neg_cap_stack = stack_create(-1);
    if (neg_cap_stack == NULL) {
        printf("stack_create(-1) correctly returned NULL.\n");
    } else {
        printf("stack_create(-1) FAILED to return NULL.\n");
        stack_destroy(neg_cap_stack);
    }
    printf("\n[Test 2: Push (no resize)]\n");
    success_op = stack_push(my_stack, 10); printf("Pushed 10: %s\n", success_op ? "OK" : "Fail");
    print_stack_status(my_stack, "After pushing 10");
    success_op = stack_push(my_stack, 20); printf("Pushed 20: %s\n", success_op ? "OK" : "Fail");
    print_stack_status(my_stack, "After pushing 20 (capacity 2 full)");
    printf("\n[Test 3: Push (with resize)]\n");
    success_op = stack_push(my_stack, 30); 
    printf("Pushed 30 (triggers resize): %s\n", success_op ? "OK" : "Fail");
    print_stack_status(my_stack, "After pushing 30 (resized)");
    printf("\n[Test 4: Peek]\n");
    item_val = stack_peek(my_stack, &success_op);
    if (success_op) printf("Peeked item: %d (Expected 30)\n", item_val);
    else printf("Peek FAILED when stack should not be empty.\n");
    print_stack_status(my_stack, "After peeking (no change)");
    printf("\n[Test 5: Pop]\n");
    item_val = stack_pop(my_stack, &success_op);
    if (success_op) printf("Popped item: %d (Expected 30)\n", item_val);
    else printf("Pop FAILED when stack should not be empty.\n");
    print_stack_status(my_stack, "After popping 30"); 
    item_val = stack_pop(my_stack, &success_op);
    if (success_op) printf("Popped item: %d (Expected 20)\n", item_val);
    else printf("Pop FAILED when stack should not be empty.\n");
    print_stack_status(my_stack, "After popping 20"); 
    item_val = stack_pop(my_stack, &success_op);
    if (success_op) printf("Popped item: %d (Expected 10)\n", item_val);
    else printf("Pop FAILED when stack should not be empty.\n");
    print_stack_status(my_stack, "After popping 10 (stack empty)"); 
    printf("\n[Test 6: Operations on Empty Stack]\n");
    item_val = stack_peek(my_stack, &success_op);
    if (!success_op) printf("Correctly FAILED to peek from empty stack.\n");
    else printf("ERROR: Incorrectly peeked %d from empty stack.\n", item_val);
    item_val = stack_pop(my_stack, &success_op);
    if (!success_op) printf("Correctly FAILED to pop from empty stack.\n");
    else printf("ERROR: Incorrectly popped %d from empty stack.\n", item_val);
    print_stack_status(my_stack, "After trying to pop/peek from empty stack");
    printf("\n[Test 7: Reserve Capacity]\n");
    printf("Current capacity: %d\n", stack_capacity(my_stack));
    success_op = stack_reserve(my_stack, 10);
    if (success_op) printf("stack_reserve(10) successful. New capacity: %d\n", stack_capacity(my_stack));
    else printf("stack_reserve(10) FAILED.\n");
    print_stack_status(my_stack, "After reserving capacity for 10");
    stack_push(my_stack, 100); stack_push(my_stack, 200);
    print_stack_status(my_stack, "After pushing 100, 200 (size 2, cap 10)");
    success_op = stack_reserve(my_stack, 5); 
    if (success_op) printf("stack_reserve(5) successful (no change expected). Capacity: %d\n", stack_capacity(my_stack));
    else printf("stack_reserve(5) FAILED (should be no-op success).\n");
    success_op = stack_reserve(my_stack, 1); 
    if (!success_op) printf("stack_reserve(1) correctly FAILED (new_capacity < size). Capacity: %d\n", stack_capacity(my_stack));
    else printf("stack_reserve(1) ERROR: should have failed. Capacity: %d\n", stack_capacity(my_stack));
    printf("\n[Test 8: Clear Stack]\n");
    stack_clear(my_stack);
    print_stack_status(my_stack, "After clear (size 0, capacity retained)");
    if (stack_is_empty(my_stack) && stack_size(my_stack) == 0) { // Capacity check can be tricky if not well-defined after clear+reserve
         printf("Stack correctly cleared (empty, size 0).\n");
    } else {
        printf("ERROR: Stack not correctly cleared. Capacity: %d\n", stack_capacity(my_stack));
    }
    printf("\n[Test 9: Push to cleared stack]\n");
    success_op = stack_push(my_stack, 777); printf("Pushed 777 to cleared stack: %s\n", success_op ? "OK" : "Fail");
    print_stack_status(my_stack, "After push_back to cleared stack (size 1, top 777)");
    printf("\n[Test 10: Destruction]\n");
    stack_destroy(my_stack);
    my_stack = NULL; 
    printf("Stack destroyed.\n");
    stack_destroy(NULL);
    printf("stack_destroy(NULL) called, should not crash.\n");
    printf("\n[Test 11: Zero initial capacity then push]\n");
    Stack* s0 = stack_create(0);
    if (!s0) { printf("Failed to create stack with 0 capacity. Test aborted.\n"); return; }
    print_stack_status(s0, "Stack with 0 initial capacity");
    success_op = stack_push(s0, 1);
    if (success_op) printf("Pushed 1 to 0-capacity stack. OK.\n");
    else printf("Pushed 1 to 0-capacity stack. FAILED.\n");
    print_stack_status(s0, "After pushing 1 to 0-capacity stack");
    stack_destroy(s0);
    printf("\n===== Stack Test Suite Complete =====\n\n");
}

void print_queue_status(const Queue* q, const char* label) {
    if (!label) label = "Current Queue Status";
    printf("\n--- %s ---\n", label);
    if (!q) {
        printf("Queue is NULL.\n");
        return;
    }
    printf("Size:     %d\n", queue_size(q));
    printf("Capacity: %d\n", queue_capacity(q));
    printf("Is Empty: %s\n", queue_is_empty(q) ? "Yes" : "No");
    printf("Front Idx: %d, Rear Idx: %d\n", q->front, q->rear); // Assuming direct access for debug
    bool success_peek;
    int front_item = queue_peek(q, &success_peek);
    if (success_peek) {
        printf("Front item: %d\n", front_item);
    } else {
        printf("Front item: (empty queue)\n");
    }
    queue_print(q); 
    printf("---------------\n");
}
void test_queue() {
    printf("===== Starting Queue Test Suite =====\n");
    Queue* my_queue = NULL;
    bool success_op;
    int item_val;
    printf("\n[Test 1: Creation]\n");
    my_queue = queue_create(3); 
    if (my_queue) {
        printf("queue_create(3) successful.\n");
    } else {
        printf("queue_create(3) FAILED. Aborting tests.\n");
        return;
    }
    print_queue_status(my_queue, "After creation with capacity 3");
    Queue* zero_cap_q = queue_create(0);
    if (zero_cap_q) {
        printf("queue_create(0) successful.\n");
        print_queue_status(zero_cap_q, "Queue with 0 initial capacity");
        queue_destroy(zero_cap_q);
    } else {
        printf("queue_create(0) FAILED.\n");
    }
    Queue* neg_cap_q = queue_create(-1);
    if (neg_cap_q == NULL) {
        printf("queue_create(-1) correctly returned NULL.\n");
    } else {
        printf("queue_create(-1) FAILED to return NULL.\n");
        queue_destroy(neg_cap_q);
    }
    printf("\n[Test 2: Enqueue (no resize)]\n");
    success_op = queue_enqueue(my_queue, 10); printf("Enqueued 10: %s\n", success_op ? "OK" : "Fail");
    print_queue_status(my_queue, "After enqueuing 10");
    success_op = queue_enqueue(my_queue, 20); printf("Enqueued 20: %s\n", success_op ? "OK" : "Fail");
    print_queue_status(my_queue, "After enqueuing 20");
    success_op = queue_enqueue(my_queue, 30); printf("Enqueued 30: %s\n", success_op ? "OK" : "Fail");
    print_queue_status(my_queue, "After enqueuing 30 (capacity 3 full)");
    printf("\n[Test 3: Enqueue (with resize)]\n");
    success_op = queue_enqueue(my_queue, 40); 
    printf("Enqueued 40 (triggers resize): %s\n", success_op ? "OK" : "Fail");
    print_queue_status(my_queue, "After enqueuing 40 (resized)");
    printf("\n[Test 4: Peek]\n");
    item_val = queue_peek(my_queue, &success_op);
    if (success_op) printf("Peeked item: %d (Expected 10)\n", item_val);
    else printf("Peek FAILED when queue should not be empty.\n");
    print_queue_status(my_queue, "After peeking (no change)");
    printf("\n[Test 5: Dequeue]\n");
    item_val = queue_dequeue(my_queue, &success_op);
    if (success_op) printf("Dequeued item: %d (Expected 10)\n", item_val);
    else printf("Dequeue FAILED when queue should not be empty.\n");
    print_queue_status(my_queue, "After dequeuing 10"); 
    item_val = queue_dequeue(my_queue, &success_op);
    if (success_op) printf("Dequeued item: %d (Expected 20)\n", item_val);
    else printf("Dequeue FAILED when queue should not be empty.\n");
    print_queue_status(my_queue, "After dequeuing 20"); 
    printf("\n[Test 6: Wrap-around]\n");
    // This test highly depends on the internal resize strategy and current state.
    // To make it more deterministic for this example, re-create for wrap test:
    queue_destroy(my_queue);
    my_queue = queue_create(3); // Start with small capacity
    queue_enqueue(my_queue, 100);
    queue_enqueue(my_queue, 200);
    queue_dequeue(my_queue, &success_op); // Dequeue 100. Q: [_, 200, _], F=1,R=2,S=1,C=3
    print_queue_status(my_queue, "After 2 enq, 1 deq");
    queue_enqueue(my_queue, 300); // Q: [_, 200, 300], F=1,R=0(wrap),S=2,C=3
    print_queue_status(my_queue, "After enq 300 (rear wrap)");
    queue_enqueue(my_queue, 400); // Q: [400, 200, 300], F=1,R=1(wrap),S=3,C=3 (full)
    print_queue_status(my_queue, "After enq 400 (full, front/rear meet)");
    // Now dequeue to show front wrap
    item_val = queue_dequeue(my_queue, &success_op); printf("Dequeued item: %d (Expected 200)\n", item_val);
    print_queue_status(my_queue, "After deq 200 (front moves)"); // Q: [400, _, 300], F=2,R=1,S=2
    item_val = queue_dequeue(my_queue, &success_op); printf("Dequeued item: %d (Expected 300)\n", item_val);
    print_queue_status(my_queue, "After deq 300 (front wraps)"); // Q: [400, _, _], F=0,R=1,S=1
    item_val = queue_dequeue(my_queue, &success_op); printf("Dequeued item: %d (Expected 400)\n", item_val);
    print_queue_status(my_queue, "After deq 400 (empty)"); // Q: empty, F=1,R=1,S=0
    printf("\n[Test 7: Operations on Empty Queue]\n");
    item_val = queue_peek(my_queue, &success_op);
    if (!success_op) printf("Correctly FAILED to peek from empty queue.\n");
    else printf("ERROR: Incorrectly peeked %d from empty queue.\n", item_val);
    item_val = queue_dequeue(my_queue, &success_op);
    if (!success_op) printf("Correctly FAILED to dequeue from empty queue.\n");
    else printf("ERROR: Incorrectly dequeued %d from empty queue.\n", item_val);
    print_queue_status(my_queue, "After trying to peek/dequeue from empty queue");
    printf("\n[Test 8: Reserve Capacity]\n");
    printf("Current capacity: %d\n", queue_capacity(my_queue));
    success_op = queue_reserve(my_queue, 10);
    if (success_op) printf("queue_reserve(10) successful. New capacity: %d\n", queue_capacity(my_queue));
    else printf("queue_reserve(10) FAILED.\n");
    print_queue_status(my_queue, "After reserving capacity for 10 (empty queue)");
    queue_enqueue(my_queue, 100); queue_enqueue(my_queue, 200);
    print_queue_status(my_queue, "After enqueuing 100, 200 (size 2, cap 10, F=0, R=2)");
    queue_dequeue(my_queue, &success_op); 
    print_queue_status(my_queue, "After one dequeue (F=1, R=2, S=1)");
    success_op = queue_reserve(my_queue, 5); 
    if (success_op) printf("queue_reserve(5) successful (no change expected if cap was >=5). Capacity: %d\n", queue_capacity(my_queue));
    else printf("queue_reserve(5) FAILED (should be no-op success if cap >= 5).\n");
    print_queue_status(my_queue, "After reserve(5)");
    success_op = queue_reserve(my_queue, 0); 
    if (!success_op) printf("queue_reserve(0) correctly FAILED (new_capacity < size).\n");
    else printf("queue_reserve(0) ERROR: should have failed. Capacity: %d\n", queue_capacity(my_queue));
    // Test reserve that forces unrolling
    queue_destroy(my_queue);
    my_queue = queue_create(3);
    queue_enqueue(my_queue, 1); queue_enqueue(my_queue, 2);
    queue_dequeue(my_queue, &success_op); 
    queue_enqueue(my_queue, 3);           
    print_queue_status(my_queue, "Wrapped queue [2,3] before reserve. F=1, R=0, S=2, C=3");
    success_op = queue_reserve(my_queue, 5);
    if (success_op) printf("queue_reserve(5) successful. New capacity: %d\n", queue_capacity(my_queue));
    else printf("queue_reserve(5) FAILED.\n");
    print_queue_status(my_queue, "After reserve(5) on wrapped queue. Should be unrolled: F=0, R=2, S=2. Elements [2,3]");
    printf("\n[Test 9: Clear Queue]\n"); // Renamed from 9 to 9 as Test 6 was simplified
    queue_clear(my_queue);
    print_queue_status(my_queue, "After clear (size 0, capacity retained, F=0, R=0)");
    if (queue_is_empty(my_queue) && queue_size(my_queue) == 0 && my_queue->front == 0 && my_queue->rear == 0) { // Capacity check removed for simplicity
         printf("Queue correctly cleared.\n");
    } else {
        printf("ERROR: Queue not correctly cleared.\n");
    }
    printf("\n[Test 10: Enqueue to cleared queue]\n");
    success_op = queue_enqueue(my_queue, 777); printf("Enqueued 777 to cleared queue: %s\n", success_op ? "OK" : "Fail");
    print_queue_status(my_queue, "After enqueue to cleared queue (size 1, F=0, R=1)");
    printf("\n[Test 11: Destruction]\n"); 
    queue_destroy(my_queue);
    my_queue = NULL; 
    printf("Queue destroyed.\n");
    queue_destroy(NULL);
    printf("queue_destroy(NULL) called, should not crash.\n");
    printf("\n[Test 12: Zero initial capacity then enqueue]\n");
    Queue* q0 = queue_create(0);
    if (!q0) { printf("Failed to create queue with 0 capacity. Test aborted.\n"); return; }
    print_queue_status(q0, "Queue with 0 initial capacity");
    success_op = queue_enqueue(q0, 1);
    if (success_op) printf("Enqueued 1 to 0-capacity queue. OK.\n");
    else printf("Enqueued 1 to 0-capacity queue. FAILED.\n");
    print_queue_status(q0, "After enqueuing 1 to 0-capacity queue");
    queue_destroy(q0);
    printf("\n===== Queue Test Suite Complete =====\n\n");
}

void print_dll_status(const DoublyLinkedList* list, const char* label) {
    if (!label) label = "Current DLL Status";
    printf("\n--- %s ---\n", label);
    if (!list) {
        printf("List is NULL.\n");
        return;
    }
    printf("Size:     %d\n", dll_size(list));
    printf("Is Empty: %s\n", dll_is_empty(list) ? "Yes" : "No");
    bool success_get;
    int first_val = dll_get_first(list, &success_get);
    if(success_get) printf("First:    %d\n", first_val); else printf("First:    (empty)\n");
    int last_val = dll_get_last(list, &success_get);
    if(success_get) printf("Last:     %d\n", last_val); else printf("Last:     (empty)\n");
    printf("Elements (H->T): ");
    dll_print_forward(list);
    printf("Elements (T->H): ");
    dll_print_backward(list);
    printf("---------------\n");
}
void test_doubly_linked_list() {
    printf("===== Starting Doubly Linked List Test Suite =====\n");
    DoublyLinkedList* my_list = NULL;
    bool success_op;
    int item_val;
    printf("\n[Test 1: Creation]\n");
    my_list = dll_create();
    if (my_list) {
        printf("dll_create() successful.\n");
    } else {
        printf("dll_create() FAILED. Aborting tests.\n");
        return;
    }
    print_dll_status(my_list, "After creation");
    printf("\n[Test 2: Add First]\n");
    success_op = dll_add_first(my_list, 10); printf("Added 10 first: %s\n", success_op ? "OK" : "Fail");
    print_dll_status(my_list, "After adding 10 first");
    success_op = dll_add_first(my_list, 5);  printf("Added 5 first: %s\n", success_op ? "OK" : "Fail");
    print_dll_status(my_list, "After adding 5 first"); 
    printf("\n[Test 3: Add Last]\n");
    success_op = dll_add_last(my_list, 20); printf("Added 20 last: %s\n", success_op ? "OK" : "Fail");
    print_dll_status(my_list, "After adding 20 last"); 
    success_op = dll_add_last(my_list, 30); printf("Added 30 last: %s\n", success_op ? "OK" : "Fail");
    print_dll_status(my_list, "After adding 30 last"); 
    printf("\n[Test 4: Get Operations]\n");
    item_val = dll_get_first(my_list, &success_op);
    if (success_op) printf("First item: %d (Expected 5)\n", item_val); else printf("Get first FAILED.\n");
    item_val = dll_get_last(my_list, &success_op);
    if (success_op) printf("Last item: %d (Expected 30)\n", item_val); else printf("Get last FAILED.\n");
    item_val = dll_get_at(my_list, 1, &success_op);
    if (success_op) printf("Item at index 1: %d (Expected 10)\n", item_val); else printf("Get at index 1 FAILED.\n");
    item_val = dll_get_at(my_list, 3, &success_op); 
    if (success_op) printf("Item at index 3: %d (Expected 30)\n", item_val); else printf("Get at index 3 FAILED.\n");
    item_val = dll_get_at(my_list, 10, &success_op); 
    if (!success_op) printf("Correctly failed to get item at out-of-bounds index 10.\n");
    else printf("ERROR: Incorrectly got item %d at index 10.\n", item_val);
    item_val = dll_get_at(my_list, dll_size(my_list)/2, &success_op); 
    if (success_op) printf("Item at index %d (middle-ish): %d\n", dll_size(my_list)/2, item_val); else printf("Get at middle index FAILED.\n");
    printf("\n[Test 5: Insert At]\n");
    success_op = dll_insert_at(my_list, 2, 15); printf("Inserted 15 at index 2: %s\n", success_op ? "OK" : "Fail");
    print_dll_status(my_list, "After inserting 15 at index 2"); 
    success_op = dll_insert_at(my_list, 0, 0); printf("Inserted 0 at index 0: %s\n", success_op ? "OK" : "Fail");
    print_dll_status(my_list, "After inserting 0 at index 0"); 
    int current_size_dll = dll_size(my_list); 
    success_op = dll_insert_at(my_list, current_size_dll, 40); printf("Inserted 40 at index %d (end): %s\n", current_size_dll, success_op ? "OK" : "Fail");
    print_dll_status(my_list, "After inserting 40 at end"); 
    success_op = dll_insert_at(my_list, dll_size(my_list) + 1, 999); 
    if (!success_op) printf("Correctly failed to insert at out-of-bounds index.\n");
    else printf("ERROR: Incorrectly inserted at out-of-bounds index.\n");
    printf("\n[Test 6: Contains]\n");
    printf("List contains 15: %s (Expected true)\n", dll_contains(my_list, 15) ? "true" : "false");
    printf("List contains 0: %s (Expected true)\n", dll_contains(my_list, 0) ? "true" : "false");
    printf("List contains 40: %s (Expected true)\n", dll_contains(my_list, 40) ? "true" : "false");
    printf("List contains 99: %s (Expected false)\n", dll_contains(my_list, 99) ? "true" : "false");
    printf("\n[Test 7: Remove First]\n");
    item_val = dll_remove_first(my_list, &success_op);
    if (success_op) printf("Removed first: %d (Expected 0)\n", item_val); else printf("Remove first FAILED.\n");
    print_dll_status(my_list, "After removing first"); 
    printf("\n[Test 8: Remove Last]\n");
    item_val = dll_remove_last(my_list, &success_op);
    if (success_op) printf("Removed last: %d (Expected 40)\n", item_val); else printf("Remove last FAILED.\n");
    print_dll_status(my_list, "After removing last"); 
    printf("\n[Test 9: Remove At]\n");
    item_val = dll_remove_at(my_list, 2, &success_op); 
    if (success_op) printf("Removed item at index 2: %d (Expected 15)\n", item_val); else printf("Remove at index 2 FAILED.\n");
    print_dll_status(my_list, "After removing at index 2"); 
    item_val = dll_remove_at(my_list, 0, &success_op); 
    if (success_op) printf("Removed item at index 0: %d (Expected 5)\n", item_val); else printf("Remove at index 0 FAILED.\n");
    print_dll_status(my_list, "After removing at index 0"); 
    item_val = dll_remove_at(my_list, dll_size(my_list) - 1, &success_op); 
    if (success_op) printf("Removed item at last index: %d (Expected 30)\n", item_val); else printf("Remove at last index FAILED.\n");
    print_dll_status(my_list, "After removing at last index"); 
    item_val = dll_remove_at(my_list, 5, &success_op); 
    if (!success_op) printf("Correctly failed to remove at out-of-bounds index 5.\n");
    else printf("ERROR: Incorrectly removed item at index 5.\n");
    printf("\n[Test 10: Clear List]\n");
    dll_clear(my_list);
    print_dll_status(my_list, "After clear");
    printf("List contains 10 after clear: %s (Expected false)\n", dll_contains(my_list, 10) ? "true" : "false");
    printf("\n[Test 11: Operations on cleared list]\n");
    item_val = dll_get_first(my_list, &success_op);
    if (!success_op) printf("Correctly failed to get_first from empty list.\n");
    else printf("ERROR: Incorrectly got %d from empty list (get_first).\n", item_val);
    item_val = dll_remove_last(my_list, &success_op);
    if (!success_op) printf("Correctly failed to remove_last from empty list.\n");
    else printf("ERROR: Incorrectly removed %d from empty list (remove_last).\n", item_val);
    success_op = dll_add_last(my_list, 100); printf("Added 100 last to cleared list: %s\n", success_op ? "OK" : "Fail");
    print_dll_status(my_list, "After adding 100 to cleared list");
    item_val = dll_remove_first(my_list, &success_op);
    if (success_op && item_val == 100) printf("Removed 100 (first) successfully. List should be empty.\n");
    else printf("Failed to remove 100 or incorrect value.\n");
    print_dll_status(my_list, "After removing the only element");
    if (dll_is_empty(my_list) && my_list->head == NULL && my_list->tail == NULL) {
        printf("List is correctly empty, head and tail are NULL.\n");
    } else {
        printf("ERROR: List not correctly empty or head/tail not NULL after removing all.\n");
    }
    printf("\n[Test 12: Removing all elements check head/tail NULL]\n");
    dll_add_last(my_list, 1); dll_add_last(my_list, 2); dll_add_last(my_list, 3);
    print_dll_status(my_list, "List with 3 elements [1,2,3]");
    item_val = dll_remove_last(my_list, &success_op); printf("Removed last: %d (Exp 3)\n", item_val);
    item_val = dll_remove_last(my_list, &success_op); printf("Removed last: %d (Exp 2)\n", item_val);
    item_val = dll_remove_last(my_list, &success_op); printf("Removed last: %d (Exp 1)\n", item_val);
    print_dll_status(my_list, "After removing all via remove_last");
    if (dll_is_empty(my_list) && my_list->head == NULL && my_list->tail == NULL) {
        printf("List is correctly empty, head and tail are NULL.\n");
    } else {
        printf("ERROR: List not correctly empty or head/tail not NULL after removing all via remove_last.\n");
    }
    dll_add_last(my_list, 1); dll_add_last(my_list, 2); dll_add_last(my_list, 3);
    print_dll_status(my_list, "List with 3 elements [1,2,3] again");
    item_val = dll_remove_first(my_list, &success_op); printf("Removed first: %d (Exp 1)\n", item_val);
    item_val = dll_remove_first(my_list, &success_op); printf("Removed first: %d (Exp 2)\n", item_val);
    item_val = dll_remove_first(my_list, &success_op); printf("Removed first: %d (Exp 3)\n", item_val);
    print_dll_status(my_list, "After removing all via remove_first");
    if (dll_is_empty(my_list) && my_list->head == NULL && my_list->tail == NULL) {
        printf("List is correctly empty, head and tail are NULL.\n");
    } else {
        printf("ERROR: List not correctly empty or head/tail not NULL after removing all via remove_first.\n");
    }
    printf("\n[Test 13: Destruction]\n");
    dll_destroy(my_list);
    my_list = NULL; 
    printf("Doubly Linked List destroyed.\n");
    dll_destroy(NULL);
    printf("dll_destroy(NULL) called, should not crash.\n");
    printf("\n===== Doubly Linked List Test Suite Complete =====\n\n");
}

void print_hash_set_status(const HashSet* set, const char* label) {
    if (!label) label = "Current HashSet Status";
    printf("\n--- %s ---\n", label);
    if (!set) {
        printf("HashSet is NULL.\n");
        return;
    }
    printf("Number of elements (size): %d\n", hash_set_size(set));
    printf("Table capacity (buckets):  %d\n", hash_set_table_capacity(set));
    printf("Is Empty:                  %s\n", hash_set_is_empty(set) ? "Yes" : "No");
    if (hash_set_table_capacity(set) > 0) { 
        printf("Load Factor:               %.2f\n", (float)hash_set_size(set) / hash_set_table_capacity(set));
    }
    hash_set_print(set); 
    printf("---------------\n");
}
void test_hash_set() {
    printf("===== Starting HashSet Test Suite =====\n");
    HashSet* my_set = NULL;
    bool success_op;
    printf("\n[Test 1: Creation]\n");
    my_set = hash_set_create(5);
    if (my_set) {
        printf("hash_set_create(5) successful.\n");
    } else {
        printf("hash_set_create(5) FAILED. Aborting tests.\n");
        return;
    }
    print_hash_set_status(my_set, "After creation with capacity 5");
    HashSet* invalid_set = hash_set_create(0);
    if (invalid_set == NULL) {
        printf("hash_set_create(0) correctly returned NULL.\n");
    } else {
        printf("hash_set_create(0) FAILED to return NULL.\n");
        hash_set_destroy(invalid_set);
    }
    printf("\n[Test 2: Insertions]\n");
    success_op = hash_set_insert(my_set, 10); printf("Inserted 10: %s (Expected true)\n", success_op ? "OK" : "Fail");
    success_op = hash_set_insert(my_set, 20); printf("Inserted 20: %s (Expected true)\n", success_op ? "OK" : "Fail");
    success_op = hash_set_insert(my_set, 5);  printf("Inserted 5:  %s (Expected true)\n", success_op ? "OK" : "Fail"); 
    print_hash_set_status(my_set, "After inserting 10, 20, 5");
    success_op = hash_set_insert(my_set, 10); printf("Inserted 10 again: %s (Expected false, already present)\n", !success_op ? "OK" : "Fail");
    print_hash_set_status(my_set, "After trying to insert 10 again");
    if (hash_set_size(my_set) != 3) printf("ERROR: Size is %d, expected 3 after duplicate insert.\n", hash_set_size(my_set));
    printf("\n[Test 3: Contains]\n");
    printf("Set contains 10: %s (Expected true)\n", hash_set_contains(my_set, 10) ? "true" : "false");
    printf("Set contains 5:  %s (Expected true)\n", hash_set_contains(my_set, 5) ? "true" : "false");
    printf("Set contains 99: %s (Expected false)\n", hash_set_contains(my_set, 99) ? "true" : "false");
    printf("\n[Test 4: Removals]\n");
    success_op = hash_set_remove(my_set, 20); printf("Removed 20: %s (Expected true)\n", success_op ? "OK" : "Fail");
    print_hash_set_status(my_set, "After removing 20");
    if (hash_set_contains(my_set, 20)) printf("ERROR: Set still contains 20 after removal.\n");
    if (hash_set_size(my_set) != 2) printf("ERROR: Size is %d, expected 2 after removing 20.\n", hash_set_size(my_set));
    success_op = hash_set_remove(my_set, 99); printf("Removed 99 (not present): %s (Expected false)\n", !success_op ? "OK" : "Fail"); 
    print_hash_set_status(my_set, "After trying to remove 99 (not present)");
    success_op = hash_set_remove(my_set, 5); printf("Removed 5: %s (Expected true)\n", success_op ? "OK" : "Fail");
    print_hash_set_status(my_set, "After removing 5");
    printf("\n[Test 5: Automatic Resize on Insert]\n");
    hash_set_insert(my_set, 1);  
    hash_set_insert(my_set, 2);  
    printf("Before potential resize: size=%d, capacity=%d\n", hash_set_size(my_set), hash_set_table_capacity(my_set));
    hash_set_insert(my_set, 3);  
    printf("After inserting 3 (possible resize): size=%d, capacity=%d\n", hash_set_size(my_set), hash_set_table_capacity(my_set));
    hash_set_insert(my_set, 4);  
    print_hash_set_status(my_set, "After inserting 1, 2, 3, 4 (check for resize)");
    printf("Contains 10: %s, 1: %s, 2: %s, 3: %s, 4: %s\n",
        hash_set_contains(my_set, 10) ? "T":"F", hash_set_contains(my_set, 1) ? "T":"F",
        hash_set_contains(my_set, 2) ? "T":"F", hash_set_contains(my_set, 3) ? "T":"F",
        hash_set_contains(my_set, 4) ? "T":"F");
    printf("\n[Test 6: Manual Resize]\n");
    int old_capacity_hs = hash_set_table_capacity(my_set); // Renamed
    int new_capacity_large_hs = old_capacity_hs * 3; // Renamed
    printf("Attempting to resize from %d to %d buckets.\n", old_capacity_hs, new_capacity_large_hs);
    success_op = hash_set_resize(my_set, new_capacity_large_hs);
    printf("Manual resize to %d buckets: %s\n", new_capacity_large_hs, success_op ? "OK" : "Fail");
    print_hash_set_status(my_set, "After manual resize to larger capacity");
    if (success_op && hash_set_table_capacity(my_set) != new_capacity_large_hs) {
        printf("ERROR: Capacity after resize is %d, expected %d\n", hash_set_table_capacity(my_set), new_capacity_large_hs);
    }
    printf("After large resize - Contains 10: %s, 1: %s, 2: %s, 3: %s, 4: %s\n",
        hash_set_contains(my_set, 10) ? "T":"F", hash_set_contains(my_set, 1) ? "T":"F",
        hash_set_contains(my_set, 2) ? "T":"F", hash_set_contains(my_set, 3) ? "T":"F",
        hash_set_contains(my_set, 4) ? "T":"F");
    int current_num_elements_hs = hash_set_size(my_set); // Renamed
    success_op = hash_set_resize(my_set, current_num_elements_hs / 2); 
    if (!success_op) {
        printf("Correctly FAILED to resize to %d (smaller than num_elements %d).\n", current_num_elements_hs/2, current_num_elements_hs);
    } else {
         printf("ERROR: Incorrectly allowed resize to %d (smaller than num_elements %d).\n", current_num_elements_hs/2, current_num_elements_hs);
    }
    print_hash_set_status(my_set, "After trying to resize too small");
    printf("\n[Test 7: Clear Set]\n");
    int capacity_before_clear_hs = hash_set_table_capacity(my_set); // Renamed
    hash_set_clear(my_set);
    print_hash_set_status(my_set, "After clear");
    if (!hash_set_is_empty(my_set) || hash_set_size(my_set) != 0) {
        printf("ERROR: Set not empty after clear.\n");
    }
    if (hash_set_table_capacity(my_set) != capacity_before_clear_hs) {
        printf("ERROR: Table capacity changed after clear. Was %d, now %d.\n", capacity_before_clear_hs, hash_set_table_capacity(my_set));
    }
    printf("Set contains 10 after clear: %s (Expected false)\n", hash_set_contains(my_set, 10) ? "true" : "false");
    printf("\n[Test 8: Operations on cleared set]\n");
    success_op = hash_set_remove(my_set, 10); printf("Removed 10 from cleared set: %s (Expected false)\n", !success_op ? "OK" : "Fail"); 
    printf("Contains 10 in cleared set: %s (Expected false)\n", hash_set_contains(my_set, 10) ? "true" : "false");
    success_op = hash_set_insert(my_set, 100); printf("Inserted 100 into cleared set: %s (Expected true)\n", success_op ? "OK" : "Fail");
    print_hash_set_status(my_set, "After inserting 100 into cleared set");
    printf("\n[Test 9: Destruction]\n");
    hash_set_destroy(my_set);
    my_set = NULL; 
    printf("HashSet destroyed.\n");
    hash_set_destroy(NULL);
    printf("hash_set_destroy(NULL) called, should not crash.\n");
    printf("\n===== HashSet Test Suite Complete =====\n\n");
}

void print_bst_status(const BinarySearchTree* tree, const char* label) {
    if (!label) label = "Current BST Status";
    printf("\n--- %s ---\n", label);
    if (!tree) {
        printf("BST is NULL.\n");
        return;
    }
    printf("Size:     %d\n", bst_size(tree));
    printf("Is Empty: %s\n", bst_is_empty(tree) ? "Yes" : "No");
    printf("Height:   %d\n", bst_height(tree));
    bool success_op; 
    int min_val = bst_find_min(tree, &success_op);
    if (success_op) printf("Min:      %d\n", min_val); else printf("Min:      (empty)\n");
    int max_val = bst_find_max(tree, &success_op);
    if (success_op) printf("Max:      %d\n", max_val); else printf("Max:      (empty)\n");
    TreeVisitData traversal_data_bst; // Use generic struct
    traversal_data_bst.count = 0;
    traversal_data_bst.first_print = true;
    printf("In-order:   [");
    bst_in_order_traversal(tree, tree_node_visit_printer, &traversal_data_bst); // Use generic printer
    printf("]\n");
    traversal_data_bst.count = 0;
    traversal_data_bst.first_print = true;
    printf("Pre-order:  [");
    bst_pre_order_traversal(tree, tree_node_visit_printer, &traversal_data_bst);
    printf("]\n");
    traversal_data_bst.count = 0;
    traversal_data_bst.first_print = true;
    printf("Post-order: [");
    bst_post_order_traversal(tree, tree_node_visit_printer, &traversal_data_bst);
    printf("]\n");
    printf("---------------\n");
}
void test_binary_search_tree() {
    printf("===== Starting Binary Search Tree Test Suite =====\n");
    BinarySearchTree* my_bst = NULL;
    bool success_op; 
    printf("\n[Test 1: Creation]\n");
    my_bst = bst_create();
    if (my_bst) {
        printf("bst_create() successful.\n");
    } else {
        printf("bst_create() FAILED. Aborting tests.\n");
        return;
    }
    print_bst_status(my_bst, "After creation");
    printf("\n[Test 2: Insertions]\n");
    bst_insert(my_bst, 50);
    bst_insert(my_bst, 30);
    bst_insert(my_bst, 70);
    bst_insert(my_bst, 20);
    bst_insert(my_bst, 40);
    bst_insert(my_bst, 60);
    success_op = bst_insert(my_bst, 80); printf("Inserted 80: %s (Expected true)\n", success_op ? "OK" : "Fail");
    print_bst_status(my_bst, "After inserting 50,30,70,20,40,60,80");
    success_op = bst_insert(my_bst, 30); printf("Inserted 30 again: %s (Expected false, already present)\n", !success_op ? "OK" : "Fail"); 
    print_bst_status(my_bst, "After trying to insert 30 again");
    if (bst_size(my_bst) != 7) printf("ERROR: Size is %d, expected 7 after duplicate insert.\n", bst_size(my_bst));
    printf("\n[Test 3: Contains]\n");
    printf("BST contains 50 (root): %s (Expected true)\n", bst_contains(my_bst, 50) ? "true" : "false");
    printf("BST contains 20 (leaf): %s (Expected true)\n", bst_contains(my_bst, 20) ? "true" : "false");
    printf("BST contains 80 (leaf): %s (Expected true)\n", bst_contains(my_bst, 80) ? "true" : "false");
    printf("BST contains 60 (internal): %s (Expected true)\n", bst_contains(my_bst, 60) ? "true" : "false");
    printf("BST contains 99 (not present): %s (Expected false)\n", bst_contains(my_bst, 99) ? "true" : "false");
    printf("\n[Test 4: Removals]\n");
    success_op = bst_remove(my_bst, 20); printf("Removed 20 (leaf): %s (Expected true)\n", success_op ? "OK" : "Fail");
    print_bst_status(my_bst, "After removing 20 (leaf)");
    if (bst_contains(my_bst, 20)) printf("ERROR: BST still contains 20 after removal.\n");
    if (bst_size(my_bst) != 6) printf("ERROR: Size is %d, expected 6 after removing 20.\n", bst_size(my_bst));
    success_op = bst_remove(my_bst, 30); printf("Removed 30 (one child): %s (Expected true)\n", success_op ? "OK" : "Fail");
    print_bst_status(my_bst, "After removing 30 (one child)");
    if (bst_contains(my_bst, 30)) printf("ERROR: BST still contains 30 after removal.\n");
    if (bst_size(my_bst) != 5) printf("ERROR: Size is %d, expected 5 after removing 30.\n", bst_size(my_bst));
    success_op = bst_remove(my_bst, 70); printf("Removed 70 (two children): %s (Expected true)\n", success_op ? "OK" : "Fail");
    print_bst_status(my_bst, "After removing 70 (two children)");
    if (bst_contains(my_bst, 70)) printf("ERROR: BST still contains 70 after removal.\n");
    if (bst_size(my_bst) != 4) printf("ERROR: Size is %d, expected 4 after removing 70.\n", bst_size(my_bst));
    success_op = bst_remove(my_bst, 50); printf("Removed 50 (root, two children): %s (Expected true)\n", success_op ? "OK" : "Fail");
    print_bst_status(my_bst, "After removing 50 (root)");
    if (bst_contains(my_bst, 50)) printf("ERROR: BST still contains 50 after removal.\n");
    if (bst_size(my_bst) != 3) printf("ERROR: Size is %d, expected 3 after removing 50.\n", bst_size(my_bst));
    success_op = bst_remove(my_bst, 99); printf("Removed 99 (not present): %s (Expected false)\n", !success_op ? "OK" : "Fail"); 
    print_bst_status(my_bst, "After trying to remove 99 (not present)");
    printf("\n[Test 5: Clear Tree]\n");
    bst_clear(my_bst);
    print_bst_status(my_bst, "After clear");
    if (!bst_is_empty(my_bst) || bst_size(my_bst) != 0) {
        printf("ERROR: Tree not empty after clear.\n");
    }
    printf("BST contains 40 after clear: %s (Expected false)\n", bst_contains(my_bst, 40) ? "true" : "false");
    printf("\n[Test 6: Operations on cleared tree]\n");
    success_op = bst_remove(my_bst, 10); printf("Removed 10 from cleared tree: %s (Expected false)\n", !success_op ? "OK" : "Fail"); 
    printf("Contains 10 in cleared tree: %s (Expected false)\n", bst_contains(my_bst, 10) ? "true" : "false");
    int min_val_bst, max_val_bst; 
    min_val_bst = bst_find_min(my_bst, &success_op); if(!success_op) printf("Correctly no min in empty tree.\n"); else printf("Error: Found min %d\n", min_val_bst);
    max_val_bst = bst_find_max(my_bst, &success_op); if(!success_op) printf("Correctly no max in empty tree.\n"); else printf("Error: Found max %d\n", max_val_bst);
    printf("Height of cleared tree: %d (Expected -1)\n", bst_height(my_bst));
    success_op = bst_insert(my_bst, 100); printf("Inserted 100 into cleared tree: %s (Expected true)\n", success_op ? "OK" : "Fail");
    print_bst_status(my_bst, "After inserting 100 into cleared tree");
    printf("\n[Test 7: Destruction]\n");
    bst_destroy(my_bst);
    my_bst = NULL; 
    printf("BST destroyed.\n");
    bst_destroy(NULL);
    printf("bst_destroy(NULL) called, should not crash.\n");
    printf("\n[Test 8: Skewed tree height]\n");
    my_bst = bst_create();
    bst_insert(my_bst, 10);
    bst_insert(my_bst, 20);
    bst_insert(my_bst, 30);
    bst_insert(my_bst, 40);
    print_bst_status(my_bst, "Skewed tree (10,20,30,40)");
    if(bst_height(my_bst) != 3) printf("ERROR: Skewed tree height is %d, expected 3.\n", bst_height(my_bst));
    bst_destroy(my_bst);
    printf("\n===== Binary Search Tree Test Suite Complete =====\n\n");
}

int* rope_to_array(const Rope* r, int* out_length) {
    if (!r || !r->root) { // Check r and r->root
        *out_length = 0;
        return NULL;
    }
    *out_length = rope_get_length(r);
    if (*out_length == 0) {
        return NULL;
    }
    int* arr = (int*)malloc(sizeof(int) * (*out_length));
    if (!arr) {
        *out_length = -1; 
        return NULL;
    }
    bool success;
    for (int i = 0; i < *out_length; ++i) {
        arr[i] = rope_get_element_at(r, i, &success);
        if (!success) {
            free(arr);
            *out_length = -1; 
            return NULL;
        }
    }
    return arr;
}
void print_rope_status(const Rope* r, const char* label) {
    if (!label) label = "Current Rope Status";
    printf("\n--- %s ---\n", label);
    if (!r) {
        printf("Rope is NULL.\n");
        return;
    }
    printf("Total Length: %d\n", rope_get_length(r));
    printf("Elements: [");
    int len;
    int* arr = rope_to_array(r, &len);
    if (arr) {
        for (int i = 0; i < len; ++i) {
            printf("%d%s", arr[i], (i == len - 1) ? "" : ", ");
        }
        free(arr);
    } else if (len == 0 && r->total_length == 0) { // Explicitly check for empty
        // empty
    } else if (len == -1) { // Error from rope_to_array
        printf("Error converting rope to array for printing");
    }
    printf("]\n");
    printf("---------------\n");
}
void test_rope() {
    printf("===== Starting Rope Test Suite =====\n");
    Rope *r1 = NULL, *r2 = NULL, *r_res = NULL;
    Rope *left_split = NULL, *right_split = NULL;
    bool success_op; 
    int item_val;
    printf("\n[Test 1: Creation]\n");
    r1 = rope_create();
    if (r1) printf("rope_create() for empty rope successful.\n");
    else { printf("rope_create() FAILED.\n"); return; }
    print_rope_status(r1, "Empty rope (r1)");
    int arr1[] = {1, 2, 3, 4, 5};
    r2 = rope_create_from_array(arr1, sizeof(arr1)/sizeof(int));
    if (r2) printf("rope_create_from_array() successful for r2.\n");
    else { printf("rope_create_from_array() FAILED for r2.\n"); rope_destroy(r1); return; }
    print_rope_status(r2, "Rope r2 from array {1,2,3,4,5}");
    if(rope_get_length(r2) != 5) printf("ERROR: r2 length is %d, expected 5.\n", rope_get_length(r2));
    printf("\n[Test 2: Get Element At]\n");
    item_val = rope_get_element_at(r2, 0, &success_op);
    if (success_op && item_val == 1) printf("r2[0] = %d (OK)\n", item_val);
    else printf("ERROR: r2[0] get failed or wrong value (%d, success: %d).\n", item_val, success_op);
    item_val = rope_get_element_at(r2, 4, &success_op);
    if (success_op && item_val == 5) printf("r2[4] = %d (OK)\n", item_val);
    else printf("ERROR: r2[4] get failed or wrong value (%d, success: %d).\n", item_val, success_op);
    item_val = rope_get_element_at(r2, 2, &success_op);
    if (success_op && item_val == 3) printf("r2[2] = %d (OK)\n", item_val);
    else printf("ERROR: r2[2] get failed or wrong value (%d, success: %d).\n", item_val, success_op);
    rope_get_element_at(r2, 10, &success_op); 
    if (!success_op) printf("Correctly failed to get element at out-of-bounds index 10.\n");
    else printf("ERROR: Incorrectly got element at out-of-bounds index 10.\n");
    rope_get_element_at(r1, 0, &success_op); 
    if (!success_op) printf("Correctly failed to get element from empty rope r1.\n");
    else printf("ERROR: Incorrectly got element from empty rope r1.\n");
    printf("\n[Test 3: Concatenate]\n");
    Rope* r1_orig_for_concat = rope_create_from_array(NULL, 0); 
    Rope* r2_orig_for_concat = rope_create_from_array(arr1, 5);  
    printf("Concatenating empty r1_orig with r2_orig {1,2,3,4,5}\n");
    r_res = rope_concatenate(r1_orig_for_concat, r2_orig_for_concat);
    // Per definition, r1_orig_for_concat and r2_orig_for_concat Rope structs are now invalid.
    // Their root nodes are part of r_res. Free the structs themselves.
    free(r1_orig_for_concat); r1_orig_for_concat = NULL; 
    free(r2_orig_for_concat); r2_orig_for_concat = NULL; 
    if (!r_res) { printf("Concatenation FAILED. Aborting further concat tests.\n"); rope_destroy(r1); rope_destroy(r2); return; }
    print_rope_status(r_res, "Result of empty_rope + {1,2,3,4,5}");
    if(rope_get_length(r_res) != 5) printf("ERROR: Concat result length %d, expected 5.\n", rope_get_length(r_res));
    rope_destroy(r1); 
    r1 = r_res; r_res = NULL; 
    int arr2[] = {6, 7, 8};
    Rope* r3 = rope_create_from_array(arr2, sizeof(arr2)/sizeof(int)); 
    printf("Concatenating r1 {1,2,3,4,5} with r3 {6,7,8}\n");
    r_res = rope_concatenate(r1, r3); 
    free(r1); r1 = NULL;
    free(r3); r3 = NULL;
    if (!r_res) { printf("Second concatenation FAILED.\n"); rope_destroy(r2); return; } 
    print_rope_status(r_res, "Result of {1,2,3,4,5} + {6,7,8}");
    if(rope_get_length(r_res) != 8) printf("ERROR: Concat result length %d, expected 8.\n", rope_get_length(r_res));
    item_val = rope_get_element_at(r_res, 7, &success_op);
    if (!success_op || item_val != 8) printf("ERROR: Last element of concat is %d, expected 8.\n", item_val);
    printf("\n[Test 4: Split]\n");
    printf("Splitting r_res at index 3 (k=3). Expect left={1,2,3}, right={4,5,6,7,8}\n");
    success_op = rope_split(r_res, 3, &left_split, &right_split);
    // The original r_res struct should be freed by the caller IF it was dynamically allocated AND split "consumes" it.
    // If rope_split creates new ropes and leaves r_res intact (less efficient), then r_res would need separate destroy.
    // Assuming split consumes r_res struct (but reuses nodes):
    free(r_res); r_res = NULL; 
    if (success_op) {
        print_rope_status(left_split, "Left part of split (k=3)");
        print_rope_status(right_split, "Right part of split (k=3)");
        if (rope_get_length(left_split) != 3) printf("ERROR: Left split length is %d, expected 3.\n", rope_get_length(left_split));
        if (rope_get_length(right_split) != 5) printf("ERROR: Right split length is %d, expected 5.\n", rope_get_length(right_split));
        item_val = rope_get_element_at(left_split, 2, &success_op); if(!success_op || item_val != 3) printf("ERR left[2]\n");
        item_val = rope_get_element_at(right_split, 0, &success_op); if(!success_op || item_val != 4) printf("ERR right[0]\n");
    } else {
        printf("Split (k=3) FAILED.\n");
    }
    rope_destroy(left_split); left_split = NULL;
    rope_destroy(right_split); right_split = NULL;
    int arr3[] = {10, 20, 30};
    Rope* r_for_split0 = rope_create_from_array(arr3, 3);
    printf("Splitting {10,20,30} at index 0 (k=0).\n");
    success_op = rope_split(r_for_split0, 0, &left_split, &right_split);
    free(r_for_split0); r_for_split0 = NULL;
    if (success_op) {
        print_rope_status(left_split, "Left part of split (k=0)"); 
        print_rope_status(right_split, "Right part of split (k=0)"); 
        if (rope_get_length(left_split) != 0) printf("ERROR: Left split k=0 length not 0.\n");
        if (rope_get_length(right_split) != 3) printf("ERROR: Right split k=0 length not 3.\n");
    } else { printf("Split (k=0) FAILED.\n"); }
    rope_destroy(left_split); left_split = NULL;
    rope_destroy(right_split); right_split = NULL;
    Rope* r_for_split_end = rope_create_from_array(arr3, 3);
    printf("Splitting {10,20,30} at index 3 (k=length).\n");
    success_op = rope_split(r_for_split_end, 3, &left_split, &right_split);
    free(r_for_split_end); r_for_split_end = NULL;
    if (success_op) {
        print_rope_status(left_split, "Left part of split (k=length)"); 
        print_rope_status(right_split, "Right part of split (k=length)"); 
        if (rope_get_length(left_split) != 3) printf("ERROR: Left split k=len length not 3.\n");
        if (rope_get_length(right_split) != 0) printf("ERROR: Right split k=len length not 0.\n");
    } else { printf("Split (k=length) FAILED.\n"); }
    // Clean up the last pair from split k=length
    rope_destroy(left_split); left_split = NULL;
    rope_destroy(right_split); right_split = NULL;
    printf("\n[Test 5: Final Destruction]\n");
    rope_destroy(r1); // r1 might be NULL if consumed by last concat
    rope_destroy(r2); // r2 was original array, its struct would be freed if consumed.
                      // The original r2 variable was overwritten by create_from_array.
    // Ensure all dynamically created Rope structs in this test are handled.
    // r_res, left_split, right_split should be NULL or destroyed.
    rope_destroy(NULL); 
    printf("Rope test cleanup done.\n");
    printf("\n===== Rope Test Suite Complete =====\n\n");
}

void print_deque_status(const Deque* dq, const char* label) {
    if (!label) label = "Current Deque Status";
    printf("\n--- %s ---\n", label);
    if (!dq) {
        printf("Deque is NULL.\n");
        return;
    }
    printf("Size:     %d\n", deque_size(dq));
    printf("Capacity: %d\n", deque_capacity(dq));
    printf("Is Empty: %s\n", deque_is_empty(dq) ? "Yes" : "No");
    printf("Front Idx: %d\n", dq->front); 
    bool success_peek;
    int first_item = deque_peek_first(dq, &success_peek);
    if (success_peek) {
        printf("First item: %d\n", first_item);
    } else {
        printf("First item: (empty deque)\n");
    }
    int last_item = deque_peek_last(dq, &success_peek);
    if (success_peek) {
        printf("Last item:  %d\n", last_item);
    } else {
        printf("Last item:  (empty deque)\n");
    }
    deque_print(dq); 
    printf("---------------\n");
}
void test_deque() {
    printf("===== Starting Deque Test Suite =====\n");
    Deque* my_dq = NULL;
    bool success_op; 
    int item_val;
    printf("\n[Test 1: Creation]\n");
    my_dq = deque_create(3); 
    if (my_dq) {
        printf("deque_create(3) successful.\n");
    } else {
        printf("deque_create(3) FAILED. Aborting tests.\n");
        return;
    }
    print_deque_status(my_dq, "After creation with capacity 3");
    Deque* zero_cap_dq = deque_create(0);
    if (zero_cap_dq) {
        printf("deque_create(0) successful.\n");
        print_deque_status(zero_cap_dq, "Deque with 0 initial capacity");
        deque_destroy(zero_cap_dq);
    } else {
        printf("deque_create(0) FAILED.\n");
    }
    Deque* neg_cap_dq = deque_create(-1);
    if (neg_cap_dq == NULL) {
        printf("deque_create(-1) correctly returned NULL.\n");
    } else {
        printf("deque_create(-1) FAILED to return NULL.\n");
        deque_destroy(neg_cap_dq);
    }
    printf("\n[Test 2: Add Last]\n");
    success_op = deque_add_last(my_dq, 10); printf("Added 10 last: %s\n", success_op ? "OK" : "Fail");
    success_op = deque_add_last(my_dq, 20); printf("Added 20 last: %s\n", success_op ? "OK" : "Fail");
    print_deque_status(my_dq, "After adding 10, 20 last"); 
    printf("\n[Test 3: Add First]\n");
    success_op = deque_add_first(my_dq, 5); printf("Added 5 first: %s\n", success_op ? "OK" : "Fail");
    print_deque_status(my_dq, "After adding 5 first"); 
    printf("\n[Test 4: Resize on Add First]\n");
    success_op = deque_add_first(my_dq, 1); printf("Added 1 first (triggers resize): %s\n", success_op ? "OK" : "Fail");
    print_deque_status(my_dq, "After adding 1 first (resized)"); 
    printf("\n[Test 5: Resize on Add Last]\n");
    deque_add_last(my_dq, 30);
    success_op = deque_add_last(my_dq, 40); printf("Added 40 last (triggers resize if needed): %s\n", success_op ? "OK" : "Fail");
    print_deque_status(my_dq, "After adding 30, 40 last (check capacity)");
    printf("\n[Test 6: Peek Operations]\n");
    item_val = deque_peek_first(my_dq, &success_op);
    if (success_op) printf("Peek first: %d (Expected 1)\n", item_val); else printf("Peek first FAILED.\n");
    item_val = deque_peek_last(my_dq, &success_op);
    if (success_op) printf("Peek last: %d (Expected 40)\n", item_val); else printf("Peek last FAILED.\n");
    print_deque_status(my_dq, "After peeks (no change)");
    printf("\n[Test 7: Remove First]\n");
    item_val = deque_remove_first(my_dq, &success_op);
    if (success_op) printf("Removed first: %d (Expected 1)\n", item_val); else printf("Remove first FAILED.\n");
    print_deque_status(my_dq, "After removing 1 first"); 
    printf("\n[Test 8: Remove Last]\n");
    item_val = deque_remove_last(my_dq, &success_op);
    if (success_op) printf("Removed last: %d (Expected 40)\n", item_val); else printf("Remove last FAILED.\n");
    print_deque_status(my_dq, "After removing 40 last"); 
    printf("\n[Test 9: Mixed Operations & Wrap-around]\n");
    // Re-create for deterministic wrap test
    deque_destroy(my_dq); my_dq = deque_create(3);
    deque_add_last(my_dq, 100); deque_add_last(my_dq, 200); // [100,200,_] S=2,F=0,C=3
    deque_remove_first(my_dq, &success_op); // [_,200,_] S=1,F=1,C=3
    deque_add_first(my_dq, 50); // [50,200,_] S=2,F=0,C=3
    deque_add_last(my_dq, 300); // [50,200,300] S=3,F=0,C=3 (Full)
    print_deque_status(my_dq, "After mixed ops to fill: [50,200,300]");
    item_val = deque_remove_first(my_dq, &success_op); printf("Removed first: %d (Exp 50)\n", item_val); // [_,200,300] S=2,F=1,C=3
    deque_add_last(my_dq, 400); // Wrap: [400,200,300] S=3,F=1,C=3
    print_deque_status(my_dq, "After remove then add_last (wrap): [200,300,400] logical");
    printf("\n[Test 10: Clear Deque]\n");
    deque_clear(my_dq);
    print_deque_status(my_dq, "After clear");
    if (!deque_is_empty(my_dq) || deque_size(my_dq) != 0) printf("ERROR: Deque not empty after clear.\n");
    printf("\n[Test 11: Operations on empty deque]\n");
    item_val = deque_peek_first(my_dq, &success_op); if(!success_op) printf("Correctly failed peek_first.\n"); else printf("ERR: peek_first on empty\n");
    item_val = deque_peek_last(my_dq, &success_op);  if(!success_op) printf("Correctly failed peek_last.\n");  else printf("ERR: peek_last on empty\n");
    item_val = deque_remove_first(my_dq, &success_op);if(!success_op) printf("Correctly failed remove_first.\n");else printf("ERR: remove_first on empty\n");
    item_val = deque_remove_last(my_dq, &success_op); if(!success_op) printf("Correctly failed remove_last.\n"); else printf("ERR: remove_last on empty\n");
    deque_add_first(my_dq, 100);
    deque_add_last(my_dq, 200);
    print_deque_status(my_dq, "After adding 100 (first), 200 (last) to empty deque"); 
    printf("\n[Test 12: Reserve]\n");
    int current_cap_deque = deque_capacity(my_dq); 
    deque_reserve(my_dq, current_cap_deque + 5);
    print_deque_status(my_dq, "After reserving more capacity");
    if(deque_capacity(my_dq) != current_cap_deque + 5) printf("ERROR: Reserve capacity mismatch.\n");
    int peek_val_first_dq = deque_peek_first(my_dq, &success_op); bool s1_dq = success_op; // Renamed
    int peek_val_last_dq = deque_peek_last(my_dq, &success_op); bool s2_dq = success_op; // Renamed
    if(deque_size(my_dq) != 2 || !s1_dq || peek_val_first_dq!=100 || !s2_dq || peek_val_last_dq!=200) {
        printf("ERROR: Elements incorrect after reserve.\n");
    }
    deque_destroy(my_dq);
    my_dq = deque_create(3);
    deque_add_last(my_dq, 1); 
    deque_add_last(my_dq, 2); 
    deque_remove_first(my_dq,&success_op); 
    deque_add_last(my_dq, 3); 
    deque_add_last(my_dq, 4); 
    print_deque_status(my_dq, "Wrapped deque: [2,3,4] (Logical)");
    success_op = deque_reserve(my_dq, 5);
    printf("Reserve(5) on wrapped: %s\n", success_op ? "OK" : "FAIL");
    print_deque_status(my_dq, "After reserve(5) on wrapped deque (should be unrolled)");
    printf("\n[Test 13: Destruction]\n");
    deque_destroy(my_dq);
    my_dq = NULL; 
    printf("Deque destroyed.\n");
    deque_destroy(NULL);
    printf("deque_destroy(NULL) called, should not crash.\n");
    printf("\n===== Deque Test Suite Complete =====\n\n");
}

void print_binary_heap_status(const BinaryHeap* heap, const char* label) {
    if (!label) label = "Current Binary Heap Status";
    printf("\n--- %s ---\n", label);
    if (!heap) {
        printf("Heap is NULL.\n");
        return;
    }
    printf("Size:     %d\n", binary_heap_size(heap));
    printf("Capacity: %d\n", binary_heap_capacity(heap));
    printf("Is Empty: %s\n", binary_heap_is_empty(heap) ? "Yes" : "No");
    bool success_peek;
    int min_item = binary_heap_peek_min(heap, &success_peek);
    if (success_peek) {
        printf("Min item (Root): %d\n", min_item);
    } else {
        printf("Min item (Root): (empty heap)\n");
    }
    binary_heap_print_array(heap); 
    printf("---------------\n");
}
void test_binary_heap() {
    printf("===== Starting Binary Min-Heap Test Suite =====\n");
    BinaryHeap* my_heap = NULL;
    bool success_op; 
    int item_val;
    printf("\n[Test 1: Creation]\n");
    my_heap = binary_heap_create(5); 
    if (my_heap) {
        printf("binary_heap_create(5) successful.\n");
    } else {
        printf("binary_heap_create(5) FAILED. Aborting tests.\n");
        return;
    }
    print_binary_heap_status(my_heap, "After creation with capacity 5");
    BinaryHeap* zero_cap_heap = binary_heap_create(0);
    if (zero_cap_heap) {
        printf("binary_heap_create(0) successful.\n");
        print_binary_heap_status(zero_cap_heap, "Heap with 0 initial capacity");
        binary_heap_destroy(zero_cap_heap);
    } else {
        printf("binary_heap_create(0) FAILED.\n");
    }
    BinaryHeap* neg_cap_heap = binary_heap_create(-1);
    if (neg_cap_heap == NULL) {
        printf("binary_heap_create(-1) correctly returned NULL.\n");
    } else {
        printf("binary_heap_create(-1) FAILED to return NULL.\n");
        binary_heap_destroy(neg_cap_heap);
    }
    printf("\n[Test 2: Insertions]\n");
    binary_heap_insert(my_heap, 10);
    binary_heap_insert(my_heap, 4);
    binary_heap_insert(my_heap, 15);
    binary_heap_insert(my_heap, 20);
    binary_heap_insert(my_heap, 1); 
    print_binary_heap_status(my_heap, "After inserting 10, 4, 15, 20, 1");
    item_val = binary_heap_peek_min(my_heap, &success_op);
    if (!success_op || item_val != 1) printf("ERROR: Min element is %d, expected 1.\n", item_val);
    printf("\n[Test 3: Resize on Insert]\n");
    binary_heap_insert(my_heap, 30); 
    binary_heap_insert(my_heap, 0);  
    print_binary_heap_status(my_heap, "After inserting 30, 0 (resized, 0 is new min)");
    item_val = binary_heap_peek_min(my_heap, &success_op);
    if (!success_op || item_val != 0) printf("ERROR: Min element is %d, expected 0 after resize.\n", item_val);
    printf("\n[Test 4: Extract Min]\n");
    item_val = binary_heap_extract_min(my_heap, &success_op);
    if (success_op) printf("Extracted min: %d (Expected 0)\n", item_val); else printf("Extract min FAILED.\n");
    print_binary_heap_status(my_heap, "After extracting 0");
    item_val = binary_heap_peek_min(my_heap, &success_op);
    if(!success_op || item_val != 1) printf("ERROR: New min is %d, expected 1.\n", item_val);
    item_val = binary_heap_extract_min(my_heap, &success_op);
    if (success_op) printf("Extracted min: %d (Expected 1)\n", item_val); else printf("Extract min FAILED.\n");
    print_binary_heap_status(my_heap, "After extracting 1");
    item_val = binary_heap_peek_min(my_heap, &success_op);
    if(success_op) printf("New min after extracting 1 is %d.\n", item_val);
    printf("\n[Test 5: Extract all elements in order]\n");
    printf("Extracting all remaining elements: ");
    int last_extracted_bh = -1; // Renamed
    bool order_ok_bh = true;    // Renamed
    while(!binary_heap_is_empty(my_heap)) {
        item_val = binary_heap_extract_min(my_heap, &success_op);
        if (success_op) {
            printf("%d ", item_val);
            if (last_extracted_bh != -1 && item_val < last_extracted_bh) {
                order_ok_bh = false;
            }
            last_extracted_bh = item_val;
        } else {
            printf("\nERROR: Extraction failed prematurely.\n");
            order_ok_bh = false;
            break;
        }
    }
    printf("\nExtraction order correct: %s\n", order_ok_bh ? "Yes" : "No");
    print_binary_heap_status(my_heap, "After extracting all elements (empty)");
    printf("\n[Test 6: Operations on empty heap]\n");
    item_val = binary_heap_peek_min(my_heap, &success_op);
    if(!success_op) printf("Correctly failed to peek_min from empty heap.\n"); else printf("ERR: peek_min on empty.\n");
    item_val = binary_heap_extract_min(my_heap, &success_op);
    if(!success_op) printf("Correctly failed to extract_min from empty heap.\n"); else printf("ERR: extract_min on empty.\n");
    printf("\n[Test 7: Clear Heap]\n");
    binary_heap_insert(my_heap, 50);
    binary_heap_insert(my_heap, 25);
    print_binary_heap_status(my_heap, "Before clear");
    int capacity_before_clear_bh = binary_heap_capacity(my_heap); 
    binary_heap_clear(my_heap);
    print_binary_heap_status(my_heap, "After clear");
    if (!binary_heap_is_empty(my_heap) || binary_heap_size(my_heap) != 0) printf("ERROR: Heap not empty after clear.\n");
    if (binary_heap_capacity(my_heap) != capacity_before_clear_bh) {
        printf("ERROR: Capacity changed after clear. Was %d, now %d.\n", capacity_before_clear_bh, binary_heap_capacity(my_heap));
    }
    printf("\n[Test 8: Destruction]\n");
    binary_heap_destroy(my_heap);
    my_heap = NULL; 
    printf("Binary Heap destroyed.\n");
    binary_heap_destroy(NULL);
    printf("binary_heap_destroy(NULL) called, should not crash.\n");
    printf("\n===== Binary Min-Heap Test Suite Complete =====\n\n");
}

void print_dsu_status(DSU* dsu, const char* label) {
    if (!label) label = "Current DSU Status";
    printf("\n--- %s ---\n", label);
    if (!dsu) {
        printf("DSU is NULL.\n");
        return;
    }
    printf("Total Elements: %d\n", dsu->num_elements);
    printf("Number of Sets: %d\n", dsu_get_num_sets(dsu));
    dsu_print_parents(dsu); 
    if (dsu->num_elements > 0 && dsu->num_elements < 20) { 
        printf("Element details (id -> representative (size of set)):\n");
        for (int i = 0; i < dsu->num_elements; ++i) {
            int root = dsu_find(dsu, i); 
            int size_of_set = dsu_get_set_size(dsu, i); 
            printf("  %d -> %d (size %d)\n", i, root, size_of_set);
        }
    }
    printf("---------------\n");
}
void test_disjoint_set_union() {
    printf("===== Starting Disjoint Set Union Test Suite =====\n");
    DSU* my_dsu = NULL;
    const int num_items_dsu = 10; 
    printf("\n[Test 1: Creation]\n");
    my_dsu = dsu_create(num_items_dsu);
    if (my_dsu) {
        printf("dsu_create(%d) successful.\n", num_items_dsu);
    } else {
        printf("dsu_create(%d) FAILED. Aborting tests.\n", num_items_dsu);
        return;
    }
    if (dsu_get_num_sets(my_dsu) != num_items_dsu) {
        printf("ERROR: Initial number of sets is %d, expected %d.\n", dsu_get_num_sets(my_dsu), num_items_dsu);
    }
    for(int i=0; i < num_items_dsu; ++i) {
        if(dsu_get_set_size(my_dsu, i) != 1) {
             printf("ERROR: Initial size of set for element %d is %d, expected 1.\n", i, dsu_get_set_size(my_dsu, i));
        }
    }
    print_dsu_status(my_dsu, "After creation");
    DSU* zero_dsu = dsu_create(0);
    if(zero_dsu) {
        printf("dsu_create(0) successful. Num sets: %d\n", dsu_get_num_sets(zero_dsu));
        dsu_destroy(zero_dsu);
    } else {
        printf("dsu_create(0) FAILED.\n");
    }
    DSU* neg_dsu = dsu_create(-1);
    if (neg_dsu == NULL) {
        printf("dsu_create(-1) correctly returned NULL.\n");
    } else {
        printf("dsu_create(-1) FAILED to return NULL.\n");
        dsu_destroy(neg_dsu);
    }
    printf("\n[Test 2: Union and Find Operations]\n");
    bool union_res;
    union_res = dsu_union_sets(my_dsu, 0, 1); printf("Union(0,1): %s (Exp true). Sets: %d\n", union_res?"OK":"Fail", dsu_get_num_sets(my_dsu)); 
    union_res = dsu_union_sets(my_dsu, 2, 3); printf("Union(2,3): %s (Exp true). Sets: %d\n", union_res?"OK":"Fail", dsu_get_num_sets(my_dsu)); 
    union_res = dsu_union_sets(my_dsu, 0, 2); printf("Union(0,2): %s (Exp true). Sets: %d\n", union_res?"OK":"Fail", dsu_get_num_sets(my_dsu)); 
    print_dsu_status(my_dsu, "After unions (0,1), (2,3), (0,2)");
    if (!dsu_are_in_same_set(my_dsu, 0, 3)) printf("ERROR: 0 and 3 should be in the same set.\n");
    if (dsu_get_set_size(my_dsu, 0) != 4) printf("ERROR: Size of set containing 0 is %d, expected 4.\n", dsu_get_set_size(my_dsu, 0));
    dsu_union_sets(my_dsu, 5, 6); 
    dsu_union_sets(my_dsu, 7, 8); 
    dsu_union_sets(my_dsu, 5, 8); 
    print_dsu_status(my_dsu, "After unions (5,6), (7,8), (5,8)");
    if (!dsu_are_in_same_set(my_dsu, 5, 7)) printf("ERROR: 5 and 7 should be in the same set.\n");
    if (dsu_get_set_size(my_dsu, 5) != 4) printf("ERROR: Size of set containing 5 is %d, expected 4.\n", dsu_get_set_size(my_dsu, 5));
    union_res = dsu_union_sets(my_dsu, 0, 0); printf("Union(0,0): %s (Exp false). Sets: %d\n", !union_res?"OK":"Fail", dsu_get_num_sets(my_dsu)); 
    union_res = dsu_union_sets(my_dsu, 1, 3); printf("Union(1,3): %s (Exp false). Sets: %d\n", !union_res?"OK":"Fail", dsu_get_num_sets(my_dsu)); 
    print_dsu_status(my_dsu, "After redundant unions");
    printf("\n[Test 3: Path Compression Check]\n");
    printf("Find(0): %d\n", dsu_find(my_dsu, 0));
    printf("Find(6): %d\n", dsu_find(my_dsu, 6));
    print_dsu_status(my_dsu, "After some find operations (check parent array for compression)");
    printf("\n[Test 4: Are In Same Set]\n");
    printf("Are 0 and 3 in same set? %s (Expected true)\n", dsu_are_in_same_set(my_dsu, 0, 3) ? "Yes" : "No");
    printf("Are 5 and 6 in same set? %s (Expected true)\n", dsu_are_in_same_set(my_dsu, 5, 6) ? "Yes" : "No");
    printf("Are 0 and 5 in same set? %s (Expected false)\n", dsu_are_in_same_set(my_dsu, 0, 5) ? "Yes" : "No");
    printf("Are 9 and 0 in same set? %s (Expected false, 9 is isolated)\n", dsu_are_in_same_set(my_dsu, 9, 0) ? "Yes" : "No");
    printf("\n[Test 5: Number of Sets]\n");
    if (dsu_get_num_sets(my_dsu) != 4) {
        printf("ERROR: Number of sets is %d, expected 4.\n", dsu_get_num_sets(my_dsu));
    } else {
        printf("Correct number of sets: %d\n", dsu_get_num_sets(my_dsu));
    }
    dsu_union_sets(my_dsu, 4, 9); 
    print_dsu_status(my_dsu, "After unioning 4 and 9");
    if (dsu_get_num_sets(my_dsu) != 3) printf("ERROR: Number of sets is %d, expected 3.\n", dsu_get_num_sets(my_dsu));
    if (dsu_get_set_size(my_dsu, 4) != 2) printf("ERROR: Size of set for 4 is %d, expected 2.\n", dsu_get_set_size(my_dsu, 4));
    dsu_union_sets(my_dsu, 0, 5); 
    dsu_union_sets(my_dsu, 0, 4); 
    print_dsu_status(my_dsu, "After unioning all sets together");
    if (dsu_get_num_sets(my_dsu) != 1) printf("ERROR: Number of sets is %d, expected 1.\n", dsu_get_num_sets(my_dsu));
    if (dsu_get_set_size(my_dsu, 0) != num_items_dsu) printf("ERROR: Size of final set is %d, expected %d.\n", dsu_get_set_size(my_dsu, 0), num_items_dsu);
    printf("\n[Test 6: Out of Bounds Access]\n");
    int invalid_find_dsu = dsu_find(my_dsu, num_items_dsu + 5); // Renamed
    if (invalid_find_dsu == -1) printf("Correctly handled find for out-of-bounds ID (%d -> %d).\n", num_items_dsu + 5, invalid_find_dsu);
    else printf("ERROR: Find for out-of-bounds ID %d returned %d, expected error indicator.\n", num_items_dsu + 5, invalid_find_dsu);
    bool invalid_union_dsu = dsu_union_sets(my_dsu, 0, num_items_dsu + 5); // Renamed
    if (!invalid_union_dsu) printf("Correctly handled union with out-of-bounds ID.\n");
    else printf("ERROR: Union with out-of-bounds ID succeeded.\n");
    printf("\n[Test 7: Destruction]\n");
    dsu_destroy(my_dsu);
    my_dsu = NULL; 
    printf("DSU destroyed.\n");
    dsu_destroy(NULL);
    printf("dsu_destroy(NULL) called, should not crash.\n");
    printf("\n===== Disjoint Set Union Test Suite Complete =====\n\n");
}

void print_trie_status(const Trie* trie_ptr, const char* label) {
    if (!label) label = "Current Trie Status";
    printf("\n--- %s ---\n", label);
    if (!trie_ptr || !trie_ptr->root) {
        printf("Trie is NULL or root is NULL (effectively empty).\n");
        return;
    }
    printf("Trie root exists. (Detailed print requires traversal logic within trie.c)\n");
    if (trie_ptr->root) { // Check if root is not NULL before accessing its members
      printf("Root pass_through_count: %d\n", trie_ptr->root->count_pass_through);
    }
    printf("---------------\n");
}
void test_trie() {
    printf("===== Starting Bitwise Trie Test Suite =====\n");
    Trie* my_trie = NULL;
    bool success_op; 
    printf("\n[Test 1: Creation]\n");
    my_trie = trie_create();
    if (my_trie && my_trie->root) {
        printf("trie_create() successful, root node allocated.\n");
    } else {
        printf("trie_create() FAILED. Aborting tests.\n");
        if(my_trie) trie_destroy(my_trie); 
        return;
    }
    print_trie_status(my_trie, "After creation");
    if (my_trie->root->count_pass_through != 0) {
         printf("ERROR: Root count_pass_through should be 0 for an empty trie.\n");
    }
    printf("\n[Test 2: Insertions]\n");
    success_op = trie_insert(my_trie, 5);  printf("Inserted 5:  %s (Expected true)\n", success_op ? "OK" : "Fail");
    success_op = trie_insert(my_trie, 9);  printf("Inserted 9:  %s (Expected true)\n", success_op ? "OK" : "Fail");
    success_op = trie_insert(my_trie, 10); printf("Inserted 10: %s (Expected true)\n", success_op ? "OK" : "Fail");
    success_op = trie_insert(my_trie, 25); printf("Inserted 25: %s (Expected true)\n", success_op ? "OK" : "Fail");
    print_trie_status(my_trie, "After inserting 5, 9, 10, 25");
    success_op = trie_insert(my_trie, 9); printf("Inserted 9 again: %s (Expected false, already present)\n", !success_op ? "OK" : "Fail"); 
    print_trie_status(my_trie, "After trying to insert 9 again");
    success_op = trie_insert(my_trie, -1); printf("Inserted -1: %s (Expected false, invalid)\n", !success_op ? "OK" : "Fail"); 
    printf("\n[Test 3: Contains]\n");
    printf("Trie contains 5:  %s (Expected true)\n", trie_contains(my_trie, 5) ? "true" : "false");
    printf("Trie contains 10: %s (Expected true)\n", trie_contains(my_trie, 10) ? "true" : "false");
    printf("Trie contains 25: %s (Expected true)\n", trie_contains(my_trie, 25) ? "true" : "false");
    printf("Trie contains 7:  %s (Expected false)\n", trie_contains(my_trie, 7) ? "true" : "false");
    printf("Trie contains 0:  %s (Expected false, unless 0 was inserted)\n", trie_contains(my_trie, 0) ? "true" : "false");
    trie_insert(my_trie, 0);
    printf("Trie contains 0 (after insert): %s (Expected true)\n", trie_contains(my_trie, 0) ? "true" : "false");
    print_trie_status(my_trie, "After inserting 0");
    printf("\n[Test 4: Removals]\n");
    success_op = trie_remove(my_trie, 10); printf("Removed 10: %s (Expected true)\n", success_op ? "OK" : "Fail");
    print_trie_status(my_trie, "After removing 10");
    if (trie_contains(my_trie, 10)) printf("ERROR: Trie still contains 10 after removal.\n");
    success_op = trie_remove(my_trie, 7); printf("Removed 7 (not present): %s (Expected false)\n", !success_op ? "OK" : "Fail"); 
    print_trie_status(my_trie, "After trying to remove 7");
    success_op = trie_remove(my_trie, 9); printf("Removed 9: %s (Expected true)\n", success_op ? "OK" : "Fail");
    print_trie_status(my_trie, "After removing 9");
    if (trie_contains(my_trie, 9)) printf("ERROR: Trie still contains 9 after removal.\n");
    if (!trie_contains(my_trie, 5)) printf("ERROR: Trie should still contain 5.\n");
    if (!trie_contains(my_trie, 25)) printf("ERROR: Trie should still contain 25.\n");
    trie_remove(my_trie, 0);
    trie_remove(my_trie, 5);
    trie_remove(my_trie, 25);
    print_trie_status(my_trie, "After removing all (0, 5, 25) - should be empty or only root");
    if (my_trie->root && my_trie->root->count_pass_through != 0) { 
         printf("ERROR: Root count_pass_through should be 0 after removing all elements.\n");
    }
    printf("\n[Test 5: Find Max XOR]\n");
    trie_insert(my_trie, 3);  
    trie_insert(my_trie, 7);  
    trie_insert(my_trie, 11); 
    trie_insert(my_trie, 13); 
    print_trie_status(my_trie, "Trie for Max XOR: {3, 7, 11, 13}");
    int query_trie = 6; // Renamed
    int result_xor_val_trie; // Renamed
    bool found_xor_trie; // Renamed
    result_xor_val_trie = trie_find_max_xor(my_trie, query_trie, &found_xor_trie);
    if (found_xor_trie) {
        printf("Max XOR with %d is %d (achieved with %d, XOR result %d)\n", query_trie, result_xor_val_trie ^ query_trie, result_xor_val_trie, result_xor_val_trie ^ query_trie);
        if (result_xor_val_trie != 11 || (result_xor_val_trie ^ query_trie) != 13) { 
            printf("ERROR: Max XOR for %d was %d (val %d), expected value 11 for XOR result 13.\n", query_trie, result_xor_val_trie ^ query_trie, result_xor_val_trie);
        }
    } else {
        printf("Max XOR for %d not found (trie might be empty or issue).\n", query_trie);
    }
    query_trie = 15; 
    result_xor_val_trie = trie_find_max_xor(my_trie, query_trie, &found_xor_trie);
     if (found_xor_trie) {
        printf("Max XOR with %d is %d (achieved with %d, XOR result %d)\n", query_trie, result_xor_val_trie ^ query_trie, result_xor_val_trie, result_xor_val_trie ^ query_trie);
        if (result_xor_val_trie != 3 || (result_xor_val_trie ^ query_trie) != 12) { 
            printf("ERROR: Max XOR for %d was %d (val %d), expected value 3 for XOR result 12.\n", query_trie, result_xor_val_trie ^ query_trie, result_xor_val_trie);
        }
    } else {
        printf("Max XOR for %d not found.\n", query_trie);
    }
    printf("\n[Test 6: Destruction]\n");
    trie_destroy(my_trie);
    my_trie = NULL; 
    printf("Trie destroyed.\n");
    trie_destroy(NULL);
    printf("trie_destroy(NULL) called, should not crash.\n");
    printf("\n===== Bitwise Trie Test Suite Complete =====\n\n");
}

void print_graph_adj_list_status(const GraphAdjList* graph, const char* label) { // Renamed helper
    if (!label) label = "Current Graph (AdjList) Status";
    printf("\n--- %s ---\n", label);
    if (!graph) {
        printf("Graph (AdjList) is NULL.\n");
        return;
    }
    printf("Number of Vertices: %d\n", graph_adj_list_get_num_vertices(graph));
    graph_adj_list_print(graph); 
    printf("---------------\n");
}
void test_graph_adj_list() {
    printf("===== Starting Graph (Adjacency List) Test Suite =====\n");
    GraphAdjList* my_graph_al = NULL; 
    const int num_v_al = 6; 
    printf("\n[Test 1: Creation]\n");
    my_graph_al = graph_adj_list_create(num_v_al);
    if (my_graph_al) {
        printf("graph_adj_list_create(%d) successful.\n", num_v_al);
    } else {
        printf("graph_adj_list_create(%d) FAILED. Aborting tests.\n", num_v_al);
        return;
    }
    print_graph_adj_list_status(my_graph_al, "After creation (AdjList)"); // Use renamed helper
    GraphAdjList* zero_g_al = graph_adj_list_create(0); 
    if (zero_g_al) printf("graph_adj_list_create(0) ok.\n"); else printf("graph_adj_list_create(0) FAILED.\n");
    graph_adj_list_destroy(zero_g_al);
    GraphAdjList* neg_g_al = graph_adj_list_create(-1); 
    if (neg_g_al == NULL) printf("graph_adj_list_create(-1) correctly NULL.\n"); else { printf("graph_adj_list_create(-1) FAILED to be NULL.\n"); graph_adj_list_destroy(neg_g_al); }
    printf("\n[Test 2: Add Edges]\n");
    graph_adj_list_add_edge(my_graph_al, 0, 1);
    graph_adj_list_add_edge(my_graph_al, 0, 3);
    graph_adj_list_add_edge(my_graph_al, 1, 2);
    graph_adj_list_add_edge(my_graph_al, 1, 4);
    graph_adj_list_add_edge(my_graph_al, 3, 4);
    graph_adj_list_add_edge(my_graph_al, 4, 5);
    printf("Added edges for a sample graph.\n");
    print_graph_adj_list_status(my_graph_al, "After adding initial edges (AdjList)");
    bool add_dup_al = graph_adj_list_add_edge(my_graph_al, 0, 1); 
    printf("Attempted to add duplicate edge (0,1): Should be present (returned %s).\n", add_dup_al ? "true/ok":"false/fail");
    bool add_invalid_al = graph_adj_list_add_edge(my_graph_al, 0, num_v_al + 1); 
    if (!add_invalid_al) printf("Correctly failed to add edge with out-of-bounds vertex.\n");
    else printf("ERROR: Succeeded adding edge with out-of-bounds vertex.\n");
    printf("\n[Test 3: Has Edge]\n");
    printf("Has edge (0,1)? %s (Expected true)\n", graph_adj_list_has_edge(my_graph_al, 0, 1) ? "Yes" : "No");
    printf("Has edge (1,0)? %s (Expected true - undirected)\n", graph_adj_list_has_edge(my_graph_al, 1, 0) ? "Yes" : "No");
    printf("Has edge (0,5)? %s (Expected false)\n", graph_adj_list_has_edge(my_graph_al, 0, 5) ? "Yes" : "No");
    printf("Has edge (4,5)? %s (Expected true)\n", graph_adj_list_has_edge(my_graph_al, 4, 5) ? "Yes" : "No");
    printf("Has edge (0, num_v_al+1)? %s (Expected false - out of bounds)\n", graph_adj_list_has_edge(my_graph_al, 0, num_v_al+1) ? "Yes" : "No");
    printf("\n[Test 4: Remove Edge]\n");
    bool remove_res_al = graph_adj_list_remove_edge(my_graph_al, 1, 4); 
    printf("Removed edge (1,4): %s (Expected true)\n", remove_res_al ? "OK" : "Fail");
    print_graph_adj_list_status(my_graph_al, "After removing edge (1,4) (AdjList)");
    if (graph_adj_list_has_edge(my_graph_al, 1, 4)) printf("ERROR: Edge (1,4) still exists after removal.\n");
    if (graph_adj_list_has_edge(my_graph_al, 4, 1)) printf("ERROR: Edge (4,1) still exists after removal.\n");
    remove_res_al = graph_adj_list_remove_edge(my_graph_al, 0, 5); 
    printf("Attempted to remove non-existent edge (0,5): %s (Expected false)\n", !remove_res_al ? "OK" : "Fail"); 
    printf("\n[Test 5: BFS Traversal]\n");
    GraphVisitData bfs_data_al = {0}; 
    printf("BFS from vertex 0 (AdjList): [");
    graph_adj_list_bfs(my_graph_al, 0, graph_node_visit_printer, &bfs_data_al); // Use generic printer
    printf("]\n");
    printf("\n[Test 6: DFS Traversal]\n");
    GraphVisitData dfs_data_al = {0}; 
    printf("DFS from vertex 0 (AdjList): [");
    graph_adj_list_dfs(my_graph_al, 0, graph_node_visit_printer, &dfs_data_al); // Use generic printer
    printf("]\n");
    printf("\n[Test 7: Destruction]\n");
    graph_adj_list_destroy(my_graph_al);
    my_graph_al = NULL; 
    printf("Graph (AdjList) destroyed.\n");
    graph_adj_list_destroy(NULL);
    printf("graph_adj_list_destroy(NULL) called, should not crash.\n");
    printf("\n===== Graph (Adjacency List) Test Suite Complete =====\n\n");
}

void print_graph_adj_matrix_status(const GraphAdjMatrix* graph, const char* label) { // Renamed helper
    if (!label) label = "Current Graph (AdjMatrix) Status";
    printf("\n--- %s ---\n", label);
    if (!graph) {
        printf("Graph (AdjMatrix) is NULL.\n");
        return;
    }
    printf("Number of Vertices: %d\n", graph_adj_matrix_get_num_vertices(graph));
    graph_adj_matrix_print(graph); 
    printf("---------------\n");
}
void test_graph_adj_matrix() {
    printf("===== Starting Graph (Adjacency Matrix) Test Suite =====\n");
    GraphAdjMatrix* my_graph_am = NULL; 
    const int num_v_am = 5; 
    printf("\n[Test 1: Creation]\n");
    my_graph_am = graph_adj_matrix_create(num_v_am);
    if (my_graph_am) {
        printf("graph_adj_matrix_create(%d) successful.\n", num_v_am);
    } else {
        printf("graph_adj_matrix_create(%d) FAILED. Aborting tests.\n", num_v_am);
        return;
    }
    print_graph_adj_matrix_status(my_graph_am, "After creation (AdjMatrix - all zeros)"); // Use renamed helper
    GraphAdjMatrix* zero_g_am = graph_adj_matrix_create(0); 
    if (zero_g_am) printf("graph_adj_matrix_create(0) ok.\n"); else printf("graph_adj_matrix_create(0) FAILED.\n");
    graph_adj_matrix_destroy(zero_g_am);
    GraphAdjMatrix* neg_g_am = graph_adj_matrix_create(-1); 
    if (neg_g_am == NULL) printf("graph_adj_matrix_create(-1) correctly NULL.\n"); else { printf("graph_adj_matrix_create(-1) FAILED to be NULL.\n"); graph_adj_matrix_destroy(neg_g_am); }
    printf("\n[Test 2: Add Edges]\n");
    graph_adj_matrix_add_edge(my_graph_am, 0, 1);
    graph_adj_matrix_add_edge(my_graph_am, 0, 2);
    graph_adj_matrix_add_edge(my_graph_am, 1, 2);
    graph_adj_matrix_add_edge(my_graph_am, 1, 4);
    graph_adj_matrix_add_edge(my_graph_am, 2, 4);
    printf("Added edges for a sample graph.\n");
    print_graph_adj_matrix_status(my_graph_am, "After adding initial edges (AdjMatrix)");
    bool add_dup_am = graph_adj_matrix_add_edge(my_graph_am, 0, 1); 
    printf("Attempted to add duplicate edge (0,1): returned %s (should be true).\n", add_dup_am ? "true/ok":"false/fail");
    bool add_invalid_am = graph_adj_matrix_add_edge(my_graph_am, 0, num_v_am + 1); 
    if (!add_invalid_am) printf("Correctly failed to add edge with out-of-bounds vertex.\n");
    else printf("ERROR: Succeeded adding edge with out-of-bounds vertex.\n");
    printf("\n[Test 3: Has Edge]\n");
    printf("Has edge (0,1)? %s (Expected true)\n", graph_adj_matrix_has_edge(my_graph_am, 0, 1) ? "Yes" : "No");
    printf("Has edge (1,0)? %s (Expected true - undirected)\n", graph_adj_matrix_has_edge(my_graph_am, 1, 0) ? "Yes" : "No");
    printf("Has edge (0,3)? %s (Expected false)\n", graph_adj_matrix_has_edge(my_graph_am, 0, 3) ? "Yes" : "No");
    printf("Has edge (2,4)? %s (Expected true)\n", graph_adj_matrix_has_edge(my_graph_am, 2, 4) ? "Yes" : "No");
    printf("Has edge (0, num_v_am+1)? %s (Expected false - out of bounds handled by has_edge)\n", graph_adj_matrix_has_edge(my_graph_am, 0, num_v_am+1) ? "Yes" : "No");
    printf("\n[Test 4: Remove Edge]\n");
    bool remove_res_am = graph_adj_matrix_remove_edge(my_graph_am, 1, 2); 
    printf("Removed edge (1,2): %s (Expected true)\n", remove_res_am ? "OK" : "Fail");
    print_graph_adj_matrix_status(my_graph_am, "After removing edge (1,2) (AdjMatrix)");
    if (graph_adj_matrix_has_edge(my_graph_am, 1, 2)) printf("ERROR: Edge (1,2) still exists after removal.\n");
    remove_res_am = graph_adj_matrix_remove_edge(my_graph_am, 0, 3); 
    printf("Attempted to remove non-existent edge (0,3): %s (Expected true, cells set to 0)\n", remove_res_am ? "OK" : "Fail");
    printf("\n[Test 5: BFS Traversal]\n");
    GraphVisitData bfs_data_am = {0}; 
    printf("BFS from vertex 0 (AdjMatrix): [");
    graph_adj_matrix_bfs(my_graph_am, 0, graph_node_visit_printer, &bfs_data_am); // Use generic printer
    printf("]\n");
    GraphVisitData bfs_data_isolated_am = {0}; 
    printf("BFS from vertex 3 (isolated) (AdjMatrix): [");
    graph_adj_matrix_bfs(my_graph_am, 3, graph_node_visit_printer, &bfs_data_isolated_am);
    printf("]\n"); 
    printf("\n[Test 6: DFS Traversal]\n");
    GraphVisitData dfs_data_am = {0}; 
    printf("DFS from vertex 0 (AdjMatrix): [");
    graph_adj_matrix_dfs(my_graph_am, 0, graph_node_visit_printer, &dfs_data_am);
    printf("]\n");
    printf("\n[Test 7: Destruction]\n");
    graph_adj_matrix_destroy(my_graph_am);
    my_graph_am = NULL; 
    printf("Graph (AdjMatrix) destroyed.\n");
    graph_adj_matrix_destroy(NULL);
    printf("graph_adj_matrix_destroy(NULL) called, should not crash.\n");
    printf("\n===== Graph (Adjacency Matrix) Test Suite Complete =====\n\n");
}

void print_fenwick_tree_status(const FenwickTree* ft, const char* label) {
    if (!label) label = "Current Fenwick Tree Status";
    printf("\n--- %s ---\n", label);
    if (!ft) {
        printf("Fenwick Tree is NULL.\n");
        return;
    }
    printf("Logical Size: %d\n", fenwick_tree_get_size(ft));
    fenwick_tree_print_internal_array(ft); 
    if (ft->size > 0 && ft->size <= 10) {
        printf("Prefix Sums (1 to N): [");
        for (int i = 1; i <= ft->size; ++i) {
            printf("%d%s", fenwick_tree_query_prefix_sum(ft, i), (i == ft->size) ? "" : ", ");
        }
        printf("]\n");
    }
    printf("---------------\n");
}
void test_fenwick_tree() {
    printf("===== Starting Fenwick Tree Test Suite =====\n");
    FenwickTree* my_ft = NULL;
    const int tree_logical_size_ft = 10; 
    printf("\n[Test 1: Creation]\n");
    my_ft = fenwick_tree_create(tree_logical_size_ft);
    if (my_ft) {
        printf("fenwick_tree_create(%d) successful.\n", tree_logical_size_ft);
    } else {
        printf("fenwick_tree_create(%d) FAILED. Aborting tests.\n", tree_logical_size_ft);
        return;
    }
    print_fenwick_tree_status(my_ft, "After creation (all zeros)");
    if (fenwick_tree_get_size(my_ft) != tree_logical_size_ft) {
         printf("ERROR: Size is %d, expected %d.\n", fenwick_tree_get_size(my_ft), tree_logical_size_ft);
    }
    if (fenwick_tree_query_prefix_sum(my_ft, tree_logical_size_ft) != 0) {
        printf("ERROR: Initial prefix sum for whole array is not 0.\n");
    }
    FenwickTree* zero_ft = fenwick_tree_create(0);
    if(zero_ft) printf("fenwick_tree_create(0) OK.\n"); else printf("fenwick_tree_create(0) FAILED.\n");
    fenwick_tree_destroy(zero_ft);
    FenwickTree* neg_ft = fenwick_tree_create(-1);
    if(neg_ft == NULL) printf("fenwick_tree_create(-1) correctly NULL.\n"); else {printf("FAILED create(-1)\n"); fenwick_tree_destroy(neg_ft);}
    printf("\n[Test 2: Updates and Prefix Sum Queries]\n");
    fenwick_tree_update(my_ft, 3, 5);  
    printf("Updated index 3 by +5.\n");
    print_fenwick_tree_status(my_ft, "After update(3, 5)");
    if (fenwick_tree_query_prefix_sum(my_ft, 2) != 0) printf("ERR: PS(2)!=0\n");
    if (fenwick_tree_query_prefix_sum(my_ft, 3) != 5) printf("ERR: PS(3)!=5\n");
    if (fenwick_tree_query_prefix_sum(my_ft, 5) != 5) printf("ERR: PS(5)!=5\n");
    fenwick_tree_update(my_ft, 5, 2);  
    printf("Updated index 5 by +2.\n");
    print_fenwick_tree_status(my_ft, "After update(5, 2)");
    if (fenwick_tree_query_prefix_sum(my_ft, 4) != 5) printf("ERR: PS(4)!=5\n");
    if (fenwick_tree_query_prefix_sum(my_ft, 5) != 7) printf("ERR: PS(5)!=7\n"); 
    if (fenwick_tree_query_prefix_sum(my_ft, 10) != 7) printf("ERR: PS(10)!=7\n");
    fenwick_tree_update(my_ft, 3, -2); 
    printf("Updated index 3 by -2.\n");
    print_fenwick_tree_status(my_ft, "After update(3, -2)");
    if (fenwick_tree_query_prefix_sum(my_ft, 3) != 3) printf("ERR: PS(3)!=3\n");
    if (fenwick_tree_query_prefix_sum(my_ft, 5) != 5) printf("ERR: PS(5)!=5\n"); 
    fenwick_tree_update(my_ft, 1, 10);
    fenwick_tree_update(my_ft, tree_logical_size_ft, 20);
    print_fenwick_tree_status(my_ft, "After update(1,10) and update(10,20)");
    if (fenwick_tree_query_prefix_sum(my_ft, 1) != 10) printf("ERR: PS(1)!=10\n");
    if (fenwick_tree_query_prefix_sum(my_ft, tree_logical_size_ft) != 35) printf("ERR: PS(10)!=35\n");
    printf("\n[Test 3: Range Sum Queries]\n");
    int r_sum_ft = fenwick_tree_query_range_sum(my_ft, 3, 5); // Renamed
    printf("Range sum (3,5): %d (Expected 5)\n", r_sum_ft);
    if (r_sum_ft != 5) printf("ERROR: Range sum (3,5) is %d, expected 5.\n", r_sum_ft);
    r_sum_ft = fenwick_tree_query_range_sum(my_ft, 1, 1); 
    printf("Range sum (1,1): %d (Expected 10)\n", r_sum_ft);
    if (r_sum_ft != 10) printf("ERROR: Range sum (1,1) is %d, expected 10.\n", r_sum_ft);
    r_sum_ft = fenwick_tree_query_range_sum(my_ft, 1, 10); 
    printf("Range sum (1,10): %d (Expected 35)\n", r_sum_ft);
    if (r_sum_ft != 35) printf("ERROR: Range sum (1,10) is %d, expected 35.\n", r_sum_ft);
    r_sum_ft = fenwick_tree_query_range_sum(my_ft, 6, 9); 
    printf("Range sum (6,9): %d (Expected 0)\n", r_sum_ft);
    if (r_sum_ft != 0) printf("ERROR: Range sum (6,9) is %d, expected 0.\n", r_sum_ft);
    printf("\n[Test 4: Boundary and Invalid Updates/Queries]\n");
    bool update_ok_ft = fenwick_tree_update(my_ft, 0, 100); 
    if (!update_ok_ft) printf("Correctly failed update for index 0.\n"); else printf("ERR: Update index 0 succeeded.\n");
    update_ok_ft = fenwick_tree_update(my_ft, tree_logical_size_ft + 1, 100); 
    if (!update_ok_ft) printf("Correctly failed update for index %d.\n", tree_logical_size_ft + 1); else printf("ERR: Update index %d succeeded.\n", tree_logical_size_ft + 1);
    int ps_invalid_ft = fenwick_tree_query_prefix_sum(my_ft, 0); 
    printf("Prefix sum(0): %d (Expected 0)\n", ps_invalid_ft);
    if(ps_invalid_ft != 0) printf("ERR: PS(0) not 0.\n");
    ps_invalid_ft = fenwick_tree_query_prefix_sum(my_ft, tree_logical_size_ft + 5);
    printf("Prefix sum(%d) (out of bounds): %d (Expected sum up to %d: 35)\n", tree_logical_size_ft + 5, ps_invalid_ft, tree_logical_size_ft);
    if(ps_invalid_ft != 35) printf("ERR: PS for out of bounds not matching PS(max_size).\n");
    printf("\n[Test 5: Destruction]\n");
    fenwick_tree_destroy(my_ft);
    my_ft = NULL; 
    printf("Fenwick Tree destroyed.\n");
    fenwick_tree_destroy(NULL);
    printf("fenwick_tree_destroy(NULL) called, should not crash.\n");
    printf("\n===== Fenwick Tree Test Suite Complete =====\n\n");
}

void print_segment_tree_status(const SegmentTree* st, const char* label) {
    if (!label) label = "Current Segment Tree Status";
    printf("\n--- %s ---\n", label);
    if (!st) {
        printf("Segment Tree is NULL.\n");
        return;
    }
    printf("Original Array Size: %d\n", segment_tree_get_original_size(st));
    segment_tree_print_internal_array(st); 
    if (st->original_array_size > 0 && st->original_array_size <= 10) {
        printf("Conceptual Array (from ST): [");
        bool success_q_st; 
        for (int i = 0; i < st->original_array_size; ++i) {
            int val_st = segment_tree_query_range_sum(st, i, i, &success_q_st); 
            if(success_q_st) {
                printf("%d%s", val_st, (i == st->original_array_size - 1) ? "" : ", ");
            } else {
                printf("ERR%s", (i == st->original_array_size - 1) ? "" : ", ");
            }
        }
        printf("]\n");
    }
    printf("---------------\n");
}
void test_segment_tree() {
    printf("===== Starting Segment Tree Test Suite =====\n");
    SegmentTree* my_st = NULL;
    int initial_array_st[] = {1, 3, 5, 7, 9, 11}; 
    int n_st = sizeof(initial_array_st) / sizeof(initial_array_st[0]); 
    bool success_op_st; 
    printf("\n[Test 1: Build]\n");
    my_st = segment_tree_build(initial_array_st, n_st);
    if (my_st) {
        printf("segment_tree_build() successful for array of size %d.\n", n_st);
    } else {
        printf("segment_tree_build() FAILED. Aborting tests.\n");
        return;
    }
    print_segment_tree_status(my_st, "After building from {1,3,5,7,9,11}");
    if (segment_tree_get_original_size(my_st) != n_st) {
         printf("ERROR: Original size is %d, expected %d.\n", segment_tree_get_original_size(my_st), n_st);
    }
    SegmentTree* empty_st = segment_tree_build(NULL, 0);
    if (empty_st) printf("segment_tree_build(NULL,0) OK.\n"); else printf("segment_tree_build(NULL,0) FAILED.\n");
    print_segment_tree_status(empty_st, "Empty segment tree");
    segment_tree_destroy(empty_st);
    SegmentTree* null_arr_st = segment_tree_build(NULL, 5); 
    if (null_arr_st == NULL) printf("segment_tree_build(NULL,5) correctly NULL.\n"); else {printf("ERR: build(NULL,5) not NULL\n"); segment_tree_destroy(null_arr_st);}
    SegmentTree* neg_size_st = segment_tree_build(initial_array_st, -1); 
    if (neg_size_st == NULL) printf("segment_tree_build(arr,-1) correctly NULL.\n"); else {printf("ERR: build(arr,-1) not NULL\n"); segment_tree_destroy(neg_size_st);}
    printf("\n[Test 2: Range Sum Queries]\n");
    int sum_st; 
    sum_st = segment_tree_query_range_sum(my_st, 0, 5, &success_op_st); 
    if(success_op_st) printf("Query(0,5) Sum: %d (Expected 36)\n", sum_st); else printf("Query(0,5) FAILED\n");
    if (sum_st != 36) printf("ERROR: Sum(0,5) is %d, expected 36.\n", sum_st);
    sum_st = segment_tree_query_range_sum(my_st, 1, 3, &success_op_st); 
    if(success_op_st) printf("Query(1,3) Sum: %d (Expected 15)\n", sum_st); else printf("Query(1,3) FAILED\n");
    if (sum_st != 15) printf("ERROR: Sum(1,3) is %d, expected 15.\n", sum_st);
    sum_st = segment_tree_query_range_sum(my_st, 2, 2, &success_op_st); 
    if(success_op_st) printf("Query(2,2) Sum: %d (Expected 5)\n", sum_st); else printf("Query(2,2) FAILED\n");
    if (sum_st != 5) printf("ERROR: Sum(2,2) is %d, expected 5.\n", sum_st);
    sum_st = segment_tree_query_range_sum(my_st, 3, 1, &success_op_st); 
    if(!success_op_st) printf("Query(3,1) (invalid range L>R) correctly failed or returned 0.\n");
    else printf("Query(3,1) succeeded with %d, but range was invalid.\n", sum_st);
    sum_st = segment_tree_query_range_sum(my_st, 0, n_st, &success_op_st); 
    if(!success_op_st) printf("Query(0,%d) (invalid range R out of bounds) correctly failed or returned 0.\n", n_st);
    else printf("Query(0,%d) succeeded with %d, but range was invalid.\n", n_st, sum_st);
    printf("\n[Test 3: Point Updates]\n");
    bool update_ok_st = segment_tree_update_point(my_st, 2, 6); 
    printf("Updated A[2] from 5 to 6: %s\n", update_ok_st ? "OK" : "Fail");
    print_segment_tree_status(my_st, "After updating A[2] to 6");
    sum_st = segment_tree_query_range_sum(my_st, 1, 3, &success_op_st); 
    if(success_op_st) printf("Query(1,3) Sum after update: %d (Expected 16)\n", sum_st); else printf("Query(1,3) FAILED post-update\n");
    if (sum_st != 16) printf("ERROR: Sum(1,3) after update is %d, expected 16.\n", sum_st);
    sum_st = segment_tree_query_range_sum(my_st, 0, 5, &success_op_st); 
    if(success_op_st) printf("Query(0,5) Sum after update: %d (Expected 37)\n", sum_st); else printf("Query(0,5) FAILED post-update\n");
    if (sum_st != 37) printf("ERROR: Sum(0,5) after update is %d, expected 37.\n", sum_st);
    segment_tree_update_point(my_st, 0, 0); 
    segment_tree_update_point(my_st, n_st-1, 10); 
    print_segment_tree_status(my_st, "After updating A[0] to 0 and A[5] to 10");
    sum_st = segment_tree_query_range_sum(my_st, 0, 5, &success_op_st); 
    if(success_op_st) printf("Query(0,5) Sum after boundary updates: %d (Expected 35)\n", sum_st); else printf("Query(0,5) FAILED post-boundary-updates\n");
    if (sum_st != 35) printf("ERROR: Sum(0,5) after boundary updates is %d, expected 35.\n", sum_st);
    update_ok_st = segment_tree_update_point(my_st, n_st, 100); 
    if (!update_ok_st) printf("Correctly failed update for index %d (out of bounds).\n", n_st);
    else printf("ERROR: Update for index %d succeeded.\n", n_st);
    printf("\n[Test 4: Destruction]\n");
    segment_tree_destroy(my_st);
    my_st = NULL; 
    printf("Segment Tree destroyed.\n");
    segment_tree_destroy(NULL);
    printf("segment_tree_destroy(NULL) called, should not crash.\n");
    printf("\n===== Segment Tree Test Suite Complete =====\n\n");
}

void print_skip_list_status(const SkipList* sl, const char* label) {
    if (!label) label = "Current Skip List Status";
    printf("\n--- %s ---\n", label);
    if (!sl) {
        printf("Skip List is NULL.\n");
        return;
    }
    printf("Size: %d\n", skip_list_size(sl));
    printf("Is Empty: %s\n", skip_list_is_empty(sl) ? "Yes" : "No");
    printf("Current Max Level in use: %d\n", sl->current_max_level);
    skip_list_print(sl); 
    printf("---------------\n");
}
void test_skip_list() {
    printf("===== Starting Skip List Test Suite =====\n");
    SkipList* my_sl = NULL;
    bool success_op_sl; 
    printf("\n[Test 1: Creation]\n");
    my_sl = skip_list_create();
    if (my_sl && my_sl->header) {
        printf("skip_list_create() successful.\n");
    } else {
        printf("skip_list_create() FAILED. Aborting tests.\n");
        if(my_sl) skip_list_destroy(my_sl);
        return;
    }
    print_skip_list_status(my_sl, "After creation (empty)");
    if (skip_list_size(my_sl) != 0 || !skip_list_is_empty(my_sl)) {
         printf("ERROR: Empty skip list size/is_empty incorrect.\n");
    }
    printf("\n[Test 2: Insertions]\n");
    int values_to_insert_sl[] = {10, 5, 20, 1, 15, 25, 7, 12}; 
    int num_vals_sl = sizeof(values_to_insert_sl) / sizeof(values_to_insert_sl[0]); 
    for (int i = 0; i < num_vals_sl; ++i) {
        success_op_sl = skip_list_insert(my_sl, values_to_insert_sl[i]);
        printf("Inserted %d: %s\n", values_to_insert_sl[i], success_op_sl ? "OK" : "Fail (or duplicate)");
    }
    print_skip_list_status(my_sl, "After inserting several values");
    if (skip_list_size(my_sl) != num_vals_sl) {
        printf("ERROR: Size is %d after %d unique insertions, expected %d.\n", skip_list_size(my_sl), num_vals_sl, num_vals_sl);
    }
    success_op_sl = skip_list_insert(my_sl, 10);
    printf("Inserted 10 again: %s (Expected false, duplicate)\n", !success_op_sl ? "OK" : "Fail"); 
    if (skip_list_size(my_sl) != num_vals_sl) {
        printf("ERROR: Size changed after duplicate insert. Size: %d, Expected: %d.\n", skip_list_size(my_sl), num_vals_sl);
    }
    print_skip_list_status(my_sl, "After attempting to insert duplicate 10");
    printf("\n[Test 3: Contains]\n");
    printf("Skip list contains 10: %s (Expected true)\n", skip_list_contains(my_sl, 10) ? "true" : "false");
    printf("Skip list contains 1:  %s (Expected true)\n", skip_list_contains(my_sl, 1) ? "true" : "false");
    printf("Skip list contains 25: %s (Expected true)\n", skip_list_contains(my_sl, 25) ? "true" : "false");
    printf("Skip list contains 12: %s (Expected true)\n", skip_list_contains(my_sl, 12) ? "true" : "false");
    printf("Skip list contains 99: %s (Expected false)\n", skip_list_contains(my_sl, 99) ? "true" : "false");
    printf("Skip list contains 6:  %s (Expected false)\n", skip_list_contains(my_sl, 6) ? "true" : "false");
    printf("\n[Test 4: Removals]\n");
    success_op_sl = skip_list_remove(my_sl, 10);
    printf("Removed 10: %s (Expected true)\n", success_op_sl ? "OK" : "Fail");
    print_skip_list_status(my_sl, "After removing 10");
    if (skip_list_contains(my_sl, 10)) printf("ERROR: Skip list still contains 10 after removal.\n");
    if (skip_list_size(my_sl) != num_vals_sl - 1) printf("ERROR: Size is %d, expected %d after removing 10.\n", skip_list_size(my_sl), num_vals_sl - 1);
    success_op_sl = skip_list_remove(my_sl, 99); 
    printf("Removed 99 (not present): %s (Expected false)\n", !success_op_sl ? "OK" : "Fail"); 
    print_skip_list_status(my_sl, "After attempting to remove 99");
    success_op_sl = skip_list_remove(my_sl, 1); 
    printf("Removed 1: %s (Expected true)\n", success_op_sl ? "OK" : "Fail");
    print_skip_list_status(my_sl, "After removing 1");
    success_op_sl = skip_list_remove(my_sl, 25); 
    printf("Removed 25: %s (Expected true)\n", success_op_sl ? "OK" : "Fail");
    print_skip_list_status(my_sl, "After removing 25");
    printf("\n[Test 5: Remove all remaining elements]\n");
    int remaining_vals_sl[] = {5, 7, 12, 15, 20}; 
    for(int i=0; i < sizeof(remaining_vals_sl)/sizeof(int); ++i) {
        skip_list_remove(my_sl, remaining_vals_sl[i]);
    }
    print_skip_list_status(my_sl, "After removing all remaining elements");
    if (!skip_list_is_empty(my_sl) || skip_list_size(my_sl) != 0) {
        printf("ERROR: Skip list not empty after removing all. Size: %d\n", skip_list_size(my_sl));
    }
    if (my_sl->current_max_level != 0 && skip_list_size(my_sl) == 0) { 
         printf("Note: current_max_level is %d for empty list.\n", my_sl->current_max_level);
    }
    printf("\n[Test 6: Operations on empty list]\n");
    printf("Contains 100 in empty list: %s (Exp false)\n", skip_list_contains(my_sl, 100) ? "true" : "false");
    success_op_sl = skip_list_remove(my_sl, 100);
    printf("Remove 100 from empty list: %s (Exp false)\n", !success_op_sl ? "OK" : "Fail"); 
    success_op_sl = skip_list_insert(my_sl, 500);
    printf("Insert 500 into empty list: %s (Exp true)\n", success_op_sl ? "OK" : "Fail");
    print_skip_list_status(my_sl, "After inserting 500 into (previously) empty list");
    printf("\n[Test 7: Destruction]\n");
    skip_list_destroy(my_sl);
    my_sl = NULL; 
    printf("Skip List destroyed.\n");
    skip_list_destroy(NULL);
    printf("skip_list_destroy(NULL) called, should not crash.\n");
    printf("\n===== Skip List Test Suite Complete =====\n\n");
}

void print_avl_tree_status(const AVLTree* tree, const char* label) {
    if (!label) label = "Current AVL Tree Status";
    printf("\n--- %s ---\n", label);
    if (!tree) {
        printf("AVL Tree is NULL.\n");
        return;
    }
    printf("Size:     %d\n", avl_tree_size(tree));
    printf("Is Empty: %s\n", avl_tree_is_empty(tree) ? "Yes" : "No");
    printf("Height:   %d\n", avl_tree_get_height(tree)); 
    TreeVisitData traversal_data_avl; 
    traversal_data_avl.count = 0;
    traversal_data_avl.first_print = true;
    printf("In-order:   [");
    avl_tree_in_order_traversal(tree, tree_node_visit_printer, &traversal_data_avl); // Use generic printer
    printf("]\n");
    printf("---------------\n");
}
void test_avl_tree() {
    printf("===== Starting AVL Tree Test Suite =====\n");
    AVLTree* my_avl = NULL;
    bool success_op_avl; 
    printf("\n[Test 1: Creation]\n");
    my_avl = avl_tree_create();
    if (my_avl) {
        printf("avl_tree_create() successful.\n");
    } else {
        printf("avl_tree_create() FAILED. Aborting tests.\n");
        return;
    }
    print_avl_tree_status(my_avl, "After creation (empty)");
    printf("\n[Test 2: Insertions and Rotations]\n");
    printf("Inserting 3, 2, 1 (LL rotation expected at root for 1)\n");
    avl_tree_insert(my_avl, 3);
    avl_tree_insert(my_avl, 2);
    avl_tree_insert(my_avl, 1); 
    print_avl_tree_status(my_avl, "After 3,2,1 (LL case -> 2 is root)"); 
    if(my_avl->root && my_avl->root->value != 2) printf("ERROR: Root not 2 after LL case.\n");
    avl_tree_destroy(my_avl); my_avl = avl_tree_create(); 
    printf("\nInserting 1, 2, 3 (RR rotation expected at root for 3)\n");
    avl_tree_insert(my_avl, 1);
    avl_tree_insert(my_avl, 2);
    avl_tree_insert(my_avl, 3); 
    print_avl_tree_status(my_avl, "After 1,2,3 (RR case -> 2 is root)"); 
    if(my_avl->root && my_avl->root->value != 2) printf("ERROR: Root not 2 after RR case.\n");
    avl_tree_destroy(my_avl); my_avl = avl_tree_create(); 
    printf("\nInserting 3, 1, 2 (LR rotation expected for 2)\n");
    avl_tree_insert(my_avl, 3);
    avl_tree_insert(my_avl, 1);
    avl_tree_insert(my_avl, 2); 
    print_avl_tree_status(my_avl, "After 3,1,2 (LR case -> 2 is root)"); 
    if(my_avl->root && my_avl->root->value != 2) printf("ERROR: Root not 2 after LR case.\n");
    avl_tree_destroy(my_avl); my_avl = avl_tree_create(); 
    printf("\nInserting 1, 3, 2 (RL rotation expected for 2)\n");
    avl_tree_insert(my_avl, 1);
    avl_tree_insert(my_avl, 3);
    avl_tree_insert(my_avl, 2); 
    print_avl_tree_status(my_avl, "After 1,3,2 (RL case -> 2 is root)"); 
    if(my_avl->root && my_avl->root->value != 2) printf("ERROR: Root not 2 after RL case.\n");
    printf("\nInserting more values: 4, 5, 0, -1, 6, 7 (testing various balances)\n");
    avl_tree_insert(my_avl, 4); 
    avl_tree_insert(my_avl, 5); 
    avl_tree_insert(my_avl, 0); 
    avl_tree_insert(my_avl, -1);
    avl_tree_insert(my_avl, 6);
    avl_tree_insert(my_avl, 7);
    print_avl_tree_status(my_avl, "After several more insertions");
    if(avl_tree_size(my_avl) != 9) printf("ERROR: Size %d, expected 9\n", avl_tree_size(my_avl));
    printf("\n[Test 3: Contains]\n");
    printf("AVL Tree contains 2: %s (Expected true)\n", avl_tree_contains(my_avl, 2) ? "true" : "false");
    printf("AVL Tree contains -1:%s (Expected true)\n", avl_tree_contains(my_avl, -1) ? "true" : "false");
    printf("AVL Tree contains 7: %s (Expected true)\n", avl_tree_contains(my_avl, 7) ? "true" : "false");
    printf("AVL Tree contains 99:%s (Expected false)\n", avl_tree_contains(my_avl, 99) ? "true" : "false");
    printf("\n[Test 4: Removals and Rotations]\n");
    success_op_avl = avl_tree_remove(my_avl, -1); printf("Removed -1: %s\n", success_op_avl?"OK":"Fail"); 
    success_op_avl = avl_tree_remove(my_avl, 7);  printf("Removed 7: %s\n", success_op_avl?"OK":"Fail");  
    success_op_avl = avl_tree_remove(my_avl, 3);  printf("Removed 3: %s\n", success_op_avl?"OK":"Fail");  
    print_avl_tree_status(my_avl, "After removing -1, 7, 3");
    if (avl_tree_size(my_avl) != 6) printf("ERROR: Size %d, expected 6 after 3 removals.\n", avl_tree_size(my_avl));
    if (avl_tree_contains(my_avl, 3)) printf("ERROR: Still contains 3.\n");
    if (!avl_tree_contains(my_avl, 4)) printf("ERROR: Should still contain 4.\n");
    int old_root_val_avl = my_avl->root ? my_avl->root->value : -999; 
    if (old_root_val_avl != -999) {
        success_op_avl = avl_tree_remove(my_avl, old_root_val_avl);
        printf("Removed old root %d: %s\n", old_root_val_avl, success_op_avl ? "OK" : "Fail");
        print_avl_tree_status(my_avl, "After removing old root");
        if (avl_tree_size(my_avl) != 5) printf("ERROR: Size %d, expected 5 after root removal.\n", avl_tree_size(my_avl));
    }
    success_op_avl = avl_tree_remove(my_avl, 99);
    printf("Attempted to remove 99 (not present): %s (Expected false)\n", !success_op_avl ? "OK" : "Fail"); 
    printf("\n[Test 5: Destruction]\n");
    avl_tree_destroy(my_avl);
    my_avl = NULL; 
    printf("AVL Tree destroyed.\n");
    avl_tree_destroy(NULL);
    printf("avl_tree_destroy(NULL) called, should not crash.\n");
    printf("\n===== AVL Tree Test Suite Complete =====\n\n");
}

void print_rbt_status(const RedBlackTree* tree, const char* label) {
    if (!label) label = "Current Red-Black Tree Status";
    printf("\n--- %s ---\n", label);
    if (!tree) {
        printf("Red-Black Tree is NULL.\n");
        return;
    }
    printf("Size:     %d\n", rbt_size(tree));
    printf("Is Empty: %s\n", rbt_is_empty(tree) ? "Yes" : "No");
    if (tree->root != tree->nil) {
        printf("Root Value: %d, Root Color: %s\n",
               tree->root->value,
               tree->root->color == RBT_COLOR_BLACK ? "BLACK" : "RED");
        if (tree->root->color == RBT_COLOR_RED && tree->root != tree->nil) { 
            printf("ERROR: Root is RED!\n");
        }
    } else {
        printf("Root: NIL (empty tree)\n");
    }
    TreeVisitData traversal_data_rbt; 
    traversal_data_rbt.count = 0;
    traversal_data_rbt.first_print = true;
    printf("In-order:   [");
    rbt_in_order_traversal(tree, tree_node_visit_printer, &traversal_data_rbt); 
    printf("]\n");
    printf("---------------\n");
}
void test_red_black_tree() {
    printf("===== Starting Red-Black Tree Test Suite =====\n");
    RedBlackTree* my_rbt = NULL;
    bool success_op_rbt; 
    printf("\n[Test 1: Creation]\n");
    my_rbt = rbt_create();
    if (my_rbt && my_rbt->nil) { 
        printf("rbt_create() successful.\n");
    } else {
        printf("rbt_create() FAILED. Aborting tests.\n");
        if(my_rbt) rbt_destroy(my_rbt);
        return;
    }
    print_rbt_status(my_rbt, "After creation (empty)");
    if (my_rbt->root != my_rbt->nil) printf("ERROR: Root of empty tree not NIL.\n");
    printf("\n[Test 2: Insertions]\n");
    int values_to_insert_rbt[] = {11, 2, 14, 1, 7, 15, 5, 8}; 
    int num_insert_rbt = sizeof(values_to_insert_rbt)/sizeof(int); 
    for(int i=0; i<num_insert_rbt; ++i) {
        success_op_rbt = rbt_insert(my_rbt, values_to_insert_rbt[i]);
        printf("Inserted %d: %s\n", values_to_insert_rbt[i], success_op_rbt ? "OK":"Fail");
    }
    success_op_rbt = rbt_insert(my_rbt, 4); printf("Inserted 4: %s\n", success_op_rbt ? "OK":"Fail"); 
    num_insert_rbt++;
    print_rbt_status(my_rbt, "After inserting {11,2,14,1,7,15,5,8,4}");
    if (rbt_size(my_rbt) != num_insert_rbt) {
        printf("ERROR: Size is %d, expected %d after %d insertions.\n", rbt_size(my_rbt), num_insert_rbt, num_insert_rbt);
    }
    success_op_rbt = rbt_insert(my_rbt, 7);
    printf("Inserted 7 again: %s (Expected false, duplicate)\n", !success_op_rbt ? "OK" : "Fail"); 
    if (rbt_size(my_rbt) != num_insert_rbt) {
        printf("ERROR: Size changed after duplicate insert. Size: %d, Expected: %d.\n", rbt_size(my_rbt), num_insert_rbt);
    }
    printf("\n[Test 3: Contains]\n");
    printf("RBT contains 7: %s (Expected true)\n", rbt_contains(my_rbt, 7) ? "true" : "false");
    printf("RBT contains 1: %s (Expected true)\n", rbt_contains(my_rbt, 1) ? "true" : "false");
    printf("RBT contains 15:%s (Expected true)\n", rbt_contains(my_rbt, 15) ? "true" : "false");
    printf("RBT contains 99:%s (Expected false)\n", rbt_contains(my_rbt, 99) ? "true" : "false");
    printf("RBT contains 6: %s (Expected false)\n", rbt_contains(my_rbt, 6) ? "true" : "false");
    printf("\n[Test 4: Removals]\n");
    success_op_rbt = rbt_remove(my_rbt, 1); printf("Removed 1 (leaf or simple case): %s\n", success_op_rbt ? "OK" : "Fail");
    print_rbt_status(my_rbt, "After removing 1");
    if (rbt_contains(my_rbt, 1)) printf("ERROR: Still contains 1.\n");
    if (rbt_size(my_rbt) != num_insert_rbt - 1) printf("ERROR: Size error after removing 1.\n");
    success_op_rbt = rbt_remove(my_rbt, 14); printf("Removed 14: %s\n", success_op_rbt ? "OK" : "Fail");
    print_rbt_status(my_rbt, "After removing 14");
    if (rbt_contains(my_rbt, 14)) printf("ERROR: Still contains 14.\n");
    if (rbt_size(my_rbt) != num_insert_rbt - 2) printf("ERROR: Size error after removing 14.\n");
    if (!rbt_contains(my_rbt, 15)) printf("ERROR: Should still contain 15.\n");
    if (my_rbt->root != my_rbt->nil) {
        int old_root_val_rbt = my_rbt->root->value; 
        success_op_rbt = rbt_remove(my_rbt, old_root_val_rbt);
        printf("Removed old root %d: %s\n", old_root_val_rbt, success_op_rbt ? "OK" : "Fail");
        print_rbt_status(my_rbt, "After removing old root");
        if (rbt_size(my_rbt) != num_insert_rbt - 3) printf("ERROR: Size error after root removal.\n");
    }
    success_op_rbt = rbt_remove(my_rbt, 99); 
    printf("Attempted to remove 99 (not present): %s (Expected false)\n", !success_op_rbt ? "OK" : "Fail"); 
    printf("\n[Test 5: Destruction]\n");
    rbt_destroy(my_rbt);
    my_rbt = NULL; 
    printf("Red-Black Tree destroyed.\n");
    rbt_destroy(NULL);
    printf("rbt_destroy(NULL) called, should not crash.\n");
    printf("\n===== Red-Black Tree Test Suite Complete =====\n\n");
}


// --- Main Function ---
int main() {
    printf("********** Starting Data Structures Test Suite **********\n\n");

    // Seed random number generator once for tests that might use it (e.g., Skip List)
    srand((unsigned int)time(NULL));

    // Call test functions in order
    test_vector();
    test_singly_linked_list();
    test_stack();
    test_queue();
    test_doubly_linked_list();
    test_hash_set();
    test_binary_search_tree();
    test_rope();
    test_deque();
    test_binary_heap();
    test_disjoint_set_union();
    test_trie();
    test_graph_adj_list();
    test_graph_adj_matrix();
    test_fenwick_tree();
    test_segment_tree();
    test_skip_list();
    test_avl_tree();
    test_red_black_tree();

    printf("\n********** Data Structures Test Suite Complete **********\n");
    return 0;
}
