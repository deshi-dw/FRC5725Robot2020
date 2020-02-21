#include <cerberus/Hardware.h>
#include <cerberus/Settings.h>
#include <frc2020/components/Shooter.h>

#include <rev/CANSparkMax.h>
#include <rev/CANEncoder.h>

#include <string>

namespace frc2020 {
Shooter::Shooter() {}
Shooter::~Shooter() {}

void Shooter::initialize() {
    // cfg::load(settingsPath);

    cfg::get<int>("hardware::motor_right1::pin", pin_top);
    cfg::get<int>("hardware::motor_right2::pin", pin_bottom);

	pin_top = 5;
	pin_bottom = 6;

    motor_top = new rev::CANSparkMax(pin_top, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    motor_bottom = new rev::CANSparkMax(pin_bottom, rev::CANSparkMaxLowLevel::MotorType::kBrushless);

	encoder_top = new rev::CANEncoder(*motor_top, rev::CANEncoder::EncoderType::kHallSensor, 0);
	encoder_bottom = new rev::CANEncoder(*motor_bottom, rev::CANEncoder::EncoderType::kHallSensor, 0);

	m_isInitialized = true;
    std::cout << "Shooter initialized." << std::endl;
}

void Shooter::deinitialize() {
    delete motor_top;
    delete motor_bottom;

	m_isInitialized = false;
}

void Shooter::update() {}

void Shooter::shoot(const double& top, const double& bottom) {
    motor_top->Set(top);
    motor_bottom->Set(bottom);
}
}  // namespace frc2020