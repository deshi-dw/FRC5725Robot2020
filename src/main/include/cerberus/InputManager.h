#pragma once

#include <frc/Joystick.h>

#include <vector>

#ifndef USE_WPILIB_INPUT
#define USE_WPILIB_INPUT 1
#endif

namespace cerberus {

typedef struct InputDigital {
    int axis;
    bool value;

    InputDigital(int axis) : axis(axis) {}
} InputDigital;

// TODO: Add multiplier atribute.
typedef struct InputAnalog {
    int axis = 0;
    double value = 0;
    double range[2] = {-1.0, 1.0};

    bool isSquared = false;
    bool isStepped = false;
    bool isNormalized = false;
    bool isDeadZoned = false;

    std::vector<double> steps;
    double deadZone = 0.01;

    InputAnalog(int axis) : axis(axis) {}
} InputAnalog;

class InputManager {
   private:
    void applyStepped(InputAnalog* analog) {}
    void applyDeadZone(InputAnalog* analog) {
        if (abs(analog->value) < analog->deadZone) {
            analog->value = 0.0f;
        }
    }
    void applyNormalize(InputAnalog* analog) {
    }
    void applySquared(InputAnalog* analog) {
        analog->value = analog->value * analog->value;
    }

#ifdef USE_WPILIB_INPUT
    frc::Joystick joystick = frc::Joystick(0);
#endif

    std::vector<InputAnalog*> analogs;
    std::vector<InputDigital*> digitals;

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