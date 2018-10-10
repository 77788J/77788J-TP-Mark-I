#include "subsystems/cap_flipper.hpp"
#include "lib/motor_sensor/motor.hpp"
#include "controller.hpp"

namespace cap_flipper {

    // motor declaration
    int motor;

    // sensor declaration
    Sensor pot;

    // current orientation of flipper
    int orientation = orientation_default;

    // initialize motors, sensors, etc
    void init() {

        // init motor
        int ports[10] = {4};
        pot.init(sensor_potentiometer, 2, 0, false, 1.f, NULL, NULL);
        motor = motorInit(ports, NULL, &pot);
    }

    // rotate to specified orientation
    void gotoOrientation(Orientation orient) {
        all_motors[motor].pid.setTarget(orientation);
    }

    // flip to opposite orientation (or default if at an abnormal orientation)
    void flip() {
        gotoOrientation(
            (orientation == orientation_default) ? orientation_flipped
                                                 : orientation_default
        );
    }

    // update controller for driver control
    void updateDriverControl() {

        // flip if button pressed
        if (joystick.btn6D_new == 1) flip();
    }

    // update general cap flipper controller
    void update(int delta_time) {}
}