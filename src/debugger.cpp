#include "controller.hpp"
#include "subsystems/subsystems.hpp"
#include "lib/motor_sensor/motor.hpp"

void debugTask() {
    printf("pot: %f\n", all_motors[cap_manipulator::motor].getPosition());
}