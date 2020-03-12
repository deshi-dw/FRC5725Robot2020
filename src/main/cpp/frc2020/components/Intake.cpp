#pragma once

#include <cerberus/Hardware.h>
#include <cerberus/Logger.h>
#include <cerberus/ConfigManager.h>
#include <frc/Spark.h>
#include <frc2020/Robot.h>
#include <frc2020/components/Intake.h>

Intake::Intake() {}
Intake::~Intake() {}

void Intake::initialize() {
    Robot::config->get<int>("hardware::motor_intake1::channel", channel);
    Robot::config->get<double>("hardware::motor_intake1::set_speed", speed);

    channel = 4;
    channel_pully1 = 8;

    speed = 0.9;
    speed_pully = 0.30;

    motor = new frc::Spark(channel);
    motor_pully1 = new rev::CANSparkMax(channel_pully1, rev::CANSparkMaxLowLevel::MotorType::kBrushless);

    Robot::logger->println(Logger::info, "[Intake] successfully initialized.");
}

void Intake::deinitialize() {
    delete motor;
    delete motor_pully1;
}
void Intake::update() {
    if(state == State::UP) {
        motor->SetSpeed(speed);
        motor_pully1->Set(speed_pully);
    }
    else if(state == State::DOWN) {
        motor->SetSpeed(-speed);
        motor_pully1->Set(-speed_pully);
    }
	else {
		motor->StopMotor();
        motor_pully1->StopMotor();
	}
}

bool Intake::condition() {
    return Robot::getRobotState() != RobotState::SHUTTING_DOWN;
}

void Intake::setState(Intake::State newState) {
    state = newState;
}
void Intake::setPulySpeed(double newSpeed) {
    speed_pully = newSpeed;
}