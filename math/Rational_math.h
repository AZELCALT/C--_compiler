#include "packed.h"

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
