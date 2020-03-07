#pragma once

#include <frc/Joystick.h>

#include <vector>

#ifndef USE_WPILIB_INPUT
#define USE_WPILIB_INPUT 1
#endif

namespace cerberus {

typedef struct DigitalInput {
    int axis;
    bool value;

    DigitalInput(int axis) : axis(axis) {}
} DigitalInput;

// TODO: Add multiplier atribute.
typedef struct AnalogInput {
    int axis = 0;
    double value = 0;
    double range[2] = {-1.0, 1.0};

    bool isSquared = false;
    bool isStepped = false;
    bool isNormalized = false;
    bool isDeadZoned = false;

    std::vector<double> steps;
    double deadZone = 0.01;

    AnalogInput(int axis) : axis(axis) {}
} AnalogInput;

class InputManager {
   private:
    void applyStepped(AnalogInput* analog) {}
    void applyDeadZone(AnalogInput* analog) {
        if (abs(analog->value) < analog->deadZone) {
            analog->value = 0.0f;
        }
    }
    void applyNormalize(AnalogInput* analog) {
    }
    void applySquared(AnalogInput* analog) {
        analog->value = analog->value * analog->value;
    }

#ifdef USE_WPILIB_INPUT
    frc::Joystick joystick = frc::Joystick(0);
#endif

    std::vector<AnalogInput*> analogs;
    std::vector<DigitalInput*> digitals;

   public:
    void initialize();
    void deinitialize();
    void update();

    template <typename T>
    void add(T* input);

    template <typename T>
    void remove(T* input);

    template <typename T>
    T* get(int axis);
};

}  // namespace cerberus