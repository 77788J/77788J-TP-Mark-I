#include "autons.hpp"
#include "macros.hpp"
#include "subsystems/subsystems.hpp"

void autons::flagSideDefault(int side, bool park) {
    bool angle_mult = side ? -1.f : 1.f;

    // wait for catapult to be loaded
    while (!catapult::limit_switch.getValue(0)) delay(1);

    ball_intake::setDirection(1);
    delay(1000);

    // launch ball at top flag
    catapult::fire();
    while (catapult::is_shooting) delay(1);

    // rotate to cap
    chassis::rotateTo(-90.f * angle_mult);
    chassis::waitForCompletion(3.f, 1500);

    // move to cap and intake ball
    chassis::resetPosition();
    ball_intake::setDirection(1);
    chassis::moveInches(34.f);
    chassis::waitForCompletion(20.f, 1500);

    // back up
    chassis::gotoInches(0.f);
    chassis::waitForCompletion(20.f, 1500);

    // rotate
    chassis::rotateTo(0.f);
    chassis::waitForCompletion(3.f, 1500);

    // move inline with cap
    chassis::moveInches(-25.f);
    chassis::waitForCompletion(20.f, 1500);

    // shoot flag
    catapult::fire();
    while (catapult::is_shooting) delay(1);

    // rotate to cap
    chassis::rotateTo(90.f * angle_mult);
    chassis::waitForCompletion(3.f, 1500);

    // go up to cap
    chassis::moveInches(-10.f);
    chassis::waitForCompletion(20.f, 1500);

    // flip cap
    macros::flipCap();
    delay(500);

    // rotate to 45 deg
    chassis::rotateTo(-45.f * angle_mult);
    chassis::waitForCompletion(3.f, 1750);

    // move inline with flags
    chassis::moveInches(-16.f);
    chassis::waitForCompletion(20.f, 1500);

    // rotate to flags
    chassis::rotateTo(0.f);
    chassis::waitForCompletion(3.f, 1000);

    // flip bottom flag
    chassis::resetPosition();
    chassis::gotoInches(-12.f);
    chassis::waitForCompletion(20.f, 1500);

    // park
    if (park) {

        // back up inline with tile
        chassis::gotoInches(59.f);
        chassis::waitForCompletion(20.f, 3000);

        // rotate to tile
        chassis::rotateTo(-90.f * angle_mult);
        chassis::waitForCompletion(3.f, 1000);

        // move onto tile
        chassis::moveInches(36.f);
    }
    else chassis::gotoInches(36.f); // if not parking, just back up
}