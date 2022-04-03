#include <portaudio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "allpass.h"

void init_allpass1(FirstOrderAllpass *instance, float alpha){
    instance->alpha = alpha;
    instance->prevX = 0;
    instance->prevY = 0;
}

float allpass1(FirstOrderAllpass *instance, float value){
    float result = -instance->alpha * instance->prevY + instance->alpha * value + instance->prevX;
    instance->prevX = value;
    instance->prevY = result;

    return result;
}

float lowpass1(FirstOrderAllpass *instance, float value){
    return 0.5 * (value + allpass1(instance, value));
}

float highpass1(FirstOrderAllpass *instance, float value){
    return 0.5 * (value - allpass1(instance, value));
}

void init_allpass2(SecondOrderAllpass *instance, float sampling_rate, float fc, float fb){
    float tmp_tan = tan(M_PI * fb / sampling_rate);
    
    float c = (tmp_tan - 1) / (tmp_tan + 1);

    float d = -cos(2 * M_PI * fc / sampling_rate);

    instance->a1 = d * (1 - c);
    instance->a2 = -c;
    instance->b0 = -c;
    instance->b1 = d * (1 - c);
    instance->b2 = 1;
}

float allpass2(SecondOrderAllpass *instance, float value){
    float b0 = instance->b0;
    float b1 = instance->b1;
    float b2 = instance->b2;
    float a1 = instance->a1;
    float a2 = instance->a2;

    float result = b0 * value + b1 * instance->prevX1 + b2 * instance->prevX2 - a1 * instance->prevY1 - a2 * instance->prevY2;

    instance->prevX2 = instance->prevX1;
    instance->prevX1 = value;
    instance->prevY2= instance->prevY1;
    instance->prevY1 = result;

    
    return result;
}
