
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

int main(int argc, char** argv) {
    unsigned long long a = 1, b = 1, c;
    unsigned long long step = 0;

    while (true) {
        if (b > 9223372036854775807) {
            fprintf(stderr, "'b' too large at step %llu\n", step);
            fflush(stderr);
            return 1;
        }

        c = a + b;
        a = b;
        b = c;

        step += 1;
        if (step % 1 == 0) {
            printf("Step %llu, a: %llu, b: %llu\n", step, a, b);
            fflush(stdout);
        }
    }

    return 0;
}
