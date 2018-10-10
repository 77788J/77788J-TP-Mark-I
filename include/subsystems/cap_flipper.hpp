#ifndef CAP_FLIPPER_H_
#define CAP_FLIPPER_H_

namespace cap_flipper {

    enum Orientation {
        orientation_default = 0,
        orientation_flipped = 180,
    };

    // motors/sensors
    extern int motor;

    // initialozer
    void init();

    // variables
    extern int orientation;

    // control functions
    void gotoOrientation(Orientation orient);
    void flip();

    // controllers
    void updateDriverControl();
    void update(int delta_time);

}

#endif
