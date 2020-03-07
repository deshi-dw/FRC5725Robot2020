#include <cerberus/EventManager.h>
#include <cerberus/InputManager.h>
#include <cerberus/Logger.h>
#include <frc2020/Robot.h>
#include <frc2020/components/Intake.h>
#include <frc2020/controllers/HumanIntakeController.h>

#include <iostream>

HumanIntakeController::HumanIntakeController() {}

void HumanIntakeController::initialize() {
    intake = (Intake*)Robot::events->get(typeid(Intake));

    if (intake == nullptr) {
        Robot::logger->println(Logger::error, "[HumanIntakeController] failed to get the intake event.");
        Robot::logger->println(Logger::warning, "[HumanIntakeController] failed to initialize.");
    }

    Robot::inputs->add<DigitalInput>(&input_toggle);

    Robot::logger->println(Logger::warning, "[HumanIntakeController] successfully initialized.");
}

void HumanIntakeController::deinitialize() {
    Robot::inputs->remove<DigitalInput>(&input_toggle);

    Robot::logger->println(Logger::warning, "[HumanIntakeController] successfully deinitialized.");
}

void HumanIntakeController::update() {
    if (input_toggle.value) {
        intake->toggle(true);
    } else {
        intake->toggle(false);
    }
}

bool HumanIntakeController::condition() {
    return Robot::getRobotState() == RobotState::TELEOP || Robot::getRobotState() == RobotState::TESTING;
}
