#ifndef AUTONS_H_
#define AUTONS_H_

namespace autons {

    enum Side {
        side_red = false,
        side_blue = true
    };

    void flagSideDefault(Side side, bool park);
    void capSideDefault(Side side, bool park);
    void kyleCompliment(Side side);

}

#endif
