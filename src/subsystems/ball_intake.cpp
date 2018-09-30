#include "subsystems/ball_intake.hpp"
#include "lib/motor_sensor/motor.hpp"
#include "controller.hpp"

namespace ball_intake {

    // motor declaration
    int motor;

    // is the ball intaking currently intaking?
    int intake_dir;

    // initialize motor and varaibles
    void init() {

        // init motors
        int ports[10] = {1};
        motor = motorInit(ports, NULL, NULL);

        // init control varaibles
        intake_dir = 0;
    }

    // change the direction in which the intake spins
    void setDirection(int dir) {
        intake_dir = dir;
    }

    // update controller for driver control
    void updateDriverControl() {
        if (joystick.btn6U_new == 1) setDirection( 1 - abs(intake_dir)); // toggle positive
        if (joystick.btn8L_new == 1) setDirection(-1 + abs(intake_dir)); // toggle negative
    }

    // update general ball intake controller
    void update() {
        all_motors[motor].setPower(100 * intake_dir, true);
    }
}