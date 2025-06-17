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
        uint32_t numberator:     15;
        uint32_t denominator:    16;
        uint32_t  sign:           1;   
    };
    uint32_t width;
}Rational_32;

_Static_assert(sizeof(Rational_32) == 4, "Rational_32 must be 32 bits");

typedef union __attribute__((packed))
{
    struct {
        uint64_t numberator:     31;  
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
        uint32_t  radical_index: 8;
        uint32_t  sign:          1;   
    };
    uint32_t width;
}Root_32;

_Static_assert(sizeof(Root_32) == 4, "Root_32 must be 32 bits");


typedef union __attribute__((packed))
{
    struct {
        uint64_t  number:       55;
        uint64_t  radical_index: 8;
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
}Fixed_32;

_Static_assert(sizeof(Fixed_32) == 4, "Fixed_32 must be 32 bits");

typedef union __attribute__((packed))
{
    struct {
        uint64_t  raw:            63;  
        uint64_t  sign:            1;   
    };
    uint64_t width;
}Fixed_64;

_Static_assert(sizeof(Fixed_64) == 8, "Fixed_64 must be 64 bits");



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
// #define GET_SIGN(x)   (((x) >> 31) & 0x1) //0101  || (0001 << 3)(1000) -> 1010 ----x || (0x1 << 31) 
// #define GET_LOC(x)    (((x) >> 23) & 0xFF)
// #define GET_INT(x)    (x >> (1U - (23 - x.locator)))
// #define GET_FRAC(X)   (x >> (23 - x.locator)) & ((1U << x.locator) - 1)

// === Pack format ===
static inline int bit_length(uint32_t value) {
    int bits = 0;
    while (value) {
        bits++;
        value >>= 1;
    }
    return bits > 0 ? bits : 1;
}

Decimal_32 pack_decimal_32(uint32_t fraction, uint32_t integers, uint8_t sign) {
    Decimal_32 packed = {0};  // Ensure all fields are zero-initialized

    int len1 = bit_length(fraction);
    int len2 = bit_length(integers);

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

Rational_32 pack_rational_32(uint32_t numberator, uint32_t denominator, uint32_t sign){
    Rational_32 packed = {0};

    int len1 = bit_lenght(numberator);
    int len2 = bit_length(denominator);

    if (len1 > 15 || len2 > 16) {
        SET_OVERFLOW();
        return packed;  // returning all zeros or leave to SET_OVERFLOW to handle
    }

    uint32_t packed_num = (numberator  << len1);
    uint32_t packed_den = (denominator << len2);

    packed.numberator  = packed_num;
    packed.denominator = packed_den;
    packed.sign        = sign;

    return packedl;
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

    int len1 = bit_lenght(number);
    int len2 = bit_length(radical_index);

    if (len1 > 15 || len2 > 16) {
        SET_OVERFLOW();
        return packed;  // returning all zeros or leave to SET_OVERFLOW to handle
    }

    uint32_t packed_num = (numberator  << len1);
    uint32_t packed_rac = (denominator << len2);

    packed.number        = packed_num;
    packed.radical_index = packed_rac;
    packed.sign          = sign;

    return packedl;
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

static inline Normalize(){

}

// === ADDITION ===
static inline Decimal_32 decimal_add(Decimal_32 a, Decimal_32 b) {
    Decimal_32 c = {0};

    if (a.locator == 0){
        int fraction_a = 0;
    }
    if (b.locator == 0){
        int fraction_b = 0;
    }

    uint32_t len_a = 23 - a.locator;
    uint32_t len_b = 23 - a.locator;
    if (len_a <= 0) int integer_a = 0;
    if (len_b <= 0) int integer_b = 0; 

    int fraction_a = (a >> (23 - a.locator)) & ((1U << a.locator) - 1);
    int integer_a = (a >> (1U - (23 - a.locator)));
    int fraction_b = (b >> (23 - b.locator)) & ((1U << b.locator) - 1);
    int integer_b = (a >> (1U - (23 - a.locator)));



    // if (sa) ma = -ma;
    // if (sb) mb = -mb;

    // // Align to same fractional bit depth
    // if (ea > eb) {
    //     mb <<= (ea - eb);
    // } else if (eb > ea) {
    //     ma <<= (eb - ea);
    // }

    // int32_t result_m = ma + mb;
    // int result_s = (result_m < 0);
    // if (result_s) result_m = -result_m;

    // int result_e = ea > eb ? ea : eb;

    // // Normalize result if needed
    // while ((result_m > MAX_MANT) && result_e < 255) {
    //     result_m >>= 1;
    //     result_e++;
    // }

    // if (result_m > MAX_MANT) {
    //     result_m = MAX_MANT;
    //     SET_OVERFLOW();
    // }

    // return pack_decimal_32(result_s, result_e, result_m);
}

// === SUBTRACTION ===
static inline Decimal_32 decimal_sub(Decimal_32 a, Decimal_32 b) {
    b.width ^= SIGN_MASK;
    return decimal_add(a, b);
}

// === MULTIPLICATION ===
static inline Decimal_32 decimal_mul(Decimal_32 a, Decimal_32 b) {
    int sa = GET_SIGN(a.width), sb = GET_SIGN(b.width);
    int32_t ma = GET_MANT(a.width), mb = GET_MANT(b.width);
    int ea = GET_SEP(a.width), eb = GET_SEP(b.width);

    if (sa) ma = -ma;
    if (sb) mb = -mb;

    int64_t result_m = (int64_t)ma * mb;
    int result_s = (result_m < 0);
    if (result_s) result_m = -result_m;

    int result_e = ea + eb;

    while ((result_m > MAX_MANT) && result_e < 255) {
        result_m >>= 1;
        result_e++;
    }

    if (result_m > MAX_MANT) {
        result_m = MAX_MANT;
        SET_OVERFLOW();
    }

    return pack_decimal_32(result_s, result_e, (int32_t)result_m);
}

// === DIVISION ===
static inline Decimal_32 decimal_div(Decimal_32 a, Decimal_32 b) {
    int sa = GET_SIGN(a.width), sb = GET_SIGN(b.width);
    int32_t ma = GET_MANT(a.width), mb = GET_MANT(b.width);
    int ea = GET_SEP(a.width), eb = GET_SEP(b.width);

    if (mb == 0) return pack_decimal_32(0, 0, 0);  // Handle divide-by-zero

    if (sa) ma = -ma;
    if (sb) mb = -mb;

    int result_s = ((ma < 0) ^ (mb < 0));
    int64_t numerator = ((int64_t)ma) << 23; // 23-bit shift to preserve fraction
    int64_t result_m = numerator / mb;

    if (result_m < 0) result_m = -result_m;

    int result_e = ea - eb;

    while ((result_m > MAX_MANT) && result_e < 255) {
        result_m >>= 1;
        result_e++;
    }

    if (result_m > MAX_MANT) {
        result_m = MAX_MANT;
        SET_OVERFLOW();
    }

    return pack_decimal_32(result_s, result_e, (int32_t)result_m);
}