#pragma once

#include <cerberus/Event.h>
#include <frc/Spark.h>
#include <rev/CANSparkMax.h>

#include <string>

class Intake : public Event {
   private:
    const std::string settingsPath = "conf/intake.rcfg";
  
    frc::Spark* motor;
    rev::CANSparkMax* motor_pully1;

   public:
    enum State {
        IDLE,
        UP,
        DOWN
    };

    State state = State::IDLE;

    int channel = 0;
    int channel_pully1 = 0;

    double speed = 0.0;
    double speed_pully = 0.0;

    Intake();
    ~Intake();

    void initialize();
    void deinitialize();
    void update();
  
    bool condition();

    void setState(Intake::State newState);
    void setPulySpeed(double newSpeed);
};
