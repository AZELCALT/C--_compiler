// #ifdef fix_negative_zero
//     if (mant == 0) sign = 0;
// #endif

#include <stdint.h>
#include <limits.h>

typedef union __attribute__((packed))
{
    struct {
        uint32_t number:  23;
        uint32_t  locator: 8;
        uint32_t  sign:    1;   
    };
    uint32_t width;
}Decimal_32;

_Static_assert(sizeof(Decimal_32) == 4, "Decimal_32 must be 32 bits");


typedef union __attribute__((packed))
{
    struct {
        uint64_t number:  55;
        uint64_t  locator: 8;
        uint64_t  sign:    1;   
    };
    uint64_t width;
}Decimal_64;


_Static_assert(sizeof(Decimal_64) == 8, "Decimal_64 must be 64 bits");


typedef union __attribute__((packed))
{
    struct {
        uint32_t numerator:     15;
        uint32_t denominator:    16;
        uint32_t  sign:           1;   
    };
    uint32_t width;
}Rational_32;

_Static_assert(sizeof(Rational_32) == 4, "Rational_32 must be 32 bits");

typedef union __attribute__((packed))
{
    struct {
        uint64_t numerator:     31;  
        uint64_t denominator:    32;
        uint64_t sign:           1;   
    };
    uint64_t width;
}Rational_64;

_Static_assert(sizeof(Rational_64) == 8, "Rational_64 must be 64 bits");

typedef union __attribute__((packed))
{
    struct {
        uint32_t  number: 23;
        uint32_t  locator: 8;
        uint32_t  sign:    1;   
    };
    uint32_t width;
}Irrational_32;

_Static_assert(sizeof(Irrational_32) == 4, "Irrational_32 must be 32 bits");


typedef union __attribute__((packed))
{
    struct {
        uint64_t  number: 55;
        uint64_t  locator: 8;
        uint64_t  sign:    1;   
    };
    uint64_t width;
}Irrational_64;


_Static_assert(sizeof(Irrational_64) == 8, "Irrational_64 must be 64 bits");

typedef union __attribute__((packed))
{
    struct {
        uint32_t  number_under_root:       11;
        uint32_t  number_outside_root:     12;
        uint32_t  radicand:                 8;
        uint32_t  sign:                     1;   
    };
    uint32_t width;
}Root_32;

_Static_assert(sizeof(Root_32) == 4, "Root_32 must be 32 bits");


typedef union __attribute__((packed))
{
    struct {
        uint64_t  number_under_root:       27;
        uint64_t  number_outside_root:     28;
        uint64_t  radicand:                 8;
        uint64_t  sign:                     1;   
    };
    uint64_t width;
}Root_64;


_Static_assert(sizeof(Root_64) == 8, "Root_64 must be 64 bits");

typedef union __attribute__((packed))
{
    struct {
        uint32_t  raw:            31;  
        uint32_t  sign:            1;    
    };
    uint32_t width;
}Fixed_32_value;

_Static_assert(sizeof(Fixed_32_value) == 4, "Fixed_32 must be 32 bits");

typedef union __attribute__((packed))
{
    struct {
        uint64_t  raw:            63;  
        uint64_t  sign:            1;   
    };
    uint64_t width;
}Fixed_64_value;

_Static_assert(sizeof(Fixed_64_value) == 8, "Fixed_64 must be 64 bits");

typedef union __attribute__((packed))
{
    struct {
        uint32_t  mantissa:       22;
        uint32_t  int_bit:         1;---
        uint32_t  exponent:        7;
        uint32_t  exponent_sign:   1;
        uint32_t  mantissa_sign:   1;    
    };
    uint32_t width;
}Float_32;

_Static_assert(sizeof(Float_32) == 4, "Float_32 must be 32 bits");

typedef union __attribute__((packed))
{
    struct {
        uint64_t  mantissa:       54;
        uint64_t  int_bit:         1;
        uint64_t  exponent:        7;
        uint64_t  exponent_sign:   1;
        uint64_t  mantissa_sign:            1;    
    };
    uint64_t width;
}Float_64;

