#ifndef MACROS_H_
#define MACROS_H_

#include <main.hpp>

namespace macros {

    extern TaskHandle task;

    // macro identifiers
    enum Macro {
        macro_shoot_both_flags, // shoots top flag, moves forward, and shoots bottom
    };

    // starts a macro
    void startMacro(Macro macro);

    // stops running macro and frees up subsystems
    void stopMacro();

    // macro functions (to run in tasks)
    void shootBothFlags(void *);

}

#endif
