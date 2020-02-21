#pragma once

#include <cerberus/Component.h>
#include <frc/Spark.h>

#include <string>

namespace frc2020 {

class Intake : public Component {
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

    void toggle(bool isOn);
};
}  // namespace frc2020