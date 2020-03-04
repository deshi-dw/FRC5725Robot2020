#pragma once

class DriveTrain;
struct AnalogInput;

#include <cerberus/Event.h>

class HumanDriveController : public Event {
   private:
    // FIXME: speed and turn axis are flipped in the drivetrain view.
    // FIXME: put definition in constructor.
    AnalogInput drive_speed = AnalogInput(0);
    AnalogInput drive_turn = AnalogInput(1);

    DriveTrain* drivetrain;

   public:
    HumanDriveController();

    void initialize();

    void deinitialize();

    void update();

    bool condition();
};