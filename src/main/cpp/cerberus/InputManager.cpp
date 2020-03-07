#include <cerberus/InputManager.h>
#include <frc/Joystick.h>

#include <vector>

#ifndef USE_WPILIB_INPUT
#define USE_WPILIB_INPUT 1
#endif

namespace cerberus {

void InputManager::initialize() {}
void InputManager::deinitialize() {}

void InputManager::update() {
    for (size_t i = 0; i < analogs.size(); i++) {
#ifdef USE_WPILIB_INPUT
        analogs[i]->value = joystick.GetRawAxis(analogs[i]->axis);
        if (analogs[i]->isSquared == true) {
            applySquared(analogs[i]);
        }
        if (analogs[i]->isNormalized == true) {
            applyNormalize(analogs[i]);
        }
        if (analogs[i]->isDeadZoned == true) {
            applyDeadZone(analogs[i]);
        }
        if (analogs[i]->isStepped == true) {
            applyStepped(analogs[i]);
        }
#else
#endif
    }

    for (size_t i = 0; i < digitals.size(); i++) {
#ifdef USE_WPILIB_INPUT
        digitals[i]->value = joystick.GetRawButton(digitals[i]->axis);
#else
#endif
    }
}

template <typename T>
void InputManager::add(T* input) {
    // TODO: Log "Type provided is not a valid input type."
}

template <>
void InputManager::add<InputAnalog>(InputAnalog* input) {
    analogs.push_back(input);
}

template <>
void InputManager::add<InputDigital>(InputDigital* input) {
    digitals.push_back(input);
}

template <typename T>
void InputManager::remove(T* input) {
    // TODO: Log "Type provided is not a valid input type."
}

template <>
void InputManager::remove<InputAnalog>(InputAnalog* input) {
    for (size_t i = 0; i < analogs.size(); i++) {
        if (analogs[i] == input) {
            analogs.erase(analogs.begin() + i);
            return;
        }
    }

    // TODO: Log "axis could not be found."
    return;
}

template <>
void InputManager::remove<InputDigital>(InputDigital* input) {
    for (size_t i = 0; i < digitals.size(); i++) {
        if (digitals[i] == input) {
            digitals.erase(digitals.begin() + i);
            return;
        }
    }

    // TODO: Log "axis could not be found."
    return;
}

template <typename T>
T* InputManager::get(int axis) {
    // TODO: Log "Type provided is not a valid input type."
}

template <>
InputAnalog* InputManager::get<InputAnalog>(int axis) {
    for (size_t i = 0; i < analogs.size(); i++) {
        if (analogs[i]->axis == axis) {
            return analogs[i];
        }
    }

    // TODO: Log "axis could not be found."
    return nullptr;
}

template <>
InputDigital* InputManager::get<InputDigital>(int axis) {
    for (size_t i = 0; i < digitals.size(); i++) {
        if (digitals[i]->axis == axis) {
            return digitals[i];
        }
    }

    // TODO: Log "axis could not be found."
    return nullptr;
}

}  // namespace cerberus