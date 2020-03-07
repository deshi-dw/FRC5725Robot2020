#pragma once

#include <util/RobotState.h>
#include <cerberus/Component.h>
#include <cerberus/Inputs.h>
#include <frc2020/components/Shooter.h>

namespace frc2020 {
class HumanShooterController : public Component {
    private:
    input::Analog speed_top = input::Analog(2);
    input::Analog speed_bottom = input::Analog(3);

	frc2020::Shooter& shooter;

    public:
	HumanShooterController(frc2020::Shooter& shooter) : shooter(shooter) {}

    void initialize() {
        input::add<input::Analog>(&speed_top);
        input::add<input::Analog>(&speed_bottom);

        std::cout << "HumanShooterController initialized." << std::endl;
    }

    void deinitialize() {
        input::remove<input::Analog>(&speed_top);
        input::remove<input::Analog>(&speed_bottom);

        m_isInitialized = false;
    }

    void update() {
		shooter.shoot(speed_top.value * 0.4, speed_bottom.value * 0.4);
    }

	bool updateCondition() {
		return c_robotState == RobotState::TELEOP || c_robotState == RobotState::TESTING;
	}
};
}