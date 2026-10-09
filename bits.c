/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  return ~(x & y) & ~(~x & ~y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  int mask = x >> 31;
  return mask & (~x + 1);
}

// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  int srcShift = src << 3;
  int dstShift = dst << 3;
  int byte = (x >> srcShift) & 0xFF;
  int cleared = x & ~(0xFF << dstShift);
  return cleared | (byte << dstShift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  int mask = ~((1 << 31) >> n << 1);
  return (x >> n) & mask;
}

// P6
int swapNibblePairs(int x) {
    int mask = 0x0F;
    mask = mask | (mask << 8);
    mask = mask | (mask << 16);
    return ((x & mask) << 4) | ((x >> 4) & mask);
}

// P7
int secondLowestZeroBit(int x) {
    int notx = ~x;
    int first = notx & (~notx + 1);
    int rem = notx ^ first;
    return rem & (~rem + 1);
}


// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  x ^= x >> 16;
  x ^= x >> 8;
  x ^= x >> 4;
  x ^= x >> 2;
  x ^= x >> 1;
  return !(x & 1);
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  int shift = 32 + (~n + 1);
  int low = x << shift;
  int high = (x >> n) & ~((1 << 31) >> n << 1);
  return high | low;
}

// P10
int roundEvenPow2(int x, int n) {
    int mask = (1 << n) + ~0;
    int half = 1 << (n + ~1 + 1);
    int frac = x & mask;
    int base = x & ~mask;
    int cmp = frac + ~half + 1;
    int geHalf = (cmp >> 31) ^ 1;
    int isHalf = !(frac ^ half);
    int baseEven = !((base >> n) & 1);
    int add = geHalf & ( !isHalf | !baseEven );
    return base + (add << n);
}


// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 */
int midpointTowardFirst(int x, int y) {
    int diff = x + ~y + 1;
    int xor = x ^ y;
    int same = !(xor >> 31);
    int gt = (!(diff >> 31) & same) | (!(x >> 31) & !same);
    int lsb = xor & 1;
    return (x & y) + (xor >> 1) + (lsb & gt);
}

// P12
int isBetweenEitherOrder(int x, int a, int b) {
    int d_xa = x + ~a + 1;
    int d_xb = x + ~b + 1;
    int d_ax = a + ~x + 1;
    int d_bx = b + ~x + 1;
    int xa = x ^ a;
    int xb = x ^ b;
    int xs = x >> 31;
    int xs1 = !xs;
    int xas = xa >> 31;
    int xas1 = !xas;
    int xbs = xb >> 31;
    int xbs1 = !xbs;
    int ge_xa = (!(d_xa >> 31) & xas1) | (xs1 & xas);
    int ge_xb = (!(d_xb >> 31) & xbs1) | (xs1 & xbs);
    int ge_ax = (!(d_ax >> 31) & xas1) | (!(a >> 31) & xas);
    int ge_bx = (!(d_bx >> 31) & xbs1) | (!(b >> 31) & xbs);
    return (ge_xa & ge_bx) | (ge_xb & ge_ax);
}


// P13 mul5Sat
int mul5Sat(int x) {
    int a = x << 2;
    int sum = a + x;
    int x_sign = x >> 31;
    int a_sign = a >> 31;
    int sum_sign = sum >> 31;

    int shift_diff = (a >> 2) ^ x;
    int shift_ov = !!shift_diff;
    shift_ov = (shift_ov << 31) >> 31;

    int same_sign = ~(a_sign ^ x_sign);
    int diff_sum = a_sign ^ sum_sign;
    int add_ov = same_sign & diff_sum;

    int ov = shift_ov | add_ov;

    int int_min = 1 << 31;
    int int_max = ~int_min;
    int sat = (x_sign & int_min) | (~x_sign & int_max);

    return (ov & sat) | (~ov & sum);
}

// P14
int classifyAdd3(int x, int y, int z) {
    int s1 = x + y;
    int ov1 = ((x ^ s1) & (y ^ s1)) >> 31;
    int s2 = s1 + z;
    int ov2 = ((s1 ^ s2) & (z ^ s2)) >> 31;
    int pos = ((ov1 & ~(x >> 31)) | (ov2 & ~(s1 >> 31))) & 1;
    int neg = ((ov1 & (x >> 31)) | (ov2 & (s1 >> 31))) & 1;
    return pos + ~neg + 1;
}


// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of f*3/2
 *   Legal ops: Any integer/unsigned, if/while
 *   Max ops: 60
 */
