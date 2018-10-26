#include "macros.hpp"
#include "subsystems/subsystems.hpp"

namespace macros {

  // holds macro task
  TaskHandle task;

  // tells what macro is currently running
  Macro current_active = macro_none;

  void macroFunction() {
    switch (current_active) {
      case (macro_none): break;
      case (macro_shoot_both_flags): shootBothFlags();
      case (macro_flip_cap): flipCap();
      default: break;
    }

    current_active = macro_none;
  }

  void init() {
    // current_active = macro_none;
    // task = taskRunLoop(macroFunction, 10);
  }
  
  // starts a macro
  void startMacro(Macro macro) {
    if (current_active != macro_none) stopMacro();
    current_active = macro;
  }

  // stops the current macro and re-enables all subsystems
  void stopMacro() {

    // restart task
    if (taskGetState(task) != TASK_DEAD) taskDelete(task);
    task = taskRunLoop(macroFunction, 10);

    // re-enable subsystems
    ball_intake::in_macro = false;
    catapult::in_macro = false;
    chassis::in_macro = false;
    lift::in_macro = false;

    // update active variable
    current_active = macro_none;
  }
}