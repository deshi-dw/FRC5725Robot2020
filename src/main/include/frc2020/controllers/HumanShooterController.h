#pragma once

class Shooter;
struct AnalogInput;

#include <cerberus/Event.h>

class HumanShooterController : public Event {
   private:
    AnalogInput speed_top = AnalogInput(2);
    AnalogInput speed_bottom = AnalogInput(3);

    Shooter* shooter;

   public:
    HumanShooterController();

    void initialize();

    void deinitialize();

    void update();

    bool condition();
};