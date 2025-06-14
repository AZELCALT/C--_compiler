#define LEXER_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>
#include <stdbool.h>

const unsigned char Modulus = 37;

typedef enum{
    SYSTEM_8BIT, // System bit type
    SYSTEM_16BIT,
    SYSTEM_32BIT,
    SYSTEM_64BIT,
    SYSTEM_CUSTOM, // Custom system type
}SystemType;

typedef enum{
    REGISTER_GENERAL_1, // general purpose register from 1 to 32
    REGISTER_GENERAL_2,
    REGISTER_GENERAL_3,
    REGISTER_GENERAL_4,
    REGISTER_GENERAL_5,
    REGISTER_GENERAL_6,
    REGISTER_GENERAL_7,
    REGISTER_GENERAL_8,
    REGISTER_GENERAL_9,
    REGISTER_GENERAL_10,
    REGISTER_GENERAL_11,
    REGISTER_GENERAL_12,
    REGISTER_GENERAL_13,
    REGISTER_GENERAL_14,
    REGISTER_GENERAL_15,
    REGISTER_GENERAL_16,
    REGISTER_GENERAL_17,
    REGISTER_GENERAL_18,
    REGISTER_GENERAL_19,
    REGISTER_GENERAL_20,
    REGISTER_GENERAL_21,
    REGISTER_GENERAL_22,
    REGISTER_GENERAL_23,
    REGISTER_GENERAL_24,
    REGISTER_GENERAL_25,
    REGISTER_GENERAL_26,
    REGISTER_GENERAL_27,
    REGISTER_GENERAL_28,
    REGISTER_GENERAL_29,
    REGISTER_GENERAL_30,
    REGISTER_GENERAL_31,
    REGISTER_GENERAL_32,
    REGISTER_STACK_POINTER, // Stack pointer
    REGISTER_PROGRAM_COUNTER, // Program counter
    REGISTER_STATUS_REGISTER, // Status register
    REGISTER_LINK_REGISTER, // Link register
    REGISTER_FRAME_POINTER, // Frame pointer
    REGISTER_FLOATING_POINT_REGISTER, // floating point register
    REGISTER_VECTOR_REGISTER, // Vector register
    REGISTER_CONTROL_REGISTER, // Control register
    REGISTER_SEGMENT_REGISTER, // Segment register
    REGISTER_DEBUG_REGISTER, // Debug register (e.g., breakpoints, watchpoints)
    REGISTER_SPECIAL_PURPOSE_REGISTER, // Catch-all for other special registers
} TypeRegister;

