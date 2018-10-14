#ifndef AUTONS_H_
#define AUTONS_H_

#define RED = 0
#define BLUE = 1

namespace autons {

    extern bool selected;
    extern int color;
    extern int side;
    extern int park;

    void flagSideDefault(int side, bool park);
    void capSideDefault(int side, bool park);
    void kyleCompliment(int side);

}

#endif
