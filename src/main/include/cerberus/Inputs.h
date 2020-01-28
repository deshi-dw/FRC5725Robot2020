#pragma once

#include <vector>
#include <frc/wpilib.h>

using namespace std;

#define USE_WPILIB_INPUT 1

namespace Inputs {
	typedef struct Digital {
		int axis;
		bool value;
	} Digital;

	typedef struct Analog {
		int axis = 0;
		double value = 0;
		double range[2] = { -1.0, 1.0 };

		bool isSquared = false;
		bool isStepped = false;
		bool isNormalized = false;
		bool isDeadZoned = false;

		std::vector<double> steps;
		double deadZone = 0.01;

	} Analog;

	namespace {
		void ApplyStepped(Analog& analog);
		void ApplyDeadZone(Analog& analog) {
			if(abs(analog.value) < analog.deadZone) {
				analog.value = 0.0f;
			}
		}
		void ApplyNormalize(Analog& analog) {
		}
		void ApplySquared(Analog& analog) {
			analog.value = analog.value * analog.value;
		}

		#ifdef USE_WPILIB_INPUT
		frc::Joystick joystick = frc::Joystick(0);
		#endif

		vector<Analog&> analogs;
		vector<Digital&> digitals;
	}

	void Initalize() {}

	void Update() {
		for(int i = 0; i < analogs.size(); i++) {
		#ifdef USE_WPILIB_INPUT
			analogs[i].value = joystick.GetRawAxis(analogs[i].axis);
			if(analogs[i].isSquared == true) {
				ApplySquared(analogs[i]);
			}
			if(analogs[i].isNormalized == true) {
				ApplyNormalize(analogs[i]);
			}
			if(analogs[i].isDeadZoned == true) {
				ApplyDeadZone(analogs[i]);
			}
			if(analogs[i].isStepped == true) {
				ApplyStepped(analogs[i]);
			}
		#else
		#endif
		}

		for(int i = 0; i < digitals.size(); i++) {
			#ifdef USE_WPILIB_INPUT
			digitals[i].value = joystick.GetRawButton(digitals[i].axis);
			#else
			#endif
		}
	}

	template<typename T> void Add(T& input) {
		// TODO: Log "Type provided is not a valid input type."
	}

	template<> void Add<Analog>(Analog& input) {
		analogs.push_back(input);
	}

	template<> void Add<Digital>(Digital& input) {
		digitals.push_back(input);
	}

	template<typename T> void Remove(T* input) {
		// TODO: Log "Type provided is not a valid input type."
	}

	template<> void Remove<Analog>(Analog* input) {
		for(int i = 0; i < analogs.size(); i++) {
			if(&analogs[i] == input) {
				analogs.erase(analogs.begin() + i);
				return;
			}
		}
	}

	template<> void Remove<Digital>(Digital* input) {
		for(int i = 0; i < digitals.size(); i++) {
			if(&digitals[i] == input) {
				digitals.erase(digitals.begin() + i);
				return;
			}
		}
	}

	template<typename T> T& Get(int axis) {
		// TODO: Log "Type provided is not a valid input type."
	}

	template<> Analog& Get<Analog>(int axis) {
		for(int i = 0; i < analogs.size(); i++) {
			if(analogs[i].axis == axis) {
				return analogs[i];
			}
		}
	}

	template<> Digital& Get<Digital>(int axis) {
		for(int i = 0; i < digitals.size(); i++) {
			if(digitals[i].axis == axis) {
				return digitals[i];
			}
		}
	}
}