typedef enum{
    // Architecture types compiling to
    ARCHITECTURE_X86_16, // 16bit architecture
    ARCHITECTURE_X86_32, // 32bit architecture
    ARCHITECTURE_X86_64, // 64bit architecture

    // ARM Architectures (General)
    ARCHITECTURE_ARM_32,      // 32bit ARM instruction set (e.g., ARMv7-A)
    ARCHITECTURE_ARM_64,      // 64bit ARM instruction set (AArch64 / ARMv8-A and later)
    ARCHITECTURE_ARM_THUMB,   // ARM Thumb instruction set (primarily 16-bit instructions for 32bit ARM)
    ARCHITECTURE_ARM_THUMB_2, // ARM Thumb-2 instruction set (mixed 16/32-bit instructions for 32bit ARM)    

    // ARM Cortex-M Series (Microcontroller Profile - primarily 32-bit)
    ARCHITECTURE_ARM_CORTEX_M,   // 32bit microcontroller architecture (family)
    ARCHITECTURE_ARM_CORTEX_M0,  // 32bit microcontroller architecture
    ARCHITECTURE_ARM_CORTEX_M3,  // 32bit microcontroller architecture
    ARCHITECTURE_ARM_CORTEX_M4,  // 32bit microcontroller architecture
    ARCHITECTURE_ARM_CORTEX_M7,  // 32bit microcontroller architecture
    ARCHITECTURE_ARM_CORTEX_M33, // 32bit microcontroller architecture
    ARCHITECTURE_ARM_CORTEX_M55, // 32bit microcontroller architecture

    // ARM Cortex-R Series (Real-time Profile - primarily 32-bit)
    ARCHITECTURE_ARM_CORTEX_R,   // 32bit real-time architecture (family)
    // ARM Cortex-R Series (Real-time Profile)
    ARCHITECTURE_ARM_CORTEX_R4,  // 32bit real-time processor
    ARCHITECTURE_ARM_CORTEX_R5,  // 32bit real-time processor
    ARCHITECTURE_ARM_CORTEX_R7,  // 32bit real-time processor
    ARCHITECTURE_ARM_CORTEX_R8,  // 32bit real-time processor
    ARCHITECTURE_ARM_CORTEX_R52, // 32bit real-time processor
    ARCHITECTURE_ARM_CORTEX_R82, // 32bit/64bit capable real-time processor (based on ARMv8-R)

    // ARM Cortex-A Series (Application Profile - mixed 32-bit and 64-bit capabilities depending on core)
    ARCHITECTURE_ARM_CORTEX_A,   // General Cortex-A family (encompassing 32-bit and 64-bit cores)

    // Specific 32-bit Cortex-A Cores (ARMv7-A based)
    ARCHITECTURE_ARM_CORTEX_A5,  // 32bit application processor
    ARCHITECTURE_ARM_CORTEX_A7,  // 32bit application processor
    ARCHITECTURE_ARM_CORTEX_A8,  // 32bit application processor
    ARCHITECTURE_ARM_CORTEX_A9,  // 32bit application processor
    ARCHITECTURE_ARM_CORTEX_A15, // 32bit application processor
    ARCHITECTURE_ARM_CORTEX_A17, // 32bit application processor
    // ARCHITECTURE_ARM_CORTEX_A32, // 32bit application processor (ARMv8-A profile, but 32-bit only)

    // Specific 32/64-bit Capable Cortex-A Cores (ARMv8-A based, supporting both AArch32 and AArch64)
    ARCHITECTURE_ARM_CORTEX_A35, // 32bit/64bit application processor
    ARCHITECTURE_ARM_CORTEX_A53, // 32bit/64bit application processor
    ARCHITECTURE_ARM_CORTEX_A55, // 32bit/64bit application processor
    ARCHITECTURE_ARM_CORTEX_A57, // 32bit/64bit application processor (often used as "big" core in 64-bit systems)
    ARCHITECTURE_ARM_CORTEX_A72, // 32bit/64bit application processor
    ARCHITECTURE_ARM_CORTEX_A73, // 32bit/64bit application processor
    ARCHITECTURE_ARM_CORTEX_A75, // 32bit/64bit application processor
    ARCHITECTURE_ARM_CORTEX_A76, // 32bit/64bit application processor
    ARCHITECTURE_ARM_CORTEX_A77, // 32bit/64bit application processor
    ARCHITECTURE_ARM_CORTEX_A78, // 32bit/64bit application processor
    ARCHITECTURE_ARM_CORTEX_A78C, // 32bit/64bit application processor (Compute)
    ARCHITECTURE_ARM_CORTEX_A78AE, // 32bit/64bit application processor (Automotive Enhanced)

    // Specific 64-bit Only Cortex-A Cores (ARMv9-A based, or later ARMv8-A cores moving to 64-bit only)
    // As of May 2023, ARM announced new Cortex-A CPU cores are 64-bit only.
    ARCHITECTURE_ARM_CORTEX_A510, // 64bit application processor (LITTLE)
    ARCHITECTURE_ARM_CORTEX_A710, // 64bit application processor (BIG)
    ARCHITECTURE_ARM_CORTEX_A715, // 64bit application processor (BIG)
    ARCHITECTURE_ARM_CORTEX_A320, // 64bit application processor (LITTLE)
    ARCHITECTURE_ARM_CORTEX_A520, // 64bit application processor (LITTLE)
    ARCHITECTURE_ARM_CORTEX_A720, // 64bit application processor (BIG)
    ARCHITECTURE_ARM_CORTEX_A725, // 64bit application processor (BIG)

    // ARM Cortex-X Series (Application Profile - 64-bit only)
    ARCHITECTURE_ARM_CORTEX_X, // General Cortex-X family (encompassing 64-bit cores)

    // ARM Cortex-X Series (Extreme Performance - 64-bit only)
    // You would add these if needed for specific high-performance targeting, e.g.:
    ARCHITECTURE_ARM_CORTEX_X1, // 64bit extreme performance processor
    ARCHITECTURE_ARM_CORTEX_X2, // 64bit extreme performance processor
    ARCHITECTURE_ARM_CORTEX_X3, // 64bit extreme performance processor
    ARCHITECTURE_ARM_CORTEX_X4, // 64bit extreme performance processor
    ARCHITECTURE_ARM_CORTEX_X925, // 64bit extreme performance processor

    ARCHITECTURE_RISC_V_32, // 32bit architecture
    ARCHITECTURE_RISC_V_64, // 64bit architecture
    ARCHITECTURE_AVR_8, // 8bit architecture
    ARCHITECTURE_MSP430_16, // 16bit architecture
    ARCHITECTURE_MSP430_32, // 32bit architecture (e.g., MSP432)
    ARCHITECTURE_MIPS_32, // 32bit architecture
    ARCHITECTURE_MIPS_64, // 64bit architecture
    ARCHITECTURE_MIPS_16, // 16bit MIPS (instruction set or highly constrained core)
    ARCHITECTURE_MIPS_8, // 8bit MIPS (highly constrained core)
    ARCHITECTURE_POWERPC_32, // 32bit architecture
    ARCHITECTURE_POWERPC_64, // 64bit architecture
    ARCHITECTURE_SUPERH_16, // 16bit instruction set (on 32bit core)
    ARCHITECTURE_SUPERH_32, // 32bit architecture
    ARCHITECTURE_RENEXA_RX_32, // 32bit architecture
    ARCHITECTURE_XTENSA, // 32bit configurable architecture
    ARCHITECTURE_XTENSA_64, // 64bit configurable architecture
    ARCHITECTURE_8051_8, // 8bit architecture
    ARCHITECTURE_PIC16_8, // 8bit architecture
    ARCHITECTURE_PIC18_8, // 8bit architecture
    ARCHITECTURE_PIC24_16, // 16bit architecture
    ARCHITECTURE_DSPIC_16, // 16bit architecture
    ARCHITECTURE_PIC32_32, // 32bit architecture
    ARCHITECTURE_PIC32MX_32, // 32bit architecture
    ARCHITECTURE_PIC32MZ_32, // 32bit architecture
    ARCHITECTURE_PIC32MM_32, // 32bit architecture
    ARCHITECTURE_PIC32MK_32, // 32bit architecture
    ARCHITECTURE_CUSTOM, // Custom architecture
} TypeArchitecture;
                         
                                              
                                              
