#include <stdio.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <math.h>

#define TWOPI (3.14159 * 2)
#define SAMPLE_RATE (44100)

int main(int argc, char **argv) {
    char * out_name = "sink.pipe";
    if (argc > 1) { out_name = argv[1]; };

    FILE * out;

    out = fopen(out_name, "wb");

    for (int i = 0; i < SAMPLE_RATE / 2; i++) {
        float x = sin(i * TWOPI / 128.0);
        fwrite(&x, sizeof(x), 1, out);
    }
    for (int i = 0; i < SAMPLE_RATE; i++) {
        float x = fmod(i / 128.0, 1.0);
        fwrite(&x, sizeof(x), 1, out);
    }

    for (int i = 0; i < SAMPLE_RATE; i++) {
        float x = 0.0;
        fwrite(&x, sizeof(x), 1, out);
    }

    for (int i = 0; i < SAMPLE_RATE / 2; i++) {
        double x = sin(i * TWOPI / 128.0);
        fwrite(&x, sizeof(x), 1, out);
    }
    for (int i = 0; i < SAMPLE_RATE; i++) {
        double x = fmod(i / 128.0, 1.0);
        fwrite(&x, sizeof(x), 1, out);
    }


    fclose(out);

    return 1;
}

