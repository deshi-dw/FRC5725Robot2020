#pragma once

#include <vector>

#include <frc/PWMSpeedController.h>
#include <frc/Spark.h>
#include <frc/VictorSP.h>
#include <frc/Victor.h>
#include <frc/Talon.h>
#include <frc/Jaguar.h>

using namespace std;

#ifndef PWM_COUNT
#define PWM_COUNT 9
#endif

namespace hardware {
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
bool addPWMSpark(int pin);

/** @brief Adds a Victor PWM to the list of PWMs.
 *
 * @param pin: the pin that the PWM should use and be accessed by.
 * @return true: if the PWM is added successfully.
 * @return false: if the PWM fails to get added.
 *
 */
bool addPWMVictor(int pin);

template <class T> bool add(int pin);
template<> bool add<frc::Spark>(int pin);
template<> bool add<frc::Victor>(int pin);
template<> bool add<frc::VictorSP>(int pin);
template<> bool add<frc::Talon>(int pin);
template<> bool add<frc::Jaguar>(int pin);

inline bool internalAdd(int pin, frc::PWMSpeedController* pwm);

/** @brief Removes a PWM from the PWM list by its pin.
 *
 * @param pin: the pin of the PWM that should be removed.
 * @return true: if the PWM is removed successfully.
 * @return false: if the PWM fails to get removed.
 *
 */
bool removePWM(int pin);

bool isPWMEmpty(int pin);

void setPWMSpeed(int pin, double speed);
double getPWMSpeed(int pin);

// TODO: Replace getPWM with get<T>.
/** @brief Get a PWM from the PWM list by its pin.
 *
 * @param pin: the pin of the desired PWM.
 * @return frc::PWMSpeedController*: a pointer to the PWM with the pin or nullptr if the PWM doesn't exist.
 *
 */
frc::PWMSpeedController* getPWM(int pin);

}  // namespace Hardware
