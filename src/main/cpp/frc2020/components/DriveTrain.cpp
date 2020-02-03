#include <cerberus/Hardware.h>
#include <cerberus/Settings.h>
#include <frc/Spark.h>
#include <frc2020/components/DriveTrain.h>
#include <util/LoadSettings.h>

namespace frc2020 {
DriveTrain::DriveTrain() {}

DriveTrain::~DriveTrain() {}

void DriveTrain::initialize() {
    cfg::load(settingsPath);

    cfg::get<int>("hardware::motor_right1::pin", pin_right1);
    cfg::get<int>("hardware::motor_right2::pin", pin_right2);
    cfg::get<int>("hardware::motor_left1::pin", pin_left1);
    cfg::get<int>("hardware::motor_left2::pin", pin_left2);

    pin_right1 = 6;
    pin_right2 = 7;
    pin_left1 = 2;
    pin_left2 = 3;

    motor_right1 = new frc::Spark(pin_right1);
    motor_right2 = new frc::Spark(pin_right1);
    motor_left1 = new frc::Spark(pin_left1);
    motor_left2 = new frc::Spark(pin_left2);

    hardware::addPWM(motor_right1);
    hardware::addPWM(motor_right2);
    hardware::addPWM(motor_left1);
    hardware::addPWM(motor_left2);
}
void DriveTrain::deinitialize() {
	hardware::removePWM(motor_right1->GetChannel());
	hardware::removePWM(motor_right2->GetChannel());
	hardware::removePWM(motor_left1->GetChannel());
	hardware::removePWM(motor_left2->GetChannel());

	delete motor_right1;
	delete motor_right2;
	delete motor_left1;
	delete motor_left2;
}

void DriveTrain::driveArcade(const double& speed, const double& turn) {
    driveTank(speed + turn, speed - turn);
}

void DriveTrain::driveTank(const double& right, const double& left) {
    // TODO: Make right and left speed class variables so they can be manipulateed outside of driveTank.
    motor_right1->SetSpeed(right);
    motor_right2->SetSpeed(right);

    motor_left1->SetSpeed(left);
    motor_left2->SetSpeed(left);
}

void DriveTrain::update() {}

}  // namespace frc2020