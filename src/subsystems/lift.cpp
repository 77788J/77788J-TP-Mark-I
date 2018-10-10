#include "subsystems/transmission.hpp"
#include "controller.hpp"

#define _USE_MATH_DEFINES
#include "math.h"

namespace transmission::lift {

    // sensors
    Sensor pot;

    // control algorithms
    Pid pid;

    // variables
    float priority = .5f;
    float desired_power = 0;
    float angle = MIN_ANGLE;
    float height = 0;
    float vel = 0;

    // calculate height of lift given specific angle
    float calcHeight(float angle) {
        float angle_rad = angle * (M_PI / 180.f); // convert to radians
        return NEUTRAL_HEIGHT + sin(angle_rad) * BOTTOM_BAR_LEN + sin(angle_rad) * TOP_BAR_LEN; // calculate height
    }

    // calculate angle of lift given specified height
    float calcAngle(float height) {
        float angle = asin((height - NEUTRAL_HEIGHT) / (BOTTOM_BAR_LEN + TOP_BAR_LEN)); // calculate angle
        return angle * (180.f / M_PI); // convert to degrees
    }

    // set power of lift
    void setPower(float p) {
        desired_power = p;
    }

    // goto specified angle
    void gotoDegrees(float dist) {
        pid.setTarget(dist);
    }

    // goto specified height
    void gotoInches(float dist) {
        pid.setTarget(calcAngle(dist));
    }

    // move by a specified angle
    void moveDegrees(float dist) {
        gotoDegrees(angle + dist);
    }

    // move by a specified height
    void moveInches(float dist) {
        gotoInches(height + dist);
    }

    // initializer
    void init() {

        // init sensors
        pot.init(sensor_potentiometer, 2, 0, false, 0, NULL, NULL);

        // init control algorithms
        pid.init(MIN_ANGLE, 1.f, 0.f ,0.f);
    }

    // update controller for driver control
    void updateDriverControl() {
    // setPower((joystick.btn5U - joystick.btn5D) * 100);

        if (joystick.btn5U_new == 1) gotoDegrees(MAX_ANGLE);
        if (joystick.btn5D_new == 1) gotoDegrees(MIN_ANGLE);
        if (joystick.btn5U_new == -1 || joystick.btn5D_new == -1) gotoDegrees(angle);
    }
    
    // update lift stats that don't fit in sensors
    void updateStats(int time_delta) {
    
        // calculate angle and height
        float trans_pos = (all_motors[motor_top_left].getPosition() + all_motors[motor_btm_left].getPosition()) * .5f;
        float new_pos = pot.getValue(0) * .2f + trans_pos * .8f;
        vel = vel * .5f + (new_pos - angle) * .5f * 166.666666667f / time_delta;
        angle = new_pos;
        height = calcHeight(angle);
    }

    // update general chassis controller
    void update(int time_delta) {
        setPower(pid.get());
    }
}