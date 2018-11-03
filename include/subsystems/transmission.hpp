#ifndef TRANSMISSION_H_
#define TRANSMISSION_H_

#include <lib/motor_sensor/motor.hpp>
#include <lib/motor_sensor/sensor.hpp>
#include <lib/control/pid.hpp>

namespace transmission {

    // generic motors
    extern int motor_top_left;
    extern int motor_btm_left;
    extern int motor_top_right;
    extern int motor_btm_right;

    // generic control functions
    void setPriorityRatio(float chassis_part, float lift_part);

    // chassis-specific stuff
    namespace chassis {

        extern bool in_macro;

        // constants
        #define WHEEL_SIZE 4.125f

        // motors
        extern int motor_left;
        extern int motor_right;
        
        // sensors
        extern Sensor gyro;
        extern Sensor sonar;

        // control algorithms
        extern Pid position_pid_left;
        extern Pid position_pid_right;
        extern Pid rotation_pid;

        // control types
        enum ControlType {
            control_manual,
            control_position,
            control_rotation
        };

        // sides
        enum Side {
            side_intake,
            side_shooter_flipper
        };

        // variables
        extern float priority;
        extern float desired_power_left;
        extern float desired_power_right;
        extern float left_pos_deg;
        extern float right_pos_deg;
        extern float left_pos_inches;
        extern float right_pos_inches;
        extern float left_vel;
        extern float right_vel;
        extern Side front_side;
        extern ControlType control_type;

        // control functions
        void resetPosition();
        void resetOrientation();
        void setFront(Side side);
        void setPowerLeft(float p);
        void setPowerRight(float p);
        void setPower(float p);
        void setPower(float l, float r);
        void gotoDegrees(float left, float right);
        void gotoDegrees(float dist);
        void gotoInches(float left, float right);
        void gotoInches(float dist);
        void moveDegrees(float dist);
        void moveInches(float dist);
        void rotateTo(float deg);
        void rotateBy(float deg);
        
        // wait for current activity to finish
        void waitForCompletion(float precision, int timeout);

        // initializer
        void init();

        // controllers
        void updateDriverControl();
        void updateStats(int time_delta);
        void update(int delta_time);
    }

    // lift-specific stuff
    namespace lift {
        
        extern bool in_macro;

        // constants
        #define BOTTOM_BAR_LEN 12.5f
        #define TOP_BAR_LEN 12.5f
        #define NEUTRAL_HEIGHT 19.f
        #define MIN_ANGLE -42.f
        #define MAX_LEGAL_ANGLE -24.f
        #define DESCORE_ANGLE -15.f
        #define MAX_ANGLE 41.f

        // pid
        extern Pid pid;

        // control algorithms
        extern Sensor left_encoder;
        extern Sensor right_encoder;

        // variables
        extern float desired_power;
        extern float priority;
        extern float angle;
        extern float height;
        extern float vel;

        // control functions
        void setPower(float p);
        void moveInches(float dist);
        void moveDegrees(float dist);
        void gotoInches(float dist);
        void gotoDegrees(float dist);
        
        // wait for current activity to finish
        void waitForCompletion(float precision, int timeout);

        // initializer
        void init();

        // controllers
        void updateDriverControl();
        void updateStats(int time_delta);
        void update(int delta_time);
    }

    // initializer
    void init();

    // controllers
    void updateDriverControl();
    void update(int delta_time);

}

#endif
