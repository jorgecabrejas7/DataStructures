#include <stdio.h>  // For printf, FILE, fopen, fclose, fgetc, fputc, fgets, fputs, fprintf, fscanf, rewind, perror, remove, putchar, feof, ferror, clearerr
#include <math.h>   // For sqrt, fabs
#include <stdlib.h> // For malloc, calloc, realloc, free, NULL
#include <string.h> // For strcpy <--- ADDED THIS

// --- Function Prototypes (Declarations) for Section 7 ---
void greet(void);
int add_numbers(int a, int b);
double calculate_square(double num);
void try_to_modify(int val);
int function_with_local_scope(void);

// Global variable
int global_variable_example = 100;

// --- Structure Definitions and Typedefs for Section 11 ---
struct Point {
    int x;
    int y;
};

struct Student {
    char name[50];
    int student_id;
    float gpa;
};

struct Date {
    int day;
    int month;
    int year;
};

struct Employee {
    char emp_name[60];
    int employee_id;
    struct Date date_of_birth;
};

typedef struct {
    char title[100];
    char author[50];
    int year_published;
} Book;

// Function prototypes for Section 11
void print_point_by_value(struct Point pt_val);
void modify_point_by_pointer(struct Point *pt_ptr);
void print_student_info(struct Student s);

// --- Union and Enum Definitions for Section 12 ---
union ValueContainer {
    int i_val;
    float f_val;
    char c_val;
};

enum DayOfWeek {
    SUN, MON, TUE, WED, THU, FRI, SAT
};

enum TrafficLight {
    RED_LIGHT = 1,
    YELLOW_LIGHT = 2,
    GREEN_LIGHT = 3
};

typedef enum {
    PENDING,
    PROCESSING,
    COMPLETED,
    FAILED
} ProcessStatus;


