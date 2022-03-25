#ifndef VIBRATO_H
#define VIBRATO_H

void init_vibrato(int _sampling_rate, float _W, int _f_LFO);

static void insert_in_delayline(float value);

static void print_delayline();

float process_vibrato(float value);

#endif
