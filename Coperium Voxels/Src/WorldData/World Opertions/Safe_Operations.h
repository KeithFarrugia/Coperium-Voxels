#ifndef SAFE_MATH_H
#define SAFE_MATH_H

/* ============================================================================
 * --------------------------- Safe_Div
 * Safely divides two integers, adjusting for negative values to avoid
 * rounding issues.
 *
 * ------ Parameters ------
 * a: The dividend (integer to be divided)
 * b: The divisor (integer by which to divide)
 *
 * ------ Returns ------
 * Integer result of the division, with adjustments for negative dividends.
 * ============================================================================
 */
inline static int Safe_Div(int a, int b) {
    return (a - (a >> 31 & (b - 1))) / b;
}

/* ============================================================================
 * --------------------------- Pos_Mod
 * Computes the modulus of two integers, ensuring the result is always
 * non-negative, even when the dividend is negative.
 *
 * ------ Parameters ------
 * a: The dividend (integer from which to calculate the remainder)
 * b: The divisor (integer by which to divide)
 *
 * ------ Returns ------
 * Non-negative remainder of the division.  
 * ============================================================================
 */
inline static int Pos_Mod(int a, int b) {
    int result = a % b;
    return result < 0 ? result + b : result;
}

#endif // SAFE_MATH_H