#include "subsystems/transmission.hpp"
#include "macros.hpp"
#include "controller.hpp"

#define _USE_MATH_DEFINES
#include "math.h"

namespace transmission::chassis {
    
    bool in_macro = false;

    // motors
    int motor_left;
    int motor_right;

    // sensors
    Sensor gyro;
    Sensor left_enc;
    Sensor right_enc;

    // control algorithms
    Pid position_pid_left;
    Pid position_pid_right;
    Pid rotation_pid;

    // variables
    float priority = .5f;
    float desired_power_left = 0;
    float desired_power_right = 0;
    float left_pos_deg = 0;
    float right_pos_deg = 0;
    float left_pos_inches = 0;
    float right_pos_inches = 0;
    float left_vel = 0;
    float right_vel = 0;
    float left_pos_offset = 0;
    float right_pos_offset = 0;
    Side front_side = side_shooter_flipper;
    ControlType control_type = control_manual;

    // reset relative position to 0
    void resetPosition() {
        left_pos_offset = left_pos_deg;
        right_pos_offset = right_pos_deg;
    }

    // reset relative orientation to 0
    void resetOrientation() {
        gyroReset(gyro.gyro_sensor);
    }

    // determines whether the front is the intake or shooter/flipper
    void setFront(Side side) {
        front_side = side;
    }

    // set power of left side
    void setPowerLeft(float p) {
        desired_power_left = p;
    }

    // set power of right side
    void setPowerRight(float p) {
        desired_power_right = p;
    }

    // set power of both sides to different values
    void setPower(float l, float r) {
        setPowerLeft(l);
        setPowerRight(r);
    }

    // set power of both sides to different values, accounting for front preference
    void setPower(float l, float r, bool a) {
        if (front_side == side_intake) {
            setPowerLeft(l);
            setPowerRight(r);
        }
        else {
            setPowerLeft(-r);
            setPowerRight(-l);
        }
    }

    // set power of both sides to same value
    void setPower(float p) {
        setPower(p, p);
    }

    // move both sides to different given angles
    void gotoDegrees(float left, float right) {
        position_pid_left.setTarget(left);
        position_pid_right.setTarget(right);
        control_type = control_position;
    }

    // move both sides to same given angle
    void gotoDegrees(float dist) {
        gotoDegrees(dist, dist);
    }

    // move both sides by given angle
    void moveDegrees(float dist) {
        gotoDegrees(left_pos_deg + dist, right_pos_deg + dist);
    }

    // move both sides to different given distances
    void gotoInches(float left, float right) {
        gotoDegrees(left * 360.f / (WHEEL_SIZE * M_PI), right * 360.f / (WHEEL_SIZE * M_PI));
    }

    // move both sides to same given distance
    void gotoInches(float dist) {
        gotoInches(dist, dist);
    }

    // move both sides by given distance
    void moveInches(float dist) {
        gotoInches(left_pos_inches + dist, right_pos_inches + dist);
    }

    // rotate to given angle
    void rotateTo(float deg) {
        rotation_pid.setTarget(deg);
        control_type = control_rotation;
    }

    // rotate by given angle
    void rotateBy(float deg) {
        rotateTo(gyro.getValue(0) + deg);
    }

    // wait for current activity to finish
    void waitForCompletion(float precision, int timeout) {
        int elapsed_time = 0;
        while (true) {
            if (elapsed_time > timeout) break;
            if (control_type == control_manual) break;
            if (control_type == control_position && !(position_pid_left.isAtTarget(precision) && position_pid_right.isAtTarget(precision))) break;
            if (control_type == control_rotation && !rotation_pid.isAtTarget(precision)) break;
            delay(5);
            elapsed_time += 5;
        }
    }

    // initializer
    void init() {

        // init motors
        int left_ports[10] = {6};
        int right_ports[10] = {5};
        right_enc.init(sensor_encoder, 2, 3, false, 7.f / 3.f, NULL, NULL);
        left_enc.init(sensor_encoder, 4, 5, false, 7.f / 3.f, NULL, NULL);
        motor_left = motorInit(left_ports, NULL, &left_enc);
        motor_right = motorInit(right_ports, NULL, &right_enc);
        all_motors[motor_right].reversed = true;

        // init sensors
        gyro.init(sensor_gyro, 1, 0, false, 196.f, NULL, NULL);

        // init control algorithms
        position_pid_left.init(0.f, 1.f, 0.f, 0.f);
        position_pid_right.init(0.f, 1.f, 0.f, 0.f);
        rotation_pid.init(0.f, 1.f, 0.f, 0.f);
    }

    // update controller for driver control
    void updateDriverControl() {
        
        // stop macro if in macro and driven
        if (in_macro && (fabs(joystick.analogLV) > 0 || fabs(joystick.analogRV) > 0)) macros::stopMacro();
        
        // toggle front if correct buttons pressed
        if (joystick.btn7L && joystick.btn7R_new == 1) setFront(front_side == side_intake ? side_shooter_flipper : side_intake);

        // drive chassis
        setPower(joystick.analogLV, joystick.analogRV, true);
        control_type = control_manual;
    }

    // update chassis stats that don't fit in sensors
    void updateStats(int time_delta) {
    
        // calculate left side stats
        float trans_pos = (-all_motors[motor_top_left].getPosition() + all_motors[motor_btm_left].getPosition()) * .5f;
        float new_pos = all_motors[motor_left].getPosition() * .5f + trans_pos * .5f;
        left_vel = left_vel * .5f + (new_pos - left_pos_deg) * .5f * 166.666666667f / time_delta;
        left_pos_deg = new_pos - left_pos_offset;
        left_pos_inches = WHEEL_SIZE * M_PI * left_pos_deg / 360.f;

        // calculate right side stats
        trans_pos = (-all_motors[motor_top_right].getPosition() + all_motors[motor_btm_right].getPosition()) * .5f;
        new_pos = all_motors[motor_right].getPosition() * .5f + trans_pos * .5f;
        right_vel = right_vel * .5f + (new_pos - right_pos_deg) * .5f * 166.666666667f / time_delta;
        right_pos_deg = new_pos - right_pos_offset;
        right_pos_inches = WHEEL_SIZE * M_PI * right_pos_deg / 360.f;
    }

    // update general chassis controller
    void update(int time_delta) {

        // set power based on PIDs
        switch (control_type) {
            case (control_manual): break;
            case (control_position): setPower(position_pid_left.get(), position_pid_right.get()); break;
            case (control_rotation): setPower(rotation_pid.get(), -rotation_pid.get()); break;
        }
    }
}