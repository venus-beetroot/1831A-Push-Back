#ifndef ROBOT_CONFIG_HPP
#define ROBOT_CONFIG_HPP

#include "lemlib/chassis/chassis.hpp"
#include "lemlib/smartMotor.hpp"
#include "pros/optical.hpp"

// ---------------------------------------
// Drivetrain & Chassis
// ---------------------------------------

extern pros::Motor left1;
extern pros::Motor left2;
extern pros::Motor left3;
extern pros::Motor right1;
extern pros::Motor right2;
extern pros::Motor right3;

extern pros::MotorGroup leftMotors;
extern pros::MotorGroup rightMotors;
extern lemlib::Drivetrain drivetrain;

// ---------------------------------------
// Subsystem Configuration
// ---------------------------------------
extern pros::Controller master;
extern pros::Motor roller;
extern pros::Motor hood;
extern pros::MotorGroup intake;
extern pros::adi::DigitalOut doinker;

// ---------------------------------------
// Sensors (Miscellaneous)
// ---------------------------------------
extern pros::Imu imu;
extern pros::Optical colorSort;

// ---------------------------------------
// Odometry
// ---------------------------------------
extern pros::Rotation horizontal_encoder;
extern pros::Rotation vertical_encoder;
extern lemlib::TrackingWheel horizontal_tracking_wheel;
extern lemlib::TrackingWheel vertical_tracking_wheel;
extern lemlib::OdomSensors sensors;

// ---------------------------------------
// PID Controller
// ---------------------------------------
extern lemlib::ControllerSettings linearController;
extern lemlib::ControllerSettings angularController;

// ---------------------------------------
// ExpoDrive Constraints
// ---------------------------------------
extern lemlib::ExpoDriveCurve throttleCurve;
extern lemlib::ExpoDriveCurve steerCurve;
extern lemlib::Chassis chassis;

#endif // ROBOT_CONFIG_HPP
