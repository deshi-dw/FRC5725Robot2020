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
#include <frc/Joystick.h>
#include <frc2020/Robot.h>
#include <frc2020/components/DriveTrain.h>
#include <frc2020/components/Intake.h>
#include <frc2020/components/Shooter.h>
#include <frc2020/controllers/HumanDriveController.h>
#include <frc2020/controllers/HumanIntakeController.h>
#include <frc2020/controllers/HumanShooterController.h>
#include <frc2020/events/EventLogMotion.h>
#include <frc2020/events/EventTest.h>

#include <iostream>
#include <sstream>
#include <string>

frc::Joystick joystick = frc::Joystick(0);
EventTest eventTest = EventTest();

frc2020::DriveTrain drivetrain;
frc2020::Shooter shooter;
frc2020::Intake intake;

// wpi::TCPStream tcp = wpi::TCPStream(socket(PF_INET, SOCK_STREAM, 0), );

frc2020::HumanDriveController driveController;
frc2020::HumanShooterController shooterController;
frc2020::HumanIntakeController intakeController;

void Robot::RobotInit() {
    std::cout << "test" << std::endl;
    // net::initialize();
    events::add(&eventTest);

    events::add(&drivetrain);
    events::add(&shooter);
    events::add(&intake);

    events::add(&driveController);
    events::add(&shooterController);
    events::add(&intakeController);
    std::cout << "Events added." << std::endl;

    std::cout << std::endl
              << "List of Event Ids:" << std::endl;
    std::cout << "EventTest id = " << typeid(EventTest).name() << std::endl;
    std::cout << "EventLogMotion id = " << typeid(EventLogMotion).name() << std::endl;
    std::cout << "HumanDriveController id = " << typeid(frc2020::HumanDriveController).name() << std::endl;
    std::cout << std::endl;

    if (events::get(typeid(EventTest)) == nullptr) {
        std::cout << "EventTest is not in events." << std::endl;
    } else {
        std::cout << "EventTest is a part of events." << std::endl;
    }

    events::update();
}

void Robot::RobotPeriodic() {
    // std::cout << "robotTime: " << this->GetPeriod().value() << std::endl;
}

void Robot::DisabledInit() {
    robotState = RobotState::DISABLED;
    std::cout << "robot state: DISABLED" << std::endl;
    // components::deinitialize();
}

void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit() {
    robotState = RobotState::AUTONOMOUS;
}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
    robotState = RobotState::TELEOP;
}
void Robot::TeleopPeriodic() {}

void Robot::TestInit() {
    robotState = RobotState::TESTING;
}
void Robot::TestPeriodic() {
    // net::update();
    input::update();
    events::update();
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
