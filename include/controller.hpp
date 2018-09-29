#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <lib/joystick.hpp>

// global reference to joystick
extern Joystick joystick;

// starts all background tasks
void startAllTasks();

// variables to store tasks
extern TaskHandle sensor_task; // includes motor data updates
extern TaskHandle motor_task; // updates physical motors
extern TaskHandle control_task; // overall driver control

#ifdef __cplusplus
}
#endif

#endif
