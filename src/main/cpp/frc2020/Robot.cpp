/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <cerberus/Events.h>
#include <cerberus/Hardware.h>
#include <cerberus/Inputs.h>
#include <cerberus/Networking.h>
#include <cerberus/Components.h>
#include <frc2020/Robot.h>
#include <frc2020/controllers/HumanDriveController.h>
#include <frc2020/controllers/HumanShooterController.h>
#include <frc2020/events/EventTest.h>

#include <frc/Joystick.h>
// #include <wpi/TCPStream.h>

// #include <cstdio>
// #include <cstring>

// #ifdef _WIN32
// #define _WINSOCK_DEPRECATED_NO_WARNINGS
// #include <WinSock2.h>
// #include <Ws2tcpip.h>
// #pragma comment(lib, "Ws2_32.lib")
// #else
// #include <arpa/inet.h>
// #include <fcntl.h>
// #include <netinet/in.h>
// #include <unistd.h>
// #endif

#include <sstream>
#include <string>

frc::Joystick joystick = frc::Joystick(0);
EventTest eventTest = EventTest();

frc2020::DriveTrain drivetrain;
frc2020::Shooter shooter;

// wpi::TCPStream tcp = wpi::TCPStream(socket(PF_INET, SOCK_STREAM, 0), );

frc2020::HumanDriveController driveController = frc2020::HumanDriveController(drivetrain);
frc2020::HumanShooterController shooterController = frc2020::HumanShooterController(shooter);

void Robot::RobotInit() {
    net::initialize();
    events::add(&eventTest);

	components::add(&drivetrain);
	components::add(&shooter);

	components::add(&driveController);
	components::add(&shooterController);

    this->IsTest();

	components::initialize();
}

void Robot::RobotPeriodic() {
    // std::cout << "robotTime: " << this->GetPeriod().value() << std::endl;
}

void Robot::DisabledInit() {
	c_robotState = State::DISABLED;
	components::deinitialize();
}

void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit() {
	c_robotState = State::AUTONOMOUS;
}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
	c_robotState = State::TELEOP;
}
void Robot::TeleopPeriodic() {}

void Robot::TestInit() {
	c_robotState = State::TESTING;
}
void Robot::TestPeriodic() {
    net::update();
    input::update();
    events::update();
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
