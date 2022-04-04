#ifndef ALLPASS_H
#define ALLPASS_H

typedef struct {
    float prevY;
    float prevX;
    float alpha;
} FirstOrderAllpass;

typedef struct {
    float prevY1;
    float prevY2;
    float prevX1;
    float prevX2;
    float a1;
    float a2;
    float b0;
    float b1;
    float b2;
} SecondOrderAllpass;

void init_allpass1(FirstOrderAllpass *instance, float alpha);

float allpass1(FirstOrderAllpass *instance, float value);

float lowpass1(FirstOrderAllpass *instance, float value);

float highpass1(FirstOrderAllpass *instance, float value);

void init_allpass2(SecondOrderAllpass *instance, float sampling_rate, float fc, float fb);

float allpass2(SecondOrderAllpass *instance, float value);

float bandpass2(SecondOrderAllpass *instance, float value);

float bandstop2(SecondOrderAllpass *instance, float value);

#endif
