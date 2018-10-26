#include "subsystems/transmission.hpp"
#include "macros.hpp"
#include "controller.hpp"

#define _USE_MATH_DEFINES
#include "math.h"

namespace transmission::lift {
    
    bool in_macro = false;

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
        return NEUTRAL_HEIGHT + sin(angle_rad) * BOTTOM_BAR_LEN + sin(angle_rad * 2.f) * TOP_BAR_LEN; // calculate height
    }

    // calculate angle of lift given specified height
    float calcAngle(float height) {
        float a = asin((height - NEUTRAL_HEIGHT) / (BOTTOM_BAR_LEN + TOP_BAR_LEN)); // calculate angle
        return a * (180.f / M_PI); // convert to degrees
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

    // wait for current activity to finish
    void waitForCompletion(float precision, int timeout) {
        int elapsed_time = 0;
        while (true) {
            if (elapsed_time > timeout) break;
            if (pid.isAtTarget(precision)) break;
            delay(5);
            elapsed_time += 5;
        }
    }

    // initializer
    void init() {

        // init sensors
        pot.init(sensor_potentiometer, 2, 0, false, 0, NULL, NULL);

        // init control algorithms
        pid.init(MIN_ANGLE, 1.f, 0.f, 0.f);
        pid.setTarget(MIN_ANGLE);
    }

    // update controller for driver control
    void updateDriverControl() {
        
        // stop macro if in macro and driven
        if (in_macro && (
            joystick.btn5U_new == 1 || 
            joystick.btn5D_new == 1 || 
            joystick.btn7D_new == 1 || 
            joystick.btn7R_new == 1 || 
            joystick.btn7L_new == 1 || 
            joystick.btn7U_new == 1
        ))
            macros::stopMacro();

        // precise control
        if (joystick.btn5U_new == 1) gotoDegrees(MAX_ANGLE);
        if (joystick.btn5D_new == 1) gotoDegrees(MIN_ANGLE);
        if (joystick.btn5U_new == -1 || joystick.btn5D_new == -1) gotoDegrees(angle);

        // function control
        if (joystick.btn7D) macros::startMacro(macros::macro_flip_cap); // flip cap
        if (joystick.btn7R) gotoDegrees(MAX_LEGAL_ANGLE); // goto highest height under 18"
        if (joystick.btn7U) gotoDegrees(DESCORE_ANGLE); // lower all the way
    }
    
    // update lift stats that don't fit in sensors
    void updateStats(int time_delta) {
    
        // calculate angle and height
        float trans_pos = (all_motors[motor_top_left].getPosition() + all_motors[motor_btm_left].getPosition()) * .5f;
        float new_pos = trans_pos;
        vel = vel * .5f + (new_pos - angle) * .5f * 166.666666667f / time_delta;
        angle = new_pos + MIN_ANGLE;
        height = calcHeight(angle);
    }

    // update general chassis controller
    void update(int time_delta) {
        setPower(pid.get());
    }
}