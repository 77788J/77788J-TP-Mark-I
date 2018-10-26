#include "macros.hpp"
#include "math.h"
#include "subsystems/subsystems.hpp"

namespace macros {
  void flipCap() {

      // disable affected subsystems
      lift::in_macro = true;

      // raise lift
      lift::gotoDegrees(MAX_ANGLE);
      while (lift::angle < MAX_LEGAL_ANGLE - 20) delay(5);

      // lower lift
      lift::gotoDegrees(MIN_ANGLE);
    }
}