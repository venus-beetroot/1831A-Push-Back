#include "lemlib/smartMotor.hpp"
#include "main.h"
#include "lemlib/chassis/chassis.hpp"
#include "pros/imu.hpp"
#include "pros/misc.h"
#include "pros/motor_group.hpp"
#include <sys/wait.h>

// ---------------------------------------
// Drivetrain & Chassis
// ---------------------------------------

pros::Motor left1(-1);
pros::Motor left2(-2);
pros::Motor left3(-3);
pros::Motor right1(8);
pros::Motor right2(9);
pros::Motor right3(10);

pros::MotorGroup leftMotors({-1, -2, -3}, pros::MotorGearset::blue); // left motor group - ports 3 (reversed), 4, 5 (reversed)
pros::MotorGroup rightMotors({8, 9, 10}, pros::MotorGearset::blue); // right motor group - ports 6, 7, 9 (reversed)

// PID settings
lemlib::Drivetrain drivetrain(&leftMotors, // left motor group
                              &rightMotors, // right motor group
                              11.6, // 11.6 inch track width
                              lemlib::Omniwheel::OLD_325, // using new 3"25' omnis
                              200, // drivetrain rpm is 200 (green direct)
                              5 // horizontal drift is 2. If we had traction wheels, it would have been 8
);

// ---------------------------------------
// Subsystem Configuration
// ---------------------------------------

pros::Controller master(pros::E_CONTROLLER_MASTER);

pros::Motor roller(-6);
pros::Motor hood(7);

pros::MotorGroup intake({-6, 7}, pros::MotorGearset::green); // front 6, back 7

pros::adi::DigitalOut doinker ('B');


// ---------------------------------------
// Sensors (Miscellaneous)
// ---------------------------------------

pros::Imu imu(20);
pros::Optical colorSort (18);

// ---------------------------------------
// Odometry
// ---------------------------------------

pros::Rotation horizontal_encoder(13); 

pros::Rotation vertical_encoder(14);

lemlib::TrackingWheel horizontal_tracking_wheel(&horizontal_encoder, lemlib::Omniwheel::NEW_275, +1.95);

lemlib::TrackingWheel vertical_tracking_wheel(&vertical_encoder, lemlib::Omniwheel::NEW_275, -1.5);

// chassis: 12.8 across, 13.5 height (tbd)
// traking cneter: 6.4, 6.75 (tbd)

lemlib::OdomSensors sensors(&vertical_tracking_wheel, // vertical tracking wheel
                            nullptr, // vertical tracking wheel 2, set to nullptr as we don't have a second one
                            &horizontal_tracking_wheel, // &horizontal_tracking_wheel
                            nullptr, // horizontal tracking wheel 2, set to nullptr as we don't have a second one
                            &imu     // inertial sensor &imu
);

// ---------------------------------------
// PID Controller
// ---------------------------------------

lemlib::ControllerSettings linearController(  6, // proportional gain (kP)
                                              -0.0045, // integral gain (kI) 0.11
                                              2, // derivative gain (kD) 1.5
                                              0, // anti windup
                                              1, // small error range, in inches
                                              200, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              75 // maximum acceleration (slew)
);

lemlib::ControllerSettings angularController(0.75, // proportional gain (kP)
                                             0.00010, // integral gain (kI)
                                             0.5, // derivative gain (kD)
                                             0, // anti windup
                                             1, // small error range, in degrees
                                             200, // small error range timeout, in milliseconds
                                             2, // large error range, in degrees
                                             500, // large error range timeout, in milliseconds
                                             0 // maximum acceleration (slew)
); 

// ---------------------------------------
// ExpoDrive Constraints
// ---------------------------------------

// input curve for throttle input during driver control
lemlib::ExpoDriveCurve throttleCurve(0, // joystick deadband out of 127
                                     10, // minimum output where drivetrain will move out of 127
                                     1 // expo curve gain 1.019 (LOG 0.9991)
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steerCurve(0, // joystick deadband out of 127
                                  10, // minimum output where drivetrain will move out of 127
                                  1.010 // expo curve gain org 1.019
);

lemlib::Chassis chassis(drivetrain, linearController, angularController, sensors, &throttleCurve, &steerCurve);
