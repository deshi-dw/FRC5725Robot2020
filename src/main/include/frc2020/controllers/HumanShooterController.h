#pragma once

class Shooter;

namespace cerberus {
struct InputAnalog;
}  // namespace cerberus

#include <cerberus/Event.h>

class HumanShooterController : public Event {
   private:
    InputAnalog speed_top = InputAnalog(2);
    InputAnalog speed_bottom = InputAnalog(3);

    Shooter* shooter;

   public:
    HumanShooterController();

    void initialize();

    void deinitialize();

    void update();

    bool condition();
};