#include <cerberus/EventManager.h>
#include <cerberus/Inputs.h>
#include <cerberus/Logger.h>
#include <frc2020/Robot.h>
#include <frc2020/components/DriveTrain.h>
#include <frc2020/controllers/HumanDriveController.h>

HumanDriveController::HumanDriveController() {}

void HumanDriveController::initialize() {
    drivetrain = (DriveTrain*)Robot::events->get(typeid(DriveTrain));

    if (drivetrain == nullptr) {
        logger::println(logger::error, "[HumanDriveController] failed to get the drivetrain event.");
        logger::println(logger::warning, "[HumanDriveController] failed to initialize.");
    }

    // drive_speed.isDeadZoned = true;
    drive_speed.deadZone = 0.15;

    // drive_turn.isDeadZoned = true;
    drive_turn.deadZone = 0.15;

    input::add<input::Analog>(&drive_speed);
    input::add<input::Analog>(&drive_turn);

    logger::println(logger::warning, "[HumanDriveController] successfully initialized.");
}
void HumanDriveController::deinitialize() {
    input::remove<input::Analog>(&drive_speed);
    input::remove<input::Analog>(&drive_turn);

    logger::println(logger::warning, "[HumanDriveController] successfully deinitialized.");
}

void HumanDriveController::update() {
    drivetrain->driveArcade(drive_speed.value * 0.4, drive_turn.value * 0.4);
}

bool HumanDriveController::condition() {
    return Robot::getRobotState() == RobotState::TELEOP || Robot::getRobotState() == RobotState::TESTING;
}
