#include <portaudio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "flanger.h"


void init_flanger(Flanger *instance, int _sampling_rate, float _W, float _f_LFO){
    instance->sampling_rate = _sampling_rate;
    instance->W = _W;
    instance->f_LFO = _f_LFO;

    instance->NOMINAL_DELAY = round((float)instance->W * (float)instance->sampling_rate); // Center of the delay
    instance->CHORUS_WIDTH = round((float)instance->W * (float)instance->sampling_rate); // Half of the delay

    instance->f_LFO_samples = (float)instance->f_LFO / (float)instance->sampling_rate;
    instance->delayline_size = (int) (instance->NOMINAL_DELAY + instance->CHORUS_WIDTH * 2);

    instance->delayline = malloc(instance->delayline_size * sizeof(float));
    for(int sample = 0; sample < instance->delayline_size; sample++){
        instance->delayline[sample] = 0;
    }

    instance->sampleNumber = 0;
}

static void insert_in_delayline_flanger(Flanger *instance, float value){
    for(int i = instance->delayline_size-1; i > 0; i--){
        *(instance->delayline + i) = *(instance->delayline + i - 1);
    }
    *(instance->delayline + 0) = value;
}

static void print_delayline_flanger(Flanger *instance){
    for(int i = 0; i < instance->delayline_size; i++){
        printf("%f\t", instance->delayline[i]);
    }
    printf("\n\n\n\n");
}

float process_flanger(Flanger *instance, float value){
    instance->i_frac = instance->NOMINAL_DELAY + instance->CHORUS_WIDTH * sinf(instance->f_LFO_samples * 2 * M_PI * instance->sampleNumber);
    instance->i = floor(instance->i_frac);
    instance->frac = instance->i_frac - instance->i;

    insert_in_delayline_flanger(instance, value);

    instance->sampleNumber++;

    value = value - (instance->delayline[(int)instance->NOMINAL_DELAY] * 0.7071);

    float forward = (instance->frac * instance->delayline[(int)instance->i + 1] + (1-instance->frac) * instance->delayline[(int)instance->i]) * 0.7071;
    float blend = value * 0.7071;

    return forward + blend;
}
