#include <stdio.h>
#include <math.h>
#include <queue>
#include "portaudio.h"

#define SAMPLE_RATE   (44100)
#define FRAMES_PER_BUFFER  (512)

#ifndef M_PI
#define M_PI  (3.14159265)
#endif
#define TWOPI (M_PI * 2.0)

#define TABLE_SIZE   (1024)

typedef struct paTestData
{
    std::queue<float> * bufferptr;
}
paTestData;

PaError checkErr(PaError err);

static int patestCallback(const void*                     inputBuffer,
                          void*                           outputBuffer,
                          unsigned long                   framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags           statusFlags,
                          void*                           userData )
{
    paTestData *data = (paTestData*)userData;
    float *out = (float*)outputBuffer;
    float outSample;
    (void) inputBuffer; /* Prevent unused argument warning. */

    for( unsigned long i=0; i<framesPerBuffer; i++ ) {
        float output = 0.0;
        std::queue<float> * bufferptr = data->bufferptr;
        if (!bufferptr->empty()) {
            output = bufferptr->front();
            bufferptr->pop();
        }
        /* else { */
	        /* output = fmod((float) i/(128), 2.0) - 1.0; */
        /* } */
        outSample = (float) (output);
        *out++ = outSample; /* Left */
        *out++ = outSample; /* Right */
    }
    return 0;
}

int main(void) {
    std::queue<float> buffer;
    for (int j=0; j < 2; j++) {
        for (unsigned long i=1; i < 2410; i++) { buffer.push( (float) sin( i / 16.0 )); }
        for (unsigned long i=1; i < 2410; i++) { buffer.push( 0.0 ); }
    }
    for (unsigned long i=1; i < 4410; i++) { buffer.push( (float) sin( i / 4.0 )); }

    PaStream*           stream;
    PaStreamParameters  outputParameters;
    PaError             err;
    paTestData          data;

    data.bufferptr = &buffer;

    printf("PortAudio Test: output sine wave. SR = %d, BufSize = %d\n", SAMPLE_RATE, FRAMES_PER_BUFFER);

    checkErr(Pa_Initialize());

    outputParameters.device                    = Pa_GetDefaultOutputDevice(); /* Default output device. */
    if (outputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default output device.\n");
	    Pa_Terminate();
    }
    outputParameters.channelCount              = 2;                           /* Stereo output. */
    outputParameters.sampleFormat              = paFloat32;                   /* 32 bit floating point output. */
    outputParameters.hostApiSpecificStreamInfo = NULL;
    outputParameters.suggestedLatency          = Pa_GetDeviceInfo(outputParameters.device)
                                                 ->defaultHighOutputLatency;
    checkErr(Pa_OpenStream(&stream,
                        NULL,               /* no input */
                        &outputParameters,
                        SAMPLE_RATE,
                        FRAMES_PER_BUFFER,
                        paClipOff,          /* No out of range samples should occur. */
                        patestCallback,
                        &data));
    checkErr(Pa_StartStream( stream ));

    FILE * in;
    float x;
    while (1) {
        in = fopen("master_pipe", "rb");
        printf("yes in");
        if (in) {
            while (fread(&x, sizeof(x), 1, in) > 0) {
                buffer.push(x);
            }
        }
        fclose(in);
    }

    checkErr(Pa_StopStream( stream ));
    checkErr(Pa_CloseStream( stream ));

    Pa_Terminate();
    return err;
}

PaError checkErr(PaError err) {
    if ( err != paNoError ) {
	    Pa_Terminate();
	    fprintf( stderr, "An error occurred while using the portaudio stream\n" );
    	fprintf( stderr, "Error number: %d\n", err );
    	fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    }
    return err;
}
