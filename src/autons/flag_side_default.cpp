#include "autons.hpp"
#include "subsystems/subsystems.hpp"

void autons::flagSideDefault(Side side, bool park) {
    bool angle_mult = side == side_blue ? -1.f : 1.f;

    // start ball intake
    ball_intake::setDirection(1);

    // move to cap
    chassis::moveInches(45.f);
    chassis::waitForCompletion(10.f, 10);

    // start moving to shot pos
    chassis::gotoInches(10.f);

    // wait 1 second
    delay(1000);

    // turn off ball intake and lower lift completely
    ball_intake::setDirection(0);
    lift::gotoDegrees(MIN_ANGLE);

    // wait for chassis to be in position
    chassis::waitForCompletion(10.f, 10);

    // rotate towards flags
    chassis::rotateTo(90.f * angle_mult);
    chassis::waitForCompletion(10.f, 5);

    // launch ball at top flag
    catapult::fire();
    delay(150);

    // go up to middle flag
    chassis::moveInches(-25.f);
    chassis::waitForCompletion(10.f, 5);

    // launch ball at middle flag
    catapult::fire();
    delay(150);

    // rotate to cap and open intake
    chassis::rotateTo(0.f * angle_mult);
    chassis::waitForCompletion(10.f, 5);

    // reset relative position
    chassis::resetPosition();

    // start ball intake in reverse (to flip cap)
    ball_intake::setDirection(-1);

    // move to cap
    chassis::gotoInches(14.f);
    chassis::waitForCompletion(10.f, 5);

    // move back in line with flags
    chassis::gotoInches(0.f);
    chassis::waitForCompletion(10.f, 5);

    // turn off ball intake
    ball_intake::setDirection(0);

    if (park) {

        // rotate to face away from flags
        chassis::rotateTo(90.f * angle_mult);
        chassis::waitForCompletion(10.f, 5);

        // move in line with parking tiles
        chassis::moveInches(50.f);
        chassis::waitForCompletion(10.f, 10);

        // rotate to face parking tile
        chassis::rotateTo(0.f * angle_mult);
        chassis::waitForCompletion(10.f, 5);

        // drive onto parking tile
        chassis::moveInches(25.f);
        chassis::waitForCompletion(10.f, 10);
    }
}
