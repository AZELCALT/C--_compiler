#ifdef fix_negative_zero
    if (mant == 0) sign = 0;
#endif

typedef union __attribute__((packed))
{
    struct {
        uint32_t number: 23;
        uint8_t  locator: 8;
        uint8_t  sign:    1;   
    };
    uint32_t witdh;
}Decimal_32;

_Static_assert(sizeof(AntiFloat_32) == 4, "AntiFloat_32 must be 32 bits");

typedef union __attribute__((packed))
{
    struct {
        uint64_t number: 55;
        uint8_t  locator: 8;
        uint8_t  sign:    1;   
    };
    uint64_t witdh;
}Decimal_64;


_Static_assert(sizeof(AntiFloat_64) == 8, "AntiFloat_64 must be 64 bits");


typedef union __attribute__((packed))
{
    struct {
        uint32_t number:         15;
        uint32_t denominator:    16;
        uint8_t  sign:           1;   
    };
    uint32_t witdh;
}Rational_32;

_Static_assert(sizeof(Rational_32) == 4, "Rational_32 must be 32 bits");

typedef union __attribute__((packed))
{
    struct {
        uint64_t number:         31;  
        uint64_t denominator:    32;
        uint8_t  sign:           1;   
    };
    uint64_t witdh;
}Rational_64;

_Static_assert(sizeof(Rational_64) == 8, "Rational_64 must be 64 bits");

typedef union __attribute__((packed))
{
    struct {
        uint16_t number:         15;
        uint16_t denominator:    16;
        uint8_t  sign:           1;   
    };
    uint32_t witdh;
}Fixed_32;

_Static_assert(sizeof(Fixed_32) == 4, "Rational_32 must be 32 bits");

typedef union __attribute__((packed))
{
    struct {
        uint64_t number:         31;  
        uint64_t denominator:    32;
        uint8_t  sign:           1;   
    };
    uint64_t witdh;
}Fixed_64;

_Static_assert(sizeof(Fixed_64) == 8, "Rational_64 must be 64 bits");



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
#define GET_SIGN(x)   (((x) >> 31) & 0x1)
#define GET_SEP(x)    (((x) >> 23) & 0xFF)
#define GET_MANT(x)   (((x) & (1 << 22)) ? ((x) | ~MANT_MASK) : ((x) & MANT_MASK))

// === Pack to decimal format ===
Decimal_32 encode_packed(int sign, int int_part, int frac_part, int int_bits, int frac_bits) {
    Decimal_32 r = {0};
    
    // Normalize bit count
    if (int_bits < 0) int_bits = 0;
    if (frac_bits < 0) frac_bits = 0;
    if ((int_bits + frac_bits) > 23) {
        if (int_bits > 23) int_bits = 23;
        frac_bits = 23 - int_bits;
    }

    r.sign = sign & 1;
    r.layout = ((int_bits & 0xF) << 4) | (frac_bits & 0xF);

    int shift_frac = 23 - frac_bits;
    int shift_int  = shift_frac - int_bits;

    r.mant = ((int_part  & ((1 << int_bits) - 1)) << shift_frac) |
             ((frac_part & ((1 << frac_bits) - 1)) << shift_int);

    return r;
}


// === Float to decimal ===
static inline Decimal_32 decimal_from_float(float val) {
    int sign = (val < 0);
    float abs_val = fabsf(val);

    int sep;
    int32_t mant = 0;

    for (sep = 0; sep < 256; sep++) {
        float scaled = abs_val * (1 << sep);
        if (scaled > INT32_MAX) continue;
        mant = (int32_t)roundf(scaled);
        if (mant >= MIN_MANT && mant <= MAX_MANT) break;
    }

    if (mant > MAX_MANT) {
        mant = MAX_MANT;
        SET_OVERFLOW();
    }

    return encode_decimal(sign, sep, mant);
}

// === decimal to Float ===
static inline float decimal_to_float(Decimal_32 fx) {
    int sign = GET_SIGN(fx);
    int sep = GET_SEP(fx);
    int32_t mant = GET_MANT(fx);
    float value = (float)mant / (1 << sep);
    return sign ? -value : value;
}

// === ADDITION ===
static inline Decimal_32 decimal_add(Decimal_32 a, Decimal_32 b) {
    int sa = GET_SIGN(a), sb = GET_SIGN(b);
    int ea = GET_SEP(a), eb = GET_SEP(b);
    int32_t ma = GET_MANT(a), mb = GET_MANT(b);
    int32_t integer;
    int32_t decimal;
    int     index;

    if (sa) ma = -ma;
    if (sb) mb = -mb;

    for (index = 0;index < ea;index++){

    }


    int e = ea > eb ? eb : ea;
    if (ea > eb) mb >>= (ea - eb);
    else ma >>= (eb - ea);

    int32_t result_m = ma + mb;
    int result_s = (result_m < 0);
    if (result_s) result_m = -result_m;

    int result_e = e;
    while ((result_m > MAX_MANT) && (result_e < 255)) {
        result_m >>= 1;
        result_e++;
    }

    if (result_m > MAX_MANT) {
        result_m = MAX_MANT;
        SET_OVERFLOW();
    }



    return encode_decimal(result_s, result_e, result_m);
}

// === SUBTRACTION ===
static inline Decimal_32 decimal_sub(Decimal_32 a, Decimal_32 b) {
    b.witdh ^= SIGN_MASK;
    return decimal_add(a, b);
}

// === MULTIPLICATION ===
static inline Decimal_32 decimal_mul(Decimal_32 a, Decimal_32 b) {
    int sa = GET_SIGN(a), sb = GET_SIGN(b);
    int32_t ma = GET_MANT(a), mb = GET_MANT(b);
    int ea = GET_SEP(a), eb = GET_SEP(b);

    if (sa) ma = -ma;
    if (sb) mb = -mb;

    int64_t result_m = (int64_t)ma * mb;
    int result_s = (result_m < 0);
    if (result_s) result_m = -result_m;

    int result_e = ea + eb;

    while ((result_m > MAX_MANT) && (result_e < 255)) {
        result_m >>= 1;
        result_e++;
    }

    if (result_m > MAX_MANT) {
        result_m = MAX_MANT;
        SET_OVERFLOW();
    }

    return encode_decimal(result_s, result_e, (int32_t)result_m);
}

// === DIVISION ===
static inline Decimal_32 decimal_div(Decimal_32 a, Decimal_32 b) {
    int sa = GET_SIGN(a), sb = GET_SIGN(b);
    int32_t ma = GET_MANT(a), mb = GET_MANT(b);
    int ea = GET_SEP(a), eb = GET_SEP(b);

    if (mb == 0) return 0;

    if (sa) ma = -ma;
    if (sb) mb = -mb;

    int64_t numerator = ((int64_t)ma) << 22;
    int64_t result_m = (numerator + (mb / 2)) / mb;

    int result_s = (result_m < 0);
    if (result_s) result_m = -result_m;

    int result_e = ea - eb - 22;

    while ((result_m > MAX_MANT) && (result_e < 255)) {
        result_m >>= 1;
        result_e++;
    }

    if (result_m > MAX_MANT) {
        result_m = MAX_MANT;
        SET_OVERFLOW();
    }

    return encode_decimal(result_s, result_e, (int32_t)result_m);
}

#endif // decimal_H
