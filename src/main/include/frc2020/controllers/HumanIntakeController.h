#pragma once

class Intake;
struct input::Digital;

#include <cerberus/Event.h>

class HumanIntakeController : public events::Event {
   private:
    // FIXME: put definition in constructor.
    input::Digital input_toggle = input::Digital(1);

    Intake* intake;

   public:
    HumanIntakeController();

    void initialize();

    void deinitialize();

    void update();

    bool condition();
};