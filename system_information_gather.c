#include "lexer.h"


LookupEntry keywordLookup[] = {
    {.character="if",                .token={.type=TOKEN_KEYWORD,       .value={.Keyword={KEYWORD_FUNCTION_IF}}}},
    {.character="goto",              .token={.type=TOKEN_KEYWORD,       .value={.Keyword={KEYWORD_SUBFUNCTION_GOTO}}}},
    {.character="else",              .token={.type=TOKEN_KEYWORD,       .value={.Keyword={KEYWORD_SUBFUNCTION_ELSE}}}},
    {.character="label",             .token={.type=TOKEN_KEYWORD,       .value={.Keyword={KEYWORD_FUNCTION_LABEL}}}},
    {.character="jmp",               .token={.type=TOKEN_KEYWORD,       .value={.Keyword={KEYWORD_FUNCTION_JUMP}}}},
    {.character="jmpc",              .token={.type=TOKEN_KEYWORD,       .value={.Keyword={KEYWORD_FUNCTION_CONDITIONAL_JUMP}}}},
    {.character="#import",           .token={.type=TOKEN_KEYWORD,       .value={.Keyword={KEYWORD_LIBRARY_FUNCTION_IMPORT}}}},
    {.character="#include",          .token={.type=TOKEN_KEYWORD,       .value={.Keyword={KEYWORD_LIBRARY_FUNCTION_INCLUDE}}}},
    {.character="architect",         .token={.type=TOKEN_KEYWORD,       .value={.Keyword={KEYWORD_ARCHITECTURE}}}},
    {.character="trap",              .token={.type=TOKEN_DEBUG,         .value={.Debug={DEBUG_TRAP}}}},
    {.character="halt",              .token={.type=TOKEN_DEBUG,         .value={.Debug={DEBUG_HALT}}}},
    {.character="cap",               .token={.type=TOKEN_DEBUG,         .value={.Debug={DEBUG_CAP}}}},
    {.character="section",           .token={.type=TOKEN_DEBUG,         .value={.Debug={DEBUG_SECTION}}}},
    {.character="zone",              .token={.type=TOKEN_DEBUG,         .value={.Debug={DEBUG_ZONE}}}},
    {.character="cap",               .token={.type=TOKEN_DEBUG,         .value={.Debug={DEBUG_CAP}}}},
    {.character="global",            .token={.type=TOKEN_DEBUG,         .value={.Debug={DEBUG_GLOBAL}}}},
    {.character="force",             .token={.type=TOKEN_DEBUG,         .value={.Debug={DEBUG_FORCE}}}},
    {.character="+",                 .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_NUMERICAL_ADD}}}},
    {.character="-",                 .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_NUMERICAL_SUBTRACT}}}},
    {.character="*",                 .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_NUMERICAL_MULTIPLY}}}},
    {.character="/",                 .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_NUMERICAL_DIVISION}}}},
    {.character=Modulus,             .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_NUMERICAL_MODULUS}}}},
    {.character="&&",                .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_LOGICAL_AND}}}},
    {.character="||",                .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_LOGICAL_OR}}}},
    {.character="^",                 .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_LOGICAL_EXCLUSIVE_OR}}}},
    {.character="!",                 .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_LOGICAL_NOT}}}},
    {.character="==",                .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_LOGICAL_EQUAL_TO}}}},
    {.character="!=",                .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_NUMERIC_LOGICAL_NOT_EQUAL_TO}}}},
    {.character=">=",                .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_NUMERIC_LOGICAL_GREATER_OR_EQUAL}}}},
    {.character="<=",                .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_NUMERIC_LOGICAL_LESS_OR_EQUAL}}}},
    {.character="<",                 .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_NUMERIC_LOGICAL_LESS_THAN}}}},
    {.character=">",                 .token={.type=TOKEN_OPERAND,       .value={.Operand={OPERAND_NUMERIC_LOGICAL_GREATER_THAN}}}},
    {.character="x86_64",            .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_X86_64}}}},
    {.character="x86_32",            .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_X86_32}}}},
    {.character="arm_cortex_m",      .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_ARM_CORTEX_M}}}},
    {.character="arm_thumb",         .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_ARM_THUMB}}}},
    {.character="arm_thumb_2",       .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_ARM_THUMB_2}}}},
    {.character="powerPC_32",        .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_POWERPC_32}}}},
    {.character="powerPC_64",        .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_POWERPC_64}}}},
    {.character="avr_8",             .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_AVR_8}}}},
    {.character="mips_64",           .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_MIPS_64}}}},
    {.character="mips_32",           .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_MIPS_32}}}},
    {.character="msp430_16",         .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_MSP430_16}}}},
    {.character="risc_v_32",         .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_RISC_V_32}}}},
    {.character="risc_v_64",         .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_RISC_V_64}}}},
    {.character="superh_32",         .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_SUPERH_32}}}},
    {.character="renexa_RX_64",      .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_RENEXA_RX_64}}}},
    {.character="xtensa",            .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_XTENSA}}}},
    {.character="pic16_8",           .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_PIC16_8}}}},
    {.character="pic18_8",           .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_PIC18_8}}}},
    {.character="pic24_16",          .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_PIC24_16}}}},
    {.character="pic32_32",          .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_PIC32_32}}}},
    {.character="dspic_16",          .token={.type=TOKEN_ARCHITECTURE,  .value={.Architecture={ARCHITECTURE_DSPIC_16}}}},
    {.character="general_1",         .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_1}}}},
    {.character="general_2",         .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_2}}}},
    {.character="general_3",         .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_3}}}},
    {.character="general_4",         .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_4}}}},
    {.character="general_5",         .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_5}}}},
    {.character="general_6",         .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_6}}}},
    {.character="general_7",         .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_7}}}},
    {.character="general_8",         .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_8}}}},
    {.character="general_9",         .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_9}}}},
    {.character="general_10",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_10}}}},
    {.character="general_11",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_11}}}},
    {.character="general_12",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_12}}}},
    {.character="general_13",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_13}}}},
    {.character="general_14",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_14}}}},
    {.character="general_15",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_15}}}},
    {.character="general_16",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_16}}}},
    {.character="general_17",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_17}}}},
    {.character="general_18",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_18}}}},
    {.character="general_19",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_19}}}},
    {.character="general_20",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_20}}}},
    {.character="general_21",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_21}}}},
    {.character="general_22",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_22}}}},
    {.character="general_23",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_23}}}},
    {.character="general_24",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_24}}}},
    {.character="general_25",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_25}}}},
    {.character="general_26",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_26}}}},
    {.character="general_27",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_27}}}},
    {.character="general_28",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_28}}}},
    {.character="general_29",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_29}}}},
    {.character="general_30",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_30}}}},
    {.character="general_31",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_31}}}},
    {.character="general_32",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_GENERAL_32}}}},
    {.character="stack_pointer",     .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_STACK_POINTER}}}},
    {.character="frame_pointer",     .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_FRAME_POINTER}}}},
    {.character="float_pointer",     .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_FLOATING_POINT_REGISTER}}}},
    {.character="status_pointer",    .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_STATUS_REGISTER}}}},
    {.character="control_pointer",   .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_CONTROL_REGISTER}}}},
    {.character="link_pointer",      .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_LINK_REGISTER}}}},
    {.character="PC_pointer",        .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_PROGRAM_COUNTER}}}},
    {.character="segment_pointer",   .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_SEGMENT_REGISTER}}}},
    {.character="special_pointer",   .token={.type=TOKEN_REGISTER,      .value={.Register={REGISTER_SPECIAL_PURPOSE_REGISTER}}}},  
};

