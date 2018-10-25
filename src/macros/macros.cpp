#include "macros.hpp"
#include "subsystems/subsystems.hpp"

namespace macros {

  // holds macro task
  TaskHandle task;

  // tells what macro is currently running
  Macro current_active = macro_none;
  
  // starts a macro
  void startMacro(Macro macro) {
    current_active = macro;

    switch (macro) {
      case (macro_none): break;
      case (macro_shoot_both_flags): task = taskCreate(shootBothFlags, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
      case (macro_flip_cap): task = taskCreate(flipCap, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);
      default: break;
    }
  }

  // stops the current macro and re-enables all subsystems
  void stopMacro() {

    // kill task
    taskDelete(task);

    // re-enable subsystems
    ball_intake::in_macro = false;
    catapult::in_macro = false;
    chassis::in_macro = false;
    lift::in_macro = false;

    // update active variable
    current_active = macro_none;
  }
}