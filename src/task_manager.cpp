#include "task_manager.hpp"
#include "lib/motor_sensor/motor.hpp"
#include "lib/motor_sensor/sensor.hpp"

#define SENSOR_INTERVAL 5
#define PHYSICAL_MOTOR_INTERVAL 15
#define CONTROL_INTERVAL 15

// sensor task
void sensorTask() {
    for (int i = 0; i < all_motors_count; i++) {
        all_motors[i].updateStats(SENSOR_INTERVAL);
    }

    // custom sensors


    // custom PIDs

}

// motor task
void motorTask() {
    for (int i = 0; i < all_motors_count; i++) {
        all_motors[i].updatePhysical(PHYSICAL_MOTOR_INTERVAL);
    }
}

// driver control task
void controlTask() {
    // stuffs
}

// starts all background tasks
void startAllTasks() {
    sensor_task = taskRunLoop(sensorTask, SENSOR_INTERVAL);
    motor_task = taskRunLoop(motorTask, PHYSICAL_MOTOR_INTERVAL);
    control_task = taskRunLoop(controlTask, CONTROL_INTERVAL);
}
