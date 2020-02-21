#pragma once

// TODO: Move to Robot.h as a lot of other robot variables reside there.
enum RobotState {
    DISABLED,
    TESTING,
    AUTONOMOUS,
    TELEOP
};

static RobotState c_robotState;