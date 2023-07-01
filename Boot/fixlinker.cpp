extern "C" uint64_t __umoddi3(uint64_t dividend, uint64_t divisor) {
    uint64_t quotient = dividend / divisor;
    uint64_t remainder = dividend - (quotient * divisor);
    return remainder;
}
extern "C" uint64_t __udivdi3(uint64_t dividend, uint64_t divisor) {
    uint64_t quotient = 0;
    uint64_t temp = 0;

    for (int i = 63; i >= 0; i--) {
        temp <<= 1;
        temp |= (dividend >> i) & 1;

        if (temp >= divisor) {
            temp -= divisor;
            quotient |= 1ULL << i;
        }
    }

    return quotient;
}