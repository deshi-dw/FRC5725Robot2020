#include <cerberus/Logger.h>
#include <cerberus/ConfigManager.h>
#include <frc2020/Robot.h>
#include <frc2020/components/Shooter.h>
#include <rev/CANEncoder.h>
#include <rev/CANSparkMax.h>

#include <string>

Shooter::Shooter() {}
Shooter::~Shooter() {}

void Shooter::initialize() {
    // cfg::load(settingsPath);

    Robot::config->get<int>("hardware::motor_right1::pin", pin_top);
    Robot::config->get<int>("hardware::motor_right2::pin", pin_bottom);

    pin_top = 5;
    pin_bottom = 6;

    motor_top = new rev::CANSparkMax(pin_top, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
    motor_bottom = new rev::CANSparkMax(pin_bottom, rev::CANSparkMaxLowLevel::MotorType::kBrushless);

    encoder_top = new rev::CANEncoder(*motor_top, rev::CANEncoder::EncoderType::kHallSensor, 0);
    encoder_bottom = new rev::CANEncoder(*motor_bottom, rev::CANEncoder::EncoderType::kHallSensor, 0);

    Robot::logger->println(Logger::info, "[Shooter] successfully initialized.");
}

void Shooter::deinitialize() {
    delete motor_top;
    delete motor_bottom;
}

void Shooter::update() {}

bool Shooter::condition() {
    return Robot::getRobotState() != RobotState::SHUTTING_DOWN;
}

void Shooter::shoot(const double& top, const double& bottom) {
    motor_top->Set(top);
    motor_bottom->Set(bottom);
}