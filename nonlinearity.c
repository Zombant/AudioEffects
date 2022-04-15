#include <portaudio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "nonlinearity.h"
#include "util.h"


float square(float inValue){
    if (inValue > 0) return 1;
    else if (inValue < 0) return -1;
    else return 0;
}

float overdrive(float inValue, float preGain){
    inValue *= preGain;
    inValue = normalize(-1, 1, inValue);
    float inValueAbs = fabsf(inValue);
    if(inValueAbs < (1.0/3.0))
        return 2 * inValue;
    else if(inValueAbs < (2.0 / 3.0))
        return (3 - powf(2 - 3 * inValue, 2))/3;
    else
        return 1;
}
