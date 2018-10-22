#include "subsystems/catapult.hpp"
#include "subsystems/ball_intake.hpp"
#include "lib/motor_sensor/motor.hpp"
#include "controller.hpp"

namespace catapult {
    
    bool in_macro = false;

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
        limit_switch.init(sensor_digital, 1, 0, false, 0, NULL, NULL);

        // init control varaibles
        is_shooting = false;
    }

    int time_since_shot = 0;

    // fire catapult
    void fire() {
        time_since_shot = 0;
        is_shooting = true;
    }
    
    // wait until back in load position
    void waitForLoadPos(int timeout) {
        int t = 0;
        while (!limit_switch.getValue(0) && t < timeout) {
            delay(1);
            ++t;
        }
    }

    // update controller for driver control
    void updateDriverControl() {

        // shoot catapult if button pressed
        if (joystick.btn8D_new == 1) {
            ball_intake::setDirection(-1);
            delay(300);
            fire();
            ball_intake::setDirection(0);
        }
    }

    // update general catapult controller
    void update(int delta_time) {

        // full power if shooting
        if (is_shooting) {
            all_motors[motors].setPower(100, true);
            if (!limit_switch.getValue(0)) is_shooting = false;
        }

        // if not shooting, only give full power when not at load angle
        else all_motors[motors].setPower((float) (10 + (!limit_switch.getValue(0)) * (65 + (float)(750 - time_since_shot) * 0.04666666666f)), true);

        time_since_shot += delta_time;
        if (time_since_shot > 750) time_since_shot = 750;
    }
}