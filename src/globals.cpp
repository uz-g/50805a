#include "globals.h"

/*
 * Although the following constants belong in their own seperate
 * files(auton.cpp, drivetriain.cpp), they are put here in order to maintain a
 * common location for all of the constants used by the program to belong in.
 * NOTE: This is the location where these variables are put into memory, but
 * they can be otherwise modified throughout the program.
 */

// Defines the objects that are used by the program for each of the individual
// subsystems.

namespace Robot {
namespace Globals {

pros::Controller controller(pros::E_CONTROLLER_MASTER);

pros::MotorGroup intake({2, 3}, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);

pros::adi::DigitalIn drivetrainToggleSwitch('G');
pros::adi::DigitalIn autonToggleSwitch('F');

pros::adi::Pneumatics LatchControl('H', false);
pros::adi::Pneumatics IntakeToggle('B', false);

pros::Imu inertial_sensor(12);

pros::MotorGroup drive_right({16, -17, 15}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
pros::MotorGroup drive_left({-13, 18 , -11}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);

// Describes the lemlib objects that are used to control the autonomous
// functions of the robot.
lemlib::Drivetrain drivetrain{
    &drive_left,  // left drivetrain motors
    &drive_right, // right drivetrain motors
    12,       // track width
    lemlib::Omniwheel::OLD_325,
    480, // drivetrain rpm
    2    // horizontal drift is 2
};

lemlib::OdomSensors sensors{
    nullptr,         // vertical tracking wheel 1
    nullptr,         // vertical tracking wheel 2
    nullptr,         // horizontal tracking wheel 1
    nullptr,         // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};

// forward/backward PID
lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

// turning PID
lemlib::ControllerSettings angular_controller(2,  // proportional gain (kP)
                                              0,  // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);

lemlib::ExpoDriveCurve throttle_curve(5,    // joystick deadband out of 127
                                      10,   // minimum output where drivetrain will move out of 127
                                      1.011 // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(4,     // joystick deadband out of 127
                                   6,     // minimum output where drivetrain will move out of 127
                                   1.0053 // expo curve gain
);

lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller, sensors, &throttle_curve, &steer_curve);

} // namespace Globals

} // namespace Robot