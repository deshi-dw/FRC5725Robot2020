#pragma once

class DriveTrain;

namespace cerberus {
struct InputAnalog;
}  // namespace cerberus

#include <cerberus/Event.h>

using namespace cerberus;

class HumanDriveController : public Event {
   private:
    // FIXME: speed and turn axis are flipped in the drivetrain view.
    // FIXME: put definition in constructor.
    InputAnalog drive_speed = InputAnalog(0);
    InputAnalog drive_turn = InputAnalog(1);

    InputDigital toggle_drive_straight = InputDigital(2);
    InputDigital toggle_drive_turn = InputDigital(3);

    DriveTrain* drivetrain;

   public:
    HumanDriveController();

    void initialize();

    void deinitialize();

    void update();

    bool condition();
};
