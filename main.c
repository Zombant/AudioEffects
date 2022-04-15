#include <portaudio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "util.h"

#include "vibrato.h"
#include "flanger.h"
#include "chorus.h"
#include "allpass.h"
#include "wahwah.h"
#include "nonlinearity.h"

#define NUM_SECONDS 500
#define Fs 44100 // Sampling rate

Vibrato *vibrato;
Flanger *flanger;
Chorus *white_chorus;
WahWah *wahwah;

FirstOrderAllpass *allpass_filter1;
SecondOrderAllpass *allpass_filter2;

static int callback(const void *inputBuffer, void *outputBuffer, unsigned long framesPerBuffer,
                             const PaStreamCallbackTimeInfo* timeInfo,
                             PaStreamCallbackFlags statusFlags, void *userData){
    
    float *out = (float*) outputBuffer;
    float *in = (float*) inputBuffer;
    float inValue, outValue = 0;

    for(unsigned _i = 0; _i < framesPerBuffer; _i++){

        // Get input sample
        inValue = *in++;

        // Apply vibrato effect (1-stage)
        //outValue = process_vibrato(vibrato, inValue);

        // Apply flanger
        //outValue = process_flanger(flanger, inValue);

        // Apply white chorus
        //outValue = process_white_chorus(white_chorus, inValue);
        
        // Apply wahwah
        //outValue = process_wahwah(wahwah, inValue);

        // Apply static nonlinearities
        //outValue = square(inValue);
        outValue = overdrive(inValue, 10);
        

        // Apply allpass filter
        //outValue = allpass1(allpass_filter1, inValue);
        //outValue = allpass2(allpass_filter2, inValue);

        // Apply filter
        //outValue = lowpass1(allpass_filter1, inValue);
        //outValue = highpass1(allpass_filter1, inValue);
        //outValue = bandstop2(allpass_filter2, inValue);
        //outValue = bandpass2(allpass_filter2, inValue);

        // Pass audio
        //outValue = inValue;

        //printf("Input: %f\nOutput: %f\n\n", inValue, outValue);


        // Apply vibrato effect (2-stage)
        //outValue1 = process_vibrato(vib1, inValue);
        //outValue2 = process_vibrato(vib2, outValue1);

        // Output the resulting samples to both channels
        *out++ = outValue;
        *out++ = outValue;
    }
        
    return 0;
}

int main(void) {

    srand(time(0));

    vibrato = malloc(sizeof(Vibrato));
    flanger = malloc(sizeof(Flanger));
    white_chorus = malloc(sizeof(Chorus));
    wahwah = malloc(sizeof(WahWah));

    allpass_filter1 = malloc(sizeof(FirstOrderAllpass));
    allpass_filter2 = malloc(sizeof(SecondOrderAllpass));

    // Set up effects
    init_vibrato(vibrato, Fs, 0.005, 10);
    init_flanger(flanger, Fs, 0.001, 0.1);
    init_white_chorus(white_chorus, Fs, 0.01, 0.1);
    init_allpass1(allpass_filter1, -.99);
    init_allpass2(allpass_filter2, Fs, 1000, 500);
    init_wahwah(wahwah, Fs, 0.7, 350, 2200, 3.0); // Dunlop Crybaby

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