int main() {
    // --- Welcome Message & Program Purpose ---
    // This section prints a welcome banner and a brief description of the program's purpose.
    // It helps orient the user to what the program will demonstrate.
    printf("========================================\n");
    printf("    C Language Concepts Explainer\n");
    printf("========================================\n\n");

    printf("This program demonstrates and explains various C language concepts.\n");
    printf("Follow along with the code and its output to refresh your C knowledge!\n\n");

    // --- Section: Compiling with GCC ---
    // This section explains the basics of compiling C programs using GCC (GNU Compiler Collection).
    // It covers common command-line options for compilation, output naming, warnings,
    // C standards, debugging information, and optimization.
    printf("----------------------------------------\n");
    printf("  Section 1: Compiling C with GCC\n");
    printf("----------------------------------------\n");
    printf("GCC (GNU Compiler Collection) is a common compiler for C programs on Linux.\n\n");
    printf("  Basic Compilation:\n");
    printf("    To compile a simple C file (e.g., 'my_program.c'), you use:\n");
    printf("    $ gcc my_program.c\n");
    printf("    This creates an executable file named 'a.out' by default.\n\n");
    printf("  Specifying Output File Name (-o):\n");
    printf("    To name your executable (e.g., 'my_program_executable'):\n");
    printf("    $ gcc my_program.c -o my_program_executable\n\n");
    printf("  Enabling Warnings (Highly Recommended!):\n");
    printf("    Warnings help catch potential bugs and bad practices.\n");
    printf("    -Wall: Enables many common warnings.\n");
    printf("    -Wextra: Enables additional useful warnings.\n");
    printf("    -Wpedantic: Issues all warnings demanded by strict ISO C standard.\n");
    printf("    Example: $ gcc my_program.c -o my_program -Wall -Wextra\n\n");
    printf("  Specifying C Standard (-std=):\n");
    printf("    You can tell GCC which C standard to use (e.g., C99, C11, C17).\n");
    printf("    -std=c99\n");
    printf("    -std=c11 (a good modern default)\n");
    printf("    -std=c17\n");
    printf("    Example: $ gcc my_program.c -o my_program -Wall -Wextra -std=c11\n\n");
    printf("  Including Debug Information (-g):\n");
    printf("    To allow debuggers (like GDB) to step through your code effectively:\n");
    printf("    $ gcc -g my_program.c -o my_program -Wall -Wextra -std=c11\n\n");
    printf("  Optimization Flags (-O):\n");
    printf("    GCC can optimize your code for speed or size.\n");
    printf("    -O0: No optimization (good for debugging, usually the default without -g).\n");
    printf("    -O1, -O2, -O3: Increasing levels of optimization (can make debugging harder).\n");
    printf("    -Os: Optimize for size.\n");
    printf("    Example (common optimization): $ gcc -O2 my_program.c -o my_program\n");
    printf("    For development and debugging, often -g is used without -O or with -O0.\n");
    printf("    For release, -O2 or -O3 might be used.\n\n");
    printf("  Putting it all together (a good general development command):\n");
    printf("    $ gcc -g my_program.c -o my_program -Wall -Wextra -Wpedantic -std=c11\n\n");

    // --- Section 2: Integer Data Types ---
    // This section introduces various integer data types available in C.
    // It demonstrates their declaration, initialization, typical sizes (using sizeof),
    // and how to print them using printf with appropriate format specifiers.
    // It covers: int, short, long, long long, and their unsigned counterparts.
    // The use of suffixes (L, LL, U, UL, ULL) for integer literals is also noted.
    printf("\n----------------------------------------\n");
    printf("  Section 2: Integer Data Types\n");
    printf("----------------------------------------\n");
    printf("Integer types store whole numbers. C offers various sizes.\n\n");
    printf("  --- The 'int' Type ---\n");
    printf("  'int' is the most common integer type. Usually 4 bytes on modern systems.\n");
    int an_integer = 42;
    printf("  Example int value: %d\n", an_integer);
    printf("  Size of 'int' type on this system: %zu bytes\n", sizeof(int));
    printf("  Size of 'an_integer' variable: %zu bytes\n\n", sizeof(an_integer));
    printf("  --- The 'short' type ---\n");
    printf("  'short' (or 'short int') is an integer type that uses less storage than 'int'.\n");
    printf("  It is guaranteed to be at least 16 bits (2 bytes).\n");
    short a_short = 77;
    printf("  Example short value: %hd\n", a_short);
    printf("  Size of 'short' type on this system: %zu bytes\n", sizeof(short));
    printf("  Size of 'a_short' variable: %zu bytes\n\n", sizeof(a_short));
    printf("  --- The 'long' type ---\n");
    printf("  'long' (or 'long int') is used for integers that might be larger than 'int'.\n");
    printf("  It is guaranteed to be at least 32 bits (4 bytes).\n");
    printf("  On many 64-bit systems, 'long' is 64 bits (8 bytes).\n");
    long large_number = 1234567890L;
    printf("  Example long value: %ld\n", large_number);
    printf("  Size of 'long' type on this system: %zu bytes\n", sizeof(long));
    printf("  Size of 'large_number' variable: %zu bytes\n\n", sizeof(large_number));
    printf("  --- The 'long long' type ---\n");
    printf("  'long long' (or 'long long int') is for even larger integer values (C99 and later).\n");
    printf("  It is guaranteed to be at least 64 bits (8 bytes).\n");
    long long very_large_number = 987654321098765432LL;
    printf("  Example long long value: %lld\n", very_large_number);
    printf("  Size of 'long long' type on this system: %zu bytes\n", sizeof(long long));
    printf("  Size of 'very_large_number' variable: %zu bytes\n\n", sizeof(very_large_number));
    printf("  --- The 'unsigned int' type ---\n");
    printf("  'unsigned int' stores non-negative 'int' integer values.\n");
    unsigned int positive_counter = 65000U;
    printf("  Example unsigned int value: %u\n", positive_counter);
    printf("  Size of 'unsigned int' type: %zu bytes\n", sizeof(unsigned int));
    printf("  Size of 'positive_counter': %zu bytes\n\n", sizeof(positive_counter));
    printf("  --- The 'unsigned long' type ---\n");
    printf("  'unsigned long' stores non-negative 'long' integer values.\n");
    unsigned long positive_large_num = 4000000000UL;
    printf("  Example unsigned long value: %lu\n", positive_large_num);
    printf("  Size of 'unsigned long' type: %zu bytes\n", sizeof(unsigned long));
    printf("  Size of 'positive_large_num': %zu bytes\n\n", sizeof(positive_large_num));
    printf("  --- The 'unsigned long long' type ---\n");
    printf("  'unsigned long long' stores non-negative 'long long' integer values.\n");
    unsigned long long very_positive_large_num = 18000000000000000000ULL;
    printf("  Example unsigned long long value: %llu\n", very_positive_large_num);
    printf("  Size of 'unsigned long long' type: %zu bytes\n", sizeof(unsigned long long));
    printf("  Size of 'very_positive_large_num': %zu bytes\n\n", sizeof(very_positive_large_num));
    printf("  Note on Integer Suffixes: L, LL, U, UL, ULL are used for integer literals\n");
    printf("  to specify their type explicitly (e.g., 10L is a long, 10U is unsigned int).\n\n");

    // --- Section 3: Character Data Type (char) ---
    // This section focuses on the 'char' data type.
    // It explains its use for storing single characters or small integers, its typical size,
    // and its relation to ASCII values.
    // Differences between 'signed char', 'unsigned char', and plain 'char' are discussed.
    // Common escape sequences (like \n, \t, \', \", \\, \0) are demonstrated.
    printf("\n----------------------------------------\n");
    printf("  Section 3: Character Data Type (char)\n");
    printf("----------------------------------------\n");
    printf("'char' is used to store single characters or small integers.\n");
    printf("It typically occupies 1 byte (8 bits) of memory.\n");
    printf("Characters are often represented by their ASCII or UTF-8 numerical value.\n\n");
    printf("  --- Basic char Usage ---\n");
    char my_letter = 'G';
    char my_digit_char = '5';
    char another_char_val = 65;
    printf("  Character variable 'my_letter': %c\n", my_letter);
    printf("  Numerical (ASCII) value of 'my_letter' (%c): %d\n", my_letter, my_letter);
    printf("  Character variable 'my_digit_char': %c\n", my_digit_char);
    printf("  Numerical (ASCII) value of 'my_digit_char' (%c): %d\n", my_digit_char, my_digit_char);
    printf("  Character initialized with ASCII 65: %c\n", another_char_val);
    printf("  Size of 'char' type on this system: %zu byte\n", sizeof(char));
    printf("  Size of 'my_letter' variable: %zu byte\n\n", sizeof(my_letter));
    printf("  --- signed char vs. unsigned char vs. plain char ---\n");
    printf("  'signed char': Can hold values typically from -128 to 127.\n");
    printf("  'unsigned char': Can hold values typically from 0 to 255.\n");
    printf("  Plain 'char': Whether it's signed or unsigned by default is implementation-defined.\n");
    printf("                It always has a size of 1 byte.\n");
    signed char sc = -10;
    unsigned char uc = 250;
    printf("  Example signed char value: %d\n", sc);
    printf("  Example unsigned char value: %u\n", uc);
    printf("  Size of 'signed char': %zu byte, Size of 'unsigned char': %zu byte\n\n", sizeof(signed char), sizeof(unsigned char));
    printf("  --- Escape Sequences ---\n");
    printf("  Escape sequences represent special characters using a backslash '\\'.\n");
    printf("  Common escape sequences:\n");
    printf("  '\\n' - Newline:      Line 1.\n                       Line 2 after newline.\n");
    printf("  '\\t' - Horizontal Tab:Col1\tCol2\tCol3\n");
    char single_quote_char = '\'';
    printf("  '\\'' - Single Quote:  '%c'\n", single_quote_char);
    printf("  '\\\"' - Double Quote:  \"This is a quote.\"\n");
    printf("  '\\\\' - Backslash:     C:\\Path\\To\\File\n");
    char null_char = '\0';
    printf("  '\\0' - Null Character: Integer value is %d. Crucial for C strings.\n", null_char);
    printf("  '\\xHH' - Hex value:   Character with hex 41 is '\\x41' -> %c (A)\n", '\x41');
    printf("  '\\OOO' - Octal value:  Character with octal 102 is '\\102' -> %c (B)\n\n", '\102');

    // --- Section 4: Floating-Point Data Types ---
    // This section covers floating-point types: 'float', 'double', and 'long double'.
    // It explains their purpose (storing numbers with fractional parts), typical sizes,
    // precision, and the use of suffixes (f, F, l, L) for literals.
    // Important considerations like precision limitations, comparison issues (avoiding ==),
    // and special values (Inf, NaN) are highlighted.
    printf("\n----------------------------------------\n");
    printf("  Section 4: Floating-Point Data Types\n");
    printf("----------------------------------------\n");
    printf("Floating-point types store numbers with a fractional part.\n");
    printf("They represent numbers using a form of scientific notation (mantissa and exponent).\n\n");
    printf("  --- The 'float' Type (Single-precision) ---\n");
    printf("  'float' is typically a 32-bit (4 bytes) floating-point number.\n");
    printf("  It offers about 6-7 decimal digits of precision.\n");
    printf("  Use 'f' or 'F' suffix for float literals (e.g., 3.14f), otherwise it's a double.\n");
    float f_pi_approx = 3.14159f;
    float f_another_val = 1.23456789f;
    printf("  Example float value (f_pi_approx): %f\n", f_pi_approx);
    printf("  f_pi_approx to 2 decimal places: %.2f\n", f_pi_approx);
    printf("  f_pi_approx in scientific notation: %e\n", f_pi_approx);
    printf("  Another float (f_another_val showing precision limit): %.10f\n", f_another_val);
    printf("  Size of 'float' type: %zu bytes\n\n", sizeof(float));
    printf("  --- The 'double' Type (Double-precision) ---\n");
    printf("  'double' is typically a 64-bit (8 bytes) floating-point number.\n");
    printf("  It offers about 15-16 decimal digits of precision.\n");
    printf("  This is the default type for floating-point literals (e.g., 3.14159).\n");
    double d_precise_e = 2.718281828459045;
    double d_fraction = 1.0 / 3.0;
    printf("  Example double value (d_precise_e): %lf\n", d_precise_e);
    printf("  d_precise_e to 10 decimal places: %.10lf\n", d_precise_e);
    printf("  d_precise_e in scientific notation: %le\n", d_precise_e);
    printf("  A fraction (1.0/3.0 as double): %.16lf\n", d_fraction);
    printf("  Size of 'double' type: %zu bytes\n\n", sizeof(double));
    printf("  --- The 'long double' Type (Extended-precision) ---\n");
    printf("  'long double' provides precision greater than or equal to 'double'.\n");
    printf("  Its size is implementation-defined (e.g., 10, 12, or 16 bytes).\n");
    printf("  Use 'L' or 'l' suffix for long double literals (e.g., 0.1L).\n");
    long double ld_val = 0.1234567890123456789L;
    printf("  Example long double value (ld_val): %Lf\n", ld_val);
    printf("  ld_val to 20 decimal places: %.20Lf\n", ld_val);
    printf("  Size of 'long double' type on this system: %zu bytes\n\n", sizeof(long double));
    printf("  --- Important Notes on Floating-Point Numbers ---\n");
    printf("  1. Precision, Not Exactness: Due to binary representation, many decimal fractions\n");
    printf("     (like 0.1) cannot be stored *exactly*. This leads to small rounding errors.\n");
    float f_point_one = 0.1f;
    double d_point_one = 0.1;
    printf("     0.1f as float:  %.10f\n", f_point_one);
    printf("     0.1 as double: %.20lf\n", d_point_one);
    printf("  2. Comparison: Avoid direct equality checks (== or !=) with floats/doubles.\n");
    printf("     Instead, check if their absolute difference is within a small tolerance (epsilon).\n");
    if (fabs((0.1f + 0.2f) - 0.3f) < 0.000001f) {
        printf("     (0.1f + 0.2f) is close to 0.3f\n");
    } else {
        printf("     (0.1f + 0.2f) is NOT close to 0.3f\n");
        printf("     Value of (0.1f + 0.2f): %.10f,  0.3f is %.10f\n", (0.1f + 0.2f), 0.3f);
    }
    printf("  3. Special Values: Floats/doubles can represent Infinity (Inf) and Not-a-Number (NaN).\n");
    printf("     e.g., 1.0/0.0 yields %f, sqrt(-1.0) yields %f (requires <math.h>)\n\n", 1.0 / 0.0, sqrt(-1.0));

    // --- Section 5: C Operators ---
    // This section provides a comprehensive overview of various operators in C.
    // It is broken down into subsections for clarity:
    // 5.1 Arithmetic Operators: +, -, *, /, %
    // 5.2 Assignment Operators: =, +=, -=, *=, /=, %=
    // 5.3 Increment/Decrement Operators: ++, -- (prefix and postfix)
    // 5.4 Relational Operators: ==, !=, >, <, >=, <=
    // 5.5 Logical Operators: &&, ||, ! (including short-circuiting behavior)
    // 5.6 Bitwise Operators: &, |, ^, ~, <<, >>
    // 5.7 Conditional (Ternary) Operator: condition ? true_expr : false_expr
    // 5.8 sizeof Operator: Returns the size of a type or variable.
    // 5.9 Comma Operator: Evaluates multiple expressions, value is the rightmost.
    // 5.10 Operator Precedence and Associativity: Rules governing evaluation order.
    printf("\n----------------------------------------\n");
    printf("  Section 5: C Operators\n");
    printf("----------------------------------------\n");
    printf("Operators are symbols that perform operations on operands (values/variables).\n\n");
    printf("  --- 5.1 Arithmetic Operators ---\n");
    printf("  Used for mathematical calculations.\n");
    int arith_a = 10, arith_b = 4;
    double arith_x = 10.0, arith_y = 4.0;
    printf("  Let int a = %d, int b = %d; double x = %.1f, double y = %.1f\n", arith_a, arith_b, arith_x, arith_y);
    printf("  Addition (a + b):        %d + %d = %d\n", arith_a, arith_b, arith_a + arith_b);
    printf("  Subtraction (a - b):     %d - %d = %d\n", arith_a, arith_b, arith_a - arith_b);
    printf("  Multiplication (a * b):  %d * %d = %d\n", arith_a, arith_b, arith_a * arith_b);
    printf("  Division (/):\n");
    printf("    Integer division (a / b): %d / %d = %d (truncates decimal)\n", arith_a, arith_b, arith_a / arith_b);
    printf("    Floating-point division (x / y): %.1f / %.1f = %.2f\n", arith_x, arith_y, arith_x / arith_y);
    printf("    Mixed division ((double)a / b): (double)%d / %d = %.2f\n", arith_a, arith_b, (double)arith_a / arith_b);
    printf("  Modulus (%%) (remainder of integer division):\n");
    printf("    a %% b: %d %% %d = %d\n", arith_a, arith_b, arith_a % arith_b);
    printf("    10 %% 3 = %d\n", 10 % 3);
    printf("    11 %% 3 = %d\n\n", 11 % 3);
    printf("  --- 5.2 Assignment Operators ---\n");
    printf("  Used to assign values to variables.\n");
    int assign_val = 10;
    printf("  Initial value of assign_val: %d\n", assign_val);
    assign_val = 20;
    printf("  Basic assignment (=): assign_val = 20; -> assign_val is now %d\n", assign_val);
    printf("  Compound Assignment Operators (shorthand):\n");
    int current_assign_val = assign_val;
    assign_val += 5;
    printf("    assign_val (was %d) += 5; (assign_val = assign_val + 5) -> assign_val is now %d\n", current_assign_val, assign_val);
    current_assign_val = assign_val;
    assign_val -= 3;
    printf("    assign_val (was %d) -= 3; (assign_val = assign_val - 3) -> assign_val is now %d\n", current_assign_val, assign_val);
    current_assign_val = assign_val;
    assign_val *= 2;
    printf("    assign_val (was %d) *= 2; (assign_val = assign_val * 2) -> assign_val is now %d\n", current_assign_val, assign_val);
    current_assign_val = assign_val;
    assign_val /= 4;
    printf("    assign_val (was %d) /= 4; (assign_val = assign_val / 4) -> assign_val is now %d\n", current_assign_val, assign_val);
    current_assign_val = assign_val;
    assign_val %= 3;
    printf("    assign_val (was %d) %%= 3; (assign_val = assign_val %% 3) -> assign_val is now %d\n\n", current_assign_val, assign_val);
    printf("  --- 5.3 Increment (++) and Decrement (--) Operators ---\n");
    printf("  Increase or decrease a variable's value by 1.\n");
    int counter_op = 5; 
    int result_incr_decr;
    printf("  Initial counter_op = %d\n", counter_op);
    printf("  Prefix Increment (++counter_op):\n");
    printf("    Increments 'counter_op' THEN uses its value.\n");
    result_incr_decr = ++counter_op;
    printf("    After 'result = ++counter_op;': result = %d, counter_op = %d\n", result_incr_decr, counter_op);
    counter_op = 5;
    printf("  Reset counter_op = %d\n", counter_op);
    printf("  Postfix Increment (counter_op++):\n");
    printf("    Uses 'counter_op's current value THEN increments it.\n");
    result_incr_decr = counter_op++;
    printf("    After 'result = counter_op++;': result = %d, counter_op = %d\n", result_incr_decr, counter_op);
    counter_op = 5;
    printf("  Reset counter_op = %d\n", counter_op);
    printf("  Prefix Decrement (--counter_op):\n");
    result_incr_decr = --counter_op;
    printf("    After 'result = --counter_op;': result = %d, counter_op = %d\n", result_incr_decr, counter_op);
    counter_op = 5;
    printf("  Reset counter_op = %d\n", counter_op);
    printf("  Postfix Decrement (counter_op--):\n");
    result_incr_decr = counter_op--;
    printf("    After 'result = counter_op--;': result = %d, counter_op = %d\n\n", result_incr_decr, counter_op);
    printf("  --- 5.4 Relational Operators ---\n");
    printf("  Used to compare two values. Result is 1 (true) or 0 (false).\n");
    int rel_x = 5, rel_y = 10, rel_z = 5;
    printf("  Let x = %d, y = %d, z = %d\n", rel_x, rel_y, rel_z);
    printf("  x == z (Equal to):         %d == %d -> %d\n", rel_x, rel_z, rel_x == rel_z);
    printf("  x == y (Equal to):         %d == %d -> %d\n", rel_x, rel_y, rel_x == rel_y);
    printf("  x != y (Not equal to):     %d != %d -> %d\n", rel_x, rel_y, rel_x != rel_y);
    printf("  x > y  (Greater than):     %d > %d  -> %d\n", rel_x, rel_y, rel_x > rel_y);
    printf("  x < y  (Less than):        %d < %d  -> %d\n", rel_x, rel_y, rel_x < rel_y);
    printf("  y >= z (Greater or equal): %d >= %d -> %d\n", rel_y, rel_z, rel_y >= rel_z);
    printf("  x <= z (Less or equal):    %d <= %d -> %d\n\n", rel_x, rel_z, rel_x <= rel_z);
    printf("  --- 5.5 Logical Operators ---\n");
    printf("  Used to combine or negate conditions. Operands treated as true (non-zero) or false (0).\n");
    printf("  Result is 1 (true) or 0 (false).\n");
    int log_a_val = 1, log_b_val = 0, log_c_val = 5;
    int logical_op_side_effect_check;
    printf("  Let a = %d (true), b = %d (false), c = %d (true)\n", log_a_val, log_b_val, log_c_val);
    printf("  Logical AND (&&): expr1 && expr2 -> 1 if both are true, else 0.\n");
    printf("    a && c (%d && %d): %d\n", log_a_val, log_c_val, log_a_val && log_c_val);
    printf("    a && b (%d && %d): %d\n", log_a_val, log_b_val, log_a_val && log_b_val);
    printf("    Short-circuiting for &&: If expr1 is false, expr2 is not evaluated.\n");
    logical_op_side_effect_check = 0;
    int result_and = (log_b_val && ((logical_op_side_effect_check = 1), 1));
    printf("    (b && (expr_with_side_effect)): result = %d. Side effect check = %d (0 means not executed).\n\n", result_and, logical_op_side_effect_check);
    printf("  Logical OR (||): expr1 || expr2 -> 1 if at least one is true, else 0.\n");
    printf("    a || b (%d || %d): %d\n", log_a_val, log_b_val, log_a_val || log_b_val);
    printf("    b || b (%d || %d): %d\n", log_b_val, log_b_val, log_b_val || log_b_val);
    printf("    Short-circuiting for ||: If expr1 is true, expr2 is not evaluated.\n");
    logical_op_side_effect_check = 0;
    int result_or = (log_a_val || ((logical_op_side_effect_check = 1), 0));
    printf("    (a || (expr_with_side_effect)): result = %d. Side effect check = %d (0 means not executed).\n\n", result_or, logical_op_side_effect_check);
    printf("  Logical NOT (!): !expr -> 1 if expr is false (0), 0 if expr is true (non-zero).\n");
    printf("    !a (!%d): %d\n", log_a_val, !log_a_val);
    printf("    !b (!%d): %d\n\n", log_b_val, !log_b_val);
    printf("  --- 5.6 Bitwise Operators ---\n");
    printf("  Perform operations on individual bits of integer operands.\n");
    unsigned char bit_a_val = 0x0F;
    unsigned char bit_b_val = 0x33;
    printf("  Let unsigned char a = 0x%02X (00001111), b = 0x%02X (00110011)\n", bit_a_val, bit_b_val);
    printf("  Bitwise AND (&): Sets a bit if it's set in both operands.\n");
    printf("    a & b (0x%02X & 0x%02X) = 0x%02X (Binary: 00000011)\n", bit_a_val, bit_b_val, bit_a_val & bit_b_val);
    printf("  Bitwise OR (|): Sets a bit if it's set in either operand.\n");
    printf("    a | b (0x%02X | 0x%02X) = 0x%02X (Binary: 00111111)\n", bit_a_val, bit_b_val, bit_a_val | bit_b_val);
    printf("  Bitwise XOR (^): Sets a bit if it's set in one operand but not both (exclusive OR).\n");
    printf("    a ^ b (0x%02X ^ 0x%02X) = 0x%02X (Binary: 00111100)\n", bit_a_val, bit_b_val, bit_a_val ^ bit_b_val);
    printf("  Bitwise NOT (~): Inverts all bits of the operand.\n");
    printf("    ~a (~0x%02X where a is unsigned char) = 0x%02X (Binary: 11110000)\n", bit_a_val, (unsigned char)(~bit_a_val));
    unsigned char bit_c_val = 0x81;
    printf("  Left Shift (<<): Shifts bits to the left, fills right with 0s.\n");
    printf("    c = 0x%02X (10000001)\n", bit_c_val);
    printf("    c << 1 (0x%02X << 1) = 0x%02X (Binary: 00000010, high bit shifted out)\n", bit_c_val, (unsigned char)(bit_c_val << 1));
    printf("    c << 2 (0x%02X << 2) = 0x%02X (Binary: 00000100)\n", bit_c_val, (unsigned char)(bit_c_val << 2));
    printf("  Right Shift (>>): Shifts bits to the right.\n");
    printf("    For unsigned types, fills left with 0s (logical shift).\n");
    printf("    For signed types, behavior for negative numbers can be implementation-defined.\n");
    printf("    c = 0x%02X (10000001)\n", bit_c_val);
    printf("    c >> 1 (0x%02X >> 1) = 0x%02X (Binary: 01000000)\n", bit_c_val, (unsigned char)(bit_c_val >> 1));
    printf("    c >> 2 (0x%02X >> 2) = 0x%02X (Binary: 00100000)\n\n", bit_c_val, (unsigned char)(bit_c_val >> 2));
    printf("  --- 5.7 Conditional (Ternary) Operator ---\n");
    printf("  A shorthand for an if-else statement. Syntax: condition ? expr_if_true : expr_if_false\n");
    int cond_a_val = 10, cond_b_val = 20;
    int max_val_cond;
    printf("  Let a = %d, b = %d\n", cond_a_val, cond_b_val);
    max_val_cond = (cond_a_val > cond_b_val) ? cond_a_val : cond_b_val;
    printf("  max_val = (a > b) ? a : b;  ->  max_val = %d\n", max_val_cond);
    char *message = (cond_a_val % 2 == 0) ? "a is even" : "a is odd";
    printf("  (a %% 2 == 0) ? \"a is even\" : \"a is odd\" -> message: \"%s\"\n\n", message);
    printf("  --- 5.8 sizeof Operator (Revisited) ---\n");
    printf("  Returns the size (in bytes) of a data type or a variable.\n");
    printf("  It's a compile-time operator (mostly; VLA in C99 is an exception).\n");
    printf("  Size of int: %zu bytes\n", sizeof(int));
    double d_var_for_sizeof = 3.14;
    printf("  Size of a double variable 'd_var_for_sizeof': %zu bytes\n", sizeof(d_var_for_sizeof));
    printf("  Size of char[10] (array of 10 chars): %zu bytes\n\n", sizeof(char[10]));
    printf("  --- 5.9 Comma Operator (,) ---\n");
    printf("  Evaluates expressions from left to right, and the value of the entire\n");
    printf("  comma-separated expression is the value of the rightmost expression.\n");
    int comma_x = 5, comma_y = 10, comma_z;
    printf("  Let x = %d, y = %d\n", comma_x, comma_y);
    comma_z = (comma_x++, comma_y += comma_x, comma_y + 5);
    printf("  z = (x++, y += x, y + 5); -> x = %d, y = %d, z = %d\n", comma_x, comma_y, comma_z);
    printf("  Often used in 'for' loops: for (i=0, j=10; i < j; i++, j--)\n\n");
    printf("  --- 5.10 Operator Precedence and Associativity ---\n");
    printf("  Precedence: Determines the order in which operators are evaluated in an expression.\n");
    printf("              (e.g., * and / before + and -).\n");
    printf("  Associativity: Determines the order for operators of the SAME precedence.\n");
    printf("                 (e.g., Left-to-right for +, -, *, /; Right-to-left for assignment =).\n");
    int prec_a = 2, prec_b = 3, prec_c = 4, prec_result;
    prec_result = prec_a + prec_b * prec_c;
    printf("  a=2, b=3, c=4. Result of a + b * c = %d (due to * higher precedence than +)\n", prec_result);
    prec_result = (prec_a + prec_b) * prec_c;
    printf("  Result of (a + b) * c = %d (parentheses override precedence)\n", prec_result);
    int assign_x_op, assign_y_op, assign_z_op = 10;
    assign_x_op = assign_y_op = assign_z_op;
    printf("  x = y = z = 10; -> x=%d, y=%d, z=%d (assignment is right-to-left)\n", assign_x_op, assign_y_op, assign_z_op);
    printf("  It's good practice to use parentheses to make order explicit if unsure.\n\n");

    // --- Section 6: Control Flow Structures ---
    // This section explains structures that control the order of statement execution.
    // 6.1 Conditional Statements: if, else if, else for decision making.
    // 6.2 Switch Statement: Multi-way branching based on an integral expression.
    // 6.3 Loops:
    //     6.3.1 for Loop: Iteration with initialization, condition, and update.
    //     6.3.2 while Loop: Iteration as long as a condition is true (pre-test).
    //     6.3.3 do-while Loop: Iteration with condition checked after execution (post-test).
    // 6.4 Jump Statements:
    //     break: Exits loops or switch statements.
    //     continue: Skips to the next iteration of a loop.
    // 6.5 goto Statement: Unconditional jump to a label (use with caution).
    printf("\n----------------------------------------\n");
    printf("  Section 6: Control Flow Structures\n");
    printf("----------------------------------------\n");
    printf("Control flow structures determine the order in which statements are executed.\n\n");
    printf("  --- 6.1 Conditional Statements: if, else if, else ---\n");
    printf("  Execute blocks of code based on conditions (true/false).\n");
    int score = 85;
    printf("  Let score = %d\n", score);
    printf("  Example 1: Simple if\n");
    if (score > 50) {
        printf("    score (%d) is greater than 50. Well done!\n", score);
    }
    printf("  Example 2: if-else\n");
    int number_check = 7;
    if (number_check % 2 == 0) {
        printf("    %d is even.\n", number_check);
    } else {
        printf("    %d is odd.\n", number_check);
    }
    printf("  Example 3: if-else if-else (Grading)\n");
    printf("    Current score: %d\n", score);
    if (score >= 90) {
        printf("    Grade: A\n");
    } else if (score >= 80) {
        printf("    Grade: B\n");
    } else if (score >= 70) {
        printf("    Grade: C\n");
    } else if (score >= 60) {
        printf("    Grade: D\n");
    } else {
        printf("    Grade: F\n");
    }
    printf("  Note: Curly braces {} can be omitted for a single statement in if/else,\n");
    printf("        but it's good practice to always use them to avoid errors.\n\n");
    printf("  --- 6.2 Switch Statement ---\n");
    printf("  Selects one of many code blocks to be executed based on the value of an expression.\n");
    printf("  The expression must evaluate to an integral type (char, int, enum).\n");
    char grade_char = 'B';
    printf("  Let grade = '%c'\n", grade_char);
    printf("  Switching on grade:\n");
    switch (grade_char) {
    case 'A':
        printf("    Excellent!\n");
        break;
    case 'B':
        printf("    Good job!\n");
        break;
    case 'C':
        printf("    Satisfactory.\n");
        break;
    case 'D':
        printf("    Needs improvement.\n");
        break;
    case 'F':
        printf("    Failed.\n");
        break;
    default:
        printf("    Invalid grade.\n");
    }
    printf("  Key points for switch:\n");
    printf("    - 'case' labels must be constant integral expressions.\n");
    printf("    - 'break' is crucial to prevent fall-through to the next case.\n");
    printf("    - 'default' handles values not covered by specific cases.\n\n");
    printf("  --- 6.3 Loops (Iteration Statements) ---\n");
    printf("  Execute a block of code repeatedly.\n\n");
    printf("    --- 6.3.1 for Loop ---\n");
    printf("    Typically used when the number of iterations is known.\n");
    printf("    Syntax: for (initialization; condition; increment/decrement)\n");
    printf("    Counting from 1 to 3:\n");
    for (int i_for = 1; i_for <= 3; i_for++) {
        printf("      Iteration %d\n", i_for);
    }
    printf("    Multiple initializations/increments using comma operator:\n");
    for (int j_for = 0, k_for = 5; j_for < k_for; j_for++, k_for--) {
        printf("      j = %d, k = %d\n", j_for, k_for);
    }
    printf("\n");
    printf("    --- 6.3.2 while Loop ---\n");
    printf("    Repeats as long as a condition is true. Condition checked *before* each iteration.\n");
    int count_while = 3;
    printf("    Counting down from %d with while:\n", count_while);
    while (count_while > 0) {
        printf("      count_while = %d\n", count_while);
        count_while--;
    }
    printf("      After loop, count_while = %d\n\n", count_while);
    printf("    --- 6.3.3 do-while Loop ---\n");
    printf("    Similar to while, but condition is checked *after* each iteration.\n");
    printf("    Guarantees the loop body executes at least once.\n");
    int count_do_while = 0;
    printf("    Example with do-while (starts with count_do_while = %d):\n", count_do_while);
    do {
        printf("      Inside do-while, count_do_while = %d\n", count_do_while);
        count_do_while++;
    } while (count_do_while < 0);
    printf("      After loop, count_do_while = %d (ran once)\n", count_do_while);
    count_do_while = 1;
    printf("    Another do-while example (starts with count_do_while = %d, condition count_do_while < 3):\n", count_do_while);
    do {
        printf("      Inside do-while, count_do_while = %d\n", count_do_while);
        count_do_while++;
    } while (count_do_while < 3);
    printf("      After loop, count_do_while = %d\n\n", count_do_while);
    printf("  --- 6.4 Jump Statements: break and continue ---\n");
    printf("  Alter the normal flow of control within loops or switch statements.\n\n");
    printf("    --- break Statement ---\n");
    printf("    Exits the innermost loop (for, while, do-while) or switch statement immediately.\n");
    printf("    Example: Find first number divisible by 3 in a loop (1 to 10):\n");
    int num_break;
    for (num_break = 1; num_break <= 10; num_break++) {
        if (num_break % 3 == 0) {
            printf("      Found %d (divisible by 3). Breaking loop.\n", num_break);
            break;
        }
        printf("      Checked %d...\n", num_break);
    }
    printf("      After break loop, num_break = %d\n\n", num_break);
    printf("    --- continue Statement ---\n");
    printf("    Skips the rest of the current iteration of a loop and proceeds to the next iteration.\n");
    printf("    Example: Print odd numbers from 1 to 5 using continue:\n");
    int num_continue;
    for (num_continue = 1; num_continue <= 5; num_continue++) {
        if (num_continue % 2 == 0) {
            printf("      Skipping even number %d with continue.\n", num_continue);
            continue;
        }
        printf("      Odd number: %d\n", num_continue);
    }
    printf("\n");
    printf("  --- 6.5 goto Statement ---\n");
    printf("  Transfers control unconditionally to a labeled statement within the same function.\n");
    printf("  WARNING: 'goto' can make code hard to read and debug. Use sparingly, if at all.\n");
    printf("           It's often better to refactor using loops or functions.\n");
    int goto_count = 0;
    printf("  goto example (simulating a loop, generally bad practice):\n");
my_label:
    if (goto_count < 2) {
        printf("    goto_count = %d\n", goto_count);
        goto_count++;
        goto my_label;
    }
    printf("    After goto 'loop', goto_count = %d\n", goto_count);
    printf("  A more legitimate (though still rare) use might be for breaking out of nested loops,\n");
    printf("  or for a common cleanup point at the end of a function.\n\n");

    // --- Section 7: Functions ---
    // This section delves into functions in C.
    // 7.1 Declaration (Prototype) & Definition: How to declare and define functions.
    // 7.2 Calling Functions: How to invoke functions and pass arguments.
    // 7.3 Return Values: How functions return values (or 'void' for no return).
    // 7.4 Parameters and Arguments (Pass-by-Value): C's mechanism of passing copies of arguments.
    // 7.5 Scope of Variables:
    //     Local Variables: Confined to a function or block.
    //     Global Variables: Accessible throughout the file (or program if extern).
    // Function prototypes are shown at the top of the file, definitions at the bottom.
    printf("\n----------------------------------------\n");
    printf("  Section 7: Functions\n");
    printf("----------------------------------------\n");
    printf("Functions are blocks of code that perform a specific task and can be reused.\n\n");
    printf("  --- 7.1 Function Declaration (Prototype) & Definition ---\n");
    printf("  Declaration (Prototype): Tells the compiler about the function's name, \n");
    printf("                           return type, and parameters before it's used.\n");
    printf("                           (See prototypes defined before main() in this file).\n");
    printf("  Definition: Contains the actual code (statements) of the function.\n");
    printf("              (See definitions after main() in this file).\n\n");
    printf("  --- 7.2 Calling Functions ---\n");
    printf("  Calling greet():\n    ");
    greet();
    int num1 = 10, num2 = 25;
    int sum_result = add_numbers(num1, num2);
    printf("  Calling add_numbers(%d, %d): Result = %d\n", num1, num2, sum_result);
    double val_to_square = 5.5;
    double squared_val = calculate_square(val_to_square);
    printf("  Calling calculate_square(%.1f): Result = %.2f\n\n", val_to_square, squared_val);
    printf("  --- 7.3 Return Values ---\n");
    printf("  Functions can return a single value of a specified type using 'return'.\n");
    printf("  'void' return type means the function does not return a value (e.g., greet()).\n");
    printf("  'add_numbers' returns an 'int', 'calculate_square' returns a 'double'.\n\n");
    printf("  --- 7.4 Parameters and Arguments (Pass-by-Value) ---\n");
    printf("  Parameters: Variables listed in the function declaration/definition.\n");
    printf("  Arguments: Actual values passed to the function when it is called.\n");
    printf("  C uses 'pass-by-value': A copy of the argument's value is passed to the function.\n");
    printf("  Modifications to parameters inside the function do NOT affect the original arguments.\n");
    int original_value = 50;
    printf("  Original value before calling try_to_modify(): %d\n", original_value);
    try_to_modify(original_value);
    printf("  Original value after calling try_to_modify(): %d (remains unchanged)\n\n", original_value);
    printf("  --- 7.5 Scope of Variables ---\n");
    printf("  Scope: The region of the program where a variable is accessible.\n");
    printf("  Local Variables: Declared inside a function or block {}. Accessible only within that function/block.\n");
    printf("                   They are created when the function/block is entered and destroyed when exited.\n");
    int local_in_main = 77;
    printf("  'local_in_main' (value: %d) is local to main().\n", local_in_main);
    printf("  Calling function_with_local_scope() which has its own local variable:\n");
    int scope_test_result = function_with_local_scope();
    printf("  Result from function_with_local_scope(): %d\n", scope_test_result);
    printf("  Global Variables: Declared outside all functions. Accessible from any function in the file\n");
    printf("                    (after their declaration). Persist for the entire program execution.\n");
    printf("  Value of 'global_variable_example' (defined outside main): %d\n", global_variable_example);
    global_variable_example = 150;
    printf("  Modified 'global_variable_example': %d\n", global_variable_example);
    printf("  Note: Overuse of global variables can make code harder to manage and debug.\n\n");

    // --- Section 8: Arrays ---
    // This section explains arrays in C.
    // 8.1 Declaring and Initializing 1D Arrays: Different ways to create and populate arrays.
    // 8.2 Accessing Array Elements: Using 0-based indexing.
    // 8.3 Iterating Through an Array: Common use of for loops.
    // 8.4 Array Size (sizeof): Calculating total size and number of elements.
    // 8.5 Character Arrays (Strings): C-style strings as null-terminated char arrays.
    // 8.6 Multidimensional Arrays: Example of a 2D array (matrix).
    // 8.7 Arrays and Pointers: Brief introduction to array name decay to a pointer.
    // 8.8 No Bounds Checking: Important C caveat regarding array access.
    printf("\n----------------------------------------\n");
    printf("  Section 8: Arrays\n");
    printf("----------------------------------------\n");
    printf("Arrays store a fixed-size sequential collection of elements of the same type.\n\n");
    printf("  --- 8.1 Declaring and Initializing 1D Arrays ---\n");
    int uninitialized_array[3];
    (void)uninitialized_array;
    printf("  int uninitialized_array[3]; (Elements have indeterminate values if local & not static)\n");
    int simple_nums[5] = {10, 20, 30, 40, 50};
    printf("  int simple_nums[5] = {10, 20, 30, 40, 50};\n");
    float prices[] = {9.99f, 15.50f, 7.25f};
    printf("  float prices[] = {9.99f, 15.50f, 7.25f}; (Size inferred)\n");
    int partial_init[5] = {100, 200};
    printf("  int partial_init[5] = {100, 200}; (partial_init[0]=%d, partial_init[1]=%d, partial_init[2]=%d)\n\n",
           partial_init[0], partial_init[1], partial_init[2]);
    printf("  --- 8.2 Accessing Array Elements (0-based index) ---\n");
    printf("  simple_nums[0] = %d\n", simple_nums[0]);
    printf("  simple_nums[2] = %d\n", simple_nums[2]);
    simple_nums[0] = 11;
    printf("  After simple_nums[0] = 11;, simple_nums[0] is now %d\n\n", simple_nums[0]);
    printf("  --- 8.3 Iterating Through an Array (using a for loop) ---\n");
    printf("  Elements of simple_nums: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", simple_nums[i]);
    }
    printf("\n\n");
    printf("  --- 8.4 Array Size (sizeof) ---\n");
    printf("  sizeof(simple_nums) (total bytes): %zu bytes\n", sizeof(simple_nums));
    printf("  sizeof(simple_nums[0]) (bytes of one element): %zu bytes\n", sizeof(simple_nums[0]));
    int num_elements_simple = sizeof(simple_nums) / sizeof(simple_nums[0]);
    printf("  Number of elements in simple_nums: %d\n", num_elements_simple);
    int num_elements_prices = sizeof(prices) / sizeof(prices[0]);
    printf("  Number of elements in prices (inferred size): %d\n\n", num_elements_prices);
    printf("  --- 8.5 Character Arrays (Strings) ---\n");
    char greeting_message[] = "Hello C!";
    printf("  char greeting_message[] = \"Hello C!\";\n");
    printf("  Greeting: %s\n", greeting_message);
    printf("  sizeof(greeting_message): %zu bytes (includes null terminator)\n", sizeof(greeting_message));
    printf("  Individual characters: greeting_message[0]='%c', greeting_message[6]='%c'\n\n",
           greeting_message[0], greeting_message[6]);
    printf("  --- 8.6 Multidimensional Arrays (e.g., 2D Array) ---\n");
    int matrix[2][3] = {
        {1, 2, 3},
        {4, 5, 6}
    };
    printf("  int matrix[2][3] = {{1,2,3}, {4,5,6}};\n");
    printf("  Accessing matrix[0][1]: %d\n", matrix[0][1]);
    printf("  Accessing matrix[1][2]: %d\n", matrix[1][2]);
    printf("  Iterating through a 2D array:\n");
    for (int i = 0; i < 2; i++) {
        printf("    Row %d: ", i);
        for (int j = 0; j < 3; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("  sizeof(matrix): %zu bytes\n", sizeof(matrix));
    printf("  sizeof(matrix[0]): %zu bytes (size of one row: 3 * sizeof(int))\n", sizeof(matrix[0]));
    printf("  Number of rows: sizeof(matrix) / sizeof(matrix[0]) = %zu\n", sizeof(matrix) / sizeof(matrix[0]));
    printf("  Number of columns: sizeof(matrix[0]) / sizeof(matrix[0][0]) = %zu\n\n", sizeof(matrix[0]) / sizeof(matrix[0][0]));
    printf("  --- 8.7 Arrays and Pointers (Brief Introduction) ---\n");
    printf("  The name of an array often 'decays' to a pointer to its first element.\n");
    printf("  So, 'simple_nums' can be treated as '&simple_nums[0]'.\n");
    printf("  This is why when passing an array to a function, a pointer is actually passed.\n");
    printf("  More on this in the Pointers section.\n\n");
    printf("  --- 8.8 No Bounds Checking ---\n");
    printf("  C does NOT check if array indices are within bounds at runtime.\n");
    printf("  Accessing simple_nums[10] (when size is 5) is UNDEFINED BEHAVIOR.\n");
    printf("  This can lead to crashes or silent data corruption. Be careful!\n\n");

    // --- Section 9: Pointers ---
    // This section covers pointers, a fundamental concept in C.
    // 9.1 Declaring Pointers and Address-Of Operator (&): How to declare pointers and get addresses.
    // 9.2 The Dereference Operator (*): Accessing the value at a pointer's address.
    // 9.3 Null Pointers: Pointers not pointing to any valid memory location (NULL).
    // 9.4 Pointers and Arrays: Relationship between pointers and array names, pointer arithmetic for array traversal.
    // 9.5 Pointer Arithmetic: How arithmetic operations on pointers are scaled by type size.
    // 9.6 void Pointers (Generic Pointers): Pointers that can hold addresses of any type (require casting).
    // 9.7 Pointers to Pointers (Double Pointers): Pointers that store addresses of other pointers.
    // 9.8 Common Pointer Pitfalls: Uninitialized, null dereference, dangling pointers.
    printf("\n----------------------------------------\n");
    printf("  Section 9: Pointers\n");
    printf("----------------------------------------\n");
    printf("A pointer is a variable that stores the memory address of another variable.\n\n");
    printf("  --- 9.1 Declaring Pointers and the Address-Of Operator (&) ---\n");
    int var_age = 30;
    int *ptr_to_age;
    ptr_to_age = &var_age;
    printf("  int var_age = %d;\n", var_age);
    printf("  int *ptr_to_age;\n");
    printf("  ptr_to_age = &var_age;\n");
    printf("  Value of var_age: %d\n", var_age);
    printf("  Address of var_age (&var_age): %p\n", (void*)&var_age);
    printf("  Value of ptr_to_age (stores address of var_age): %p\n", (void*)ptr_to_age);
    printf("  Address of the pointer itself (&ptr_to_age): %p\n\n", (void*)&ptr_to_age);
    printf("  --- 9.2 The Dereference Operator (*) ---\n");
    printf("  Used to access the value at the address stored in a pointer.\n");
    if (ptr_to_age != NULL) {
        printf("  Value pointed to by ptr_to_age (*ptr_to_age): %d\n", *ptr_to_age);
        *ptr_to_age = 35;
        printf("  After *ptr_to_age = 35;\n");
        printf("  Value of var_age (modified via pointer): %d\n", var_age);
        printf("  Value pointed to by ptr_to_age (*ptr_to_age): %d\n\n", *ptr_to_age);
    } else {
        printf("  ptr_to_age is NULL, cannot dereference.\n\n");
    }
    var_age = 30;
    printf("  --- 9.3 Null Pointers ---\n");
    int *null_ptr = NULL;
    printf("  int *null_ptr = NULL;\n");
    printf("  Value of null_ptr: %p\n", (void*)null_ptr);
    if (null_ptr == NULL) {
        printf("  null_ptr is indeed NULL.\n");
    }
    printf("  Attempting to dereference a NULL pointer leads to undefined behavior.\n\n");
    printf("  --- 9.4 Pointers and Arrays ---\n");
    int numbers_arr[5] = {10, 20, 30, 40, 50};
    int *ptr_to_arr;
    ptr_to_arr = numbers_arr;
    printf("  int numbers_arr[5] = {10, 20, 30, 40, 50};\n");
    printf("  int *ptr_to_arr = numbers_arr;\n");
    printf("  Address of numbers_arr[0]: %p\n", (void*)&numbers_arr[0]);
    printf("  Value of ptr_to_arr: %p\n", (void*)ptr_to_arr);
    printf("  Value at *ptr_to_arr (numbers_arr[0]): %d\n", *ptr_to_arr);
    printf("  Value at *(ptr_to_arr + 1) (numbers_arr[1]): %d\n", *(ptr_to_arr + 1));
    printf("  Value using array notation on pointer ptr_to_arr[2]: %d\n\n", ptr_to_arr[2]);
    printf("  Iterating array using a pointer:\n  ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", *(ptr_to_arr + i));
    }
    printf("\n\n");
    printf("  --- 9.5 Pointer Arithmetic ---\n");
    printf("  When an integer is added/subtracted from a pointer, the pointer is scaled by sizeof(pointed-to-type).\n");
    int *p_arith = numbers_arr;
    printf("  p_arith currently points to address %p, value %d\n", (void*)p_arith, *p_arith);
    p_arith++;
    printf("  After p_arith++, it points to address %p, value %d (numbers_arr[1])\n", (void*)p_arith, *p_arith);
    p_arith = p_arith + 2;
    printf("  After p_arith = p_arith + 2, it points to address %p, value %d (numbers_arr[3])\n", (void*)p_arith, *p_arith);
    int *p_start = numbers_arr;
    int *p_end = &numbers_arr[4];
    long diff_elements = p_end - p_start;
    printf("  Difference between pointer to numbers_arr[4] and numbers_arr[0] is %ld elements.\n\n", diff_elements);
    printf("  --- 9.6 void Pointers (Generic Pointers) ---\n");
    int int_val_for_void = 123;
    float float_val_for_void = 45.67f;
    void *generic_ptr;
    generic_ptr = &int_val_for_void;
    printf("  generic_ptr points to an int (address %p).\n", generic_ptr);
    printf("  Value via casting to int*: %d\n", *( (int*)generic_ptr ) );
    generic_ptr = &float_val_for_void;
    printf("  generic_ptr now points to a float (address %p).\n", generic_ptr);
    printf("  Value via casting to float*: %.2f\n\n", *( (float*)generic_ptr ) );
    printf("  --- 9.7 Pointers to Pointers (Double Pointers) ---\n");
    int x_double_ptr = 77;
    int *p1_double_ptr = &x_double_ptr;
    int **p2_double_ptr = &p1_double_ptr;
    printf("  int x = %d;\n", x_double_ptr);
    printf("  int *p1 = &x;       (p1 stores address of x: %p)\n", (void*)p1_double_ptr);
    printf("  int **p2 = &p1;     (p2 stores address of p1: %p)\n", (void*)p2_double_ptr);
    printf("  Value of x: %d\n", x_double_ptr);
    printf("  Value using *p1: %d\n", *p1_double_ptr);
    printf("  Value using **p2 (dereferencing p2 twice): %d\n", **p2_double_ptr);
    printf("  Value of p1 (address of x) using *p2: %p\n\n", (void*)*p2_double_ptr);
    printf("  --- 9.8 Common Pointer Pitfalls ---\n");
    printf("  1. Uninitialized Pointers: int *bad_ptr; *bad_ptr = 10; (Undefined Behavior - points to random memory)\n");
    printf("  2. Null Pointer Dereference: int *n_ptr = NULL; *n_ptr = 5; (Undefined Behavior - usually crash)\n");
    printf("  3. Dangling Pointers: Pointing to memory that's been freed or is out of scope.\n");
    printf("     Example (conceptual, actual behavior depends on compiler/OS):\n");
    printf("     int *dangling_p; { int local_var = 100; dangling_p = &local_var; } \n");
    printf("     // local_var is now out of scope, dangling_p is a dangling pointer.\n");
    printf("     // *dangling_p would be undefined behavior.\n\n");

    // --- Section 10: Memory Management: Stack, Heap, and Dynamic Allocation ---
    // This section discusses memory regions and dynamic memory allocation.
    // 10.1 The Stack: Automatic memory for local variables and function calls (LIFO).
    // 10.2 The Heap: Region for dynamic memory allocation, managed by the programmer.
    //      Covers purpose, management, speed, size, access, lifetime, and risks (leaks, dangling pointers, double free).
    // 10.3 Dynamic Memory Allocation Functions (<stdlib.h>):
    //      10.3.1 malloc: Allocates uninitialized memory.
    //      10.3.2 calloc: Allocates and zero-initializes memory.
    //      10.3.3 realloc: Resizes a previously allocated memory block.
    //      10.3.4 free: Deallocates memory, preventing leaks.
    // The importance of pairing allocations with deallocations is emphasized.
    printf("\n----------------------------------------\n");
    printf("  Section 10: Memory Management\n");
    printf("----------------------------------------\n");
    printf("C programs use different memory regions. Stack and Heap are key for understanding\n");
    printf("how variables and dynamically allocated data are stored and managed.\n\n");
    printf("  --- 10.1 The Stack ---\n");
    printf("  - Purpose: Used for 'static' memory allocation (size known at compile time).\n");
    printf("    - Stores local variables declared inside functions.\n");
    printf("    - Stores function arguments (parameters passed to functions).\n");
    printf("    - Manages function call mechanics (e.g., return addresses).\n");
    printf("  - Management: Automatic. Memory is allocated when a function is called (a 'stack frame'\n");
    printf("    is pushed) and deallocated when the function returns (frame is 'popped').\n");
    printf("  - Speed: Very fast allocation and deallocation (just adjusting a stack pointer).\n");
    printf("  - Size: Relatively small and fixed for the program's execution. Exceeding this\n");
    printf("    limit (e.g., via deep recursion or large local arrays) causes a 'stack overflow'.\n");
    printf("  - Access: LIFO (Last-In, First-Out) - the last function call's frame is the first to be removed.\n");
    printf("  - Lifetime: Data on the stack exists only for the duration of the function call\n");
    printf("    in which it was created. It becomes invalid after the function returns.\n");
    int stack_example_var = 10;
    printf("  Example: 'stack_example_var' (value: %d) is on the stack. Address: %p\n\n",
           stack_example_var, (void*)&stack_example_var);
    printf("  --- 10.2 The Heap ---\n");
    printf("  - Purpose: Used for 'dynamic' memory allocation, where memory is requested by the\n");
    printf("    program at runtime. Useful when:\n");
    printf("    - The amount of memory needed isn't known at compile time.\n");
    printf("    - Data needs to persist beyond the scope of a single function call.\n");
    printf("  - Management: Explicitly by the programmer using functions from <stdlib.h>:\n");
    printf("    `malloc()`, `calloc()`, `realloc()`, and `free()`.\n");
    printf("  - Speed: Slower than stack allocation due to more complex management algorithms\n");
    printf("    (finding free blocks, handling fragmentation).\n");
    printf("  - Size: Much larger than the stack, typically limited by available system RAM and swap space.\n");
    printf("  - Access: No specific order; you receive a pointer to a memory block.\n");
    printf("  - Lifetime: Memory allocated on the heap remains allocated until it is explicitly\n");
    printf("    deallocated by the programmer using `free()`.\n");
    printf("  - Responsibilities & Risks:\n");
    printf("    - Memory Leaks: If heap memory is allocated but not freed when no longer needed,\n");
    printf("      the program consumes more and more memory, potentially crashing.\n");
    printf("    - Dangling Pointers: If memory is freed, but pointers still hold the address of that\n");
    printf("      freed (now invalid) memory. Using such pointers is undefined behavior.\n");
    printf("    - Double Free: Freeing the same memory block more than once is undefined behavior.\n\n");
    printf("  --- 10.3 Dynamic Memory Allocation Functions ---\n");
    printf("    These functions are declared in <stdlib.h>.\n\n");
    printf("    --- 10.3.1 malloc (Memory Allocation) ---\n");
    printf("    `void* malloc(size_t size)`: Allocates `size` bytes on the heap.\n");
    printf("    - Returns a `void*` pointer to the start of the block, or `NULL` if allocation fails.\n");
    printf("    - The allocated memory is UNINITIALIZED (contains garbage values).\n");
    int *arr_malloc_ptr;
    int n_malloc_size = 5;
    printf("    Attempting to allocate memory for %d integers using malloc...\n", n_malloc_size);
    arr_malloc_ptr = (int*)malloc(n_malloc_size * sizeof(int));
    if (arr_malloc_ptr == NULL) {
        printf("    malloc failed! Not enough memory or other error.\n");
    } else {
        printf("    malloc successful. Address of allocated block: %p\n", (void*)arr_malloc_ptr);
        printf("    Initializing malloc'd memory (was uninitialized):\n    ");
        for (int i = 0; i < n_malloc_size; i++) {
            arr_malloc_ptr[i] = i * 10;
            printf("%d ", arr_malloc_ptr[i]);
        }
        printf("\n");
    }
    printf("\n");
    printf("    --- 10.3.2 calloc (Contiguous Allocation & Initialization) ---\n");
    printf("    `void* calloc(size_t num_elements, size_t element_size)`: Allocates memory for\n");
    printf("    an array of `num_elements`, each of `element_size` bytes.\n");
    printf("    - Total memory: `num_elements * element_size`.\n");
    printf("    - Returns `void*` to the block, or `NULL` on failure.\n");
    printf("    - The allocated memory IS INITIALIZED TO ZERO.\n");
    int *arr_calloc_ptr;
    int n_calloc_size = 3;
    printf("    Attempting to allocate memory for %d integers using calloc...\n", n_calloc_size);
    arr_calloc_ptr = (int*)calloc(n_calloc_size, sizeof(int));
    if (arr_calloc_ptr == NULL) {
        printf("    calloc failed!\n");
    } else {
        printf("    calloc successful. Address of allocated block: %p\n", (void*)arr_calloc_ptr);
        printf("    arr_calloc elements (initialized to zero by calloc): ");
        for (int i = 0; i < n_calloc_size; i++) {
            printf("%d ", arr_calloc_ptr[i]);
        }
        printf("\n");
        printf("    Freeing arr_calloc_ptr block.\n");
        free(arr_calloc_ptr);
        arr_calloc_ptr = NULL;
    }
    printf("\n");
    printf("    --- 10.3.3 realloc (Re-allocation) ---\n");
    printf("    `void* realloc(void* ptr, size_t new_size)`: Changes the size of the memory block\n");
    printf("    pointed to by `ptr` (from malloc/calloc/realloc) to `new_size`.\n");
    printf("    - If `ptr` is NULL, `realloc` acts like `malloc(new_size)`.\n");
    printf("    - Returns `void*` to the new block (may be same or different address), or `NULL` on failure.\n");
    printf("    - If `NULL` is returned on failure, the original `ptr` block is NOT freed.\n");
    printf("    - If block is enlarged, new portion is uninitialized. Content is preserved if block moves.\n");
    if (arr_malloc_ptr != NULL) {
        int n_realloc_size = n_malloc_size + 3;
        printf("    Attempting to realloc 'arr_malloc_ptr' from %d to %d integers...\n", n_malloc_size, n_realloc_size);
        int *temp_realloc_ptr = (int*)realloc(arr_malloc_ptr, n_realloc_size * sizeof(int));
        if (temp_realloc_ptr == NULL) {
            printf("    realloc failed! Original 'arr_malloc_ptr' at %p is still valid but not resized.\n", (void*)arr_malloc_ptr);
            printf("    Freeing original arr_malloc_ptr block.\n");
            free(arr_malloc_ptr);
            arr_malloc_ptr = NULL;
        } else {
            arr_malloc_ptr = temp_realloc_ptr;
            printf("    realloc successful. New/current address: %p\n", (void*)arr_malloc_ptr);
            printf("    Initializing the new portion of realloc'd memory:\n    ");
            for (int i = n_malloc_size; i < n_realloc_size; i++) {
                arr_malloc_ptr[i] = i * 100;
            }
            printf("    arr_malloc_ptr after realloc and initializing new part: ");
            for (int i = 0; i < n_realloc_size; i++) {
                printf("%d ", arr_malloc_ptr[i]);
            }
            printf("\n");
            printf("    Freeing reallocated arr_malloc_ptr block.\n");
            free(arr_malloc_ptr);
            arr_malloc_ptr = NULL;
        }
    } else {
        printf("    Skipping realloc example as initial arr_malloc_ptr was NULL or already freed.\n");
    }
    printf("\n");
    printf("    --- 10.3.4 free (De-allocation) ---\n");
    printf("    `void free(void* ptr)`: Deallocates the memory block pointed to by `ptr`.\n");
    printf("    - `ptr` must be from malloc/calloc/realloc, or NULL.\n");
    printf("    - Passing `NULL` to `free()` is safe and does nothing.\n");
    printf("    - After freeing, `ptr` becomes a 'dangling pointer'. Set it to `NULL`.\n");
    int *ptr_to_free_demo = (int*)malloc(sizeof(int));
    if (ptr_to_free_demo != NULL) {
        *ptr_to_free_demo = 12345;
        void* address_before_free = (void*)ptr_to_free_demo;
        printf("    Allocated memory for ptr_to_free_demo at %p, value: %d\n", address_before_free, *ptr_to_free_demo);
        printf("    Freeing memory for ptr_to_free_demo.\n");
        free(ptr_to_free_demo);
        ptr_to_free_demo = NULL; // Set to NULL *before* any further mention of the original pointer value
        printf("    Memory at address %p was deallocated. ptr_to_free_demo is now NULL.\n", address_before_free);
    } else {
        printf("    malloc failed for ptr_to_free_demo.\n");
    }
    printf("\n");
    printf("  Summary: Always pair allocations with `free()`. Manage pointers carefully to avoid leaks and dangling pointers.\n\n");

    // --- Section 11: Structures (struct) ---
    // This section explains structures, which allow grouping of different data types.
    // 11.1 Defining and Declaring Structure Variables: Creating blueprints and instances.
    // 11.2 Accessing Structure Members: Using the dot operator (.).
    // 11.3 Initializing Structure Variables: Various methods including designated initializers.
    // 11.4 Pointers to Structures: Using the arrow operator (->) for access via pointers.
    // 11.5 Arrays of Structures: Collections of structure instances.
    // 11.6 Nested Structures: Structures within structures.
    // 11.7 Passing Structures to Functions: By value (copy) and by pointer (reference).
    // 11.8 typedef with Structures: Creating aliases for structure types for convenience.
    // Structure definitions and related function prototypes are at the top of the file.
    printf("\n----------------------------------------\n");
    printf("  Section 11: Structures (struct)\n");
    printf("----------------------------------------\n");
    printf("Structures group variables of different data types under a single name.\n");
    printf("They define a custom data type (a template).\n\n");
    printf("  --- 11.1 Defining and Declaring Structure Variables ---\n");
    printf("  Structure definitions (like 'struct Point', 'struct Student') are blueprints.\n");
    printf("  (See definitions before main() in this file).\n");
    struct Point p1;
    struct Student student1;
    printf("  struct Point p1; // Declared p1\n");
    printf("  struct Student student1; // Declared student1\n\n");
    printf("  --- 11.2 Accessing Structure Members (Dot Operator '.') ---\n");
    p1.x = 10;
    p1.y = 20;
    printf("  p1.x = 10; p1.y = 20;\n");
    printf("  p1 values: x = %d, y = %d\n", p1.x, p1.y);
    strcpy(student1.name, "Alice Wonderland");
    student1.student_id = 1001;
    student1.gpa = 3.85f;
    printf("  strcpy(student1.name, \"Alice Wonderland\"); student1.student_id = 1001; student1.gpa = %.2f;\n", student1.gpa);
    printf("  Student 1: Name: %s, ID: %d, GPA: %.2f\n\n",
           student1.name, student1.student_id, student1.gpa);
    printf("  --- 11.3 Initializing Structure Variables ---\n");
    struct Point p2 = {30, 40};
    printf("  struct Point p2 = {30, 40}; -> p2.x = %d, p2.y = %d\n", p2.x, p2.y);
    struct Student student2 = {.name = "Bob The Builder", .student_id = 1002, .gpa = 3.5f};
    printf("  Designated init: student2.name = %s, ID = %d, GPA = %.2f\n\n",
           student2.name, student2.student_id, student2.gpa);
    printf("  --- 11.4 Pointers to Structures (Arrow Operator '->') ---\n");
    struct Point p3 = {5, 15};
    struct Point *ptr_p3 = &p3;
    printf("  struct Point p3 = {5, 15};\n");
    printf("  struct Point *ptr_p3 = &p3;\n");
    printf("  Accessing via (*ptr_p3).x: %d\n", (*ptr_p3).x);
    printf("  Accessing via ptr_p3->y (arrow operator): %d\n", ptr_p3->y);
    ptr_p3->x = 55;
    (*ptr_p3).y = 65;
    printf("  After modification: p3.x = %d, p3.y = %d\n\n", p3.x, p3.y);
    printf("  --- 11.5 Arrays of Structures ---\n");
    struct Student class_roster[2];
    strcpy(class_roster[0].name, "Charlie Brown");
    class_roster[0].student_id = 2001;
    class_roster[0].gpa = 2.5f;
    class_roster[1] = (struct Student){"Lucy Van Pelt", 2002, 3.9f};
    printf("  Class Roster:\n");
    for (int i = 0; i < 2; i++) {
        printf("    Student %d: %s, ID: %d, GPA: %.2f\n",
               i + 1, class_roster[i].name, class_roster[i].student_id, class_roster[i].gpa);
    }
    printf("\n");
    printf("  --- 11.6 Nested Structures ---\n");
    struct Employee emp1;
    strcpy(emp1.emp_name, "Diana Prince");
    emp1.employee_id = 707;
    emp1.date_of_birth.day = 22;
    emp1.date_of_birth.month = 3;
    emp1.date_of_birth.year = 1941;
    printf("  Employee: %s (ID: %d)\n", emp1.emp_name, emp1.employee_id);
    printf("  Date of Birth: %02d/%02d/%d\n\n",
           emp1.date_of_birth.day, emp1.date_of_birth.month, emp1.date_of_birth.year);
    printf("  --- 11.7 Passing Structures to Functions ---\n");
    struct Point my_point = {7, 14};
    printf("  Original my_point: (%d, %d)\n", my_point.x, my_point.y);
    printf("  Calling print_point_by_value(my_point):\n    ");
    print_point_by_value(my_point);
    printf("  my_point after by-value call: (%d, %d) (unchanged)\n", my_point.x, my_point.y);
    printf("  Calling modify_point_by_pointer(&my_point):\n");
    modify_point_by_pointer(&my_point);
    printf("  my_point after by-pointer call: (%d, %d) (modified)\n", my_point.x, my_point.y);
    struct Student another_student = {"Eve Future", 3001, 4.0f};
    printf("  Calling print_student_info(another_student):\n    ");
    print_student_info(another_student);
    printf("\n");
    printf("  --- 11.8 typedef with Structures ---\n");
    printf("  'typedef' creates an alias for a structure type, simplifying declarations.\n");
    printf("  Example: typedef struct { ... } Book; (See definition before main)\n");
    Book novel = {"The Hitchhiker's Guide to the Galaxy", "Douglas Adams", 1979};
    printf("  Novel Title: %s\n", novel.title);
    printf("  Author: %s\n", novel.author);
    printf("  Year: %d\n\n", novel.year_published);

    // --- Section 12: Unions and Enumerations (enum) ---
    // This section covers two other user-defined type mechanisms:
    // 12.1 Unions (`union`): Allow different data types to share the same memory location.
    //      Only one member is active at a time. Size is that of the largest member.
    //      Programmer responsibility to track active member.
    // 12.2 Enumerations (`enum`): Create sets of named integer constants for readability.
    //      Demonstrates basic enum usage, enums with assigned values, and typedef'd enums.
    // Definitions for 'union ValueContainer', 'enum DayOfWeek', 'enum TrafficLight',
    // and 'ProcessStatus' are at the top of the file.
    printf("\n----------------------------------------\n");
    printf("  Section 12: Unions and Enumerations\n");
    printf("----------------------------------------\n\n");
    printf("  --- 12.1 Unions (`union`) ---\n");
    printf("  Unions allow different data types to share the SAME memory location.\n");
    printf("  Only one member of a union can hold a value at any given time.\n");
    printf("  The size of a union is the size of its largest member.\n");
    printf("  (See 'union ValueContainer' definition before main).\n\n");
    union ValueContainer container;
    printf("  union ValueContainer container;\n");
    container.i_val = 12345;
    printf("  Assigned container.i_val = %d\n", container.i_val);
    container.f_val = 98.76f;
    printf("  Assigned container.f_val = %.2f\n", container.f_val);
    container.c_val = 'Z';
    printf("  Assigned container.c_val = '%c'\n", container.c_val);
    printf("  Size of 'union ValueContainer': %zu bytes (size of largest member, possibly with padding)\n",
           sizeof(union ValueContainer));
    printf("  (Compare with sizeof(int)=%zu, sizeof(float)=%zu, sizeof(char)=%zu)\n\n",
           sizeof(int), sizeof(float), sizeof(char));
    printf("  It's the programmer's responsibility to track which union member is currently active.\n\n");
    printf("  --- 12.2 Enumerations (`enum`) ---\n");
    printf("  Enumerations create a set of named integer constants, improving code readability.\n");
    printf("  (See 'enum DayOfWeek', 'enum TrafficLight', 'typedef enum ProcessStatus' before main).\n\n");
    enum DayOfWeek today = WED;
    printf("  enum DayOfWeek today = WED;\n");
    if (today == WED) {
        printf("  Today is Wednesday (value: %d).\n", today);
    } else {
        printf("  Today is not Wednesday (value: %d).\n", today);
    }
    enum TrafficLight light_status = GREEN_LIGHT;
    printf("  enum TrafficLight light_status = GREEN_LIGHT;\n");
    switch (light_status) {
        case RED_LIGHT:    printf("  Light is RED (value: %d). Stop!\n", light_status); break;
        case YELLOW_LIGHT: printf("  Light is YELLOW (value: %d). Caution!\n", light_status); break;
        case GREEN_LIGHT:  printf("  Light is GREEN (value: %d). Go!\n", light_status); break;
        default:           printf("  Unknown light status.\n");
    }
    printf("\n");
    printf("  Using typedef'd enum 'ProcessStatus':\n");
    ProcessStatus current_status = COMPLETED;
    printf("  ProcessStatus current_status = COMPLETED;\n");
    printf("  Current process status: ");
    switch (current_status) {
        case PENDING:    printf("Pending (value: %d)\n", current_status); break;
        case PROCESSING: printf("Processing (value: %d)\n", current_status); break;
        case COMPLETED:  printf("Completed (value: %d)\n", current_status); break;
        case FAILED:     printf("Failed (value: %d)\n", current_status); break;
    }
    printf("  Enum constants are essentially integers. 'COMPLETED' is %d.\n\n", COMPLETED);

    // --- Section 13: File I/O (Input/Output) ---
    // This section explains how to perform file operations in C using <stdio.h>.
    // 13.1 Opening and Closing Files: `fopen()` with various modes (r, w, a, r+, w+, a+, binary 'b') and `fclose()`.
    // 13.2 Writing to a File (Text): `fputc()` (char), `fputs()` (string), `fprintf()` (formatted).
    // 13.3 Reading from a File (Text): `fgetc()` (char), `fgets()` (string), `fscanf()` (formatted).
    //      Also demonstrates `rewind()`, `feof()`, `ferror()`, `clearerr()`.
    // 13.4 Binary File I/O: `fread()` and `fwrite()` for raw byte operations (e.g., writing/reading structs).
    // 13.5 File Positioning: Briefly mentions `fseek()`, `ftell()`, `rewind()`.
    // Error handling with `perror()` and file removal with `remove()` are also shown.
    printf("\n----------------------------------------\n");
    printf("  Section 13: File I/O (Input/Output)\n");
    printf("----------------------------------------\n");
    printf("File I/O allows programs to read from and write to files on disk.\n");
    printf("Key functions are in <stdio.h>. The 'FILE*' pointer is central.\n\n");
    const char *temp_filename = "c_theory_tempfile.txt";
    FILE *file_ptr;
    printf("  --- 13.1 Opening and Closing Files (fopen, fclose) ---\n");
    printf("  `FILE* fopen(const char *filename, const char *mode);`\n");
    printf("  Modes: \"r\" (read), \"w\" (write, truncates), \"a\" (append),\n");
    printf("         \"r+\" (read/write), \"w+\" (read/write, truncates), \"a+\" (read/append).\n");
    printf("         Append 'b' for binary modes (e.g., \"rb\", \"wb\").\n");
    printf("  `int fclose(FILE *stream);`\n\n");
    printf("  --- 13.2 Writing to a File (fputc, fputs, fprintf) ---\n");
    printf("  Attempting to open '%s' in write mode (\"w\")...\n", temp_filename);
    file_ptr = fopen(temp_filename, "w");
    if (file_ptr == NULL) {
        perror("    Error opening file for writing");
        printf("    Could not open '%s' for writing. Skipping write examples.\n", temp_filename);
    } else {
        printf("    File '%s' opened successfully for writing.\n", temp_filename);
        printf("    Writing 'H' 'i' '\\n' using fputc().\n");
        fputc('H', file_ptr);
        fputc('i', file_ptr);
        fputc('\n', file_ptr);
        const char *line1 = "This is a line written by fputs.\n";
        printf("    Writing \"%s\" using fputs().\n", line1);
        if (fputs(line1, file_ptr) == EOF) {
            perror("    Error writing line1 with fputs");
        }
        int year = 2024;
        float pi_val = 3.14159f;
        printf("    Writing formatted data using fprintf(): Year %d, Pi %.3f\n", year, pi_val);
        fprintf(file_ptr, "Year: %d\nPi approximation: %.3f\n", year, pi_val);
        printf("    Closing file '%s' after writing.\n", temp_filename);
        if (fclose(file_ptr) == EOF) {
            perror("    Error closing file after writing");
        }
        file_ptr = NULL;
    }
    printf("\n");
    printf("  --- 13.3 Reading from a File (fgetc, fgets, fscanf) ---\n");
    printf("  Attempting to open '%s' in read mode (\"r\")...\n", temp_filename);
    file_ptr = fopen(temp_filename, "r");
    if (file_ptr == NULL) {
        perror("    Error opening file for reading");
        printf("    Could not open '%s' for reading. Skipping read examples.\n", temp_filename);
    } else {
        printf("    File '%s' opened successfully for reading.\n", temp_filename);
        char buffer[256];
        printf("    Reading with fgetc() until EOF:\n    \"");
        int ch_read; 
        while ((ch_read = fgetc(file_ptr)) != EOF) {
            putchar(ch_read);
        }
        printf("\"\n    (End of fgetc() read attempt)\n");
        rewind(file_ptr);
        printf("    Rewound file pointer to the beginning.\n");
        printf("    Reading with fgets():\n");
        int line_num = 1;
        while (fgets(buffer, sizeof(buffer), file_ptr) != NULL) {
            printf("      Line %d: %s", line_num++, buffer);
        }
        if (feof(file_ptr)) {
            printf("    (End of file reached by fgets)\n");
        } else if (ferror(file_ptr)) {
            perror("    Error during fgets reading");
        }
        clearerr(file_ptr);
        rewind(file_ptr);
        printf("    Rewound file pointer again.\n");
        printf("    Reading with fscanf() (assuming specific format):\n");
        char hi_word[10];
        int read_year;
        float read_pi;
        if (fscanf(file_ptr, "%9s", hi_word) == 1) { // Added width specifier for safety
             printf("      fscanf read word: %s\n", hi_word);
        }
        while((ch_read = fgetc(file_ptr)) != '\n' && ch_read != EOF);
        if (fgets(buffer, sizeof(buffer), file_ptr) != NULL) {
            printf("      fscanf then fgets read line: %s", buffer);
        }
        if (fscanf(file_ptr, "Year: %d\nPi approximation: %f", &read_year, &read_pi) == 2) {
            printf("      fscanf read: Year = %d, Pi = %.3f\n", read_year, read_pi);
        } else {
            printf("      fscanf failed to match expected format for Year/Pi.\n");
        }
        printf("    Closing file '%s' after reading.\n", temp_filename);
        if (fclose(file_ptr) == EOF) {
            perror("    Error closing file after reading");
        }
        file_ptr = NULL;
    }
    printf("\n");
    printf("  --- 13.4 Binary File I/O (fread, fwrite) ---\n");
    printf("  Used for reading/writing raw bytes, e.g., structs, arrays of numbers directly.\n");
    const char *binary_filename = "c_theory_binary.dat";
    struct Point points_to_write[2] = {{10, 20}, {30, 40}};
    struct Point points_to_read[2];
    size_t items_written, items_read_count; 
    printf("  Attempting to open '%s' in binary write mode (\"wb\")...\n", binary_filename);
    file_ptr = fopen(binary_filename, "wb");
    if (file_ptr == NULL) {
        perror("    Error opening binary file for writing");
    } else {
        printf("    Writing 2 'struct Point' objects using fwrite().\n");
        items_written = fwrite(points_to_write, sizeof(struct Point), 2, file_ptr);
        if (items_written == 2) {
            printf("    Successfully wrote %zu Point objects.\n", items_written);
        } else {
            printf("    Error or partial write with fwrite(). Wrote %zu items.\n", items_written);
        }
        fclose(file_ptr);
        file_ptr = NULL;
        printf("  Attempting to open '%s' in binary read mode (\"rb\")...\n", binary_filename);
        file_ptr = fopen(binary_filename, "rb");
        if (file_ptr == NULL) {
            perror("    Error opening binary file for reading");
        } else {
            printf("    Reading 2 'struct Point' objects using fread().\n");
            items_read_count = fread(points_to_read, sizeof(struct Point), 2, file_ptr);
            if (items_read_count == 2) {
                printf("    Successfully read %zu Point objects:\n", items_read_count);
                for (size_t i = 0; i < items_read_count; i++) { // CORRECTED: i is size_t
                    printf("      Point %zu: x=%d, y=%d\n", i, points_to_read[i].x, points_to_read[i].y);
                }
            } else {
                printf("    Error or partial read with fread(). Read %zu items.\n", items_read_count);
                if (feof(file_ptr)) printf("      (End of file reached prematurely)\n");
                if (ferror(file_ptr)) perror("      (Error indicator set)");
            }
            fclose(file_ptr);
            file_ptr = NULL;
        }
    }
    printf("\n");
    printf("  --- 13.5 File Positioning (fseek, ftell, rewind) ---\n");
    printf("  `fseek` changes current file position, `ftell` gets it, `rewind` goes to start.\n");
    printf("  (rewind() was used in earlier examples).\n\n");
    printf("  Error Handling: `feof()` checks for EOF, `ferror()` for errors, `perror()` prints system error messages.\n\n");
    
    FILE *check_file_exists; 
    check_file_exists = fopen(temp_filename, "r");
    if (check_file_exists != NULL) { 
        fclose(check_file_exists); 
        if (remove(temp_filename) == 0) {
            printf("  Temporary text file '%s' removed successfully.\n", temp_filename);
        } else {
            perror("  Error removing temporary text file");
        }
    }
    check_file_exists = fopen(binary_filename, "r");
    if (check_file_exists != NULL) {
        fclose(check_file_exists);
        if (remove(binary_filename) == 0) {
            printf("  Temporary binary file '%s' removed successfully.\n", binary_filename);
        } else {
            perror("  Error removing temporary binary file");
        }
    }
    printf("\n");

    // --- Section 14: The C Preprocessor ---
    // This section covers C preprocessor directives, which modify source code before compilation.
    // 14.1 #include: File inclusion (<standard_header.h> vs "user_header.h").
    // 14.2 #define: Macro definition.
    //      Object-like macros (constants).
    //      Function-like macros (with parameters, potential side-effect issues).
    //      #undef: Undefining a macro.
    // 14.3 Conditional Compilation: #if, #ifdef, #ifndef, #else, #elif, #endif.
    //      Allows code to be included/excluded based on conditions at preprocessing time.
    // 14.4 #error and #warning: Directives to stop compilation or issue warnings.
    // 14.5 Predefined Macros: __FILE__, __LINE__, __DATE__, __TIME__, __STDC__, __STDC_VERSION__.
    // 14.6 Stringizing Operator (#): Converts a macro argument to a string literal.
    // 14.7 Token Pasting Operator (##): Concatenates two tokens into one.
    // The concept of Header Guards for preventing multiple inclusions is also mentioned.
    printf("\n----------------------------------------\n");
    printf("  Section 14: The C Preprocessor\n");
    printf("----------------------------------------\n");
    printf("The preprocessor modifies source code before compilation based on directives (lines starting with #).\n\n");
    printf("  --- 14.1 #include (File Inclusion) ---\n");
    printf("  - `#include <header.h>`: For standard library headers (searches system paths).\n");
    printf("    Example: `#include <stdio.h>` (already used for printf).\n");
    printf("  - `#include \"myheader.h\"`: For user-defined headers (searches current dir first).\n");
    printf("    (We would use this if we had separate .h files for our functions/structs).\n\n");
    printf("  --- 14.2 #define (Macro Definition) ---\n");
    #define MAX_ITEMS_DEFINE 100 
    #define GREETING_MSG_DEFINE "Hello from a macro!" // Renamed to avoid conflict
    printf("  Object-like macros (Constants):\n");
    printf("    `#define MAX_ITEMS_DEFINE 100` -> MAX_ITEMS_DEFINE = %d\n", MAX_ITEMS_DEFINE);
    printf("    `#define GREETING_MSG_DEFINE \"Hello from a macro!\"` -> GREETING_MSG_DEFINE = %s\n", GREETING_MSG_DEFINE);
    #define ADD_MACRO(x, y) ((x) + (y)) 
    #define MULTIPLY_MACRO(a, b) ((a) * (b)) 
    int num_a_macro = 5, num_b_macro = 3; 
    printf("  Function-like macros:\n");
    printf("    `#define ADD_MACRO(x, y) ((x) + (y))` -> ADD_MACRO(%d, %d) = %d\n", num_a_macro, num_b_macro, ADD_MACRO(num_a_macro, num_b_macro));
    printf("    `#define MULTIPLY_MACRO(a, b) ((a) * (b))` -> MULTIPLY_MACRO(%d+1, %d-1) = %d\n",
           num_a_macro, num_b_macro, MULTIPLY_MACRO(num_a_macro + 1, num_b_macro - 1));
    int counter_macro_val = 0; 
    (void)counter_macro_val; // CORRECTED: Mark as unused
    #define INCREMENT_TWICE(val) (val++ + val++) 
    printf("    Function-like macros can have issues with side-effects if arguments are expressions\n");
    printf("    that modify variables (e.g., `val++` evaluated multiple times, as in INCREMENT_TWICE).\n\n");
    #undef MAX_ITEMS_DEFINE
    printf("  --- 14.3 Conditional Compilation (#if, #ifdef, #ifndef, #else, #elif, #endif) ---\n");
    #define DEBUG_MODE_PREPROC 1 
    #define RELEASE_VERSION_PREPROC 0 
    printf("  Conditional compilation allows including/excluding code at preprocessing time.\n");
    #ifdef DEBUG_MODE_PREPROC
        printf("    DEBUG_MODE_PREPROC is defined. Debugging messages enabled.\n");
    #else
        printf("    DEBUG_MODE_PREPROC is NOT defined.\n");
    #endif
    #ifndef PRODUCTION_BUILD_PREPROC 
        printf("    PRODUCTION_BUILD_PREPROC is NOT defined. This might be a development build.\n");
    #endif
    #if DEBUG_MODE_PREPROC == 1 && RELEASE_VERSION_PREPROC == 0
        printf("    This is a debug build (DEBUG_MODE_PREPROC=1, RELEASE_VERSION_PREPROC=0).\n");
    #elif RELEASE_VERSION_PREPROC == 1
        printf("    This is a release build.\n");
    #else
        printf("    Build configuration is neither full debug nor full release.\n");
    #endif
    #undef DEBUG_MODE_PREPROC
    printf("\n");
    printf("  --- 14.4 #error and #warning ---\n");
    printf("  `#error message` stops compilation with an error.\n");
    printf("  `#warning message` issues a warning (compiler-dependent, common extension).\n");
    printf("    (See commented examples in code for #error and #warning).\n\n");
    printf("  --- 14.5 Predefined Macros ---\n");
    printf("  C provides several standard predefined macros:\n");
    printf("    __FILE__: Name of the current source file: %s\n", __FILE__);
    printf("    __LINE__: Current line number in the source file: %d\n", __LINE__);
    printf("    __DATE__: Date of compilation: %s\n", __DATE__);
    printf("    __TIME__: Time of compilation: %s\n", __TIME__);
    #ifdef __STDC__
        printf("    __STDC__: %d (Indicates ISO C standard compliance)\n", __STDC__);
    #else
        printf("    __STDC__ is not defined (Compiler may not be in strict ISO C mode).\n");
    #endif
    #ifdef __STDC_VERSION__
        printf("    __STDC_VERSION__: %ldL (Indicates C standard version, e.g., C11 is 201112L)\n", __STDC_VERSION__);
    #else
        printf("    __STDC_VERSION__ is not defined (May be pre-C99 or specific compiler settings).\n");
    #endif
    printf("\n");
    printf("  --- 14.6 Stringizing Operator (#) ---\n");
    printf("  In function-like macros, `#argument` converts the argument token into a string literal.\n");
    #define PRINT_EXPRESSION(expr) printf("  Expression: %s, Value: %d\n", #expr, (expr))
    int x_str = 10, y_str = 5;
    PRINT_EXPRESSION(x_str + y_str);
    PRINT_EXPRESSION(x_str * (y_str - 2));
    printf("\n");
    printf("  --- 14.7 Token Pasting Operator (##) ---\n");
    printf("  In macros, `token1##token2` concatenates token1 and token2 into a single token.\n");
    #define CREATE_VARIABLE(type, name_prefix, number_suffix) type name_prefix##number_suffix
    CREATE_VARIABLE(int, my_var_, 1) = 100;
    CREATE_VARIABLE(double, value_suffix_, 2) = 3.14; // CORRECTED: Used a concrete number
    printf("  `CREATE_VARIABLE(int, my_var_, 1) = 100;` creates `int my_var_1 = %d`\n", my_var_1);
    printf("  `CREATE_VARIABLE(double, value_suffix_, 2) = 3.14;` creates `double value_suffix_2 = %.2f`\n", value_suffix_2); // CORRECTED: Print the used variable
    printf("  (Token pasting is powerful but can make code harder to read/debug).\n\n");
    printf("  Header Guards (using #ifndef, #define, #endif) are crucial for preventing multiple\n");
    printf("  inclusions of the same header file, which can lead to redefinition errors.\n");
    printf("  Example structure for 'my_custom_header.h':\n");
    printf("    #ifndef MY_CUSTOM_HEADER_H\n");
    printf("    #define MY_CUSTOM_HEADER_H\n");
    printf("    // ... header content ...\n");
    printf("    #endif // MY_CUSTOM_HEADER_H\n\n");

    return 0;
}

