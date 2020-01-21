#pragma once

#include<vector>

namespace Inputs {
	typedef struct Button {
		int axis;
		bool value;
	} Button;

	typedef struct Analog {
		int axis = 0;
		double value = 0;
		
		bool isSquared = false;
		bool isStepped = false;
		bool isRanged = false;
		bool isDeadZoned = false;

		std::vector<double> steps;
		double range[2] = { 0, 1 };
		double deadZone = 0.01;

	} Analog;
}