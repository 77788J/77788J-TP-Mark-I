#include "autons.hpp"
#include "macros.hpp"
#include "subsystems/subsystems.hpp"

void autons::capSideDefault(int side, bool park) {
    bool angle_mult = side ? -1.f : 1.f;

    // wait for catapult to be loaded
    while (!catapult::limit_switch.getValue(0)) delay(5);

    ball_intake::setDirection(1);
    delay(1000);

    // launch ball at middle flag
    catapult::fire();
    while (catapult::is_shooting) delay(1);

    // back up slightly
    chassis::moveInches(4.f);
    delay(250);

    // rotate to cap
    chassis::rotateTo(-90.f * angle_mult);
    chassis::waitForCompletion(3.f, 1500);

    // move to cap and intake ball
    chassis::resetPosition();
    ball_intake::setDirection(1);
    chassis::moveInches(34.f);
    chassis::waitForCompletion(20.f, 1500);

    // back up
    chassis::gotoInches(20.f);
    chassis::waitForCompletion(20.f, 1500);

    // rotate to back of field
    chassis::rotateTo(0.f);
    chassis::waitForCompletion(2.f, 1500);

    // move inline with cap
    chassis::moveInches(24.f);
    chassis::waitForCompletion(20.f, 1500);

    // rotate to cap
    chassis::rotateTo(90.f);
    chassis::waitForCompletion(3.f, 1500);

    // move to cap
    chassis::resetPosition();
    chassis::gotoInches(14.f);
    chassis::waitForCompletion(20.f, 1500);

    // flip cap
    macros::flipCap();
    delay(500);

    // move back
    chassis::gotoInches(21.f);
    delay(250);

    // park
    if (park) {

        // rotate to platform
        chassis::rotateTo(180.f);
        chassis::waitForCompletion(3.f, 1500);

        // drive onto platform
        chassis::moveInches(50.f);
        chassis::waitForCompletion(20.f, 2000);
    }
}
