#include "macros.hpp"
#include "subsystems/subsystems.hpp"

namespace macros {
  void shootBothFlags() {

      // disable affected subsystems
      chassis::in_macro = true;
      ball_intake::in_macro = true;
      catapult::in_macro = true;

      // fire catapult
      catapult::fire();
      while (catapult::is_shooting) delay(5);

      // move forward and load catapult
      chassis::moveInches(36.f);
      while (!catapult::limit_switch.getValue(0)) delay(5);
      ball_intake::setDirection(1);
      chassis::waitForCompletion(25.f, 5000);

      // fire catapult again
      catapult::fire();
      while (catapult::is_shooting) delay(5);
    }
}