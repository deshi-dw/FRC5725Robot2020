/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>

enum RobotState {
    DISABLED,
    TESTING,
    AUTONOMOUS,
    TELEOP,
    SHUTTING_DOWN,
    BOOTING_UP
};

class Robot : public frc::TimedRobot {
   public:
    void RobotInit() override;
    void RobotPeriodic() override;

    void DisabledInit() override;
    void DisabledPeriodic() override;

    void AutonomousInit() override;
    void AutonomousPeriodic() override;

    void TeleopInit() override;
    void TeleopPeriodic() override;

    void TestInit() override;
    void TestPeriodic() override;

    static double m_robotTime;
};

// TODO: move inside Robot class. (ie. Robot::m_robotState + getRobotState())
static RobotState robotState;

extern double getRobotTime();
