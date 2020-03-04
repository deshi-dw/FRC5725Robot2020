#pragma once

class Intake;
struct DigitalInput;

#include <cerberus/Event.h>

class HumanIntakeController : public Event {
   private:
    // FIXME: put definition in constructor.
    DigitalInput input_toggle = DigitalInput(1);

    Intake* intake;

   public:
    HumanIntakeController();

    void initialize();

    void deinitialize();

    void update();

    bool condition();
};