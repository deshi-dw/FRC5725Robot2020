/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <CompilerSettings.h>
#include <cerberus/EventManager.h>
#include <cerberus/Hardware.h>
#include <cerberus/Inputs.h>
#include <cerberus/Logger.h>
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

double Robot::m_robotTime = 0.0;
RobotState Robot::m_robotState = RobotState::BOOTING_UP;

EventManager* Robot::events = new EventManager();

RobotState Robot::getRobotState() {
    return m_robotState;
}

double Robot::getRobotTime() {
    return m_robotTime;
}

void Robot::RobotInit() {
    logger::initialize();
    logger::println(logger::info, "Robot Initializing...");
    logger::println();

    logger::println(logger::info, "adding events...");

    events->add(new EventTest());

    events->add(new DriveTrain());
    events->add(new Shooter());
    events->add(new Intake());

    events->add(new HumanDriveController());
    events->add(new HumanShooterController());
    events->add(new HumanIntakeController());

    logger::println(logger::info, "%u events added.", events->size());
    logger::println();

    events->update();

    logger::println(logger::info, "Robot Initialization Complete.");
}

void Robot::RobotPeriodic() {
    m_robotTime = this->GetPeriod().value();
    // std::cout << "robotTime: " << this->GetPeriod().value() << std::endl;
}

void Robot::DisabledInit() {
    m_robotState = RobotState::DISABLED;

    logger::println(logger::info, "RobotState = DISABLED");
}

void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit() {
    m_robotState = RobotState::AUTONOMOUS;
    logger::println(logger::info, "RobotState = AUTONOMOUS");
}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
    m_robotState = RobotState::TELEOP;
    logger::println(logger::info, "RobotState = TELEOP");
}
void Robot::TeleopPeriodic() {}

void Robot::TestInit() {
    m_robotState = RobotState::TESTING;
    logger::println(logger::info, "RobotState = TESTING");
}
void Robot::TestPeriodic() {
    input::update();
    events->update();
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
