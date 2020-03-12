#include <cerberus/EventManager.h>
#include <cerberus/InputManager.h>
#include <cerberus/Logger.h>
#include <frc2020/Robot.h>
#include <frc2020/components/Intake.h>
#include <frc2020/controllers/HumanIntakeController.h>

#include <iostream>

using namespace cerberus;

HumanIntakeController::HumanIntakeController() {}

void HumanIntakeController::initialize() {
    intake = (Intake*)Robot::events->get(typeid(Intake));

    if (intake == nullptr) {
        Robot::logger->println(Logger::error, "[HumanIntakeController] failed to get the intake event.");
        Robot::logger->println(Logger::warning, "[HumanIntakeController] failed to initialize.");
    }

    Robot::inputs->add<InputDigital>(&input_up);
    Robot::inputs->add<InputDigital>(&input_down);
    Robot::inputs->add<InputAnalog>(&input_pullySpeed);

    Robot::logger->println(Logger::warning, "[HumanIntakeController] successfully initialized.");
}

void HumanIntakeController::deinitialize() {
    Robot::inputs->remove<InputDigital>(&input_up);
    Robot::inputs->remove<InputDigital>(&input_down);
    Robot::inputs->remove<InputAnalog>(&input_pullySpeed);

    Robot::logger->println(Logger::warning, "[HumanIntakeController] successfully deinitialized.");
}

void HumanIntakeController::update() {
    if (input_up.value) {
        intake->setState(Intake::State::UP);
    } else if (input_down.value) {
        intake->setState(Intake::State::DOWN);
    } else {
        intake->setState(Intake::State::IDLE);
    }

    intake->setPulySpeed(input_pullySpeed.value * 0.6);
}

bool HumanIntakeController::condition() {
    return Robot::getRobotState() == RobotState::TELEOP || Robot::getRobotState() == RobotState::TESTING;
}
