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