#include <cerberus/Hardware.h>

#include <frc/PWM.h>

namespace hardware {
	bool addPWM(frc::PWM* pwm) {
		// TODO: Print that a pwm was added.
		// FIXME: Make sure that the channel is not already occupied.
		ptr_pwms[pwm->GetChannel()] = pwm;

		return true;
	}

	template <class T> T* getPWM(int pin) {
		if(isPWMEmpty(pin) == false) {
			return (T*)ptr_pwms[pin];
		}

		return nullptr;
	}
	template <> frc::PWM* getPWM<frc::PWM>(int pin) {
		if(isPWMEmpty(pin) == false) {
			return ptr_pwms[pin];
		}
		return nullptr;
	}

	bool removePWM(int pin) {
		// If the pwm trying to be removed doesn't exist, return false.
		if(isPWMEmpty(pin)) {
			return false;
		}

		// Delete the pwm at the index of pin.
		free(ptr_pwms[pin]);
		ptr_pwms[pin] = nullptr;

		return true;
	}

	bool isPWMEmpty(int pin) {
		return pin > (int)ptr_pwms.size() || pin < 0 || ptr_pwms[pin] == nullptr;
	}
}
