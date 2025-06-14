#include <Lookup_table.h>

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
    else {
        // Custom architecture
        TypeArchitecture arch = ARCHITECTURE_CUSTOM; // or any default you prefer
    }

    switch (arch) {
        // --- X86 Architectures ---
        case ARCHITECTURE_X86_16:
            system_token.System = SYSTEM_16BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = false; // 16-bit architecture, no 32-bit support
            system_token.allowed_64bit = false; // 16-bit architecture, no 64-bit support
            break;
        case ARCHITECTURE_X86_32:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // 32-bit architecture, no 64-bit support
            break;
        case ARCHITECTURE_X86_64:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        // --- ARM Architectures (General) ---
        // ARM 32-bit and Thumb/Thumb-2 instruction sets mostly operate on 32-bit cores
        case ARCHITECTURE_ARM_32:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // ARM 32-bit architecture, no 64-bit support
            break;
        case ARCHITECTURE_ARM_THUMB:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // ARM Thumb is primarily 32-bit
            break;
        case ARCHITECTURE_ARM_THUMB_2:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            break;
        case ARCHITECTURE_ARM_64:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        // --- ARM Cortex-M Series (Primarily 32-bit Microcontrollers) ---
        case ARCHITECTURE_ARM_CORTEX_M:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // Cortex-M series are typically 32-bit
            break;

        case ARCHITECTURE_ARM_CORTEX_M0:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // Cortex-M series are typically 32-bit
            break;

        case ARCHITECTURE_ARM_CORTEX_M3:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // Cortex-M series are typically 32-bit
            break;

        case ARCHITECTURE_ARM_CORTEX_M4:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // Cortex-M series are typically 32-bit
            break;

        case ARCHITECTURE_ARM_CORTEX_M7:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // Cortex-M series are typically 32-bit
            break;

        case ARCHITECTURE_ARM_CORTEX_M33:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // Cortex-M series are typically 32-bit
            break;

        case ARCHITECTURE_ARM_CORTEX_M55:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // Cortex-M55 is primarily 32-bit, but has some 64-bit capabilities
            break;

        // --- ARM Cortex-R Series (Real-time Profile) ---
        case ARCHITECTURE_ARM_CORTEX_R:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // Cortex-R series are typically 32-bit
            break;

        case ARCHITECTURE_ARM_CORTEX_R4:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // Cortex-R series are typically 32-bit
            break;

        case ARCHITECTURE_ARM_CORTEX_R5:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // Cortex-R series are typically 32-bit
            break;

        case ARCHITECTURE_ARM_CORTEX_R7:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // Cortex-R series are typically 32-bit
            break;

        case ARCHITECTURE_ARM_CORTEX_R8:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // Cortex-R series are typically 32-bit
            break;
        case ARCHITECTURE_ARM_CORTEX_R52:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_R82:
            // Cortex-R82 is 32/64-bit capable
            system_token.System = SYSTEM_64BIT; // Classify as 64-bit as it has the capability
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        // --- ARM Cortex-A Series (Application Profile) ---
        case ARCHITECTURE_ARM_CORTEX_A:
            // General Cortex-A family, can be 32-bit or 64-bit depending on core, assume highest capability
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        // Specific 32-bit Cortex-A Cores (ARMv7-A based)
        case ARCHITECTURE_ARM_CORTEX_A5:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // 32-bit architecture, no 64-bit support
            break;

        case ARCHITECTURE_ARM_CORTEX_A7:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // 32-bit architecture, no 64-bit support
            break;

        case ARCHITECTURE_ARM_CORTEX_A8:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // 32-bit architecture, no 64-bit support
            break;

        case ARCHITECTURE_ARM_CORTEX_A9:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // 32-bit architecture, no 64-bit support
            break;

        case ARCHITECTURE_ARM_CORTEX_A15:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // 32-bit architecture, no 64-bit support
            break;

        case ARCHITECTURE_ARM_CORTEX_A17:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // 32-bit architecture, no 64-bit support
            break;

        // Specific 32/64-bit Capable Cortex-A Cores (ARMv8-A based, supporting both AArch32 and AArch64)
        case ARCHITECTURE_ARM_CORTEX_A35:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_A53:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_A55:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_A57:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_A72:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_A73:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_A75:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_A76:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_A77:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_A78:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;
        
        case ARCHITECTURE_ARM_CORTEX_A78C:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_A78AE:
            system_token.System = SYSTEM_64BIT; // Capable of 64-bit, so classify as such
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_A78AE:
            system_token.System = SYSTEM_64BIT; // Capable of 64-bit, so classify as such
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        // Specific 64-bit Only Cortex-A Cores (ARMv9-A based, or later ARMv8-A cores moving to 64-bit only)
        case ARCHITECTURE_ARM_CORTEX_A510:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_A710:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;


        case ARCHITECTURE_ARM_CORTEX_A715:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;


        case ARCHITECTURE_ARM_CORTEX_A320:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;


        case ARCHITECTURE_ARM_CORTEX_A520:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_A720:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_A725:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        // --- ARM Cortex-X Series (Extreme Performance - 64-bit only) ---
        case ARCHITECTURE_ARM_CORTEX_X:
            system_token.System = SYSTEM_64BIT; // Cortex-X series are 64-bit only
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true; 
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_X1:
            system_token.System = SYSTEM_64BIT; // Cortex-X series are 64-bit only
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true; 
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_X2:
            system_token.System = SYSTEM_64BIT; // Cortex-X series are 64-bit only
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true; 
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_X3:
            system_token.System = SYSTEM_64BIT; // Cortex-X series are 64-bit only
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true; 
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        case ARCHITECTURE_ARM_CORTEX_X4:    
            system_token.System = SYSTEM_64BIT; // Cortex-X series are 64-bit only
            system_token.allowed_8bit = true;  
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;
            
        case ARCHITECTURE_ARM_CORTEX_X925:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        // --- RISC-V Architectures ---
        case ARCHITECTURE_RISC_V_32:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // RISC-V 32-bit is typically not 64-bit
            break;

        case ARCHITECTURE_RISC_V_64:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        // --- AVR Architecture ---
        case ARCHITECTURE_AVR_8:
            system_token.System = SYSTEM_8BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = false; // AVR is typically 8-bit, but can use 16-bit registers in some cases
            system_token.allowed_32bit = false; // AVR is typically not 32-bit
            system_token.allowed_64bit = false; // AVR is typically not 64-bit
            break;

        // --- MSP430 Architectures ---
        case ARCHITECTURE_MSP430_16:
            system_token.System = SYSTEM_16BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = false; // MSP430 is typically not 32-bit
            system_token.allowed_64bit = false; // MSP430 is typically not 64-bit
            break;

        case ARCHITECTURE_MSP430_32:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // MSP430 is typically not 64-bit
            break;

        // --- MIPS Architectures ---
        case ARCHITECTURE_MIPS_8:
            system_token.System = SYSTEM_8BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = false; // MIPS 8-bit is not common, but can be used in some embedded systems
            system_token.allowed_32bit = false; // MIPS 8-bit is not typically 32-bit 
            system_token.allowed_64bit = false; // MIPS 8-bit is not typically 64-bit
            break;

        case ARCHITECTURE_MIPS_16:
            system_token.System = SYSTEM_16BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = false; // MIPS 16-bit is typically not 32-bit
            system_token.allowed_64bit = false; // MIPS 16-bit is typically not 64-bit
            break;

        case ARCHITECTURE_MIPS_32:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // MIPS 32-bit is typically not 64-bit
            break;

        case ARCHITECTURE_MIPS_64:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        // --- PowerPC Architectures ---
        case ARCHITECTURE_POWERPC_32:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // PowerPC 32-bit is typically not 64-bit
            break;

        case ARCHITECTURE_POWERPC_64:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        // --- SuperH Architectures ---
        case ARCHITECTURE_SUPERH_16:
            system_token.System = SYSTEM_16BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = false; // SuperH is typically 16-bit or 32-bit
            system_token.allowed_64bit = false; // SuperH is not typically 64-bit
            break;
        case ARCHITECTURE_SUPERH_32:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // SuperH is typically 32-bit
            break;

        // --- Renesas RX Architecture ---
        case ARCHITECTURE_RENEXA_RX_32:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // RX is typically 32-bit
            break;

        // --- Xtensa Architectures ---
        case ARCHITECTURE_XTENSA: // Assuming default Xtensa is 32-bit
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // Xtensa is typically 32-bit, but can be extended to 64-bit
            break;
        case ARCHITECTURE_XTENSA_64:
            system_token.System = SYSTEM_64BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;

        // --- 8051 Architecture ---
        case ARCHITECTURE_8051_8:
            system_token.System = SYSTEM_8BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = false; // 8051 can use 16-bit registers for some operations
            system_token.allowed_32bit = false; // 8051 is not typically 32-bit
            system_token.allowed_64bit = false; // 8051 is not typically 64-bit
            break;

        // --- PIC Architectures ---
        case ARCHITECTURE_PIC16_8:
            system_token.System = SYSTEM_8BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = false; // PIC16 is primarily 8-bit
            system_token.allowed_32bit = false; // PIC16 is not typically 32-bit
            system_token.allowed_64bit = false; // PIC16 is not typically 64-bit
            break;

        case ARCHITECTURE_PIC18_8:
            system_token.System = SYSTEM_8BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = false; // 8051 can use 16-bit registers for some operations
            system_token.allowed_32bit = false; // 8051 is not typically 32-bit
            system_token.allowed_64bit = false; // 8051 is not typically 64-bit
            break;

        case ARCHITECTURE_PIC24_16:
            system_token.System = SYSTEM_16BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = false; // PIC24 is primarily 16-bit
            system_token.allowed_64bit = false; // PIC24 is not typically 64-bit
            break;

        case ARCHITECTURE_DSPIC_16:
            system_token.System = SYSTEM_16BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = false; // PIC24/DSPIC is primarily 16-bit
            system_token.allowed_64bit = false; // PIC24/DSPIC is not typically 64-bit
            break;

        case ARCHITECTURE_PIC32_32:
            system_token.System = SYSTEM_32BIT;
            system_token.Literal = LITERAL_VALUE_UNSIGNED; // Explicitly set as per your example
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // PIC32 is primarily 32-bit
            break;

        case ARCHITECTURE_PIC32MX_32:
            system_token.System = SYSTEM_32BIT;
            system_token.Literal = LITERAL_VALUE_UNSIGNED; // Explicitly set as per your example
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // PIC32 is primarily 32-bit
            break;

        case ARCHITECTURE_PIC32MZ_32:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // PIC32 is primarily 32-bit
            break;

        case ARCHITECTURE_PIC32MM_32:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // PIC32 is primarily 32-bit
            break;
        case ARCHITECTURE_PIC32MK_32:
            system_token.System = SYSTEM_32BIT;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = false; // PIC32 is primarily 32-bit
            break;

        // --- Custom Architecture ---
        default ARCHITECTURE_CUSTOM:
            system_token.System = SYSTEM_CUSTOM;
            system_token.allowed_8bit = true;
            system_token.allowed_16bit = true;
            system_token.allowed_32bit = true;
            system_token.allowed_64bit = true;
            break;
    }
    return system_token;
}