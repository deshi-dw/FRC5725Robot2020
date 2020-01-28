#include <frc2020/DriveTrain.h>

#include <cerberus/Hardware.h>
#include <cerberus/Settings.h>

namespace DriveTrain {
	void Initialize() {
		// Settings::Load(settingsPath);
		
		// pin_right1 = Settings::Get<int>("hardware::motor_right1::pin");
		// pin_right2 = Settings::Get<int>("hardware::motor_right2::pin");
		// pin_left1 = Settings::Get<int>("hardware::motor_left1::pin");
		// pin_left2 = Settings::Get<int>("hardware::motor_left2::pin");
		
		pin_right1 = 6;
		pin_right2 = 7;
		pin_left1 = 2;
		pin_left2 = 3;

		Hardware::AddPWMSpark(pin_right1);
		Hardware::AddPWMSpark(pin_right2);
		Hardware::AddPWMSpark(pin_left1);
		Hardware::AddPWMSpark(pin_left2);
	}
	void DriveArcade(const double& speed, const double& turn) {
		DriveTank(speed + turn, speed - turn);
	}

	void DriveTank(const double& right, const double& left) {
		Hardware::SetPWMSpeed(pin_right1, right);
		Hardware::SetPWMSpeed(pin_right2, right);

		Hardware::SetPWMSpeed(pin_left1, left);
		Hardware::SetPWMSpeed(pin_left2, left);
	}
}