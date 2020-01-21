#pragma once

#include <frc/PWMSpeedController.h>
#include <vector>

using namespace std;

#ifndef PWM_COUNT
#define PWM_COUNT 9
#endif

namespace Hardware {
namespace {
vector<frc::PWMSpeedController*> ptr_pwms = vector<frc::PWMSpeedController*>(PWM_COUNT);
}

/** @brief Adds a Spark PWM to the list of PWMs.
 *
 * @param pin: the pin that the PWM should use and be accessed by.
 * @return true: if the PWM is added successfully.
 * @return false: if the PWM fails to get added.
 *
 */
bool AddPWMSpark(int pin);

/** @brief Adds a Victor PWM to the list of PWMs.
 *
 * @param pin: the pin that the PWM should use and be accessed by.
 * @return true: if the PWM is added successfully.
 * @return false: if the PWM fails to get added.
 *
 */
bool AddPWMVictor(int pin);

/** @brief Removes a PWM from the PWM list by its pin.
 *
 * @param pin: the pin of the PWM that should be removed.
 * @return true: if the PWM is removed successfully.
 * @return false: if the PWM fails to get removed.
 *
 */
bool RemovePWM(int pin);

bool IsPWMEmpty(int pin);

void SetPWMSpeed(int pin, double speed);
double GetPWMSpeed(int pin);

/** @brief Get a PWM from the PWM list by its pin.
 *
 * @param pin: the pin of the desired PWM.
 * @return frc::PWMSpeedController*: a pointer to the PWM with the pin or nullptr if the PWM doesn't exist.
 *
 */
frc::PWMSpeedController* GetPWM(int pin);

}  // namespace Hardware
