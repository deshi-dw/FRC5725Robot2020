#pragma once

class DriveTrain;
class Intake;
class Shooter;

namespace cerberus {
struct InputDigital;
}  // namespace cerberus

#include <cerberus/Event.h>

using namespace cerberus;

class TestRunnerController : public Event {
   private:
    InputDigital buttonA = InputDigital(2);
    InputDigital buttonB = InputDigital(3);
    InputDigital buttonX = InputDigital(1);
    InputDigital buttonY = InputDigital(4);

    InputDigital buttonNext = InputDigital(6);
    InputDigital buttonPrev = InputDigital(5);

    DriveTrain* drivetrain;
    Intake* intake;
    Shooter* shooter;

    bool previousIsInputDown = false;
    bool isInputDown = false;

    int previousMode = -1;
    int selectedMode = 0;
    int modeCount = 2;

   public:
    TestRunnerController();
    void initialize();

    void deinitialize();

    void update();

    bool condition();

    bool start = false;
    double startTime = 0;

    double drive_speed = 0.5;
    double turn_speed = 0.5;

    void test_drive1(bool is_init, bool in_a, bool in_b, bool in_x, bool in_y);

    void test_drive2(bool is_init, bool in_a, bool in_b, bool in_x, bool in_y);
};