#pragma once

#include <AHRS.h>
#include <cerberus/Event.h>
#include <cerberus/Logger.h>
#include <frc2020/Robot.h>

class EventLogMotion : public events::Event {
   public:
    EventLogMotion();

    bool condition() {
        return robotState == RobotState::TESTING;
    }

    void initialize() {
        ahrs = new AHRS(SPI::Port::kMXP);
        ahrs->Reset();
    }

    void deinitialize() {
        delete ahrs;
    }
    void update() {
        if (getRobotTime() - lastPrintTime > 2.0) {
            logger::println(logger::info, "position(m) {%d,%d}", ahrs->GetDisplacementX(), ahrs->GetDisplacementZ());
            lastPrintTime = getRobotTime();
        }
    }

   private:
    AHRS* ahrs;
    double lastPrintTime = 0.0;
};
