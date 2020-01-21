#include <cerberus/Hardware.h>

#include <frc/Spark.h>
#include <frc/Victor.h>

using namespace std;

namespace Hardware {
	bool AddPWMSpark(int pin) {
		// If a PWM already exists in the pin index, return false.
		if( ! IsPWMEmpty(pin)) {
			return false;
		}

		// Store a Spark pwm in memory and assign it's memory address to ptr_pwms[pin].
		ptr_pwms[pin] = new frc::Spark(pin);
		
		return true;
	}

	bool AddPWMVictor(int pin) {
		// If a PWM already exists in the pin index, return false.
		if( ! IsPWMEmpty(pin)) {
			return false;
		}

		// Store a Victor pwm in memory and assign it's memory address to ptr_pwms[pin].
		frc::Victor pwm = frc::Victor(pin);
		ptr_pwms[pin] = &pwm;

		return true;
	}

	void SetPWMSpeed(int pin, double speed) {
		ptr_pwms[pin]->SetSpeed(speed);
	}

	double GetPWMSpeed(int pin) {
		return ptr_pwms[pin]->GetSpeed();
	}

	bool RemovePWM(int pin) {
		// If the pwm trying to be removed doesn't exist, return false.
		if(IsPWMEmpty(pin)) {
			return false;
		}

		// Delete the pwm at the index of pin.
		free(ptr_pwms[pin]);
		ptr_pwms[pin] = nullptr;

		return true;
	}

	frc::PWMSpeedController* GetPWM(int pin) {
		// If the pwm trying to be accessed doesn't exist, return null.
		if(IsPWMEmpty(pin)) {
			return nullptr;
		}

		return ptr_pwms[pin];
	}

	bool IsPWMEmpty(int pin) {
		return pin > (int)ptr_pwms.size() || pin < 0 || ptr_pwms[pin] == nullptr;
	}
}
