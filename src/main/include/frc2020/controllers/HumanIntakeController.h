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
    InputDigital input_toggle = InputDigital(1);

    Intake* intake;

   public:
    HumanIntakeController();

    void initialize();

    void deinitialize();

    void update();

    bool condition();
};