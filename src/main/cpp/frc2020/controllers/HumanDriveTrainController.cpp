#include <cerberus/EventManager.h>
#include <cerberus/InputManager.h>
#include <cerberus/Logger.h>
#include <frc2020/Robot.h>
#include <frc2020/components/DriveTrain.h>
#include <frc2020/controllers/HumanDriveController.h>

using namespace cerberus;

HumanDriveController::HumanDriveController() {}

void HumanDriveController::initialize() {
    drivetrain = (DriveTrain*)Robot::events->get(typeid(DriveTrain));

    if (drivetrain == nullptr) {
        Robot::logger->println(Logger::error, "[HumanDriveController] failed to get the drivetrain event.");
        Robot::logger->println(Logger::warning, "[HumanDriveController] failed to initialize.");
    }

    // drive_speed.isDeadZoned = true;
    drive_speed.deadZone = 0.15;

    // drive_turn.isDeadZoned = true;
    drive_turn.deadZone = 0.15;

    Robot::inputs->add<InputAnalog>(&drive_speed);
    Robot::inputs->add<InputAnalog>(&drive_turn);
    
    Robot::inputs->add<InputDigital>(&toggle_drive_straight);
    Robot::inputs->add<InputDigital>(&toggle_drive_turn);

    Robot::logger->println(Logger::warning, "[HumanDriveController] successfully initialized.");
}
void HumanDriveController::deinitialize() {
    Robot::inputs->remove<InputAnalog>(&drive_speed);
    Robot::inputs->remove<InputAnalog>(&drive_turn);

    Robot::logger->println(Logger::warning, "[HumanDriveController] successfully deinitialized.");
}

void HumanDriveController::update() {
    if(toggle_drive_straight.value == true) {
        drivetrain->driveArcade(0.0, drive_speed.value * 0.6);
    }
    else if(toggle_drive_turn.value == true) {
        drivetrain->driveArcade(drive_turn.value * 0.6, 0.0);
    }
    else {
        drivetrain->driveArcade(drive_speed.value * 0.2, drive_turn.value * 0.6);
    }
}

bool HumanDriveController::condition() {
    return Robot::getRobotState() == RobotState::TELEOP || Robot::getRobotState() == RobotState::TESTING;
}
