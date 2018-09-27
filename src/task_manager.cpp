#include "task_manager.h"

// sensor task
void sensorTask() {
    for (int i = 0; i < all_motors_count; i++) {
        all_motors[i].updateData();
    }

    // custom sensors


    // custom PIDs

}

// motor task
void motorTask() {
    for (int i = 0; i < all_motors_count; i++) {
        all_motors[i].updatePhysical();
    }
}

// driver control task
void controlTask() {
    // stuffs
}

// starts all background tasks
void startAllTasks() {
    sensor_task = taskRunLoop(sensorTask, 5);
    motor_task = taskRunLoop(motorTask, 15);
    control_task = taskRunLoop(controlTask, 15);
}