// --- Function Definitions for Section 7 ---

/**
 * @brief A simple function that prints a greeting message to the console.
 *
 * This function demonstrates:
 *  - A function with a 'void' return type, meaning it doesn't return any value.
 *  - A function with no parameters.
 *  - Basic output using printf.
 */
void greet(void) {
    // Prints a static string to standard output.
    printf("Hello from the greet() function!\n");
}

/**
 * @brief Adds two integer numbers and returns their sum.
 *
 * This function demonstrates:
 *  - A function that takes two integer parameters ('a' and 'b').
 *  - A function that returns an integer value (the sum).
 *  - A local variable 'sum' to store the intermediate result.
 *  - The 'return' statement to send a value back to the caller.
 *
 * @param a The first integer.
 * @param b The second integer.
 * @return The sum of a and b.
 */
int add_numbers(int a, int b) {
    // Declare a local variable 'sum' to hold the result of the addition.
    int sum = a + b;
    // Return the calculated sum to the function caller.
    return sum;
}

/**
 * @brief Calculates the square of a double-precision floating-point number.
 *
 * This function demonstrates:
 *  - A function that takes a 'double' parameter.
 *  - A function that returns a 'double' value.
 *  - Performing a calculation and returning the result directly.
 *
 * @param num The number to be squared.
 * @return The square of num.
 */
