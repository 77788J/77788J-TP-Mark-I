#include "macros.hpp"
#include "subsystems/subsystems.hpp"

namespace macros {

  TaskHandle task;
  
  // starts a macro
  void startMacro(Macro macro) {
    switch (macro) {

      case (macro_shoot_both_flags): task = taskCreate(shootBothFlags, TASK_DEFAULT_STACK_SIZE, NULL, TASK_PRIORITY_DEFAULT);

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
  }
}