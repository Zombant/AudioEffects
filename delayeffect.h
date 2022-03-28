#ifndef VIBRATO_H
#define VIBRATO_H

typedef struct {
    int sampling_rate;
    float W; // Delay in seconds
    int f_LFO; // Frequency of LFO

    float NOMINAL_DELAY;
    float CHORUS_WIDTH;

    float f_LFO_samples;
    int delayline_size;

    float *delayline;
    float i_frac;
    float i;
    float frac;
    int sampleNumber;
} DelayEffect;

void init_delay_effect(DelayEffect *instance, int _sampling_rate, float _W, int _f_LFO);

static void insert_in_delayline(DelayEffect *instance, float value);

static void print_delayline(DelayEffect *instance);

float process_vibrato(DelayEffect *instance, float value);

float process_flanger(DelayEffect *instance, float value);

#endif
