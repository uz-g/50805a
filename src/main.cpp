#include "main.h"

#include "globals.h"
#include "pros/motors.h"
#include "robot/auton.h"
#include "robot/intake.h"
#include "robot/latch.h"

using namespace Robot;
using namespace Robot::Globals;

/**
 * @file main.cpp
 * @brief This file contains the main code for the robot's operation.
 */

/**
 * @brief Structure that holds instances of all robot subsystems.
 */
struct RobotSubsystems {
   Robot::Autonomous autonomous;
   Robot::Drivetrain drivetrain;
   Robot::Intake intake;
   Robot::Latch latch;
} subsystem;

struct RobotScreen {
   Robot::selector_screen selector;
   Robot::status_screen status;
} screen;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void initialize() {
   //IMU Plugged in at port number 15
   chassis.calibrate();

   drive_left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
   drive_right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

   screen.selector.selector();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */

void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.<asd></asd>
 */
void competition_initialize() {}

/**6
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start
 * it from where it left off.
 */
void autonomous() {
   subsystem.autonomous.AutoDrive(subsystem.intake, subsystem.latch);
   // set position to x:0, y:0, heading:0
}

/**
 * Runs the operator control code. This function will be started in its own
 * task with the default priority and stack size whenever the robot is enabled
 * via the Field Management System or the VEX Competition Switch in the
 * operator control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart
 * the task, not resume it from where it left off.
 */


void opcontrol() 
{
   auto start_time = std::chrono::steady_clock::now();
   bool flagged = false;

   while (true) 
   {
      auto current_time = std::chrono::steady_clock::now();
      auto elapsed_time = std::chrono::duration_cast<std::chrono::seconds>(current_time - start_time).count();
      
      if(elapsed_time >= 85 && !flagged)
      {
         controller.rumble(". - . -");
         flagged = true;
      }

      subsystem.drivetrain.run();
      subsystem.latch.run();
      // Intake controller, uses the X button holded down to push the 
   
      subsystem.intake.run();
      // Intake controller, moves the left and right intakes and stops them if
      // nothing is pressed.

      pros::delay(20);
   }
}