#ifndef MACROS_H_
#define MACROS_H_

#include <main.hpp>

namespace macros {

    extern TaskHandle task;

    // macro identifiers
    enum Macro {
        macro_none,
        macro_shoot_both_flags, // shoots top flag, moves forward, and shoots bottom
        macro_flip_cap, // moves the lift to flip a grounded cap
    };

    // tells which macro is currently running
    extern Macro current_active;

    void init();

    // starts a macro
    void startMacro(Macro macro);

    // stops running macro and frees up subsystems
    void stopMacro();

    // macro functions (to run in tasks)
    void shootBothFlags();
    void flipCap();

}

#endif
