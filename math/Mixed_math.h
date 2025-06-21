#include "packed.h"

static inline Irrational_32 irrational_decimal_add_and_sub(Irrational_32 a, Decimal_32 b, int base, bool add_or_sub) {
    Decimal_32 c = {0}; 

    int sign_a = GET_SIGN(a);
    int sign_b = GET_SIGN(b);

    if (a.locator == 0){
        int fraction_a = 0;
    }
    if (b.locator == 0){
        int fraction_b = 0;
    }

    uint32_t len_a = 23 - a.locator;
    uint32_t len_b = 23 - b.locator;
    if (len_a <= 0) int integer_a = 0;
    if (len_b <= 0) int integer_b = 0; 

    int locator_a = a.locator;
    int locator_b = b.locator;
    int fraction_a = (a.width >> (1U - (23 - a.locator)));
    int integer_a = (a.width >> (23 - a.locator)) & ((1U << a.locator) - 1);
    int fraction_b = (b.width >> (23 - b.locator)) & ((1U << b.locator) - 1);
    int integer_b = (a.width >> (1U - (23 - a.locator)));

    int len_fragtion_a =  bit_length(fraction_a);
    int len_fragtion_b =  bit_length(fraction_b);

    int depth_a =locator_a - len_fragtion_a;
    int depth_b =locator_b - len_fragtion_b;
    int base_depth_a;
    int base_depth_b;
    int base_calculate = fraction_a/base;
    
    int normalize_limit = base * base_calculate;

    int integers_a = integer_a * normalize_limit;
    int integers_b = integer_b * normalize_limit;

    int number_b = integers_b + fraction_b;
    int number_a = integers_a + fraction_a;
    int sign_result;
    
    if (sign_a == 1){
        number_a = -number_a;
    }
    
    if (sign_b == 1){
        number_b = -number_b;
    }

    int result;
    if (add_or_sub == false){
        result   = number_a + number_b;
        if (result > 0){
            sign_result = 0;
        }
        else{
            sign_result = 1;
        }
    }
    else{
        result   = number_a - number_b;
        if (result > 0){
            sign_result = 0;
        }
        else{
            sign_result = 1;
        }
    }
    result = -result;
    

    int integer_result  = result / normalize_limit;
    int fraction_result = result % normalize_limit;

    int fragtion_less_than_limit;
    int padding;
    if (fraction_result > 0){
        fragtion_less_than_limit = normalize_limit/fraction_result;
        padding = fragtion_less_than_limit/base;
    }

    return pack_decimal_32(fraction_result, integer_result, sign_result, padding)
}

static inline Decimal_32 irrational_decimal_add_and_sub_default(Decimal_32 a, Decimal_32 b, bool add_or_sub) {
    return decimal_add_and_sub(a,b,10,add_or_sub)
}

// === MULTIPLICATION ===
static inline Decimal_32 irrational_decimal_mul_and_div(Decimal_32 a, Decimal_32 b, int base, bool mul_or_div) {
    Decimal_32 c = {0}; 

    int sign_a = GET_SIGN(a);
    int sign_b = GET_SIGN(b);

    if (a.locator == 0){
        int fraction_a = 0;
    }
    if (b.locator == 0){
        int fraction_b = 0;
    }

    uint32_t len_a = 23 - a.locator;
    uint32_t len_b = 23 - b.locator;
    if (len_a <= 0) int integer_a = 0;
    if (len_b <= 0) int integer_b = 0; 

    int locator_a = a.locator;
    int locator_b = b.locator;
    int fraction_a = (a.width >> (23 - a.locator)) & ((1U << a.locator) - 1);
    int integer_a = (a.width >> (1U - (23 - a.locator)));
    int fraction_b = (b.width >> (23 - b.locator)) & ((1U << b.locator) - 1);
    int integer_b = (a.width >> (1U - (23 - a.locator)));

    int len_fragtion_a =  bit_length(fraction_a);
    int len_fragtion_b =  bit_length(fraction_b);

    int depth_a =locator_a - len_fragtion_a;
    int depth_b =locator_b - len_fragtion_b;
    int base_depth_a;
    int base_calculate = fraction_a/base;
    
    int normalize_limit = base * base_calculate;

    int integers_a = integer_a * normalize_limit;
    int integers_b = integer_b * normalize_limit;

    int number_b = integers_b + fraction_b;
    int number_a = integers_a + fraction_a;
    int sign_result;

    if (sign_a == 1){
        number_a = -number_a;
    }
    
    if (sign_b == 1){
        number_b = -number_b;
    }

    int result;
    if (mul_or_div == false){
        result   = number_a * number_b;
        if (result > 0){
            sign_result = 0;
        }
        else{
            sign_result = 1;
        }
    }
    else{
        result   = number_a / number_b;
        if (result > 0){
            sign_result = 0;
        }
        else{
            sign_result = 1;
        }
    }
    result = -result;
    

    int integer_result  = result / normalize_limit;
    int fraction_result = result % normalize_limit;

    int fragtion_less_than_limit;
    int padding;
    if (fraction_result > 0){
        fragtion_less_than_limit = normalize_limit/fraction_result;
        padding = fragtion_less_than_limit/base;
    }

    return pack_decimal_32(fraction_result, integer_result, sign_result, padding)
}

