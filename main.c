#include <portaudio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "vibrato.h"

#define NUM_SECONDS 500
#define Fs 44100 // Sampling rate

static int callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
                             const PaStreamCallbackTimeInfo* timeInfo,
                             PaStreamCallbackFlags statusFlags, void *userData){
    
    float *out = (float*) outputBuffer;
    float *in = (float*) inputBuffer;
    float inValue, outValue = 0;

    for(unsigned _i = 0; _i < framesPerBuffer; _i++){

        // Get input sample
        inValue = *in++;

        // Apply vibrato effect
        outValue = process_vibrato(inValue);

        // Output the resulting samples to both channels
        *out++ = outValue;
        *out++ = outValue;
    }
        
    return 0;
}

int main(void) {

    // Set up vibrato effect
    init_vibrato(Fs, 0.005, 5);

    // Reference to the stream
    PaStream *stream;

    // Error
    PaError err;

    // Initialize PortAudio
    err = Pa_Initialize();
    if(err != paNoError) goto error;

    // Open audio I/O stream with default devices
    err = Pa_OpenDefaultStream(&stream,
                               1, /* number of input channels */
                               2, /* number of output channels*/
                               paFloat32, /* 32 bit floating point output */
                               Fs, /* sampling rate */
                               256, /* frames per buffer, the number of sample
                                       frames that PortAudio will request from the callback.
                                       May want paFramesPerBufferUnspecified, which tells
                                       PortAudio to pick the best size */
                               callback, /* Callback function */
                               NULL); /*Pointer that will be passed to the callback as userData */
    if(err != paNoError) goto error;

    // Start stream. Will start calling callback function
    err = Pa_StartStream(stream);
    if(err != paNoError) goto error;

    // Amount of time before the program stops the effect and shuts down
    Pa_Sleep(NUM_SECONDS * 1000);

    // Stop stream
    err = Pa_StopStream(stream);
    if(err != paNoError) goto error;

    // Close stream
    err = Pa_CloseStream(stream);
    if(err != paNoError) goto error;

    // Terminate PortAudio
    err = Pa_Terminate();
    if(err != paNoError) goto error;

error:
    Pa_Terminate();
    printf("\nProgram has ended\n");
    printf("Error %d: %s\n", err, Pa_GetErrorText(err));
    return err;
}
