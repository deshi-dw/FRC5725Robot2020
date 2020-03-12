#pragma once

class Intake;

namespace cerberus {
struct InputDigital;
}  // namespace cerberus

#include <cerberus/Event.h>

using namespace cerberus;

class HumanIntakeController : public Event {
   private:
    // FIXME: put definition in constructor.
    InputDigital input_up = InputDigital(1);
    InputDigital input_down = InputDigital(1);
    InputAnalog input_pullySpeed = InputAnalog(5);

    Intake* intake;

   public:
    HumanIntakeController();

    void initialize();

    void deinitialize();

    void update();

    bool condition();
};