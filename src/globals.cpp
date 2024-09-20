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
pros::Motor RightFront(15, pros::v5::MotorGears::blue,
                       pros::v5::MotorUnits::degrees);
pros::Motor LeftFront(18, pros::v5::MotorGears::blue,
                      pros::v5::MotorUnits::degrees);
pros::Motor LeftBack(-13, pros::v5::MotorGears::blue,
                     pros::v5::MotorUnits::degrees);
pros::Motor RightBack(16, pros::v5::MotorGears::blue,
                      pros::v5::MotorUnits::degrees);
pros::Motor LeftMid(-20, pros::v5::MotorGears::blue,
                    pros::v5::MotorUnits::degrees);
pros::Motor RightMid(-17, pros::v5::MotorGears::blue,
                     pros::v5::MotorUnits::degrees);
pros::Motor IntakeMotor(2, pros::v5::MotorGears::green,
                        pros::v5::MotorUnits::degrees);
pros::Motor TopIntakeMotor(1, pros::v5::MotorGears::blue,
                           pros::v5::MotorUnits::degrees);

pros::adi::DigitalIn drivetrainToggleSwitch('G');
pros::adi::DigitalIn autonToggleSwitch('F');

pros::Optical colorSensor(4);  // placeholder port number

pros::adi::Pneumatics LatchControl('H', false);
pros::adi::Pneumatics IntakeToggle('B', false);

pros::Imu inertial_sensor(15);

pros::MotorGroup drive_left({LeftFront.get_port(), LeftMid.get_port(),
                             LeftBack.get_port()});
pros::MotorGroup drive_right({RightFront.get_port(), RightMid.get_port(),
                              RightBack.get_port()});



// Describes the lemlib objects that are used to control the autonomous
// functions of the robot.
lemlib::Drivetrain drivetrain{
    &drive_left,   // left drivetrain motors
    &drive_right,  // right drivetrain motors
    12.125,        // track width
    lemlib::Omniwheel::OLD_325,
    480,  // drivetrain rpm is 450
    2     // horizontal drift is 2
};

lemlib::OdomSensors sensors{
    nullptr,  // vertical tracking wheel 1
    nullptr,  // vertical tracking wheel 2
    nullptr,  // horizontal tracking wheel 1
    nullptr,  // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor  // inertial sensor
};

// forward/backward PID
lemlib::ControllerSettings lateral_controller{
    7.6,  // kP
    0,    // KI
    8,    // kD
    3,    // Anti Windup
    1,    // smallErrorRange
    100,  // smallErrorTimeout
    3,    // largeErrorRange
    500,  // largeErrorTimeout
    90    // slew rate
};

// turning PID
lemlib::ControllerSettings angular_controller{
    4.04,  // kP
    0,     // kI
    24.5,  // kD
    3,     // Anti Windup
    1,     // smallErrorRange
    100,   // smallErrorTimeout
    3,     // largeErrorRange
    500,   // largeErrorTimeout
    0      // slew rate
};

lemlib::ExpoDriveCurve throttle_curve(
    3,     // joystick deadband out of 127
    10,    // minimum output where drivetrain will move out of 127
    1.019  // expo curve gain
);

// input curve for steer input during driver control
lemlib::ExpoDriveCurve steer_curve(
    4,      // joystick deadband out of 127
    6,      // minimum output where drivetrain will move out of 127
    1.0053  // expo curve gain
);

lemlib::Chassis chassis(drivetrain, lateral_controller, angular_controller,
                        sensors, &throttle_curve, &steer_curve);

bool isReversed = false;

}  // namespace Globals

}  // namespace Robot