typedef enum{
    // ---High-level keywords---
    KEYWORD_STRUCT,                     // Defines a structure type and how it should be laid out in memory and how it storage should be allocated resembling struct concept in asm
    KEYWORD_CLASS,                     // Defines a class type and how it should be laid out in memory and how it behave should be resembling class concept in asm
    KEYWORD_DATA_DEFINE,               // Defines a data type and how it behave and work a kind of defined new type in asm

    // --- Data Definition ---
    KEYWORD_DATA_TYPE,                  // Defines and optionally allocates/initializes a named data location (e.g., 'data my_var = 10;', 'data my_array[10];')
    KEYWORD_DATA_EXTERNAL_DECLARE,      // Declares a variable that is defined in another compilation unit (e.g., 'external data another_var;')
    KEYWORD_SUB_DATA_AS,                //  refernce a name for compiler to know what is that name meaning and always going with the define keyword

    // --- C-like Control Flow Structures ---
    KEYWORD_CONTROL_IF,                 // Corresponds to C's 'if' statement logic
    KEYWORD_CONTROL_ELSE,               // Corresponds to C's 'else' statement logic
    KEYWORD_CONTROL_LABEL,              // Defines a jump target (e.g., 'my_label:')
    KEYWORD_CONTROL_GOTO,               // Unconditional transfer of control to a label (e.g., 'goto my_label ;')
    KEYWORD_CONTROL_CONDITIONAL_JUMP,   // Represents jumping based on a condition (e.g., 'jmpc ( a > 2 ) my_label ;')
    KEYWORD_CONTROL_JUMP,               // Represents jumping no condition 

    // --- C-like Function Call/Return ---
    KEYWORD_FUNCTION_CALL,              // Calls a function/subroutine (e.g., 'call my_func();')
    KEYWORD_FUNCTION_RETURN,            // Returns from a function/subroutine (e.g., 'return;')

    // --- Explicit Stack Operations (Fundamental for ASM-like logic) ---
    KEYWORD_STACK_PUSH,                 // Push data onto the stack (e.g., 'push reg;')
    KEYWORD_STACK_POP,                  // Pop data from the stack (e.g., 'pop reg;')

    // --- External Code/Data Linkage Directives (General) ---
    KEYWORD_EXTERNAL_INCLUDE,           // Include external code/data (like C's #include)
    KEYWORD_EXTERNAL_IMPORT,            // Import symbols (functions, variables) from other modules (for linker resolution)

    // --- Compiler/Target Directives ---
    KEYWORD_DIRECTIVE_ARCHITECTURE,     // Specifies the target processor architecture for compilation

} TypeKeyword;

