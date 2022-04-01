#ifndef FLANGER_H
#define FLANGER_H

typedef struct {
    int sampling_rate;
    float W; // Delay in seconds
    float f_LFO; // Frequency of LFO

    float NOMINAL_DELAY;
    float CHORUS_WIDTH;

    float f_LFO_samples;
    int delayline_size;

    float *delayline;
    float i_frac;
    float i;
    float frac;
    int sampleNumber;
} Flanger;


void init_flanger(Flanger *instance, int _sampling_rate, float _W, float _f_LFO);

static void insert_in_delayline_flanger(Flanger *instance, float value);

static void print_delayline_flanger(Flanger *instance);

float process_flanger(Flanger *instance, float value);


#endif
