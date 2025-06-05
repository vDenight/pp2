//
// Created by mrybczynski on 6/5/2025.
//

int is_equal(int a, int b) {
    int xnor_result = ~(a ^ b);
    unsigned int bit = 1U;

    while (bit) {
        if (!(xnor_result & bit)) return 0;
        bit <<= 1;
    }
    return 1;
}

int is_negative(int value) {
    unsigned int sign_bit = 1U << 31;
    if (sign_bit & value) return 1;
    return 0;
}