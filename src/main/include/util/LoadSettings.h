#pragma once

#include <cerberus/Hardware.h>
#include <cerberus/Inputs.h>
#include <cerberus/Settings.h>
#include <frc/Spark.h>

#include <string>

frc::Spark* loadPWM_spark(const std::string& motorName) {
    int pin;
    bool reversed;
    bool safety;

    if (cfg::get<int>(motorName + "::pin", pin)) {
        // If "pin" is in the motor config, create a motor.
        frc::Spark* spark = new frc::Spark(pin);

        if (cfg::get<bool>(motorName + "::reversed", reversed)) {
            // If reversed exists, set if the motor is reversed.
            spark->SetInverted(reversed);
        }

        if (cfg::get<bool>(motorName + "::safety", safety)) {
            // If safety exists, set if the motor safety is enabled.
            spark->SetSafetyEnabled(safety);
        }

        if (hardware::addPWM(spark)) {
            // If the motor was added successfully, return the motor pointer.
            return spark;
        }

        // If the motor was not added, delete the object.
        delete spark;
    }

    // If all else fails, return nullptr.
    return nullptr;
}

// input::Analog* loadInput_analog(const std::string& analogName) {
// 	input::Analog* analog = new input::Analog(0);

// 	if(cfg::get<int>(analogName + "::axis", analog->axis)) {
// 		cfg::get<bool>(analogName + "::normalized", analog->isNormalized);
// 		cfg::get<bool>(analogName + "::deadzoned", analog->isDeadZoned);
// 		cfg::get<bool>(analogName + "::squared", analog->isSquared);
// 		cfg::get<bool>(analogName + "::stepped", analog->isStepped);

// 		cfg::get<double>(analogName + "::deadzone", analog->deadZone);

// 		vector<double> range = vector<double>();
// 		cfg::get<vector<double>>(analogName + "::deadzone", range);
// 	}
// }