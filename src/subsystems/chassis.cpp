#include "subsystems/transmission.hpp"
#include "controller.hpp"

#define _USE_MATH_DEFINES
#include "math.h"

namespace transmission::chassis {

    // motors
    int motor_left;
    int motor_right;

    // sensors
    Sensor gyro;

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
    float orientation = 0;
    float rotation_vel = 0;

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

    // set power of both sides to same value
    void setPower(float p) {
        setPower(p, p);
    }

    // move both sides to different given angles
    void gotoDegrees(float left, float right) {
        position_pid_left.setTarget(left);
        position_pid_right.setTarget(right);
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
        position_pid_left.setTarget(left * 360.f / (WHEEL_SIZE * M_PI));
        position_pid_right.setTarget(right * 360.f / (WHEEL_SIZE * M_PI));
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
    }

    // rotate by given angle
    void rotateBy(float deg) {
        rotateTo(orientation + deg);
    }

    // initializer
    void init() {

        // init motors
        int left_ports[10] = {6};
        int right_ports[10] = {5};
        Sensor left_enc;
        Sensor right_enc;
        left_enc.init(sensor_encoder, 2, 3, false, 7.f / 3.f, NULL, NULL);
        left_enc.init(sensor_encoder, 4, 5, false, 7.f / 3.f, NULL, NULL);
        motor_left = motorInit(left_ports, NULL, &left_enc);
        motor_right = motorInit(right_ports, NULL, &right_enc);

        // init sensors
        gyro.init(sensor_gyro, 1, 0, false, 196, NULL, NULL);

        // init control algorithms
        position_pid_left.init(0.f, 1.f, 0.f, 0.f);
        position_pid_right.init(0.f, 1.f, 0.f, 0.f);
        rotation_pid.init(0.f, 1.f, 0.f, 0.f);
    }

    // update controller for driver control
    void updateDriverControl() {
        setPower(joystick.analogLV, joystick.analogRV);
    }

    // update general chassis controller
    void update(int time_delta) {}
}