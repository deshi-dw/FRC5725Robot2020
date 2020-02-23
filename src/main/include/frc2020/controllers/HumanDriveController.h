#pragma once

class DriveTrain;
struct input::Analog;

#include <cerberus/Event.h>

class HumanDriveController : public events::Event {
   private:
    // FIXME: speed and turn axis are flipped in the drivetrain view.
    // FIXME: put definition in constructor.
    input::Analog drive_speed = input::Analog(0);
    input::Analog drive_turn = input::Analog(1);

    DriveTrain* drivetrain;

   public:
    HumanDriveController();

    void initialize();

    void deinitialize();

    void update();

    bool condition();
};