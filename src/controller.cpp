#include "controller.hpp"
#include "main.hpp"
#include "subsystems/subsystems.hpp"
#include "lib/joystick.hpp"
#include "macros.hpp"
#include "lib/motor_sensor/motor.hpp"
#include "lib/motor_sensor/sensor.hpp"

// task update intervals
#define TASK_SENSOR_INTERVAL 5
#define TASK_PHYSICAL_MOTOR_INTERVAL 15
#define TASK_CONTROL_INTERVAL 15
#define TASK_DEBUG_INTERVAL 100

// variables to store tasks
TaskHandle sensor_task; // includes motor data updates
TaskHandle motor_task; // updates physical motors
TaskHandle control_task; // overall driver control
TaskHandle debug_task; // debugging task

// global joystick reference
Joystick joystick;

// sensor task
void sensorTask() {

    // sensors attached to motors
    for (int i = 0; i < all_motors_count; i++) {
        all_motors[i].updateStats(TASK_SENSOR_INTERVAL);
    }

    // custom sensors
    catapult::limit_switch.update(TASK_SENSOR_INTERVAL);
    chassis::gyro.update(TASK_SENSOR_INTERVAL);
    lift::left_encoder.update(TASK_SENSOR_INTERVAL);
    lift::right_encoder.update(TASK_SENSOR_INTERVAL);
    ball_intake::ball_identifier.update(TASK_SENSOR_INTERVAL);

    // general subsystem stats
    chassis::updateStats(TASK_CONTROL_INTERVAL);
    lift::updateStats(TASK_CONTROL_INTERVAL);

    // custom PIDs
    chassis::position_pid_left.update(chassis::left_pos_deg, chassis::left_vel, TASK_SENSOR_INTERVAL);
    chassis::position_pid_right.update(chassis::right_pos_deg, chassis::right_vel, TASK_SENSOR_INTERVAL);
    chassis::rotation_pid.update(chassis::gyro.getValue(0), chassis::gyro.getVelocity(), TASK_SENSOR_INTERVAL);
    lift::pid.update(lift::angle, lift::vel, TASK_SENSOR_INTERVAL);

}

// motor task
void motorTask() {
    for (int i = 0; i < all_motors_count; i++) {
        all_motors[i].updatePhysical(TASK_PHYSICAL_MOTOR_INTERVAL);
    }
}

// subystem control task
void controlTask() {

    // driver control
    if (isEnabled() && !isAutonomous()) {

        // joystick update
        joystick.update();

        // subsystems
        ball_intake::updateDriverControl();
        // cap_manipulator::updateDriverControl();
        catapult::updateDriverControl();
        chassis::updateDriverControl();
        lift::updateDriverControl();
        transmission::updateDriverControl();
    }

    // general control
    ball_intake::update();
    // cap_manipulator::update(TASK_CONTROL_INTERVAL);
    catapult::update(TASK_CONTROL_INTERVAL);
    chassis::update(TASK_CONTROL_INTERVAL);
    lift::update(TASK_CONTROL_INTERVAL);
    transmission::update(TASK_CONTROL_INTERVAL);
}

// starts all background tasks
void startAllTasks() {
    sensor_task = taskRunLoop(sensorTask, TASK_SENSOR_INTERVAL);
    motor_task = taskRunLoop(motorTask, TASK_PHYSICAL_MOTOR_INTERVAL);
    control_task = taskRunLoop(controlTask, TASK_CONTROL_INTERVAL);
    debug_task = taskRunLoop(debugTask, TASK_DEBUG_INTERVAL);
    // macros::init();
}
