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





Token get_normal_token(int column,int line,char character[100]){
    
    int i;
    int lenght = len(keywordLookup);
    int character_lenght = len(character);
    for (i=0;i <= lenght; i++);{
        if (strcmp(character,keywordLookup[i].character) == 0){
            Token current_token  = keywordLookup[i].token;
            current_token.column = column;
            current_token.line   = line;
            return current_token;

        }
    }
    if (isdigit(character[0])==0){
        if(check_for_int_value(character,character_lenght)==0){
            int value = get_int_value(character);
        }
        else if(check_for_float_value(character,character_lenght)==0){
            int value = get_float_value(character);
        }
        else{

        }
        
    }
    else{
        identifier_counter = identifier_counter + 1;
        //Token current_token  = {.value={.Identifier={.ID=identifier_counter,.type={}}}};
    }
   
 }

bool check_for_int_value(char character[100],int character_lenght){
    int i;
    for (i=0;i<=character_lenght;i++){
        if (isdigit(character[i])==0){
            continue;
        }
        else{
            return false;
        }
    }
    return true;
}

bool check_for_float_value(char character[100],int character_lenght){
    int i;
    int flag =0;
    for (i=0;i<=character_lenght;i++){
        if (character[i]=="."){
            flag = flag+1;
        }
        if (isdigit(character[i])==0 || flag <=1){
            continue;
        }
        else{
            return false;
        }
    }
    return true;
}

int get_int_value(char character[100]){
    char *endptr;
    long int_val = strtol(character, &endptr, 10);
        return int_val;
}
double get_float_value(char character[100]){
    char *endptr;
    double float_val = strtod(character, &endptr);
        return float_val;
}


