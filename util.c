#include <math.h>

float normalize(float min, float max, float input) {
    return (input - ((min + max) / 2)) / ((max - min) / 2);
}
