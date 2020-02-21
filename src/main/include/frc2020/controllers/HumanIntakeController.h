#pragma once

#include <util/RobotState.h>
#include <cerberus/Component.h>
#include <cerberus/Inputs.h>
#include <frc2020/components/Intake.h>

namespace frc2020 {
class HumanIntakeController : public Component {
    private:
    input::Digital input_toggle = input::Digital(1);

	frc2020::Intake& intake;

    public:
	HumanIntakeController(frc2020::Intake& intake) : intake(intake) {}

    void initialize() {
        input::add<input::Digital>(&input_toggle);
		
        std::cout << "HumanIntakeController initialized." << std::endl;
    }

    void deinitialize() {
        input::remove<input::Digital>(&input_toggle);
    }

    void update() {
        if(input_toggle.value) {
		    intake.toggle(true);
        }
        else {
		    intake.toggle(false);
        }
    }

	bool updateCondition() {
		return c_robotState == RobotState::TELEOP || c_robotState == RobotState::TESTING;
	}
};
}