double calculate_square(double num) {
    // Calculates num multiplied by itself and returns the result.
    return num * num;
}

/**
 * @brief Attempts to modify a value passed by parameter.
 *
 * This function demonstrates C's 'pass-by-value' mechanism for function arguments.
 * When 'val' is passed to this function, a *copy* of the original argument's value
 * is created and stored in the parameter 'val'.
 * Any modifications made to 'val' inside this function affect only this local copy,
 * not the original variable in the calling function (e.g., 'original_value' in main).
 *
 * @param val An integer value passed to the function.
 */
void try_to_modify(int val) {
    // Print the value of 'val' as it was received by the function.
    printf("    Inside try_to_modify(): Received value = %d\n", val);
    // Modify the local copy of 'val'. This change is confined to this function's scope.
    val = 999;
    // Print the modified value of the local 'val'.
    printf("    Inside try_to_modify(): Changed 'val' to %d\n", val);
}

/**
 * @brief Demonstrates local variable scope and interaction with a global variable.
 *
 * This function illustrates:
 *  - Local variables: 'local_var_in_func' is declared inside this function and is
 *    only accessible within this function. Its lifetime is limited to the execution
 *    of this function.
 *  - Accessing global variables: 'global_variable_example' (declared outside any function)
 *    can be accessed and modified from within this function. Changes to global variables
 *    persist across function calls and throughout the program's execution.
 *
 * @return An integer value derived from the local variable.
 */
