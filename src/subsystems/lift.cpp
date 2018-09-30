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
    float angle = MIN_ANGLE;
    float height = 0;

    // private variables
    float desired_power = 0;

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
        setPower((joystick.btn5U - joystick.btn5D) * 100);
    }

    // update general chassis controller
    void update(int time_delta) {}
}