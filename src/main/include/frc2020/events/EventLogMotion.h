#pragma once

#include <frc/SPI.h>
#include <AHRS.h>
#include <cerberus/Event.h>
#include <cerberus/Logger.h>
#include <frc2020/Robot.h>

class EventLogMotion : public Event {
   public:
    EventLogMotion();

    bool condition() {
        return Robot::getRobotState() == RobotState::TESTING;
    }

    void initialize() {
        ahrs = new AHRS(frc::SPI::Port::kMXP);
        ahrs->Reset();
    }

    void deinitialize() {
        delete ahrs;
    }
    void update() {
        if (Robot::getRobotTime() - lastPrintTime > 2.0) {
            Robot::logger->println(cerberus::Logger::info, "position(m) {%d,%d}", ahrs->GetDisplacementX(), ahrs->GetDisplacementZ());
            lastPrintTime = Robot::getRobotTime();
        }
    }

   private:
    AHRS* ahrs;
    double lastPrintTime = 0.0;
};