int function_with_local_scope(void) {
    // 'local_var_in_func' is local to this function.
    // It is created when the function is called and destroyed when the function exits.
    int local_var_in_func = 25;
    printf("    Inside function_with_local_scope(): local_var_in_func = %d\n", local_var_in_func);
    // Accessing and printing the current value of the global variable.
    printf("    Inside function_with_local_scope(): global_variable_example = %d\n", global_variable_example);
    // Modifying the global variable. This change will be visible outside this function.
    global_variable_example += 10;
    // Return a value based on the local variable.
    return local_var_in_func * 2;
}

// --- Function Definitions for Section 11 (Structs) ---

/**
 * @brief Prints the coordinates of a Point structure passed by value.
 *
 * This function demonstrates passing a structure by value.
 * When 'pt_val' (a 'struct Point') is passed, a complete copy of the structure
 * from the calling function is made and given to this function.
 * Modifications to 'pt_val' members (e.g., pt_val.x = 1000) inside this function
 * affect only this local copy and do NOT change the original structure in the caller.
 *
 * @param pt_val A 'struct Point' whose coordinates are to be printed.
 */
void print_point_by_value(struct Point pt_val) {
    // Print the x and y members of the local copy of the Point structure.
    printf("Inside print_point_by_value: (%d, %d)\n", pt_val.x, pt_val.y);
    // Modifying the 'x' member of the local copy 'pt_val'.
    // This change will not be reflected in the original 'my_point' in main().
    pt_val.x = 1000;
}

