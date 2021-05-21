#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <math.h>

#define TWOPI (3.14159 * 2)
#define SAMPLE_RATE (44100)

int main() {
    FILE * out;

    out = fopen("master.pipe", "wb");

    for (int i = 0; i < SAMPLE_RATE / 2; i++) {
        float x = sin(i * TWOPI / 128.0);
        fwrite(&x, sizeof(x), 1, out);
    }

    for (int i = 0; i < SAMPLE_RATE * 2; i++) {
        float x = fmod(i / 128.0, 1.0);
        fwrite(&x, sizeof(x), 1, out);
    }


    fclose(out);

    return 1;
}

