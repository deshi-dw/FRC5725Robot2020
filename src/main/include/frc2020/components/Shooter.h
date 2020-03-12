#pragma once

namespace rev {
class CANSparkMax;
class CANEncoder;
}  // namespace rev

#include <cerberus/Event.h>

#include <string>

class Shooter : public Event {
   private:
    const std::string settingsPath = "conf/drivetrain.rcfg";

    int pin_top = 0;
    int pin_bottom = 0;

    rev::CANSparkMax* motor_top;
    rev::CANSparkMax* motor_bottom;

    rev::CANEncoder* encoder_top;
    rev::CANEncoder* encoder_bottom;

   public:
    Shooter();
    ~Shooter();

    void initialize();
    void deinitialize();
    void update();
    bool condition();

    void shoot(const double& top, const double& bottom);
};