static inline Decimal_32 irrational_decimal_mul_and_div_default(Decimal_32 a, Decimal_32 b, bool mul_or_div) {
    return decimal_mul_and_div(a,b,10,mul_or_div)
}

static inline Decimal_32 rational_decimal_add_and_sub(Rational_32 a, Decimal_32 b, bool add_or_sub, int base) {
    Decimal_32 c = {0}; 

    int sign_a = GET_SIGN(a);
    int sign_b = GET_SIGN(b);

    int numerator_a = a.numerator;
    if (sign_a == 1) {
        numerator_a = -numerator_a;
    }
    int denominator_a = a.denominator;
    int fraction_b = (b.width >> (23 - b.locator)) & ((1U << b.locator) - 1);
    int integer_b = (b.width >> (1U - (23 - b.locator)));


    int locator_b = b.locator;
    int len_b = bit_length(fraction_b);
    int base_depth_b= locator_b - len_b;
    int base_normalize_limit = base * (base_depth_b + 1);
    int number_b = integer_b * base_normalize_limit + fraction_b;
    int normalize_denominator;
    int result_numerator;

    if (denominator_a != 1 ) {
        normalize_denominator = denominator_a;
    } else {
        normalize_denominator = 1;
    }
    if (add_or_sub == false) {
        result_numerator = numerator_a + number_b;
    } else {
        result_numerator = numerator_a - number_b;
    }
    
    int result_denominator = normalize_denominator;
    int sign_result;
    if (result_numerator > 0) {
        sign_result = 0;
    } else {
        sign_result = 1;
        result_numerator = -result_numerator;   
    }

    if (result_numerator > 32767 || result_denominator > 65536) {
        SET_OVERFLOW();
        return c;  // returning all zeros or leave to SET_OVERFLOW to handle
    }

    int normalized_numerator_frac = result_numerator % result_denominator;
    int normalized_numerator_int = result_numerator / result_denominator;
    int normalized_int = normalized_numerator_int/ base_normalize_limit;
    int leftover_frac = normalized_numerator_int % base_normalize_limit;
    int normalized_frac = normalized_numerator_frac + leftover_frac;
    int fragtion_less_than_limit;

    int padding;
    if (normalized_frac > 0){
        fragtion_less_than_limit = base_normalize_limit/normalized_frac;
        padding = fragtion_less_than_limit/base;
    }
    
    return pack_decimal_32(normalized_frac, normalized_int, sign_result, padding);
}

static inline Decimal_32 rational_decimal_add_and_sub_default(Rational_32 a, Decimal_32 b, bool add_or_sub) {
    return rational_decimal_add_and_sub(a, b, add_or_sub, 10);
}

