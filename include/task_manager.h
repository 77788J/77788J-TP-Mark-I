#ifndef MOTION_PROFILE_H_
#define MOTION_PROFILE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <main.h>

// starts all background tasks
void startAllTasks();

// variables to store tasks
TaskHandle sensor_task; // includes motor data updates
TaskHandle motor_task; // updates physical motors
TaskHandle control_task; // overall driver control

#ifdef __cplusplus
}
#endif

#endif
