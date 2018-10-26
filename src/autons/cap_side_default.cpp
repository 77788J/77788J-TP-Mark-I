#include "autons.hpp"
#include "subsystems/subsystems.hpp"

void autons::capSideDefault(int side, bool park) {
    bool angle_mult = side ? -1.f : 1.f;

    // wait for catapult to be loaded
    while (!catapult::limit_switch.getValue(0)) delay(1);

    // launch ball at middle flag
    catapult::fire();
    while (catapult::is_shooting) delay(1);

    // drive forward
    chassis::gotoInches(25.f);
    chassis::waitForCompletion(10.f, 5000);

    // rotate to cap
    chassis::rotateTo(-90.f);
    chassis::waitForCompletion(10.f, 5000);

    // reset encoders
    chassis::resetPosition();

    // drive to cap and hopefully flip it
    ball_intake::setDirection(-1);
    chassis::gotoInches(50.f);
    chassis::waitForCompletion(10.f, 5000);

    // back up
    ball_intake::setDirection(0);
    chassis::gotoInches(34.f);
    chassis::waitForCompletion(10.f, 5000);

    // rotate
    chassis::rotateTo(-180.f);
    chassis::waitForCompletion(10.f, 5000);

    // move forward
    chassis::moveInches(25.f);
    chassis::waitForCompletion(10.f, 5000);

    // rotate to cap
    chassis::rotateTo(-90.f);
    chassis::waitForCompletion(10.f, 5000);

    // reset encoders
    chassis::resetPosition();

    // move to cap
    ball_intake::setDirection(1);
    chassis::gotoInches(16.f);
    chassis::waitForCompletion(10.f, 5000);

    // back up
    chassis::gotoInches(6.f);
    chassis::waitForCompletion(10.f, 5000);

    if (park) {

        // rotate to tile
        chassis::rotateTo(0.f);
        chassis::waitForCompletion(10.f, 5000);

        // park
        chassis::moveInches(23.f);
        chassis::waitForCompletion(10.f, 5000);
    }
}
