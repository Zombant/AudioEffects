#ifndef VIBRATO_H
#define VIBRATO_H


#define Fs 44100 // Sampling rate
#define NUM_SECONDS 5
#define W 0.005 // Delay in seconds
#define f_LFO 5 // Frequency of the LFO

/*extern float NOMINAL_DELAY;
extern float CHORUS_WIDTH;
extern float f_LFO_samples;
extern int delayline_size;

extern float *delayline;
extern float i_frac;
extern float i;
extern float frac;
extern float sampleNumber;*/

void init_vibrato();

static void insert_in_delayline(float value);

static void print_delayline();

float process_vibrato(float value);

#endif
