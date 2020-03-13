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

bool TestRunnerController::isAPressed() {
    return buttonA.value && previousIsInputDown == false;
}
bool TestRunnerController::isBPressed() {
    return buttonA.value && previousIsInputDown == false;
}
bool TestRunnerController::isXPressed() {
    return buttonA.value && previousIsInputDown == false;
}
bool TestRunnerController::isYPressed() {
    return buttonA.value && previousIsInputDown == false;
}

void TestRunnerController::change_value(bool is_up, bool is_down, double* value, double increment, double min, double max, const std::string& value_name) {
    if (is_up == true) {
        *value = std::min(*value + increment, max);
    } else if (is_down == true) {
        *value = std::max(*value - increment, min);
    } else {
        return;
    }
    Robot::logger->println("%s = %f", value_name, value);
}

bool TestRunnerController::change_mode(bool is_up, int* mode, int mode_count) {
    if (is_up == true) {
        *mode = std::abs(*mode + 1) % mode_count;
    } else {
        return false;
    }

    return true;
}

void TestRunnerController::print_controls(const std::string& task_name) {
    Robot::logger->println("X = start/stop %s.", task_name);
    Robot::logger->println("B = select mode.");
    Robot::logger->println("Y = increase value.");
    Robot::logger->println("A = decrease value.");
}

void TestRunnerController::print_mode(int mode, const std::string& mode_name, bool is_sub) {
    if (is_sub == true) {
        Robot::logger->println("submode %i [%s]", mode, mode_name);
    } else {
        Robot::logger->println("mode %i [%s]", mode, mode_name);
    }
}

void TestRunnerController::start_and_stop(std::function<void()> func) {
    if (isAPressed()) {
        if (start == false) {
            startTime = Robot::getRobotTime();
            start = true;
        } else {
            startTime = 0;
            drivetrain->driveTank(0, 0);
            intake->setState(Intake::IDLE);
            start = false;
        }
    }

    // if the timer has started,
    if (start == true) {
        // drive forwards for 1000 ms (1 sec).
        if (Robot::getRobotTime() - startTime <= test_duration) {
            func();
        } else {
            start = false;
            drivetrain->driveTank(0, 0);
        }
    }
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
        print_mode(selectedMode, "DRIVE_STRAIGHT", false);
        print_controls("driving straight");

        b_mode = 0;
    }

    start_and_stop([&]() -> void { drivetrain->driveArcade(drive_speed, 0.0); });

    // if b is pressed, stop the robot.
    if (change_mode(in_b, &b_mode, 2)) {
        if (b_mode == 0) {
            print_mode(b_mode, "SET SPEED", true);
        } else if (b_mode == 1) {
            print_mode(b_mode, "SET TIME(sec)", true);
        }
    }

    if (b_mode == 0) {
        change_value(isYPressed(), isAPressed(), &drive_speed, speed_increment, -1.0, 1.0, "drive_speed");
    } else if (b_mode == 1) {
        change_value(isYPressed(), isAPressed(), &test_duration, time_increment, 0.0, 5.0, "test_duration");
    }
}

void TestRunnerController::test_drive2(bool is_init, bool in_a, bool in_b, bool in_x, bool in_y) {
    if (is_init) {
        print_mode(selectedMode, "SPIN", false);
        print_controls("spin");

        b_mode = 0;
    }

    start_and_stop([&]() -> void { drivetrain->driveArcade(0.0, drive_speed); });

    // if b is pressed, stop the robot.
    if (change_mode(in_b, &b_mode, 2)) {
        if (b_mode == 0) {
            print_mode(b_mode, "SET SPEED", true);
        } else if (b_mode == 1) {
            print_mode(b_mode, "SET TIME(sec)", true);
        }
    }

    if (b_mode == 0) {
        change_value(isYPressed(), isAPressed(), &turn_speed, speed_increment, -1.0, 1.0, "turn_speed");
    } else if (b_mode == 1) {
        change_value(isYPressed(), isAPressed(), &test_duration, time_increment, 0.0, 5.0, "test_duration");
    }
}

void TestRunnerController::test_drive3(bool is_init, bool in_a, bool in_b, bool in_x, bool in_y) {
    if (is_init) {
        print_mode(selectedMode, "ARC", false);
        print_controls("arc");

        b_mode = 0;
    }

    start_and_stop([&]() -> void { drivetrain->driveArcade(0.0, drive_speed); });

    // if b is pressed, stop the robot.
    if (change_mode(in_b, &b_mode, 3)) {
        if (b_mode == 0) {
            print_mode(b_mode, "SET RIGHT SPEED", true);
        } else if (b_mode == 1) {
            print_mode(b_mode, "SET LEFT SPEED", true);
        } else if (b_mode == 2) {
            print_mode(b_mode, "SET TIME(sec)", true);
        }
    }

    if (b_mode == 0) {
        change_value(isYPressed(), isAPressed(), &right_speed, speed_increment, -1.0, 1.0, "right_speed");
    } else if (b_mode == 1) {
        change_value(isYPressed(), isAPressed(), &left_speed, speed_increment, -1.0, 1.0, "left_speed");
    } else if (b_mode == 1) {
        change_value(isYPressed(), isAPressed(), &test_duration, time_increment, 0.0, 5.0, "test_duration");
    }
}