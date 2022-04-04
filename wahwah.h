#ifndef WAHWAH_H
#define WAHWAH_H

#include "allpass.h"

typedef struct {
    int sampling_rate;
    float current_f_LFO;
    float min_f_LFO;
    float max_f_LFO;
    float LFO_Frequency;
    float mix;

    SecondOrderAllpass *filter;

    int i;


} WahWah;


void init_wahwah(WahWah *instance, int _sampling_rate, float _mix, float _min_f_LFO, float _max_f_LFO, float _LFO_Frequency);

float process_wahwah(WahWah *instance, float value);

#endif
