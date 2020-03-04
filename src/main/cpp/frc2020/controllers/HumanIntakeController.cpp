#include <cerberus/Events.h>
#include <cerberus/Inputs.h>
#include <cerberus/Logger.h>
#include <frc2020/Robot.h>
#include <frc2020/components/Intake.h>
#include <frc2020/controllers/HumanIntakeController.h>

#include <iostream>

HumanIntakeController::HumanIntakeController() {}

void HumanIntakeController::initialize() {
    intake = (Intake*)events::get(typeid(Intake));

    if (intake == nullptr) {
        logger::println(logger::error, "[HumanIntakeController] failed to get the intake event.");
        logger::println(logger::warning, "[HumanIntakeController] failed to initialize.");
    }

    input::add<input::Digital>(&input_toggle);

    logger::println(logger::warning, "[HumanIntakeController] successfully initialized.");
}

void HumanIntakeController::deinitialize() {
    input::remove<input::Digital>(&input_toggle);

    logger::println(logger::warning, "[HumanIntakeController] successfully deinitialized.");
}

void HumanIntakeController::update() {
    if (input_toggle.value) {
        intake->toggle(true);
    } else {
        intake->toggle(false);
    }
}

bool HumanIntakeController::condition() {
    return robotState == RobotState::TELEOP || robotState == RobotState::TESTING;
}