_Static_assert(sizeof(Float_64) == 8, "Float_64 must be 64 bits");

typedef union __attribute__((packed))
{
    struct {
        uint32_t  symbol  :        16;
        uint32_t  scenario:        16;
    };
    uint32_t width;
}Symbol_32;

_Static_assert(sizeof(Symbol_32) == 4, "Symbol_32 must be 32 bits");


typedef union __attribute__((packed))
{
    struct {
        uint64_t  symbol:          32;
        uint64_t  scenario:        32;
    };
    uint64_t width;
}Symbol_64;

_Static_assert(sizeof(Symbol_64) == 8, "Symbol_64 must be 64 bits");

typedef struct {
    int integer_range;
    int fraction_range;
    int sign;
    Fixed_32_value value;
}Fixed_32;

typedef struct {
    int integer_range;
    int fraction_range;
    int sign;
    Fixed_64_value value;
}Fixed_64;


// === Constants and Masks ===
#define SIGN_MASK   0x80000000
#define SEP_MASK    0x7F800000
#define MANT_MASK   0x007FFFFF

#define MAX_MANT    ((1 << 22) - 1)
#define MIN_MANT    (-(1 << 22))

// === Overflow Flag ===
static int decimal_overflow = 0;
#define SET_OVERFLOW() (decimal_overflow = 1)
#define CLEAR_OVERFLOW() (decimal_overflow = 0)
#define GET_OVERFLOW() (decimal_overflow)



// === Extractors ===
#define GET_SIGN(x)   (((x.width) >> 31) & 0x1) //0101  || (0001 << 3)(1000) -> 1010 ----x || (0x1 << 31) 
// #define GET_LOC(x)    (((x.width) >> 23) & 0xFF)
// #define GET_INT(x)    (x.width >> (1U - (23 - x.locator)))
// #define GET_FRAC(x)   (x.width >> (23 - x.locator)) & ((1U << x.locator) - 1)

// === Pack format ===
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

// === Float to decimal ===
// static inline Decimal_32 decimal_from_float(float val) {
//     int sign = (val < 0);
//     float abs_val = fabsf(val);

//     int sep;
//     int32_t mant = 0;

//     for (sep = 0; sep < 256; sep++) {
//         float scaled = abs_val * (1 << sep);
//         if (scaled > INT32_MAX) continue;
//         mant = (int32_t) roundf(scaled);
//         if (mant >= MIN_MANT && mant <= MAX_MANT) break;
//     }

//     if (mant > MAX_MANT) {
//         mant = MAX_MANT;
//         SET_OVERFLOW();
//     }

//     return encode_decimal(sign, sep, mant);
// }

// === decimal to Float ===
// static inline float decimal_to_float(Decimal_32 fx) {
//     int sign = GET_SIGN(fx.width);
//     int sep = GET_SEP(fx.width);
//     int32_t mant = GET_MANT(fx.width);
//     float value = (float)mant / (1 << sep);
//     return sign ? -value : value;
// }

// static inline Normalize(){

// }