static inline Decimal_32 rational_decimal_mul_and_div(Rational_32 a, Decimal_32 b, bool mul_or_div, int base) {
    Decimal_32 c = {0}; 

    int sign_a = GET_SIGN(a);
    int sign_b = GET_SIGN(b);

    int numerator_a = a.numerator;
    if (sign_a == 1) {
        numerator_a = -numerator_a;
    }
    int denominator_a = a.denominator;
    int fraction_b = (b.width >> (23 - b.locator)) & ((1U << b.locator) - 1);
    int integer_b = (b.width >> (1U - (23 - b.locator)));
    int locator_b = b.locator;
    int len_b = bit_length(fraction_b);
    int base_depth_b= locator_b - len_b;
    int base_normalize_limit = base * (base_depth_b + 1);
    int number_b = integer_b * base_normalize_limit + fraction_b;
    int result_denominator;
    int result_numerator;   
    if (mul_or_div == false) {
        result_numerator = numerator_a * number_b;
        result_denominator = denominator_a * 1; // denominator of decimal is always 1
    } else {
        result_numerator = numerator_a * 1; // numerator of decimal is always 1
        result_denominator = denominator_a * number_b;
    }
    int sign_result;
    if (result_numerator > 0) {
        sign_result = 0;
    } else {
        sign_result = 1;
        result_numerator = -result_numerator;   
    }
    if (result_numerator > 32767 || result_denominator > 65536) {
        SET_OVERFLOW();
        return c;  // returning all zeros or leave to SET_OVERFLOW to handle
    }   
    int normalized_numerator_frac = result_numerator % result_denominator;
    int normalized_numerator_int = result_numerator / result_denominator;
    int normalized_int = normalized_numerator_int/ base_normalize_limit;
    int leftover_frac = normalized_numerator_int % base_normalize_limit;
    int normalized_frac = normalized_numerator_frac + leftover_frac;
    int fragtion_less_than_limit;   
    int padding;
    if (normalized_frac > 0){
        fragtion_less_than_limit = base_normalize_limit/normalized_frac;
        padding = fragtion_less_than_limit/base;
    }
    return pack_decimal_32(normalized_frac, normalized_int, sign_result, padding);
}

static inline Decimal_32 rational_decimal_mul_and_div_default(Rational_32 a, Decimal_32 b, bool mul_or_div) {
    return rational_decimal_mul_and_div(a, b, mul_or_div, 10);
}

static inline Decimal_32 decimal_rational_mul_and_div(Rational_32 b, Decimal_32 a, bool mul_or_div, int base) {
    Decimal_32 c = {0}; 

    int sign_a = GET_SIGN(a);
    int sign_b = GET_SIGN(b);

    int numerator_a = a.numerator;
    if (sign_a == 1) {
        numerator_a = -numerator_a;
    }
    int denominator_a = a.denominator;
    int fraction_a = (a.width >> (23 - a.locator)) & ((1U << a.locator) - 1);
    int integer_a = (a.width >> (1U - (23 - a.locator)));
    int locator_a = a.locator;
    int len_a = bit_length(fraction_a);
    int base_depth_a = locator_a - len_a;
    int base_normalize_limit = base * (base_depth_a + 1);
    int number_b = integer_a * base_normalize_limit + fraction_a;
    int result_denominator;
    int result_numerator;   
    if (mul_or_div == false) {
        result_numerator = numerator_a * number_b;
        result_denominator = denominator_a * 1; // denominator of decimal is always 1
    } else {
        result_numerator = denominator_a * number_b; // decimal first so it flips rational
        result_denominator =  numerator_a * 1;
    }
    int sign_result;
    if (result_numerator > 0) {
        sign_result = 0;
    } else {
        sign_result = 1;
        result_numerator = -result_numerator;   
    }
    if (result_numerator > 32767 || result_denominator > 65536) {
        SET_OVERFLOW();
        return c;  // returning all zeros or leave to SET_OVERFLOW to handle
    }   
    int normalized_numerator_frac = result_numerator % result_denominator;
    int normalized_numerator_int = result_numerator / result_denominator;
    int normalized_int = normalized_numerator_int/ base_normalize_limit;
    int leftover_frac = normalized_numerator_int % base_normalize_limit;
    int normalized_frac = normalized_numerator_frac + leftover_frac;
    int fragtion_less_than_limit;   
    int padding;
    if (normalized_frac > 0){
        fragtion_less_than_limit = base_normalize_limit/normalized_frac;
        padding = fragtion_less_than_limit/base;
    }
    return pack_decimal_32(normalized_frac, normalized_int, sign_result, padding);
}

static inline Decimal_32 decimal_rational_mul_and_div_default(Rational_32 a, Decimal_32 b, bool mul_or_div) {
    return rational_decimal_mul_and_div(a, b, mul_or_div, 10);
}

