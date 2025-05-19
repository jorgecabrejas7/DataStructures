# My Personal C Data Structures & Algorithms Course

This repository documents my journey of learning and implementing fundamental Data Structures and Algorithms in C. The primary goal is to solidify my understanding by building each structure from scratch based on a clear interface definition.

## Course Structure

For simplicity and focus on the core logic of each data structure:
*   All data structures are designed to store elements of type `int`.
*   Each data structure resides in its own subfolder (e.g., `vector/`, `singly_linked_list/`).
*   Each subfolder contains:
    *   `<datastructure_name>.h`: The header file acting as the interface definition or "problem statement." It includes a detailed comment block defining the data structure, its properties, common operations, use cases, and pros/cons, followed by struct definitions and function prototypes with thorough documentation.
    *   `<datastructure_name>.c`: My C implementation of the data structure based on the header file. (This file will be written by me).
*   A root `test.c` file is used as the main testing ground to instantiate and verify the functionality of each data structure.

## Data Structures Covered (or to be covered)

The following data structures are included in this course, roughly grouped by increasing implementation complexity:

**Tier 1: Foundational / Beginner**
*   [ ] Vector (Dynamic Array)
*   [ ] Stack (Array-based)
*   [ ] Queue (Circular Array-based)
*   [ ] Singly Linked List

**Tier 2: Early Intermediate**
*   [ ] Deque (Circular Array-based)
*   [ ] Doubly Linked List
*   [ ] Binary Heap (Min-Heap / Max-Heap)
*   [ ] Disjoint Set Union (DSU) / Union-Find

**Tier 3: Intermediate**
*   [ ] Binary Search Tree (BST)
*   [ ] Hash Set (Chaining with Singly Linked Lists)
*   [ ] Trie (Bitwise for Integers)
*   [ ] Rope (adapted for sequences of `int`s)

**Tier 4: Advanced**
*   [ ] Graph (Adjacency List Representation)
*   [ ] Graph (Adjacency Matrix Representation)
*   [ ] Fenwick Tree (Binary Indexed Tree - BIT)
*   [ ] Segment Tree

**Tier 5: More Advanced / Complex**
*   [ ] Skip List
*   [ ] AVL Tree
*   [ ] Red-Black Tree

*(Checkboxes can be updated as implementations are completed: `[x]`)*

## Development & Testing

*   **Interface First:** For each data structure, the `.h` file is provided first. This clearly defines the "what" and the "how" (API) before I dive into the "how-to-implement."
*   **Implementation:** I will write the `.c` files to match the interfaces defined in the `.h` files.
*   **Testing:** The `test.c` file will contain test functions for each data structure, including basic usage scenarios, edge cases, and verification of operations using `printf` statements or simple assertions.

## Learning Objectives

*   To gain a deep, practical understanding of how common data structures work internally.
*   To practice C programming, including pointer manipulation, dynamic memory management, and modular design.
*   To build a personal library of well-commented and understood data structure implementations.
*   To prepare for more advanced algorithm study which often relies on these fundamental structures.

## How to Use (for myself)

1.  Select a data structure from the list.
2.  Review the provided `<datastructure_name>.h` file as the specification.
3.  Implement the corresponding `<datastructure_name>.c` file.
4.  Add the provided test code snippet to `test.c` (or write my own).
5.  To compile and run `test.c` to verify the implementation:
    *   Create a build directory if it doesn't exist: `mkdir build`
    *   Navigate into the build directory: `cd build`
    *   Run CMake to configure the project: `cmake ..`
    *   Run Make to build the project: `make`
    *   Run the test executable: `./test_program` (or the name specified in your CMakeLists.txt)
6.  Debug and iterate until all tests pass and I am confident in the implementation.

This project is a personal learning endeavor.