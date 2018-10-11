#include "subsystems/cap_manipulator.hpp"
#include "lib/motor_sensor/motor.hpp"
#include "controller.hpp"

namespace cap_manipulator {

    // motor declaration
    int motor;

    // sensor declaration
    Sensor pot;

    // current orientation of flipper
    int orientation = orientation_default;

    // is intake extended?
    bool extended = false;

    // initialize motors, sensors, etc
    void init() {

        // init motor
        int ports[10] = {4};
        pot.init(sensor_potentiometer, 2, 0, false, 1.f, NULL, NULL);
        motor = motorInit(ports, NULL, &pot);

        // init pistons
        pinMode(PNEUMATIC_PORTA, OUTPUT);
        pinMode(PNEUMATIC_PORTB, OUTPUT);
        digitalWrite(PNEUMATIC_PORTA, extended ? HIGH : LOW);
        digitalWrite(PNEUMATIC_PORTB, extended ? HIGH : LOW);
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

    // extends/retracts pneumatic cap intake
    void setExtended(bool extend) {

        // update variable
        extended = extend;

        // move pistons
        digitalWrite(PNEUMATIC_PORTA, extended ? HIGH : LOW);
        digitalWrite(PNEUMATIC_PORTB, extended ? HIGH : LOW);
    }

    // update controller for driver control
    bool has_flipped = false;
    void updateDriverControl() {

        // extend/retract if button released and was not held
        if (joystick.btn6D_new == -1 && !has_flipped) setExtended(!extended);

        // flip if button held for over 500 ms
        if (joystick.btn6D_hold_time >= 500) {
            if (!has_flipped) {
                flip();
                has_flipped = true;
            }
        }
        else has_flipped = false;
    }

    // update general cap flipper controller
    void update(int delta_time) {}
}