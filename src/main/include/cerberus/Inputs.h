#pragma once

#include <vector>
#include <frc/Joystick.h>

using namespace std;

#ifndef USE_WPILIB_INPUT
#define USE_WPILIB_INPUT 1
#endif

namespace input {
	typedef struct Digital {
		int axis;
		bool value;

		Digital(int axis) : axis(axis) {}
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

		Analog(int axis) : axis(axis) {}
	} Analog;

	namespace {
		void applyStepped(Analog* analog) {}
		void applyDeadZone(Analog* analog) {
			if(abs(analog->value) < analog->deadZone) {
				analog->value = 0.0f;
			}
		}
		void applyNormalize(Analog* analog) {
		}
		void applySquared(Analog* analog) {
			analog->value = analog->value * analog->value;
		}

		#ifdef USE_WPILIB_INPUT
		frc::Joystick joystick = frc::Joystick(0);
		#endif

		vector<Analog*> analogs;
		vector<Digital*> digitals;
	}

	void initialize() {}
	void deinitialize() {}

	void update() {
		for(size_t i = 0; i < analogs.size(); i++) {
		#ifdef USE_WPILIB_INPUT
			analogs[i]->value = joystick.GetRawAxis(analogs[i]->axis);
			if(analogs[i]->isSquared == true) {
				applySquared(analogs[i]);
			}
			if(analogs[i]->isNormalized == true) {
				applyNormalize(analogs[i]);
			}
			if(analogs[i]->isDeadZoned == true) {
				applyDeadZone(analogs[i]);
			}
			if(analogs[i]->isStepped == true) {
				applyStepped(analogs[i]);
			}
		#else
		#endif
		}

		for(size_t i = 0; i < digitals.size(); i++) {
			#ifdef USE_WPILIB_INPUT
			digitals[i]->value = joystick.GetRawButton(digitals[i]->axis);
			#else
			#endif
		}
	}

	template<typename T> void add(T* input) {
		// TODO: Log "Type provided is not a valid input type."
	}

	template<> void add<Analog>(Analog* input) {
		analogs.push_back(input);
	}

	template<> void add<Digital>(Digital* input) {
		digitals.push_back(input);
	}

	template<typename T> void remove(T* input) {
		// TODO: Log "Type provided is not a valid input type."
	}

	template<> void remove<Analog>(Analog* input) {
		for(size_t i = 0; i < analogs.size(); i++) {
			if(analogs[i] == input) {
				analogs.erase(analogs.begin() + i);
				return;
			}
		}

		// TODO: Log "axis could not be found."
		return;
	}

	template<> void remove<Digital>(Digital* input) {
		for(size_t i = 0; i < digitals.size(); i++) {
			if(digitals[i] == input) {
				digitals.erase(digitals.begin() + i);
				return;
			}
		}

		// TODO: Log "axis could not be found."
		return;
	}

	template<typename T> T* get(int axis) {
		// TODO: Log "Type provided is not a valid input type."
	}

	template<> Analog* get<Analog>(int axis) {
		for(size_t i = 0; i < analogs.size(); i++) {
			if(analogs[i]->axis == axis) {
				return analogs[i];
			}
		}

		// TODO: Log "axis could not be found."
		return nullptr;
	}

	template<> Digital* get<Digital>(int axis) {
		for(size_t i = 0; i < digitals.size(); i++) {
			if(digitals[i]->axis == axis) {
				return digitals[i];
			}
		}

		// TODO: Log "axis could not be found."
		return nullptr;
	}
}