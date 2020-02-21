/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <frc2020/Robot.h>

#include <util/RobotState.h>
#include <cerberus/Events.h>
#include <cerberus/Hardware.h>
#include <cerberus/Inputs.h>
#include <cerberus/Networking.h>
#include <cerberus/Components.h>

#include <frc2020/components/DriveTrain.h>
#include <frc2020/components/Shooter.h>
#include <frc2020/components/Intake.h>

#include <frc2020/controllers/HumanDriveController.h>
#include <frc2020/controllers/HumanShooterController.h>
#include <frc2020/controllers/HumanIntakeController.h>

#include <frc2020/events/EventTest.h>

#include <frc/Joystick.h>
#include <sstream>
#include <string>

frc::Joystick joystick = frc::Joystick(0);
EventTest eventTest = EventTest();

frc2020::DriveTrain drivetrain;
frc2020::Shooter shooter;
frc2020::Intake intake;

// wpi::TCPStream tcp = wpi::TCPStream(socket(PF_INET, SOCK_STREAM, 0), );

frc2020::HumanDriveController driveController = frc2020::HumanDriveController(drivetrain);
frc2020::HumanShooterController shooterController = frc2020::HumanShooterController(shooter);
frc2020::HumanIntakeController intakeController = frc2020::HumanIntakeController(intake);

void Robot::RobotInit() {
	std::cout << "test" << std::endl;
    // net::initialize();
    events::add(&eventTest);
	std::cout << "Events added." << std::endl;

	components::add(&drivetrain);
	components::add(&shooter);
	components::add(&intake);

	components::add(&driveController);
	components::add(&shooterController);
	components::add(&intakeController);
	components::initialize();
	std::cout << "Components added." << std::endl;
}

void Robot::RobotPeriodic() {
    // std::cout << "robotTime: " << this->GetPeriod().value() << std::endl;
}

void Robot::DisabledInit() {
	c_robotState = RobotState::DISABLED;
	std::cout << "robot state: DISABLED" << std::endl;
	// components::deinitialize();
}

void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit() {
	c_robotState = RobotState::AUTONOMOUS;
}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
	c_robotState = RobotState::TELEOP;
}
void Robot::TeleopPeriodic() {}

void Robot::TestInit() {
	c_robotState = RobotState::TESTING;
}
void Robot::TestPeriodic() {
    // net::update();
    components::update();
    input::update();
    events::update();
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
