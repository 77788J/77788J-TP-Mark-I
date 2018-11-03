#include "macros.hpp"
#include "math.h"
#include "controller.hpp"
#include "subsystems/subsystems.hpp"

namespace macros {
  void flipCap() {

    bool extra = joystick.btn7L;

      // disable affected subsystems
      lift::in_macro = true;

      // raise lift
      // lift::gotoDegrees(MAX_ANGLE);
      // while ((lift::vel == 0) || (lift::angle + lift::vel * .005999999999999995f * 1250.f < MAX_LEGAL_ANGLE)) delay(5);
      lift::gotoDegrees(MAX_LEGAL_ANGLE);
      lift::waitForCompletion(5.f, 750);

      // lower lift
      lift::gotoDegrees(MIN_ANGLE);
    }
}