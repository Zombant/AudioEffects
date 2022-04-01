#ifndef CHORUS_H
#define CHORUS_H

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
} Chorus;


void init_white_chorus(Chorus *instance, int _sampling_rate, float _W, float _f_LFO);

static void insert_in_delayline_chorus(Chorus *instance, float value);

static void print_delayline_chorus(Chorus *instance);

float process_white_chorus(Chorus *instance, float value);

#endif
