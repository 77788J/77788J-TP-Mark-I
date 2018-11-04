#include "autons.hpp"
#include "macros.hpp"
#include "subsystems/subsystems.hpp"

void autons::flagSideRed(int side, bool park) {
    print("START");

    // wait for catapult to be loaded
    while (!catapult::limit_switch.getValue(0)) delay(1);

    ball_intake::setDirection(1);
    delay(1000);

    // launch ball at top flag
    catapult::fire();
    while (catapult::is_shooting) delay(1);

    chassis::gotoInches(6.f);
    chassis::waitForCompletion(10.f, 500);

    // rotate to cap
    chassis::rotateTo(90.f);
    chassis::waitForCompletion(1.f, 1500);

    delay(150);

    // move to cap and intake ball
    chassis::resetPosition();
    ball_intake::setDirection(1);
    chassis::gotoInches(-34.f);
    chassis::waitForCompletion(2.f, 1500);

    delay(500);

    // back up
    chassis::gotoInches(18.f);
    chassis::waitForCompletion(2.f, 1400);

    // move forward a bit
    chassis::moveInches(8.f);
    chassis::waitForCompletion(2.f, 1500);

    // rotate
    chassis::rotateTo(0.f);
    chassis::waitForCompletion(1.f, 1750);

    delay(250);

    // move up
    chassis::moveInches(20.f);
    chassis::waitForCompletion(4.f, 1500);

    // align
    // chassis::rotateTo(8.f);
    delay(750);

    // shoot flag
    catapult::fire();
    while (catapult::is_shooting) delay(1);

    // turn a bit
    chassis::rotateTo(22.f);
    delay(1000);

    // ram into flag
    chassis::moveInches(32.f);
    chassis::waitForCompletion(2.f, 1250);
    chassis::moveInches(-12.f);

    // // rotate to cap
    // chassis::rotateTo(90.f * angle_mult);
    // chassis::waitForCompletion(3.f, 1500);

    // // go up to cap
    // chassis::moveInches(-10.f);
    // chassis::waitForCompletion(20.f, 1500);

    // // flip cap
    // macros::flipCap();
    // delay(500);

    // // rotate to 45 deg
    // chassis::rotateTo(-45.f * angle_mult);
    // chassis::waitForCompletion(3.f, 1750);

    // // move inline with flags
    // chassis::moveInches(-16.f);
    // chassis::waitForCompletion(20.f, 1500);

    // // rotate to flags
    // chassis::rotateTo(0.f);
    // chassis::waitForCompletion(3.f, 1000);

    // // flip bottom flag
    // chassis::resetPosition();
    // chassis::gotoInches(-12.f);
    // chassis::waitForCompletion(20.f, 1500);

    // // park
    // if (park) {

    //     // back up inline with tile
    //     chassis::gotoInches(59.f);
    //     chassis::waitForCompletion(20.f, 3000);

    //     // rotate to tile
    //     chassis::rotateTo(-90.f * angle_mult);
    //     chassis::waitForCompletion(3.f, 1000);

    //     // move onto tile
    //     chassis::moveInches(36.f);
    // }
    // else chassis::gotoInches(36.f); // if not parking, just back up
}