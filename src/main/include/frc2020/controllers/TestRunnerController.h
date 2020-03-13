#pragma once

class DriveTrain;
class Intake;
class Shooter;

namespace cerberus {
struct InputDigital;
}  // namespace cerberus

#include <cerberus/Event.h>

#include <functional>
#include <string>

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

    bool isAPressed();
    bool isBPressed();
    bool isXPressed();
    bool isYPressed();

    void change_value(bool is_up, bool is_down, double* value, double increment, double min, double max, const std::string& value_name);
    bool change_mode(bool is_up, int* mode, int mode_count);

    void print_controls(const std::string& task_name);
    void print_mode(int mode, const std::string& mode_name, bool is_sub);

    void start_and_stop(std::function<void()> func);

    bool start = false;
    double startTime = 0;

    double speed_increment = 0.1;
    double time_increment = 0.1;

    double drive_speed = 0.5;
    double turn_speed = 0.5;

    double right_speed = 0.5;
    double left_speed = 0.5;

    double test_duration = 1.000;

    int b_mode = 0;

    void test_drive1(bool is_init, bool in_a, bool in_b, bool in_x, bool in_y);
    void test_drive2(bool is_init, bool in_a, bool in_b, bool in_x, bool in_y);
    void test_drive3(bool is_init, bool in_a, bool in_b, bool in_x, bool in_y);
};