// === ADDITION ===
static inline Decimal_32 decimal_add_and_sub(Decimal_32 a, Decimal_32 b, int base, bool add_or_sub) {
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
    int base_depth_b;


    if (depth_a == 0) {
        base_depth_a = 1;
    }
    else{
       base_depth_a = depth_a + 1;
    }
    if (depth_b == 0) {
        base_depth_b = 1;
    }
    else{
       base_depth_b = depth_b + 1;
    }

    int base_max;

    if (base_depth_a > base_depth_b){
        base_max = base_depth_a;
    }
    else{
        base_max = base_depth_b;
    }

    int normalize_limit = base * base_max;

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

static inline Decimal_32 decimal_add_and_sub_default(Decimal_32 a, Decimal_32 b, bool add_or_sub) {
    return decimal_add_and_sub(a,b,10,add_or_sub)
}

// === MULTIPLICATION ===
static inline Decimal_32 decimal_mul_and_div(Decimal_32 a, Decimal_32 b, int base, bool mul_or_div) {
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
    int base_depth_b;


    if (depth_a == 0) {
        base_depth_a = 1;
    }
    else{
       base_depth_a = depth_a + 1;
    }
    if (depth_b == 0) {
        base_depth_b = 1;
    }
    else{
       base_depth_b = depth_b + 1;
    }

    int base_max;

    if (base_depth_a > base_depth_b){
        base_max = base_depth_a;
    }
    else{
        base_max = base_depth_b;
    }

    int normalize_limit = base * base_max;

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

static inline Decimal_32 decimal_mul_and_div_default(Decimal_32 a, Decimal_32 b, bool mul_or_div) {
    return decimal_mul_and_div(a,b,10,mul_or_div)
}

// === ADDITION ===
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

// === Rational ===
static inline Rational_32 rational_add_and_sub(Rational_32 a, Rational_32 b, bool add_or_sub) {
    Rational_32 c = {0}; 

    int sign_a = GET_SIGN(a);
    int sign_b = GET_SIGN(b);

    int numerator_a = a.numerator;
    if (sign_a == 1) {
        numerator_a = -numerator_a;
    }
    int denominator_a = a.denominator;
    int numerator_b = b.numerator;
    if (sign_b == 1) {
        numerator_b = -numerator_b;
    }
    int denominator_b = b.denominator;
    int normalize_denominator;
    int result_numerator;

    if (denominator_a != denominator_b ) {
        normalize_denominator = denominator_a * denominator_b;
        numerator_a = numerator_a * denominator_b;
        numerator_b = numerator_b * denominator_a;
    }
    if (add_or_sub == false) {
        result_numerator = numerator_a + numerator_b;
    } else {
        result_numerator = numerator_a - numerator_b;
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
    int optimized_numerator_able = result_numerator% result_denominator;
    if (optimized_numerator_able == 0) {
        c.numerator = result_numerator / result_denominator;
        c.denominator = 1;
    } else {
        c.numerator = result_numerator;
        c.denominator = result_denominator;
    }
    c.sign = sign_result;
    return c;
}

static inline Rational_32 rational_mul_and_div(Rational_32 a, Rational_32 b, bool mul_or_div) {
    Rational_32 c = {0}; 

    int sign_a = GET_SIGN(a);
    int sign_b = GET_SIGN(b);

    int numerator_a = a.numerator;
    if (sign_a == 1) {
        numerator_a = -numerator_a;
    }
    int denominator_a = a.denominator;
    int numerator_b = b.numerator;
    if (sign_b == 1) {
        numerator_b = -numerator_b;
    }
    int denominator_b = b.denominator;
    int result_denominator;
    int result_numerator;

    if (mul_or_div == false) {
        result_numerator = numerator_a * numerator_b;
        result_denominator = denominator_a * denominator_b;
    } else {
        result_numerator = numerator_a *denominator_b;
        result_denominator = denominator_a * numerator_b;
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
    int optimized_numerator_able = result_numerator% result_denominator;
    if (optimized_numerator_able == 0) {
        c.numerator = result_numerator / result_denominator;
        c.denominator = 1;
    } else {
        c.numerator = result_numerator;
        c.denominator = result_denominator;
    }
    c.sign = sign_result;
    return c;
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

// === Root ===
typedef struct {
    uint64_t first_int;      // Integer part of sqrt(y)
    uint64_t remainder; // What's left: y - z^n
    uint64_t scale; // Scale factor for normalization
} SqrtResult;

typedef struct {
    uint32_t normalize;
    uint32_t scale;
} normalize_result;

static inline normalize_result normalization_for_root(uint32_t Number, uint32_t base) {
    // Normalize the number for root calculation
    normalize_result result = {.normalize = Number, .scale = 0};
    while ((result.normalize <= (UINT32_MAX  / base ))) {
        result.normalize *= base;
        result.scale++;
    }
    return result;
}

// Generalized root evaluator
SqrtResult int_root(uint32_t Number, uint32_t radix) {
    if (Number == 0) return (SqrtResult){.first_int = 0, .remainder = 0, .scale=0}; // Special case for zero
    if (radix == 0 || radix == 1) return (SqrtResult){.first_int = Number, .remainder = 0, .scale=0}; // Special case for radix 0 or 1
    if (Number == 1) return (SqrtResult){.first_int = 1, .remainder = 0, .scale=0}; // Special case for one
    normalize_result normalization = normalization_for_root(Number);
    uint64_t Normalize = normalization.normalize;
    uint64_t scale = normalization.scale;
    uint32_t low = 0, high = Normalize, mid;
    SqrtResult finalize_result = {0, 0};
    while (low <= high) {
        mid = (low + high) / 2;

        // Compute mid^n safely
        uint64_t result = 1;
        for (uint32_t i = 0; i < radix; ++i) {
            result *= mid;
            if (result > Normalize) break;
        }

        if (result == Normalize) return (SqrtResult){.first_int = mid, .remainder = 0}; // Found exact root
        if (result < Normalize) low = mid + 1;
        else high = mid - 1;
    }
    int index;
    uint64_t remainder = Normalize - high^radix; // What's left after subtracting the largest perfect power of radix
    finalize_result.first_int = high;
    finalize_result.remainder = remainder;
    finalize_result.scale = scale; // Store the scale factor for normalization
    return finalize_result; // max z where z^n ≤ y
}

static inline Root_32 root_add_and_sub(Root_32 a, Root_32 b, bool add_or_sub) {
    Root_32 c = {0};    
    int sign_a = GET_SIGN(a);
    int sign_b = GET_SIGN(b);
    int Root_number_a = a.number_under_root;
    int Root_number_b = b.number_under_root;
    int outside_root_a = a.number_outside_root;
    int outside_root_b = b.number_outside_root;
    int radicand_a = a.radicand;
    int radicand_b = b.radicand;
    int sign_result;
    if (sign_a == 1) {
        outside_root_a = -outside_root_a;
    }
    if (sign_b == 1) {
       outside_root_b = -outside_root_b;
    }

    if (Root_number_a != Root_number_b || radicand_a != radicand_b) {
        SET_OVERFLOW();
        return c;  // returning all zeros or leave to SET_OVERFLOW to handle
    }

    if (add_or_sub == false) {
        Root_number_a += Root_number_b;
        outside_root_a += outside_root_b;
        if (Root_number_a > 32767 || outside_root_a > 65536) {
            SET_OVERFLOW();
            return c;  // returning all zeros or leave to SET_OVERFLOW to handle
        }
        sign_result = (Root_number_a < 0 || outside_root_a < 0) ? 1 : 0;
    } else {
        Root_number_a -= Root_number_b;
        outside_root_a -= outside_root_b;
        if (Root_number_a < -32768 || outside_root_a < -65536) {
            SET_OVERFLOW();
            return c;  // returning all zeros or leave to SET_OVERFLOW to handle
        }
        sign_result = (Root_number_a < 0 || outside_root_a < 0) ? 1 : 0;
    }
    int Root_number_result = Root_number_a + Root_number_b;
    int outside_root_result = outside_root_a + outside_root_b;
    if (sign_a == 1) {
        outside_root_result = -outside_root_result;
    }
    if (sign_b == 1) {
        outside_root_result = -outside_root_result;
    }

    if (outside_root_result < 0) {
        outside_root_result = -outside_root_result;
        sign_result = 1;
    } else {
        sign_result = 0;
    }

    if (outside_root_result > 65536 || Root_number_result > 32767) {
        SET_OVERFLOW();
        return c;  // returning all zeros or leave to SET_OVERFLOW to handle
    }
    c.number_under_root = Root_number_result;
    c.number_outside_root = outside_root_result;
    c.radicand = radicand_a;  // assuming radicand is the same for both roots
    c.sign = sign_result;
    return c;
}

static inline Root_32 root_mul_and_div(Root_32 a, Root_32 b, bool mul_or_div) {
    Root_32 c = {0};    
    int sign_a = GET_SIGN(a);
    int sign_b = GET_SIGN(b);
    int Root_number_a = a.number_under_root;
    int Root_number_b = b.number_under_root;
    int outside_root_a = a.number_outside_root;
    int outside_root_b = b.number_outside_root;
    int radicand_a = a.radicand;
    int radicand_b = b.radicand;
    int sign_result;

    if (sign_a == 1) {
        outside_root_a = -outside_root_a;
    }
    if (sign_b == 1) {
       outside_root_b = -outside_root_b;
    }

    if (radicand_a != radicand_b) {
        SET_OVERFLOW();
        return c;  // returning all zeros or leave to SET_OVERFLOW to handle
    }

    if (mul_or_div == false) {
        Root_number_a *= Root_number_b;
        outside_root_a *= outside_root_b;
        if (Root_number_a > 32767 || outside_root_a > 65536) {
            SET_OVERFLOW();
            return c;  // returning all zeros or leave to SET_OVERFLOW to handle
        }
        sign_result = (Root_number_a < 0 || outside_root_a < 0) ? 1 : 0;
    } else {
        if (Root_number_b == 0 || outside_root_b == 0) {
            SET_OVERFLOW();
            return c;  // division by zero
        }
        Root_number_a /= Root_number_b;
        outside_root_a /= outside_root_b;
        if (Root_number_a < -32768 || outside_root_a < -65536) {
            SET_OVERFLOW();
            return c;  // returning all zeros or leave to SET_OVERFLOW to handle
        }
        sign_result = (Root_number_a < 0 || outside_root_a < 0) ? 1 : 0;
    }
    
    int Root_number_result = Root_number_a + Root_number_b;
    int outside_root_result = outside_root_a + outside_root_b;

    if (sign_a == 1) {
        outside_root_result = -outside_root_result;
    }
    if (sign_b == 1) {
        outside_root_result = -outside_root_result;
    }
    if (outside_root_result < 0) {
        outside_root_result = -outside_root_result;
        sign_result = 1;
    } else {
        sign_result = 0;
    }
    if (outside_root_result > 65536 || Root_number_result > 32767) {
        SET_OVERFLOW();
        return c;  // returning all zeros or leave to SET_OVERFLOW to handle
    }
    c.number_under_root = Root_number_result;
    c.number_outside_root = outside_root_result;
    c.radicand = radicand_a;  // assuming radicand is the same for both roots
    c.sign = sign_result;   
    return c;
}

static inline Irrational_32 root_cast_to_decimal(Root_32 a,int base) {
    Irrational_32 c = {0};    

    Root_32 d = a;  // Copy the root to work with
    int sign_a = GET_SIGN(a);
    int Number_outside_root_a = a.number_outside_root;
    
    
    // if (sign_a == 1) {
    //     d.number_outside_root = -d.number_outside_root;
    // }--
    SqrtResult sqrt_result = int_root(d.number_outside_root, d.radicand);
    uint32_t first_int = sqrt_result.first_int;
    uint32_t remainder = sqrt_result.remainder;
    uint32_t scale = sqrt_result.scale;
    uint32_t Normalize_base = base * scale;
    uint32_t Main_number = first_int * Number_outside_root_a;
    uint32_t Normalize_int = Main_number / Normalize_base;
    uint32_t Normalize_fraction = Main_number % Normalize_base;

    

    if (outside_root_a > 65536 || Root_number_a > 32767) {
        SET_OVERFLOW();
        return c;  // returning all zeros or leave to SET_OVERFLOW to handle
    }
    


    return pack_irrational_32(Normalize_fraction, Normalize_int, sign_a, base);
}
