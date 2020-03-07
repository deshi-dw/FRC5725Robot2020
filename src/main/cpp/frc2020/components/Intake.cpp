#pragma once

#include <frc2020/components/Intake.h>
#include <cerberus/Hardware.h>
#include <cerberus/Settings.h>

#include <rev/CANSparkMax.h>

namespace frc2020 {
Intake::Intake() { }
Intake::~Intake() { }

void Intake::initialize() {
    cfg::get<int>("hardware::motor_intake1::channel", channel);
    cfg::get<double>("hardware::motor_intake1::set_speed", speed);
    
    channel = 4;
    channel_pully1 = 8;

	speed = 1.0;
	speed_pully = 0.30;

    motor = new frc::Spark(channel);
    motor_pully1 = new rev::CANSparkMax(channel_pully1, rev::CANSparkMaxLowLevel::MotorType::kBrushless);
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

void Intake::setState(Intake::State newState) {
    state = newState;
}
void Intake::setPulySpeed(double newSpeed) {
    speed_pully = newSpeed;
}

}  // namespace frc2020