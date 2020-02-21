#pragma once

#include <util/RobotState.h>
#include <cerberus/Component.h>
#include <cerberus/Inputs.h>
#include <frc2020/components/DriveTrain.h>

#include<stdio.h>

namespace frc2020 {
class HumanDriveController : public Component {
    private:
    // FIXME: speed and turn axis are flipped in the drivetrain view.
    input::Analog drive_speed = input::Analog(0);
    input::Analog drive_turn = input::Analog(1);

	frc2020::DriveTrain& drivetrain;

    public:
	HumanDriveController(frc2020::DriveTrain& drivetrain) : drivetrain(drivetrain) {}

    void initialize() {
        // drive_speed.isDeadZoned = true;
        drive_speed.deadZone = 0.15;

        // drive_turn.isDeadZoned = true;
        drive_turn.deadZone = 0.15;

        input::add<input::Analog>(&drive_speed);
        input::add<input::Analog>(&drive_turn);

		// drivetrain.initialize();

        m_isInitialized = true;
        std::cout << "HumanDriveController initialized." << std::endl;
    }
    void deinitialize() {
        input::remove<input::Analog>(&drive_speed);
        input::remove<input::Analog>(&drive_turn);

		// drivetrain.deinitialize();

        m_isInitialized = false;
    }

    void update() {
        drivetrain.driveArcade(drive_speed.value * 0.4, drive_turn.value * 0.4);

        // std::cout << "human drive speed:" << drive_speed.value << std::endl;
        // std::cout << "human drive turn:" << drive_turn.value << std::endl;
    }

	bool updateCondition() {
		return c_robotState == RobotState::TELEOP || c_robotState == RobotState::TESTING;
	}
};
}