#pragma once

#include <cerberus/Component.h>

#include <rev/CANSparkMax.h>
#include <rev/CANEncoder.h>

#include <string>

namespace frc2020 {

class Shooter : public Component {
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

    void shoot(const double& top, const double& bottom);
};
}  // namespace frc2020