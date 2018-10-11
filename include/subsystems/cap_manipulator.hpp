#ifndef CAP_MANIPULATOR_H_
#define CAP_MANIPULATOR_H_

namespace cap_manipulator {

    // pneumatic ports
    #define PNEUMATIC_PORTA 6
    #define PNEUMATIC_PORTB 7

    // orientations for flipper
    enum Orientation {
        orientation_default = 0,
        orientation_flipped = 180,
    };

    // motors
    extern int motor;

    // initializer
    void init();

    // variables
    extern int orientation;
    extern bool extended;

    // flipper control functions
    void gotoOrientation(Orientation orient);
    void flip();

    // intake control functions
    void setExtended(bool extend);

    // controllers
    void updateDriverControl();
    void update(int delta_time);

}

#endif
