#include "subsystems/catapult.hpp"
#include "controller.hpp"

namespace catapult {

    // motor/sensor declarations
    int motors;
    Sensor limit_switch;

    // is the catapult currently shooting?
    bool is_shooting;

    // initialize motors, sensors, etc
    void init() {

        // init motors
        int ports[10] = {7};
        motors = motorInit(ports, NULL, NULL);

        // init limit switch
        limit_switch.init(digital, 1, 0, false, 0, NULL, NULL);

        // init control varaibles
        is_shooting = false;
    }

    // update controller for driver control
    void updateDriverControl() {

        // shoot catapult if button pressed
        if (joystick.btn8D_new == 1) is_shooting = true;
    }

    // update general catapult controller
    void update() {

        // full power if shooting
        if (is_shooting) {
            all_motors[motors].setPower(100, true);
            if (!limit_switch.getValue(0)) is_shooting = false;
        }

        // if not shooting, only give full power when not at load angle
        else all_motors[motors].setPower(15 + 100 * (!limit_switch.getValue(0)), true);
    }
}