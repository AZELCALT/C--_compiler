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
