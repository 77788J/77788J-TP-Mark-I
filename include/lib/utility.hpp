#ifndef UTILITY_H_
#define UTILITY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.hpp>

int sign(float x);
float min(float a, float b);
float max(float a, float b);
float minMag(float a, float b);
float maxMag(float a, float b);
float median(float a, float b, float c);
float clamp(float val, float min, float max);
float wrap(float val, float min, float max);
float calcRpm(float error, int interval);

#ifdef __cplusplus
}
#endif

#endif
