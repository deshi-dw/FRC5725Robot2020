#pragma once

#include <cerberus/Event.h>
#include <cerberus/Inputs.h>
#include <frc2020/Robot.h>
#include <frc2020/components/Shooter.h>

#include <iostream>

namespace frc2020 {
class HumanShooterController : public events::Event {
   private:
    input::Analog speed_top = input::Analog(2);
    input::Analog speed_bottom = input::Analog(3);

    frc2020::Shooter* shooter;

   public:
    HumanShooterController() {}

    void initialize() {
        shooter = (Shooter*)events::get(typeid(Shooter));

        input::add<input::Analog>(&speed_top);
        input::add<input::Analog>(&speed_bottom);

        std::cout << "HumanShooterController initialized." << std::endl;
    }

    void deinitialize() {
        input::remove<input::Analog>(&speed_top);
        input::remove<input::Analog>(&speed_bottom);
    }

    void update() {
        shooter->shoot(speed_top.value, speed_bottom.value);
    }

    bool condition() {
        return robotState == RobotState::TELEOP || robotState == RobotState::TESTING;
    }
};
}  // namespace frc2020