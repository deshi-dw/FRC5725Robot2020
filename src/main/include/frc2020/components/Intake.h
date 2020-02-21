#pragma once

#include <cerberus/Event.h>
#include <frc/Spark.h>

#include <string>

namespace frc2020 {

class Intake : public events::Event {
   private:
    const std::string settingsPath = "conf/intake.rcfg";
    frc::Spark* motor;

    bool m_isOn;

   public:
    int channel = 0;
    double speed = 0.0;

    Intake();
    ~Intake();

    void initialize();
    void deinitialize();
    void update();
    bool condition();

    void toggle(bool isOn);
};
}  // namespace frc2020