#include <cerberus/Hardware.h>
#include <cerberus/Logger.h>
#include <cerberus/ConfigManager.h>
#include <frc/Spark.h>
#include <frc2020/Robot.h>
#include <frc2020/components/DriveTrain.h>
#include <stdio.h>

#include <iostream>

DriveTrain::DriveTrain() {}

DriveTrain::~DriveTrain() {}

void DriveTrain::initialize() {
    // cfg::load(settingsPath);

    Robot::config->get<int>("hardware::motor_right1::pin", pin_right1);
    Robot::config->get<int>("hardware::motor_right2::pin", pin_right2);
    Robot::config->get<int>("hardware::motor_left1::pin", pin_left1);
    Robot::config->get<int>("hardware::motor_left2::pin", pin_left2);

    pin_right1 = 2;
    pin_right2 = 3;
    pin_left1 = 0;
    pin_left2 = 1;

    motor_right1 = new frc::Spark(pin_right1);
    motor_right2 = new frc::Spark(pin_right2);
    motor_left1 = new frc::Spark(pin_left1);
    motor_left2 = new frc::Spark(pin_left2);

    Robot::logger->println(Logger::info, "[DriveTrain] successfully initialized.");
}

void DriveTrain::deinitialize() {
    delete motor_right1;
    delete motor_right2;
    delete motor_left1;
    delete motor_left2;
}

void DriveTrain::driveArcade(const double& speed, const double& turn) {
    driveTank(speed + turn, speed - turn);
}

void DriveTrain::driveTank(const double& right, const double& left) {
    // TODO: Make right and left speed class variables so they can be manipulateed outside of driveTank.
    motor_right1->SetSpeed(right);
    motor_right2->SetSpeed(right);

    motor_left1->SetSpeed(left);
    motor_left2->SetSpeed(left);
}

void DriveTrain::update() {}

bool DriveTrain::condition() {
    return Robot::getRobotState() != SHUTTING_DOWN;
}