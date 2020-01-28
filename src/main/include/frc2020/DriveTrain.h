#pragma once

#include <string>

namespace DriveTrain {

namespace {
	const std::string settingsPath = "conf/drivetrain.rcfg";

    int pin_right1;
    int pin_right2;
    int pin_left1;
    int pin_left2;
}

void Initialize();
void DriveArcade(const double& speed, const double& turn);
void DriveTank(const double& right, const double& left);

}