SystemToken get_default_system_token(char character[100]) {
    TypeArchitecture arch;
    if (strcmp(character, "x86_64") == 0) {
        TypeArchitecture arch = ARCHITECTURE_X86_64;
    }
    else if (strcmp(character, "x86_32") == 0) {
        TypeArchitecture arch = ARCHITECTURE_X86_32;
    }
    else if (strcmp(character, "arm_cortex_m") == 0) {
        TypeArchitecture arch = ARCHITECTURE_ARM_CORTEX_M;
    }
    else if (strcmp(character, "arm_thumb") == 0) {
        TypeArchitecture arch = ARCHITECTURE_ARM_THUMB;
    }
    else if (strcmp(character, "arm_thumb_2") == 0) {
        TypeArchitecture arch = ARCHITECTURE_ARM_THUMB_2;
    }
    else if (strcmp(character, "powerPC_32") == 0) {
        TypeArchitecture arch = ARCHITECTURE_POWERPC_32;
    }
    else if (strcmp(character, "powerPC_64") == 0) {
        TypeArchitecture arch = ARCHITECTURE_POWERPC_64;
    }
    else if (strcmp(character, "avr_8") == 0) {
        TypeArchitecture arch = ARCHITECTURE_AVR_8;
    }
    else if (strcmp(character, "mips_64") == 0) {
        TypeArchitecture arch = ARCHITECTURE_MIPS_64;
    }
    else if (strcmp(character, "mips_32") == 0) {
        TypeArchitecture arch = ARCHITECTURE_MIPS_32;
    }
    else if (strcmp(character, "msp430_16") == 0) {
        TypeArchitecture arch = ARCHITECTURE_MSP430_16;
    }
    else if (strcmp(character, "risc_v_32") == 0) {
        TypeArchitecture arch = ARCHITECTURE_RISC_V_32;
    }
    else if (strcmp(character, "risc_v_64") == 0) {
        TypeArchitecture arch = ARCHITECTURE_RISC_V_64;
    }
    else if (strcmp(character, "superh_32") == 0) {
        TypeArchitecture arch = ARCHITECTURE_SUPERH_32;
    }
    else if (strcmp(character, "renexa_RX_64") == 0) {
        TypeArchitecture arch = ARCHITECTURE_RENEXA_RX_64;
    }
    else if (strcmp(character, "xtensa") == 0){
        TypeArchitecture arch = ARCHITECTURE_XTENSA;
    }
    else if (strcmp(character, "pic16_8") == 0) {
        TypeArchitecture arch = ARCHITECTURE_PIC16_8;
    }
    else if (strcmp(character, "pic18_8") == 0) {
        TypeArchitecture arch = ARCHITECTURE_PIC18_8;
    }
    else if (strcmp(character, "pic24_16") == 0) {
        TypeArchitecture arch = ARCHITECTURE_PIC24_16;
    }
    else if (strcmp(character, "pic32_32") == 0) {
        TypeArchitecture arch = ARCHITECTURE_PIC32_32;
    }
    else if (strcmp(character, "dspic_16") == 0) {
        TypeArchitecture arch = ARCHITECTURE_DSPIC_16;
    }
    else if (strcmp(character, "custom") == 0) {
        // Custom architecture
        TypeArchitecture arch = ARCHITECTURE_X86_64; // or any default you prefer
    }

    switch (TypeArchitecture arch))
    {
    case ARCHITECTURE_X86_64:
        SystemToken x86_64_token = {
            .System = SYSTEM_64BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = true
        };
        break;
    case ARCHITECTURE_X86_32:
        SystemToken x86_32_token = {
            .System = SYSTEM_32BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = false
        };
        break;
    case ARCHITECTURE_ARM_CORTEX_M:
        SystemToken arm_cortex_m_token = {
            .System = SYSTEM_32BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = false
        };
        break;
    case ARCHITECTURE_ARM_THUMB:
        SystemToken arm_thumb_token = {
            .System = SYSTEM_32BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = false
        };
        break;
    case ARCHITECTURE_ARM_THUMB_2:
        SystemToken arm_thumb_2_token = {
            .System = SYSTEM_32BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = false
        };
        break;
    case ARCHITECTURE_POWERPC_32:
        SystemToken powerpc_32_token = {
            .System = SYSTEM_32BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = false
        };
        break;
    case ARCHITECTURE_POWERPC_64:
        SystemToken powerpc_64_token = {
            .System = SYSTEM_64BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = true
        };
        break;

    case ARCHITECTURE_AVR_8:
        SystemToken avr_8_token = {
            .System = SYSTEM_8BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = false,
            .allowed_32bit = false,
            .allowed_64bit = false
        };
        break;

    case ARCHITECTURE_MIPS_64:
        SystemToken mips_64_token = {
            .System = SYSTEM_64BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = true
        };
        break;

    case ARCHITECTURE_MIPS_32:
        SystemToken mips_32_token = {
            .System = SYSTEM_32BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = false
        };
        break;

    case ARCHITECTURE_MSP430_16:
        SystemToken msp430_16_token = {
            .System = SYSTEM_16BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = false,
            .allowed_64bit = false
        };
        break;

    case ARCHITECTURE_RISC_V_32:
        SystemToken risc_v_32_token = {
            .System = SYSTEM_32BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = false
        };
        break;

    case ARCHITECTURE_RISC_V_64:
        SystemToken risc_v_64_token = {
            .System = SYSTEM_64BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = true
        };
        break;
    
    case ARCHITECTURE_SUPERH_32:
        SystemToken superh_32_token = {
            .System = SYSTEM_32BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = false
        };
        break;
    
    case ARCHITECTURE_RENEXA_RX_64:
        SystemToken renexa_rx_64_token = {
            .System = SYSTEM_64BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = true
        };
        break;

    case ARCHITECTURE_XTENSA:
        SystemToken xtensa_token = {
            .System = SYSTEM_32BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = false
        };
        break;
    
    case ARCHITECTURE_PIC16_8:
        SystemToken pic16_8_token = {
            .System = SYSTEM_8BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = false,
            .allowed_32bit = false,
            .allowed_64bit = false
        };
        break;
    
    case ARCHITECTURE_PIC18_8:
        SystemToken pic18_8_token = {
            .System = SYSTEM_8BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = false,
            .allowed_32bit = false,
            .allowed_64bit = false
        };
        break;

    case ARCHITECTURE_PIC24_16:
        SystemToken pic24_16_token = {
            .System = SYSTEM_16BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = false,
            .allowed_64bit = false
        };
        break;

    case ARCHITECTURE_PIC32_32:
        SystemToken pic32_32_token = {
            .System = SYSTEM_32BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = false
        };
        break;

    case ARCHITECTURE_DSPIC_16:
        SystemToken dspic_16_token = {
            .System = SYSTEM_16BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = false,
            .allowed_64bit = false
        };
        break;
    
    case ARCHITECTURE_MIPS_32:
        SystemToken mips_32_token = {
            .System = SYSTEM_32BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = false
        };
        break;
    
    case ARCHITECTURE_MIPS_64:
        SystemToken mips_64_token = {
            .System = SYSTEM_64BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = true
        };
        break;
    
    case ARCHITECTURE_POWERPC_32
        SystemToken powerpc_32_token = {
            .System = SYSTEM_32BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = false
        };
        break;
    
    case ARCHITECTURE_POWERPC_64:
        SystemToken powerpc_64_token = {
            .System = SYSTEM_64BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = true
        };
        break;
    
    case ARCHITECTURE_8051_8:
        SystemToken _8051_8_token = {
            .System = SYSTEM_8BIT,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = false,
            .allowed_32bit = false,
            .allowed_64bit = false
        };
        break;
    
    default ARCHITECTURE_CUSTOM:
        SystemToken default_system_token = {
            .System = SYSTEM_CUSTOM,
            .Literal = LITERAL_VALUE_UNSIGNED,
            .allowed_8bit = true,
            .allowed_16bit = true,
            .allowed_32bit = true,
            .allowed_64bit = true
        };
        break;
    }



    
    return default_system_token;
}






