#include <cerberus/EventManager.h>
#include <cerberus/InputManager.h>
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

    Robot::inputs->add<AnalogInput>(&drive_speed);
    Robot::inputs->add<AnalogInput>(&drive_turn);

    logger::println(logger::warning, "[HumanDriveController] successfully initialized.");
}
void HumanDriveController::deinitialize() {
    Robot::inputs->remove<AnalogInput>(&drive_speed);
    Robot::inputs->remove<AnalogInput>(&drive_turn);

    logger::println(logger::warning, "[HumanDriveController] successfully deinitialized.");
}

void HumanDriveController::update() {
    drivetrain->driveArcade(drive_speed.value * 0.4, drive_turn.value * 0.4);
}

bool HumanDriveController::condition() {
    return Robot::getRobotState() == RobotState::TELEOP || Robot::getRobotState() == RobotState::TESTING;
}
