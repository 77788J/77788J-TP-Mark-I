#include "macros.hpp"
#include "subsystems/subsystems.hpp"

namespace macros {
  void shootBothFlags(void *) {

      // disable affected subsystems
      chassis::in_macro = true;
      ball_intake::in_macro = true;
      catapult::in_macro = true;

      // fire catapult
      catapult::fire();
      while (catapult::is_shooting) delay(5);

      // move forward and load catapult
      chassis::moveInches(36.f);
      ball_intake::load(true);
      chassis::waitForCompletion(25.f, 5);

      // fire catapult again
      catapult::fire();
      while (catapult::is_shooting) delay(5);

      // restart task and re-enable all subsystems
      stopMacro();
    }
}