typedef enum{
    // --- Execution Control Debug Keywords ---
    DEBUG_TRAP,      // Inserts a software breakpoint, causing execution to halt for debugger intervention.
    DEBUG_HALT,      // Terminates program execution unconditionally; often used for critical error states in debug builds.
    DEBUG_CAP,       // Triggers a capture or dump of a specified memory region's contents at this point in execution.

    // --- Debug-Specific Memory & Scope Control Keywords ---
    DEBUG_SECTION,   // A compiler directive defining a named memory region for debug-only variables, conceptually scoped to a code label or range.
                     // The compiler ensures variables in this section are primarily associated with the defined region.

    DEBUG_ZONE,      // Defines a specific code region (e.g., delimited by labels) within which variables declared in an associated DEBUG_SECTION are valid and accessible.
                     // The compiler commits to enforcing that these variables cannot be accessed from code outside this zone, preventing accidental corruption common in raw assembly.

    DEBUG_GLOBAL,    // Declares a debug variable or resource as globally accessible from any code label during debugging.
                     // This allows deliberate bypass of stricter scoping, but the developer is responsible for potential side effects or conflicts.

    DEBUG_FORCE,     // A highly granular access control keyword: a variable or resource marked with DEBUG_FORCE can ONLY be accessed (read/write)
                     // when program execution is precisely at a specific, designated label, or within an extremely narrow code window around it.

}TypeDebug;                                                                 
                                          
// --- General Literal Properties/Types ---
typedef enum {
    LITERAL_VALUE_UNSIGNED, // Property: indicates an unsigned numerical literal (e.g., '10U')
    LITERAL_VALUE_BOOL,     // Boolean literal (e.g., 'true', 'false')
    // No specific 'signed' literal, as numbers are implicitly signed unless 'UNSIGNED' property is applied
} Literal_general;

// --- Bit-Width Specific Literals ---
typedef enum {
    LITERAL_VALUE_INT8,         // 8-bit integer literal
    LITERAL_VALUE_FLOAT8,       // 8-bit floating-point literal (if supported)
    LITERAL_VALUE_CHARACTER8,   // 8-bit character literal (e.g., 'a')
} Literal_8bit;

