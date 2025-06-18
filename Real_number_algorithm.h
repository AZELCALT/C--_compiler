#ifdef fix_negative_zero
    if (mant == 0) sign = 0;
#endif

#include <stdint.h>

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
        uint32_t  number:       23;
        uint32_t  radicand:      8;
        uint32_t  sign:          1;   
    };
    uint32_t width;
}Root_32;

_Static_assert(sizeof(Root_32) == 4, "Root_32 must be 32 bits");


typedef union __attribute__((packed))
{
    struct {
        uint64_t  number:       55;
        uint64_t  radicand: 8;
        uint64_t  sign:          1;   
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



