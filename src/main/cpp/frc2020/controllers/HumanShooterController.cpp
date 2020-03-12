#include <cerberus/EventManager.h>
#include <cerberus/InputManager.h>
#include <cerberus/Logger.h>
#include <frc2020/Robot.h>
#include <frc2020/components/Shooter.h>
#include <frc2020/controllers/HumanShooterController.h>

#include <iostream>

using namespace cerberus;

HumanShooterController::HumanShooterController() {}

void HumanShooterController::initialize() {
    shooter = (Shooter*)Robot::events->get(typeid(Shooter));

    if (shooter == nullptr) {
        Robot::logger->println(Logger::error, "[HumanShooterController] failed to get the intake event.");
        Robot::logger->println(Logger::warning, "[HumanShooterController] failed to initialize.");
    }

    Robot::inputs->add<InputAnalog>(&speed_top);
    Robot::inputs->add<InputAnalog>(&speed_bottom);

    Robot::logger->println(Logger::warning, "[HumanShooterController] successfully initialized.");
}

void HumanShooterController::deinitialize() {
    Robot::inputs->remove<InputAnalog>(&speed_top);
    Robot::inputs->remove<InputAnalog>(&speed_bottom);

    Robot::logger->println(Logger::warning, "[HumanShooterController] successfully deinitialized.");
}

void HumanShooterController::update() {
    shooter->shoot(speed_top.value * -0.6, speed_bottom.value * -0.6);
}

bool HumanShooterController::condition() {
    return Robot::getRobotState() == RobotState::TELEOP || Robot::getRobotState() == RobotState::TESTING;
}
