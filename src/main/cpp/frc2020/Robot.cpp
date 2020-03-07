/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <CompilerSettings.h>
#include <cerberus/EventManager.h>
#include <cerberus/Hardware.h>
#include <cerberus/InputManager.h>
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
InputManager* Robot::inputs = new InputManager();

RobotState Robot::getRobotState() {
    return m_robotState;
}

double Robot::getRobotTime() {
    return m_robotTime;
}

void Robot::RobotInit() {
    logger = new Logger();
    logger->println(Logger::info, "Robot Initializing...");
    logger->println();

    logger->println(Logger::info, "adding events...");

    events->add(new EventTest());

    events->add(new DriveTrain());
    events->add(new Shooter());
    events->add(new Intake());

    events->add(new HumanDriveController());
    events->add(new HumanShooterController());
    events->add(new HumanIntakeController());

    logger->println(Logger::info, "%u events added.", events->size());
    logger->println();

    events->update();

    logger->println(Logger::info, "Robot Initialization Complete.");
}

void Robot::RobotPeriodic() {
    m_robotTime = this->GetPeriod().value();
    // std::cout << "robotTime: " << this->GetPeriod().value() << std::endl;
}

void Robot::DisabledInit() {
    m_robotState = RobotState::DISABLED;

    logger->println(Logger::info, "RobotState = DISABLED");
}

void Robot::DisabledPeriodic() {}

void Robot::AutonomousInit() {
    m_robotState = RobotState::AUTONOMOUS;
    logger->println(Logger::info, "RobotState = AUTONOMOUS");
}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
    m_robotState = RobotState::TELEOP;
    logger->println(Logger::info, "RobotState = TELEOP");
}
void Robot::TeleopPeriodic() {}

void Robot::TestInit() {
    m_robotState = RobotState::TESTING;
    logger->println(Logger::info, "RobotState = TESTING");
}
void Robot::TestPeriodic() {
    inputs->update();
    events->update();
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
