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

    channel = 6;
    speed = 1.0;

    motor = new frc::Spark(channel);

    Robot::logger->println(Logger::info, "[Intake] successfully initialized.");
}

void Intake::deinitialize() {
    delete motor;
}
void Intake::update() {
    if (m_isOn == true) {
        motor->SetSpeed(speed);
    } else {
        motor->StopMotor();
    }
}

bool Intake::condition() {
    return Robot::getRobotState() != RobotState::SHUTTING_DOWN;
}

void Intake::toggle(bool isOn) {
    m_isOn = isOn;
}