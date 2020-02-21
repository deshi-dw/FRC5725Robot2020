#pragma once

#include <cerberus/Event.h>
#include <cerberus/Inputs.h>
#include <frc2020/Robot.h>
#include <frc2020/components/Intake.h>

#include <iostream>

namespace frc2020 {
class HumanIntakeController : public events::Event {
   private:
    input::Digital input_toggle = input::Digital(1);

    frc2020::Intake* intake;

   public:
    HumanIntakeController() {}

    void initialize() {
        intake = (Intake*)events::get(typeid(Intake));

        input::add<input::Digital>(&input_toggle);

        std::cout << "HumanIntakeController initialized." << std::endl;
    }

    void deinitialize() {
        input::remove<input::Digital>(&input_toggle);
    }

    void update() {
        if (input_toggle.value) {
            intake->toggle(true);
        } else {
            intake->toggle(false);
        }
    }

    bool condition() {
        return robotState == RobotState::TELEOP || robotState == RobotState::TESTING;
    }
};
}  // namespace frc2020