#include "controller.hpp"
#include "subsystems/subsystems.hpp"
#include "lib/motor_sensor/motor.hpp"

void debugTask() {
    printf("LEFT: %f\nRIGHT: %f\n\n", chassis::left_pos_deg, chassis::right_pos_deg);
}