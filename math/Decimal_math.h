#include "packed.h"

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