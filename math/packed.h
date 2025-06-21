#include "type.h"

static inline int bit_length(uint32_t value) {
    int bits = 0;
    while (value) {
        bits++;
        value >>= 1;
    }
    return bits > 0 ? bits : 1;
}

Decimal_32 pack_decimal_32(uint32_t fraction, uint32_t integers, uint8_t sign, uint32_t padding) {
    Decimal_32 packed = {0};  // Ensure all fields are zero-initialized

    int len_fraction = bit_length(fraction);
    int len2 = bit_length(integers);
    int len1 = len_fraction + padding;

    if (len1 + len2 > 23) {
        SET_OVERFLOW();
        return packed;  // returning all zeros or leave to SET_OVERFLOW to handle
    }

    uint32_t combined = (fraction << len2) | integers;

    packed.number  = combined;
    packed.locator = len1;
    packed.sign    = sign & 1;

    return packed;
}

Rational_32 pack_rational_32(uint32_t numerator, uint32_t denominator, uint32_t sign){
    Rational_32 packed = {0};

    int len1 = bit_length(numerator);
    int len2 = bit_length(denominator);

    if (len1 > 15 || len2 > 16) {
        SET_OVERFLOW();
        return packed;  // returning all zeros or leave to SET_OVERFLOW to handle
    }

    uint32_t packed_num = (numerator  << len1);
    uint32_t packed_den = (denominator << len2);

    packed.numerator  = packed_num;
    packed.denominator = packed_den;
    packed.sign        = sign;

    return packed;
}

Irrational_32 pack_irrational_32(uint32_t fraction, uint32_t integers, uint8_t sign) {
    Irrational_32 packed = {0};  // Ensure all fields are zero-initialized

    int len1 = bit_length(fraction);
    int len2 = bit_length(integers);

    if (len1 + len2 > 23) {
        SET_OVERFLOW();
        return packed;  // returning all zeros or leave to SET_OVERFLOW to handle
    }

    uint32_t combined = (integers << len2) | fraction;

    packed.number  = combined;
    packed.locator = len1;
    packed.sign    = sign & 1;

    return packed;
}

Root_32 pack_root_32(uint32_t number, uint32_t radical_index, uint8_t sign){
    Root_32 packed = {0};

    int len1 = bit_length(number);
    int len2 = bit_length(radical_index);

    if (len1 > 15 || len2 > 16) {
        SET_OVERFLOW();
        return packed;  // returning all zeros or leave to SET_OVERFLOW to handle
    }

    uint32_t packed_num = (number << len1);
    uint32_t packed_rac = (radical_index << len2);

    packed.number        = packed_num;
    packed.radicand = packed_rac;
    packed.sign          = sign;

    return packed;
}