#pragma once

#include <frc2020/components/Intake.h>
#include <cerberus/Hardware.h>
#include <cerberus/Settings.h>

#include <frc/Spark.h>

namespace frc2020 {
Intake::Intake() { }
Intake::~Intake() { }

void Intake::initialize() {
    cfg::get<int>("hardware::motor_intake1::channel", channel);
    cfg::get<double>("hardware::motor_intake1::set_speed", speed);
    
    channel = 6;
    channel_pully1 = 7;

	speed = 0.0;

    motor = new frc::Spark(channel);
    motor_pully1 = new frc::Spark(channel_pully1);
}

void Intake::deinitialize() {
    delete motor;
    delete motor_pully1;
}
void Intake::update() {
    if(m_isOn == true) {
        motor->SetSpeed(speed);
        motor_pully1->SetSpeed(speed);
    }
	else {
		motor->StopMotor();
        motor_pully1->StopMotor();
	}
}

void Intake::toggle(bool isOn) {
    m_isOn = isOn;
}

}  // namespace frc2020