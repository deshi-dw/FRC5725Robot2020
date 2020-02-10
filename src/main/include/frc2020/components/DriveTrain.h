#pragma once

#include <frc/Spark.h>
#include <cerberus/Component.h>

#include <string>

namespace frc2020 {

class DriveTrain : public Component {
   private:
    const std::string settingsPath = "conf/drivetrain.rcfg";

    int pin_right1;
    int pin_right2;
    int pin_left1;
    int pin_left2;

	frc::Spark* motor_right1;
	// frc::Spark* motor_right2;
	frc::Spark* motor_left1;
	frc::Spark* motor_left2;

   public:
    DriveTrain();
    ~DriveTrain();
    
    void initialize();
    void deinitialize();
    void update();

    void driveArcade(const double& speed, const double& turn);
    void driveTank(const double& right, const double& left);
};
}  // namespace frc2020