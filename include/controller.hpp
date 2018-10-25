#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <lib/joystick.hpp>

// global reference to joystick
extern Joystick joystick;

// starts all background tasks
void startAllTasks();

// stupid task that I put in a seperate file cause I like to make my life hard
void debugTask();

// variables to store tasks
extern TaskHandle sensor_task; // includes motor data updates
extern TaskHandle motor_task; // updates physical motors
extern TaskHandle control_task; // overall driver control
extern TaskHandle debug_task; // debugging task

#endif
