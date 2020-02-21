#pragma once

#include <frc/AnalogInput.h>
#include <frc/CAN.h>
#include <frc/DigitalInput.h>
#include <frc/DigitalOutput.h>
#include <frc/Jaguar.h>
#include <frc/PWMSpeedController.h>
#include <frc/Spark.h>
#include <frc/Talon.h>
#include <frc/Victor.h>
#include <frc/VictorSP.h>
#include <rev/SparkMax.h>

#include <vector>

#ifndef PWM_COUNT
#define PWM_COUNT 9
#endif

#ifndef DIO_COUNT
#define DIO_COUNT 9
#endif

#ifndef AIO_COUNT
#define AIO_COUNT 3
#endif

namespace hardware {
namespace {
std::vector<frc::PWM*> ptr_pwms = std::vector<frc::PWM*>(PWM_COUNT);
std::vector<frc::DigitalInput*> ptr_di = std::vector<frc::DigitalInput*>(DIO_COUNT);
std::vector<frc::DigitalOutput*> ptr_do = std::vector<frc::DigitalOutput*>(DIO_COUNT);
std::vector<frc::AnalogInput*> ptr_ai = std::vector<frc::AnalogInput*>(AIO_COUNT);
}  // namespace

bool addPWM(frc::PWM* pwm);
template <class T>
T* getPWM(int pin);
template <>
frc::PWM* getPWM<frc::PWM>(int pin);

/** @brief Removes a PWM from the PWM list by its pin.
 *
 * @param pin: the pin of the PWM that should be removed.
 * @return true: if the PWM is removed successfully.
 * @return false: if the PWM fails to get removed.
 *
 */
bool removePWM(int pin);

bool isPWMEmpty(int pin);

}  // namespace hardware
