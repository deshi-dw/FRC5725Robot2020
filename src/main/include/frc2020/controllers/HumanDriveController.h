#pragma once

#include <cerberus/Event.h>
#include <cerberus/Events.h>
#include <cerberus/Inputs.h>
#include <frc2020/Robot.h>
#include <frc2020/components/DriveTrain.h>
#include <stdio.h>

namespace frc2020 {
class HumanDriveController : public events::Event {
   private:
    // FIXME: speed and turn axis are flipped in the drivetrain view.
    input::Analog drive_speed = input::Analog(0);
    input::Analog drive_turn = input::Analog(1);

    frc2020::DriveTrain* drivetrain;

   public:
    HumanDriveController() {}

    void initialize() {
        drivetrain = (DriveTrain*)events::get(typeid(DriveTrain));

        // drive_speed.isDeadZoned = true;
        drive_speed.deadZone = 0.15;

        // drive_turn.isDeadZoned = true;
        drive_turn.deadZone = 0.15;

        input::add<input::Analog>(&drive_speed);
        input::add<input::Analog>(&drive_turn);

        std::cout << "HumanDriveController initialized." << std::endl;
    }
    void deinitialize() {
        input::remove<input::Analog>(&drive_speed);
        input::remove<input::Analog>(&drive_turn);
    }

    void update() {
        drivetrain->driveArcade(drive_speed.value * 0.4, drive_turn.value * 0.4);
    }

    bool condition() {
        return robotState == RobotState::TELEOP || robotState == RobotState::TESTING;
    }
};
}  // namespace frc2020