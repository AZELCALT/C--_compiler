typedef union __attribute__((packed))
{
    struct {
        uint32_t number: 23;
        uint8_t  locator: 8;
        uint8_t  sign:    1;   
    };
    uint32_t witdh;
}AntiFloat_32;

_Static_assert(sizeof(AntiFloat_32) == 4, "AntiFloat_32 must be 32 bits");

typedef union __attribute__((packed))
{
    struct {
        uint64_t number: 55;
        uint8_t  locator: 8;
        uint8_t  sign:    1;   
    };
    uint64_t witdh;
}AntiFloat_64;


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