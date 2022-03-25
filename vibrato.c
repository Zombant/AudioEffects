#include <portaudio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "vibrato.h"


float NOMINAL_DELAY;
float CHORUS_WIDTH;

float f_LFO_samples;
int delayline_size;

float *delayline;
float i_frac;
float i;
float frac;
int sampleNumber;



void init_vibrato(){
    NOMINAL_DELAY = round((float)W * (float)Fs); // Center of the delay
    CHORUS_WIDTH = round((float)W * (float)Fs); // Half of the delay

    f_LFO_samples = (float)f_LFO / (float)Fs;
    delayline_size = (int) (NOMINAL_DELAY + CHORUS_WIDTH * 2);

    delayline = malloc(delayline_size * sizeof(float));
    for(int sample = 0; sample < delayline_size; sample++){
        delayline[sample] = 0;
    }

    sampleNumber = 0;
}

static void insert_in_delayline(float value){
    for(int i = delayline_size-1; i > 0; i--){
        *(delayline + i) = *(delayline + i - 1);
    }
    *(delayline + 0) = value;
    //print_delayline();
}

static void print_delayline(){
    for(int i = 0; i < delayline_size; i++){
        printf("%f\t", delayline[i]);
    }
    printf("\n\n\n\n");
}

float process_vibrato(float value){
    i_frac = NOMINAL_DELAY + CHORUS_WIDTH * sinf(f_LFO_samples * 2 * M_PI * sampleNumber);
    i = floor(i_frac);
    frac = i_frac - i;

    insert_in_delayline(value);

    sampleNumber++;

    return frac * delayline[(int)i + 1] + (1-frac) * delayline[(int)i];
    
}