typedef enum {
    LITERAL_VALUE_INT16,        // 16-bit integer literal
    LITERAL_VALUE_FLOAT16,      // 16-bit floating-point literal
    LITERAL_VALUE_CHARACTER16,  // 16-bit character literal (e.g., wide characters)
} Literal_16bit;

typedef enum {
    LITERAL_VALUE_INT32,        // 32-bit integer literal
    LITERAL_VALUE_FLOAT32,      // 32-bit floating-point literal
    LITERAL_VALUE_CHARACTER32,  // 32-bit character literal (e.g., Unicode code points)
} Literal_32bit;

typedef enum {
    LITERAL_VALUE_INT64,        // 64-bit integer literal
    LITERAL_VALUE_FLOAT64,      // 64-bit floating-point literal
    LITERAL_VALUE_CHARACTER64,  // 64-bit character literal (less common, but possible for very wide chars)
} Literal_64bit;

// --- Additional Literal Types ---
typedef enum {
    LITERAL_VALUE_STRING,       // String literal (e.g., "Hello, World!", typically stored in data section)
    LITERAL_VALUE_POINTER_NULL, // For a null pointer literal (e.g., 'NULL' or 'nullptr')
    LITERAL_VALUE_ADDRESS,      // For raw numerical addresses if they are a distinct literal concept from integers
} Literal_other;
                                          
typedef enum{                             
    // --- Statement & Expression Delimiters ---
    SEPARATOR_SEMI_COLON,    // ; (Statement terminator)
    SEPARATOR_COMMA,         // , (Separates items in lists: e.g., function arguments, multiple declarations)

    // --- Block & Grouping Delimiters ---
    SEPARATOR_OPEN_PAREN,    // ( (Function calls, expressions, type casts, grouping)
    SEPARATOR_CLOSE_PAREN,   // )
    SEPARATOR_OPEN_BRACKET,  // [ (Array indexing, memory dereference with offset)
    SEPARATOR_CLOSE_BRACKET, // ]
    SEPARATOR_OPEN_BRACE,    // { (Code blocks for functions, if/else, struct/class bodies)
    SEPARATOR_CLOSE_BRACE,   // }

    // --- Label Delimiter ---
    SEPARATOR_COLON,         // : (For defining labels: e.g., 'my_label:')

    // --- Operators (as separators/punctuators for syntax) ---
    SEPARATOR_ASSIGN,        // = (Assignment operator: e.g., 'var = value;')
    SEPARATOR_ARROW,         // -> (Pointer member access for structs/classes: e.g., 'ptr->member')
                    
} TypeSeparator;                               
                                               