unsigned floatScaleThreeHalves(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xff;
    unsigned frac = uf & 0x7fffff;
    if (exp == 0xff) return uf;
    if (exp == 0 && frac == 0) return uf;

    if (exp == 0) {
        unsigned prod = frac + (frac >> 1);
        unsigned rbit = frac & 1;
        if (rbit && (prod & 1)) prod++;
        if (prod >= 0x800000) {
            exp = 1;
            frac = prod & 0x7fffff;
        } else {
            frac = prod;
        }
    } else {
        unsigned full = frac | 0x800000;
        unsigned prod = full + (full >> 1);
        unsigned rbit = full & 1;
        if (rbit && (prod & 1)) prod++;
        if (prod >= 0x1000000) {
            unsigned r = prod & 1;
            prod >>= 1;
            exp += 1;
            if (r && (prod & 1)) prod++;
        }
        frac = prod & 0x7fffff;
    }

    if (exp >= 0xff) return sign | 0x7f800000;
    return sign | (exp << 23) | frac;
}


// P16
/* 
 *  - round uf to nearest integer, ties to even.
 *   Legal ops: Any integer/unsigned, if/while
 *   Max opfloatRoundEvens: 65
 */
unsigned floatRoundEven(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = (uf >> 23) & 0xff;
    unsigned frac = uf & 0x7fffff;
    if (exp == 0xff) return uf;

    int e = (int)exp - 127;
    if (e >= 23) return uf;

    if (e < 0) {
        unsigned full;
        if (exp == 0) full = frac;
        else full = frac | 0x800000;
        int shift = 23 - e;
        unsigned half = 1U << (shift - 1);
        unsigned mask = (1U << shift) - 1;
        unsigned low = full & mask;
        unsigned high = full >> shift;
        if (low > half || (low == half && (high & 1))) high++;
        if (high >= 1) return sign | (127 << 23);
        return sign;
    }

    int shift = 23 - e;
    unsigned half = 1U << (shift - 1);
    unsigned mask = (1U << shift) - 1;
    unsigned low = frac & mask;
    unsigned high = frac & ~mask;
    unsigned low_bit = ((1 << e) | (frac >> (23 - e))) & 1;
    if (low > half || (low == half && low_bit)) {
        high += 1U << shift;
        if (high >= 0x800000) {
            high = 0;
            exp += 1;
        }
    }
    return sign | (exp << 23) | high;
}

// P17
unsigned float_i2f(int x) {
    if (x == 0) return 0;
    unsigned sign = 0;
    unsigned ux;
    if (x < 0) {
        sign = 0x80000000;
        ux = (x == 0x80000000) ? 0x80000000 : (~x + 1);
    } else {
        ux = x;
    }
    int k = 31;
    while ((ux & (1U << k)) == 0) k--;
    unsigned exp = k + 127;
    unsigned frac;
    if (k <= 23) {
        frac = (ux ^ (1U << k)) << (23 - k);
    } else {
        int shift = k - 23;
        unsigned full = ux >> shift;
        unsigned f = full & 0x7fffff;
        int rbit = (ux >> (shift - 1)) & 1;
        int sticky = (ux & ((1U << (shift - 1)) - 1)) != 0;
        if (rbit && (sticky || (f & 1))) {
            f = f + 1;
            if (f >= 0x800000) {
                f = 0;
                exp = exp + 1;
            }
        }
        frac = f;
    }
    return sign | (exp << 23) | frac;
}

// P18
int bitCount(int x) {
    int m1 = 0x55;
    m1 = m1 | (m1 << 8);
    m1 = m1 | (m1 << 16);
    int m2 = 0x33;
    m2 = m2 | (m2 << 8);
    m2 = m2 | (m2 << 16);
    int m4 = 0x0F;
    m4 = m4 | (m4 << 8);
    m4 = m4 | (m4 << 16);
    int m8 = 0xFF;
    m8 = m8 | (m8 << 16);
    int m16 = 0xFF;
    m16 = m16 | (m16 << 8);
    x = x + ~((x >> 1) & m1) + 1;
    x = (x & m2) + ((x >> 2) & m2);
    x = (x + (x >> 4)) & m4;
    x = (x + (x >> 8)) & m8;
    x = (x + (x >> 16)) & m16;
    return x;
}

// P19
int bitReverse(int x) {
    int m1 = 0x55;
    m1 = m1 | (m1 << 8) | (m1 << 16);
    int m2 = 0x33;
    m2 = m2 | (m2 << 8) | (m2 << 16);
    int m4 = 0x0F;
    m4 = m4 | (m4 << 8) | (m4 << 16);
    int m8 = 0xFF;
    m8 = m8 | (m8 << 16);
    int m16 = 0xFF;
    m16 = m16 | (m16 << 8);
    x = ((x >> 1) & m1) | ((x & m1) << 1);
    x = ((x >> 2) & m2) | ((x & m2) << 2);
    x = ((x >> 4) & m4) | ((x & m4) << 4);
    x = ((x >> 8) & m8) | ((x & m8) << 8);
    x = ((x >> 16) & m16) | ((x & m16) << 16);
    return x;
}