/**
 * @brief Modifies the coordinates of a Point structure passed by pointer.
 *
 * This function demonstrates passing a structure by pointer (pass-by-reference).
 * Instead of a copy of the structure, the memory address of the original structure
 * is passed.
 * The function uses the arrow operator (->) to dereference the pointer and access
 * the members of the original structure.
 * Modifications made to the members via the pointer (e.g., pt_ptr->x += 5) directly
 * alter the original structure in the calling function (e.g., 'my_point' in main).
 *
 * @param pt_ptr A pointer to a 'struct Point' whose coordinates are to be modified.
 */
void modify_point_by_pointer(struct Point *pt_ptr) {
    // Print the original values of the Point structure's members by dereferencing the pointer.
    printf("    Inside modify_point_by_pointer: Original values pointed to: (%d, %d)\n", pt_ptr->x, pt_ptr->y);
    // Modify the 'x' member of the original structure using the pointer.
    pt_ptr->x += 5;
    // Modify the 'y' member of the original structure using the pointer.
    pt_ptr->y += 10;
    // Print the modified values, showing that the original structure has been changed.
    printf("    Inside modify_point_by_pointer: Modified values pointed to: (%d, %d)\n", pt_ptr->x, pt_ptr->y);
}

/**
 * @brief Prints the information of a Student structure passed by value.
 *
 * Similar to 'print_point_by_value', this function receives a copy of the
 * 'struct Student' passed to it. Any changes made to 's' within this function
 * would be local and not affect the original student structure in the caller.
 * This is generally suitable for functions that only need to read data from
 * the structure. For large structures, passing by pointer (or const pointer if
 * no modification is intended) can be more efficient to avoid copying overhead.
 *
 * @param s A 'struct Student' whose information is to be printed.
 */
void print_student_info(struct Student s) {
    // Print a header for the student information.
    printf("Student Info (passed by value):\n");
    // Access and print the 'name' member of the local copy of the Student structure.
    printf("      Name: %s\n", s.name);
    // Access and print the 'student_id' member.
    printf("      ID: %d\n", s.student_id);
    // Access and print the 'gpa' member, formatted to two decimal places.
    printf("      GPA: %.2f\n", s.gpa);
}