#include <cerberus/EventManager.h>
#include <cerberus/InputManager.h>
#include <cerberus/Logger.h>
#include <frc2020/Robot.h>
#include <frc2020/components/DriveTrain.h>
#include <frc2020/components/Intake.h>
#include <frc2020/components/Shooter.h>
#include <frc2020/controllers/TestRunnerController.h>

#include <algorithm>

using namespace cerberus;

TestRunnerController::TestRunnerController() {}

void TestRunnerController::initialize() {
    drivetrain = (DriveTrain*)Robot::events->get(typeid(DriveTrain));
    intake = (Intake*)Robot::events->get(typeid(Intake));
    shooter = (Shooter*)Robot::events->get(typeid(Shooter));

    Robot::inputs->add<InputDigital>(&buttonA);
    Robot::inputs->add<InputDigital>(&buttonB);
    Robot::inputs->add<InputDigital>(&buttonX);
    Robot::inputs->add<InputDigital>(&buttonY);

    Robot::inputs->add<InputDigital>(&buttonNext);
    Robot::inputs->add<InputDigital>(&buttonPrev);
}

void TestRunnerController::deinitialize() {}

void TestRunnerController::update() {
    previousMode = selectedMode;
    previousIsInputDown = isInputDown;

    if (buttonNext.value == true) {
        if (isInputDown == false) {
            selectedMode = (selectedMode + 1) % modeCount;

            isInputDown = true;
        }
    } else if (buttonPrev.value == true) {
        if (isInputDown == false) {
            selectedMode = abs(selectedMode - 1) % modeCount;

            isInputDown = true;
        }
    } else if (buttonA.value || buttonB.value || buttonX.value || buttonY.value) {
        isInputDown = true;
    } else {
        isInputDown = false;
    }

    bool initMode = selectedMode != previousMode;

    switch (selectedMode) {
        // driving tests 1
        case 0:
            test_drive1(initMode, buttonA.value, buttonB.value, buttonX.value, buttonY.value);
            break;

        case 1:
            test_drive2(initMode, buttonA.value, buttonB.value, buttonX.value, buttonY.value);
            break;

        default:
            break;
    }
}

bool TestRunnerController::condition() {
    return Robot::getRobotState() == RobotState::TESTING;
}

void TestRunnerController::test_drive1(bool is_init, bool in_a, bool in_b, bool in_x, bool in_y) {
    if (is_init) {
        Robot::logger->println("TEST MODE %i [DRIVE1]", selectedMode);
        Robot::logger->println("X = start driving forwards at drive_speed.");
        Robot::logger->println("B = stop the robot.");
        Robot::logger->println("Y = increase drive speed by 0.25");
        Robot::logger->println("A = decrease drive speed by 0.25");
    }

    /*
		* X = start driving forwards at drive_speed.
		* B = stop the robot and drive timer.
		* Y = increase drive speed by 0.25
		* A = decrease drive speed by 0.25
		*/

    // if x is press, start the robot.
    if (in_x == true && previousIsInputDown == false && start == false) {
        startTime = Robot::getRobotTime();
        start = true;
    }

    // if the timer has started,
    if (start == true) {
        // drive forwards for 1000 ms (1 sec).
        if (Robot::getRobotTime() - startTime <= 1.000) {
            drivetrain->driveArcade(drive_speed, 0.0);
        } else {
            start = false;
            drivetrain->driveTank(0, 0);
        }
    }

    // if b is pressed, stop the robot.
    if (in_b == true) {
        start = false;
        startTime = 0;

        drivetrain->driveTank(0, 0);
    }

    // if y is pressed, increase drive speed.
    if (in_y == true && previousIsInputDown == false) {
        drive_speed = std::min(drive_speed + 0.25, 1.0);
        Robot::logger->println("drive_speed = %f", drive_speed);
    }
    // if a is pressed, decrease drive speed.
    else if (in_a == true && previousIsInputDown == false) {
        drive_speed = std::max(drive_speed - 0.25, -1.0);
        Robot::logger->println("drive_speed = %f", drive_speed);
    }
}

void TestRunnerController::test_drive2(bool is_init, bool in_a, bool in_b, bool in_x, bool in_y) {
    if (is_init) {
        Robot::logger->println("TEST MODE %i [DRIVE2]", selectedMode);
        Robot::logger->println("X = start turning at turn_speed.");
        Robot::logger->println("B = stop the robot.");
        Robot::logger->println("Y = increase turn speed by 0.25");
        Robot::logger->println("A = decrease turn speed by 0.25");
    }

    /*
		* X = start turning at turn_speed.
		* B = stop the robot and drive timer.
		* Y = increase turn speed by 0.25
		* A = decrease turn speed by 0.25
		*/

    // if x is press, start the robot.
    if (in_x == true && previousIsInputDown == false && start == false) {
        startTime = Robot::getRobotTime();
        start = true;
    }

    // if the timer has started,
    if (start == true) {
        // turn for 1000 ms (1 sec).
        if (Robot::getRobotTime() - startTime <= 1.000) {
            drivetrain->driveArcade(0.0, turn_speed);
        } else {
            start = false;
            drivetrain->driveTank(0, 0);
        }
    }

    // if b is pressed, stop the robot.
    if (in_b == true) {
        start = false;
        startTime = 0;

        drivetrain->driveTank(0, 0);
    }

    // if y is pressed, increase turn speed.
    if (in_y == true && previousIsInputDown == false) {
        turn_speed = std::min(turn_speed + 0.25, 1.0);
        Robot::logger->println("turn_speed = %f", turn_speed);
    }
    // if a is pressed, decrease turn speed.
    else if (in_a == true && previousIsInputDown == false) {
        turn_speed = std::max(turn_speed - 0.25, -1.0);
        Robot::logger->println("turn_speed = %f", turn_speed);
    }
}