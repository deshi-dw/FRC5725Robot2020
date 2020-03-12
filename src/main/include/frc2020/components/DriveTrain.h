#pragma once

#include <cerberus/Event.h>
#include <frc/Spark.h>

#include <string>

class DriveTrain : public Event {
   private:
    const std::string settingsPath = "conf/drivetrain.rcfg";

    int pin_right1;
    int pin_right2;
    int pin_left1;
    int pin_left2;

    frc::Spark* motor_right1;
    frc::Spark* motor_right2;
    frc::Spark* motor_left1;
    frc::Spark* motor_left2;

   public:
    DriveTrain();
    ~DriveTrain();

    void initialize();
    void deinitialize();
    void update();
    bool condition();

    void driveArcade(const double& speed, const double& turn);
    void driveTank(const double& right, const double& left);
};