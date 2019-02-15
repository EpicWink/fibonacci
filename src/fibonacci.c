/* --- 100 characters -----------------------------------------------------------------------------
Created by: Laurie 2018/02/05

Large fibonacci number generator.

Compile: gcc fibonacci.c -o fib -lm -m64 -O3
Usage: ./fib
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// static const unsigned long long first_bit_mask = 9223372036854775808U;
static const unsigned long long llu_max = 18446744073709551615U;
static const unsigned long arr_size = 1073741824 - 50 * 1048576 / sizeof(unsigned long long);


void add(unsigned long long *a, unsigned long long *b, unsigned long *lena, unsigned long *lenb) {
    static unsigned long long carry;
    static unsigned long long a_chunk, b_chunk, c_chunk;
    static unsigned long stop;

    carry = 0;
    stop = arr_size - *lenb - 1;

    for (unsigned long j = arr_size - 1; j > stop; j -= 1) {
        a_chunk = a[j];
        b_chunk = b[j];
        c_chunk = a_chunk + b_chunk + carry;
        carry = (unsigned long long) a_chunk > llu_max - b_chunk;  // TODO: replace with bit-check
        // fprintf(stderr, "Add [%lu]: a_chunk: %llu, b_chunk: %llu\n", j, a_chunk, b_chunk);
        // fprintf(stderr, "Add [%lu]: c_chunk: %llu, carry: %llu\n", j, c_chunk, carry);
        // fflush(stderr);
        a[j] = b_chunk;
        b[j] = c_chunk;
    }

    b[arr_size - *lenb - 1] += carry;
    *lena = *lenb;
    *lenb += carry;
}


void log_ab(
        unsigned long long *a,
        unsigned long long *b,
        unsigned long lena,
        unsigned long lenb,
        unsigned long step,
        unsigned long t) {
    unsigned long nt = time(NULL) - t;
    fprintf(stderr, "Step %lu (%lus): len(a)=%lu, len(b)=%lu\n", step, nt, lena, lenb);
    // for (unsigned long j = 0; j < lenb; j += 1) {
    //     fprintf(
    //         stderr, "%10lu: a: %020llu, b: %020llu\n",
    //         j, a[arr_size - j - 1], b[arr_size - j - 1]);
    // }
    // fprintf(stderr, "\n");
}


int main(int argc, char** argv) {
    unsigned long long *a = calloc(arr_size, sizeof(unsigned long long));
    unsigned long long *b = calloc(arr_size, sizeof(unsigned long long));
    unsigned long lena = 1, lenb = 1;
    unsigned long step = 0;
    unsigned long t;

    if (a == NULL) {
        fprintf(stderr, "Failed to allocate 'a'\n");
        return 1;
    }
    if (b == NULL) {
        fprintf(stderr, "Failed to allocate 'b'\n");
        return 1;
    }

    fprintf(stderr, "Fibonacci sequence generator\n");
    fprintf(stderr, "Array size: %lu MB\n", arr_size * sizeof(unsigned long long) / (1024 * 1024));
    // fprintf(stderr, "arr_size: %lu\n", arr_size);
    // fprintf(stderr, "llu_max: %llu\n", llu_max);
    fprintf(stderr, "\n");

    t = time(NULL);

    a[arr_size - 1] = 1;
    b[arr_size - 1] = 1;

    fprintf(stderr, "Running adding\n");
    while (1) {
        if (step % 100000 == 0) {
            log_ab(a, b, lena, lenb, step, t);
        }
        add(a, b, &lena, &lenb);
        step += 1;

        if (lenb >= arr_size - 1) {
            log_ab(a, b, lena, lenb, step, t);
            fprintf(stderr, "Reached array max size\n");
            return 1;
        }

        // log_ab(a, b, lena, lenb, step, t);

        // if (step >= 95) {
        //     printf("Breaking early\n");
        //     return 0;
        // }
    }

    return 0;
}
