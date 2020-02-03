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

	void initialize();
	void deinitialize();
	void update();

	template<typename T> void add(T* input);

	template<> void add<Analog>(Analog* input);

	template<> void add<Digital>(Digital* input);

	template<typename T> void remove(T* input);

	template<> void remove<Analog>(Analog* input);

	template<> void remove<Digital>(Digital* input);

	template<typename T> T* get(int axis);

	template<> Analog* get<Analog>(int axis);

	template<> Digital* get<Digital>(int axis);
}