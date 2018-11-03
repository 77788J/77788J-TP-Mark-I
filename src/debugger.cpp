#include "controller.hpp"
#include "subsystems/subsystems.hpp"
#include "lib/motor_sensor/motor.hpp"

void debugTask() {
    printf("LIFT: %f\n      %f\nCHASSIS: %f, %f\n         %f, %f\n         %f\n\n", lift::angle, lift::vel, chassis::left_pos_inches, chassis::right_pos_inches, chassis::left_pos_deg, chassis::right_pos_deg, chassis::gyro.getValue(0));
}