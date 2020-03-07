#pragma once

#include <util/RobotState.h>
#include <cerberus/Component.h>
#include <cerberus/Inputs.h>
#include <frc2020/components/Intake.h>

namespace frc2020 {
class HumanIntakeController : public Component {
    private:
    input::Digital input_up = input::Digital(1);
    input::Digital input_down = input::Digital(1);
    input::Analog input_pullySpeed = input::Analog(5);

	frc2020::Intake& intake;

    public:
	HumanIntakeController(frc2020::Intake& intake) : intake(intake) {}

    void initialize() {
        input::add<input::Digital>(&input_up);
        input::add<input::Digital>(&input_down);
        input::add<input::Analog>(&input_pullySpeed);
		
        std::cout << "HumanIntakeController initialized." << std::endl;
    }

    void deinitialize() {
        input::remove<input::Digital>(&input_up);
        input::remove<input::Digital>(&input_down);
        input::remove<input::Analog>(&input_pullySpeed);
    }

    void update() {
        if(input_up.value) {
		    intake.setState(Intake::State::UP);
        }
        else if(input_down.value) {
		    intake.setState(Intake::State::DOWN);
        }
        else {
		    intake.setState(Intake::State::IDLE);
        }

        intake.setPulySpeed(input_pullySpeed.value * 0.6);
    }

	bool updateCondition() {
		return c_robotState == RobotState::TELEOP || c_robotState == RobotState::TESTING;
	}
};
}