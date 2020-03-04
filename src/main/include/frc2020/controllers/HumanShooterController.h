#pragma once

class Shooter;
struct input::Analog;

#include <cerberus/Event.h>

class HumanShooterController : public Event {
   private:
    input::Analog speed_top = input::Analog(2);
    input::Analog speed_bottom = input::Analog(3);

    Shooter* shooter;

   public:
    HumanShooterController();

    void initialize();

    void deinitialize();

    void update();

    bool condition();
};