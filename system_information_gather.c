#include "Fundamentals_property.h"

SystemToken arch;

SystemToken get_default_SystemToken(char character[100]) {
    TypeArchitecture architecture;
    // Map string to TypeArchitecture enum
    if (strcmp(character, "x86_64") == 0) {
        architecture = ARCHITECTURE_X86_64;
    } else if (strcmp(character, "x86_32") == 0) {
        architecture = ARCHITECTURE_X86_32;
    } else if (strcmp(character, "x86_16") == 0) {
        architecture = ARCHITECTURE_X86_16;
    } else if (strcmp(character, "arm_32") == 0) {
        architecture = ARCHITECTURE_ARM_32;
    } else if (strcmp(character, "arm_64") == 0) {
        architecture = ARCHITECTURE_ARM_64;
    } else if (strcmp(character, "arm_thumb") == 0) {
        architecture = ARCHITECTURE_ARM_THUMB;
    } else if (strcmp(character, "arm_thumb_2") == 0) {
        architecture = ARCHITECTURE_ARM_THUMB_2;
    } else if (strcmp(character, "arm_cortex_m") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_M;
    } else if (strcmp(character, "arm_cortex_m0") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_M0;
    } else if (strcmp(character, "arm_cortex_m3") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_M3;
    } else if (strcmp(character, "arm_cortex_m4") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_M4;
    } else if (strcmp(character, "arm_cortex_m7") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_M7;
    } else if (strcmp(character, "arm_cortex_m33") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_M33;
    } else if (strcmp(character, "arm_cortex_m55") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_M55;
    } else if (strcmp(character, "arm_cortex_r") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_R;
    } else if (strcmp(character, "arm_cortex_r4") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_R4;
    } else if (strcmp(character, "arm_cortex_r5") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_R5;
    } else if (strcmp(character, "arm_cortex_r7") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_R7;
    } else if (strcmp(character, "arm_cortex_r8") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_R8;
    } else if (strcmp(character, "arm_cortex_r52") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_R52;
    } else if (strcmp(character, "arm_cortex_r82") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_R82;
    } else if (strcmp(character, "arm_cortex_a") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A;
    } else if (strcmp(character, "arm_cortex_a5") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A5;
    } else if (strcmp(character, "arm_cortex_a7") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A7;
    } else if (strcmp(character, "arm_cortex_a8") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A8;
    } else if (strcmp(character, "arm_cortex_a9") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A9;
    } else if (strcmp(character, "arm_cortex_a15") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A15;
    } else if (strcmp(character, "arm_cortex_a17") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A17;
    } else if (strcmp(character, "arm_cortex_a35") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A35;
    } else if (strcmp(character, "arm_cortex_a53") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A53;
    } else if (strcmp(character, "arm_cortex_a55") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A55;
    } else if (strcmp(character, "arm_cortex_a57") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A57;
    } else if (strcmp(character, "arm_cortex_a72") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A72;
    } else if (strcmp(character, "arm_cortex_a73") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A73;
    } else if (strcmp(character, "arm_cortex_a75") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A75;
    } else if (strcmp(character, "arm_cortex_a76") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A76;
    } else if (strcmp(character, "arm_cortex_a77") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A77;
    } else if (strcmp(character, "arm_cortex_a78") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A78;
    } else if (strcmp(character, "arm_cortex_a78c") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A78C;
    } else if (strcmp(character, "arm_cortex_a78ae") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A78AE;
    } else if (strcmp(character, "arm_cortex_a510") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A510;
    } else if (strcmp(character, "arm_cortex_a710") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A710;
    } else if (strcmp(character, "arm_cortex_a715") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A715;
    } else if (strcmp(character, "arm_cortex_a320") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A320;
    } else if (strcmp(character, "arm_cortex_a520") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A520;
    } else if (strcmp(character, "arm_cortex_a720") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A720;
    } else if (strcmp(character, "arm_cortex_a725") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_A725;
    } else if (strcmp(character, "arm_cortex_x") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_X;
    } else if (strcmp(character, "arm_cortex_x1") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_X1;
    } else if (strcmp(character, "arm_cortex_x2") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_X2;
    } else if (strcmp(character, "arm_cortex_x3") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_X3;
    } else if (strcmp(character, "arm_cortex_x4") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_X4;
    } else if (strcmp(character, "arm_cortex_x925") == 0) {
        architecture = ARCHITECTURE_ARM_CORTEX_X925;
    } else if (strcmp(character, "risc_v_32") == 0) {
        architecture = ARCHITECTURE_RISC_V_32;
    } else if (strcmp(character, "risc_v_64") == 0) {
        architecture = ARCHITECTURE_RISC_V_64;
    } else if (strcmp(character, "avr_8") == 0) {
        architecture = ARCHITECTURE_AVR_8;
    } else if (strcmp(character, "msp430_16") == 0) {
        architecture = ARCHITECTURE_MSP430_16;
    } else if (strcmp(character, "msp430_32") == 0) {
        architecture = ARCHITECTURE_MSP430_32;
    } else if (strcmp(character, "mips_8") == 0) {
        architecture = ARCHITECTURE_MIPS_8;
    } else if (strcmp(character, "mips_16") == 0) {
        architecture = ARCHITECTURE_MIPS_16;
    } else if (strcmp(character, "mips_32") == 0) {
        architecture = ARCHITECTURE_MIPS_32;
    } else if (strcmp(character, "mips_64") == 0) {
        architecture = ARCHITECTURE_MIPS_64;
    } else if (strcmp(character, "powerPC_32") == 0) {
        architecture = ARCHITECTURE_POWERPC_32;
    } else if (strcmp(character, "powerPC_64") == 0) {
        architecture = ARCHITECTURE_POWERPC_64;
    } else if (strcmp(character, "superh_16") == 0) {
        architecture = ARCHITECTURE_SUPERH_16;
    } else if (strcmp(character, "superh_32") == 0) {
        architecture = ARCHITECTURE_SUPERH_32;
    } else if (strcmp(character, "renexa_rx_32") == 0) {
        architecture = ARCHITECTURE_RENEXA_RX_32;
    } else if (strcmp(character, "xtensa") == 0) {
        architecture = ARCHITECTURE_XTENSA;
    } else if (strcmp(character, "xtensa_64") == 0) {
        architecture = ARCHITECTURE_XTENSA_64;
    } else if (strcmp(character, "8051_8") == 0) {
        architecture = ARCHITECTURE_8051_8;
    } else if (strcmp(character, "pic16_8") == 0) {
        architecture = ARCHITECTURE_PIC16_8;
    } else if (strcmp(character, "pic18_8") == 0) {
        architecture = ARCHITECTURE_PIC18_8;
    } else if (strcmp(character, "pic24_16") == 0) {
        architecture = ARCHITECTURE_PIC24_16;
    } else if (strcmp(character, "dspic_16") == 0) {
        architecture = ARCHITECTURE_DSPIC_16;
    } else if (strcmp(character, "pic32_32") == 0) {
        architecture = ARCHITECTURE_PIC32_32;
    } else if (strcmp(character, "pic32mx_32") == 0) {
        architecture = ARCHITECTURE_PIC32MX_32;
    } else if (strcmp(character, "pic32mz_32") == 0) {
        architecture = ARCHITECTURE_PIC32MZ_32;
    } else if (strcmp(character, "pic32mm_32") == 0) {
        architecture = ARCHITECTURE_PIC32MM_32;
    } else if (strcmp(character, "pic32mk_32") == 0) {
        architecture = ARCHITECTURE_PIC32MK_32;
    } else {
        // Default to CUSTOM if no specific string matches
        architecture = ARCHITECTURE_CUSTOM;
    }


    switch (architecture) {
        // --- X86 Architectures ---
        case ARCHITECTURE_X86_16:
            arch.System = SYSTEM_16BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = false;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_X86_32:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_X86_64:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;

        // --- ARM Architectures (General) ---
        case ARCHITECTURE_ARM_32:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_64:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_THUMB:
            arch.System = SYSTEM_32BIT; // Thumb is an instruction set for 32-bit ARM cores
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_THUMB_2:
            arch.System = SYSTEM_32BIT; // Thumb-2 is an instruction set for 32-bit ARM cores
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;

        // --- ARM Cortex-M Series (Microcontroller Profile - primarily 32-bit) ---
        case ARCHITECTURE_ARM_CORTEX_M:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_M0:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_M3:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_M4:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_M7:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_M33:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_M55:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;

        // --- ARM Cortex-R Series (Real-time Profile) ---
        case ARCHITECTURE_ARM_CORTEX_R:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_R4:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_R5:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_R7:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_R8:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_R52:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_R82:
            arch.System = SYSTEM_64BIT; // R82 is 32/64-bit capable, classify as 64-bit
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;

        // --- ARM Cortex-A Series (Application Profile) ---
        case ARCHITECTURE_ARM_CORTEX_A:
            arch.System = SYSTEM_64BIT; // General Cortex-A family, assuming highest capability
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;

        // Specific 32-bit Cortex-A Cores (ARMv7-A based)
        case ARCHITECTURE_ARM_CORTEX_A5:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_A7:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_A8:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_A9:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_A15:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_ARM_CORTEX_A17:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;

        // Specific 32/64-bit Capable Cortex-A Cores (ARMv8-A based)
        case ARCHITECTURE_ARM_CORTEX_A35:
            arch.System = SYSTEM_64BIT; // Capable of 64-bit
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A53:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A55:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A57:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A72:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A73:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A75:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A76:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A77:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A78:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A78C:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A78AE:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;

        // Specific 64-bit Only Cortex-A Cores (ARMv9-A based)
        case ARCHITECTURE_ARM_CORTEX_A510:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A710:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A715:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A320:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A520:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A720:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_A725:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;

        // --- ARM Cortex-X Series (Extreme Performance - 64-bit only) ---
        case ARCHITECTURE_ARM_CORTEX_X:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_X1:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_X2:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_X3:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_X4:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
        case ARCHITECTURE_ARM_CORTEX_X925:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;

        // --- RISC-V Architectures ---
        case ARCHITECTURE_RISC_V_32:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_RISC_V_64:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;

        // --- AVR Architecture ---
        case ARCHITECTURE_AVR_8:
            arch.System = SYSTEM_8BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = false; // Primary 8-bit, 16-bit operations are often specialized or not native
            arch.allowed_32bit = false;
            arch.allowed_64bit = false;
            break;

        // --- MSP430 Architectures ---
        case ARCHITECTURE_MSP430_16:
            arch.System = SYSTEM_16BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = false;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_MSP430_32:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;

        // --- MIPS Architectures ---
        case ARCHITECTURE_MIPS_8:
            arch.System = SYSTEM_8BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = false; // MIPS 8-bit cores are very constrained
            arch.allowed_32bit = false;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_MIPS_16:
            arch.System = SYSTEM_16BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = false;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_MIPS_32:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_MIPS_64:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;

        // --- PowerPC Architectures ---
        case ARCHITECTURE_POWERPC_32:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_POWERPC_64:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;

        // --- SuperH Architectures ---
        case ARCHITECTURE_SUPERH_16:
            arch.System = SYSTEM_16BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = false; // SuperH is mostly 32-bit but can have 16-bit instruction modes
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_SUPERH_32:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;

        // --- Renesas RX Architecture ---
        case ARCHITECTURE_RENEXA_RX_32:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;

        // --- Xtensa Architectures ---
        case ARCHITECTURE_XTENSA: // Default/common Xtensa is 32-bit
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_XTENSA_64:
            arch.System = SYSTEM_64BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;

        // --- 8051 Architecture ---
        case ARCHITECTURE_8051_8:
            arch.System = SYSTEM_8BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = false; // 8051 can address 16-bit memory, but operations are 8-bit based
            arch.allowed_32bit = false;
            arch.allowed_64bit = false;
            break;

        // --- PIC Architectures ---
        case ARCHITECTURE_PIC16_8:
            arch.System = SYSTEM_8BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = false;
            arch.allowed_32bit = false;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_PIC18_8:
            arch.System = SYSTEM_8BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = false;
            arch.allowed_32bit = false;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_PIC24_16:
            arch.System = SYSTEM_16BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = false;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_DSPIC_16:
            arch.System = SYSTEM_16BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = false;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_PIC32_32:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_PIC32MX_32:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_PIC32MZ_32:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_PIC32MM_32:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;
        case ARCHITECTURE_PIC32MK_32:
            arch.System = SYSTEM_32BIT;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = false;
            break;

        // --- Custom Architecture (from your example) ---
        default:
             ARCHITECTURE_CUSTOM:
            arch.System = SYSTEM_CUSTOM;
            arch.allowed_8bit = true;
            arch.allowed_16bit = true;
            arch.allowed_32bit = true;
            arch.allowed_64bit = true;
            break;
    }

    return arch;
}