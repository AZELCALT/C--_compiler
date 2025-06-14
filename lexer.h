#define LEXER_H

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
}SystemType;

typedef enum{
    REGISTER_GENERAL_1, // general purpose register
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
    KEYWORD_FUNCTION_IF, // Keyword
    KEYWORD_SUBFUNCTION_GOTO, // like jump but for if condition and it more human readable than using condition and jump
    KEYWORD_SUBFUNCTION_ELSE, // another sub function with other condition
    KEYWORD_FUNCTION_LABEL,   // where it can jump to
    KEYWORD_FUNCTION_JUMP,    // jump to a location blindly
    KEYWORD_FUNCTION_CONDITIONAL_JUMP,  // jump to a location with a specific condition
    KEYWORD_LIBRARY_FUNCTION_INCLUDE,   // add a compiler known library
    KEYWORD_LIBRARY_FUNCTION_IMPORT,    // adda file with a path or location
    KEYWORD_ARCHITECTURE,               // tell the compiler what it need to compiling to
} TypeKeyword;

typedef enum{// Debug keyword
    DEBUG_TRAP, // stop point
    DEBUG_HALT, // stop all execution
    DEBUG_CAP,  // capture a memory 
    DEBUG_SECTION, // a pre-commited to the compiler that variable it only used by a pre-defined label can add a name for easier track
    DEBUG_ZONE,    // the defined area where the varible in section is able to call and no calling across
    DEBUG_GLOBAL,  // can be using freely dev choice but they will be respondsible for the risk
    DEBUG_FORCE,   // a strictly used by some specific label
}TypeDebug;                          
                                          
                                          
typedef enum{                             
    LITERAL_VALUE_UNSIGNED, // General Literal value            
    LITERAL_VALUE_BOOL,                          
}Literal_general;

typedef enum{                             
    LITERAL_VALUE_INT8, // 8bit and above exclusive value
    LITERAL_VALUE_FLOAT8,
    LITERAL_VALUE_CHARACTER8,                                                              
}Literal_8bit;
typedef enum{                             
    LITERAL_VALUE_INT16, // 16bit and above exclusive value
    LITERAL_VALUE_FLOAT16,                
    LITERAL_VALUE_CHARACTER16,                                                       
}Literal_16bit;
typedef enum{                             
    LITERAL_VALUE_INT32, // // 32bit and above exclusive value
    LITERAL_VALUE_FLOAT32,                 
    LITERAL_VALUE_CHARACTER32,                                       
}Literal_32bit;
typedef enum{                             
    LITERAL_VALUE_INT64, // 64bit exclusive value
    LITERAL_VALUE_FLOAT64,                 
    LITERAL_VALUE_CHARACTER64,                         
}Literal_64bit;
                                          
typedef enum{                             
    SEPARATOR_SEMI_COLON,    // Some default separator                    
    SEPARATOR_OPEN_PAREN,                       
    SEPARATOR_CLOSE_PAREN,                       
    SEPARATOR_OPEN_BRACKET,                      
    SEPARATOR_CLOSE_BRACKET,                     
} TypeSeparator;                               
                                               
typedef enum{                                  
    OPERAND_LOGICAL_NOT,                         // Logical Operand 
    OPERAND_LOGICAL_EXCLUSIVE_OR,                          
    OPERAND_LOGICAL_OR,                          
    OPERAND_LOGICAL_AND,                         
    OPERAND_LOGICAL_EQUAL_TO,                    
    OPERAND_NUMERIC_LOGICAL_LESS_OR_EQUAL,       // Numerical compare 
    OPERAND_NUMERIC_LOGICAL_GREATER_OR_EQUAL,    
    OPERAND_NUMERIC_LOGICAL_NOT_EQUAL_TO,        
    OPERAND_NUMERIC_LOGICAL_LESS_THAN,           
    OPERAND_NUMERIC_LOGICAL_GREATER_THAN,        
    OPERAND_NUMERICAL_ADD,                       // Numerical calculation            
    OPERAND_NUMERICAL_SUBTRACT,                  
    OPERAND_NUMERICAL_MODULUS,                   
    OPERAND_NUMERICAL_DIVISION,                  
    OPERAND_NUMERICAL_MULTIPLY,                 
} TypeOperand;                                  
             
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
    TypeOperand type;
} TokenOperand;

typedef ValueType; // A general value type to hold in identifier
    union {
        int int_val;
        float float_val;
        char* str_val;
        bool bool_val;
    } value; 

typedef struct{
    const int ID; // the identifier token ID
    SystemType type; // the identifier value type it can hold
    ValueType val_type; // the value it hold
} TokenIdentifier;

typedef struct
{
    TypeDebug type;

} TokenDebug;

typedef enum {
    TOKEN_KEYWORD,   // Token type                             
    TOKEN_SYSTEM,                             
    TOKEN_OPERAND,                               
    TOKEN_SEPARATOR,                            
    TOKEN_IDENTIFIER,                            
    TOKEN_DEBUG,                                 
    TOKEN_REGISTER,
    TOKEN_ARCHITECTURE,                              
} TokenType;

typedef union{
    TokenKeyword       Keyword;
    SystemToken        SystemToken;
    TokenOperand       Operand;
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
