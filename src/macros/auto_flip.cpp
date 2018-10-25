#include "macros.hpp"
#include "subsystems/subsystems.hpp"

namespace macros {
  void flipCap(void *) {

      // disable affected subsystems
      lift::in_macro = true;

      // raise lift
      lift::gotoDegrees(MAX_LEGAL_ANGLE);
      lift::waitForCompletion(10.f, 1);

      // lower lift
      lift::gotoDegrees(MIN_ANGLE);

      // restart task and re-enable all subsystems
      stopMacro();
    }
}