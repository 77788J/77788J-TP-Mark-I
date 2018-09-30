#ifndef TRANSMISSION_H_
#define TRANSMISSION_H_

#include <lib/motor_sensor/motor.hpp>
#include <lib/motor_sensor/sensor.hpp>
#include <lib/control/pid.hpp>

namespace transmission {

    // generic motors/sensors
    extern int motors;
    extern Sensor pot;

    // generic control functions
    void setPriorityRatio;

    // chassis-specific stuff
    namespace chassis {

        // constants
        #define WHEEL_SIZE 4.125f

        // sensors
        extern Sensor gyro;
        extern Sensor left_enc;
        extern Sensor right_enc;

        // control algorithms
        extern Pid position_pid;
        extern Pid rotation_pid;

        // variables
        extern float priority;
        extern float left_pos_deg;
        extern float right_pos_deg;
        extern float left_pos_inches;
        extern float right_pos_inches;
        extern float left_vel;
        extern float right_vel;
        extern float orientation;
        extern float rotation_vel;

        // control functions
        void setPower(float l, float r);
        void moveInches(float dist);
        void moveDegrees(float dist);
        void gotoInches(float dist);
        void gotoDegrees(float dist);
        void rotate(float deg);
    }

    // lift-specific stuff
    namespace lift {

        // constants
        #define BOTTOM_BAR_LEN 12.5f
        #define TOP_BAR_LEN 17.5f
        #define NEUTRAL_HEIGHT 19.f
        #define MIN_ANGLE -45.f
        #define MAX_ANGLE 60.f

        // sensors
        extern Sensor pot;

        // control algorithms
        extern Pid pid;

        // variables
        extern float priority;
        extern float angle;
        extern float height;

        // control functions
        void setPower(float p);
        void moveInches(float dist);
        void moveDegrees(float dist);
        void gotoInches(float dist);
        void gotoDegrees(float dist);
    }

    // initializer
    void init();

    // controllers
    void updateDriverControl();
    void update(int delta_time);

}

#endif
