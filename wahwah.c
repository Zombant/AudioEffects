#include <portaudio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "wahwah.h"
#include "allpass.h"

//TODO: parameterize fb and oscilation frequency
void init_wahwah(WahWah *instance, int _sampling_rate, float _mix, float _min_f_LFO, float _max_f_LFO, float _LFO_Frequency){
    instance->sampling_rate = _sampling_rate;
    instance->min_f_LFO = _min_f_LFO;
    instance->max_f_LFO = _max_f_LFO;
    instance->LFO_Frequency = _LFO_Frequency;
    instance->filter = malloc(sizeof(SecondOrderAllpass));
    init_allpass2(instance->filter, _sampling_rate, _min_f_LFO, 100);
    instance->mix = _mix;

    instance->i = 0;

}

float process_wahwah(WahWah *instance, float value){

    float amplitude = (instance->max_f_LFO - instance->min_f_LFO) * 0.5;
    float new_fc = amplitude * sinf(instance->LFO_Frequency/instance->sampling_rate * 2 * M_PI * instance->i) + amplitude + instance->min_f_LFO;

    instance->i++;

    init_allpass2(instance->filter, instance->sampling_rate, new_fc, 100);

    float filter_result = bandpass2(instance->filter, value);

    return value * (1-instance->mix) + filter_result * instance->mix;

}

//TODO: Make manual wahwah
