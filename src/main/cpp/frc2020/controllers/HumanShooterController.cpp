#include <cerberus/EventManager.h>
#include <cerberus/InputManager.h>
#include <cerberus/Logger.h>
#include <frc2020/Robot.h>
#include <frc2020/components/Shooter.h>
#include <frc2020/controllers/HumanShooterController.h>

#include <iostream>

HumanShooterController::HumanShooterController() {}

void HumanShooterController::initialize() {
    shooter = (Shooter*)Robot::events->get(typeid(Shooter));

    if (shooter == nullptr) {
        logger::println(logger::error, "[HumanShooterController] failed to get the intake event.");
        logger::println(logger::warning, "[HumanShooterController] failed to initialize.");
    }

    Robot::inputs->add<AnalogInput>(&speed_top);
    Robot::inputs->add<AnalogInput>(&speed_bottom);

    logger::println(logger::warning, "[HumanShooterController] successfully initialized.");
}

void HumanShooterController::deinitialize() {
    Robot::inputs->remove<AnalogInput>(&speed_top);
    Robot::inputs->remove<AnalogInput>(&speed_bottom);

    logger::println(logger::warning, "[HumanShooterController] successfully deinitialized.");
}

void HumanShooterController::update() {
    shooter->shoot(speed_top.value, speed_bottom.value);
}

bool HumanShooterController::condition() {
    return Robot::getRobotState() == RobotState::TELEOP || Robot::getRobotState() == RobotState::TESTING;
}