typedef enum {
    // --- Assignment Operators ---
    OPERATOR_ASSIGNMENT,            // = (Assignment operator: e.g., 'var = value;')
    
    // --- Unary Operators ---
    OPERATOR_LOGICAL_NOT,           // ! (Logical NOT: typically acts on boolean results)
    OPERATOR_BITWISE_NOT,           // ~ (Bitwise NOT/One's complement: inverts all bits)
    OPERATOR_UNARY_POSITIVE,        // ++ (Forces operand to be positive: e.g., '++myVar' makes 'myVar = abs(myVar)')
    OPERATOR_UNARY_NEGATIVE,        // -- (Forces operand to be negative: e.g., '--myVar' makes 'myVar = -abs(myVar)')

    // --- Bitwise Operators ---
    OPERATOR_BITWISE_EXCLUSIVE_OR,  // ^ (Bitwise XOR)
    OPERATOR_BITWISE_OR,            // | (Bitwise OR)
    OPERATOR_BITWISE_AND,           // & (Bitwise AND)
    OPERATOR_SHIFT_LEFT,            // << (Bitwise Left Shift)
    OPERATOR_SHIFT_RIGHT,           // >> (Bitwise Right Shift)

    // --- Comparison Operators (Numerical & Logical Result) ---
    OPERATOR_EQUAL_TO,              // ==
    OPERATOR_NOT_EQUAL_TO,          // !=
    OPERATOR_LESS_THAN,             // <
    OPERATOR_GREATER_THAN,          // >
    OPERATOR_LESS_OR_EQUAL,         // <=
    OPERATOR_GREATER_OR_EQUAL,      // >=

    // --- Arithmetic Operators ---
    OPERATOR_ADD,                   // +
    OPERATOR_SUBTRACT,              // -
    OPERATOR_MODULUS,               // %
    OPERATOR_DIVISION,              // /
    OPERATOR_MULTIPLY,              // *

    // --- Compound Assignment Operators (Your Custom Syntax) ---
    OPERATOR_INCREMENT,             // =+ (Compound addition: e.g., 'var =+ value' means 'var = var + value')
    OPERATOR_DECREMENT,             // =- (Compound subtraction: e.g., 'var =- value' means 'var = var - value')
    OPERATOR_MULTIPLEMENT,          // =* (Compound multiplication: e.g., 'var =* value' means 'var = var * value')
    OPERATOR_DIVIDEMENT,            // =/ (Compound division: e.g., 'var =/ value' means 'var = var / value')
    OPERATOR_MODULUSMENT,           // =% (Compound modulus: e.g., 'var =% value' means 'var = var % value')

    // --- Logical Short-Circuiting Operators ---
    OPERATOR_LOGICAL_OR,            // || (Logical OR with short-circuiting)
    OPERATOR_LOGICAL_AND,           // && (Logical AND with short-circuiting)

    // --- Special Purpose Operators ---
    OPERATOR_BITFIELD_ACCESS,       // $ (For accessing specific bits or fields within a register/memory operand)

} TypeOperator;                             
             
typedef struct                                  
{                                               
    TypeArchitecture type;                      
} TokenArchitecture;                            
                                                
typedef struct                                 
{
    TypeRegister type;
} TokenRegister;

typedef struct
{
    TypeKeyword type;
} TokenKeyword;

typedef struct {
    Literal_general  TypeLiteral_general;
    Literal_8bit     type_8bit;
    Literal_16bit    type_16bit;
    Literal_32bit    type_32bit;
    Literal_64bit    type_64bit;
    Literal_other    type_other; // Other types of literal
} TypeLiteral; // Separate Literal to system

typedef struct {
    SystemType  System; // System type too accept or reject base on what is currently doing
    TypeLiteral Literal; // System value type it can hold
    bool allowed_8bit;   // permission to using
    bool allowed_16bit;
    bool allowed_32bit;
    bool allowed_64bit;
}SystemToken;


typedef struct
{
    TypeSeparator type;
} TokenSeparator;

typedef struct
{
    TypeOperator type;
} TokenOperator;

typedef ValueType; // A general value type to hold in identifier
    union {
        int int_val;
        float float_val;
        char* str_val;
        bool bool_val;
    } value; 

typedef struct{
    const int ID; // the identifier token ID
    ValueType val_type; // the value it hold
} TokenIdentifier;

typedef struct
{
    TypeDebug type;

} TokenDebug;

typedef enum {
    TOKEN_KEYWORD,   // Token type                             
    TOKEN_SYSTEM,                             
    TOKEN_OPERATOR,                               
    TOKEN_SEPARATOR,                            
    TOKEN_IDENTIFIER,                            
    TOKEN_DEBUG,                                 
    TOKEN_REGISTER,
    TOKEN_ARCHITECTURE,                              
} TokenType;

typedef union{
    TokenKeyword       Keyword;
    SystemToken        SystemToken;
    TokenOperator       Operator;
    TokenSeparator     Separator;
    TokenIdentifier    Identifier;
    TokenDebug         Debug;
    TokenArchitecture  Architecture;
    TokenRegister      Register;
} TokenValue;

typedef struct {
    TokenType type;  // What kind of token it is
    TokenValue value; // The value of the token (one of the types)
    int column;
    int line;
} Token;

typedef struct {
    const char character[100];  // Character to match
    Token token;  // Associated token
} LookupEntry;

int identifier_counter;
char Modulusment = '=' + '%'; // Modulusment character
