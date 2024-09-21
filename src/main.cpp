#include "main.h"

#include "globals.h"
#include "pros/apix.h"
#include "pros/motors.h"

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
   if (pros::c::registry_get_plugged_type(15) == pros::c::E_DEVICE_IMU) {
      chassis.calibrate();
   }
   chassis.setPose(0, 0, 0);

   screen.selector.selector();

   drive_left.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
   drive_right.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
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
   //subsystem.autonomous.AutoDrive(subsystem.intake, subsystem.latch); 
   //Drive forward towards center goal and pick it up
   
   chassis.setPose(0, 0, 0);
   chassis.turnToHeading(90.0f, 100000);
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
      
      if(elapsed_time >= 72 && !flagged)
      {
         controller.rumble(". - . -");
         flagged = true;
      }

      if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) 
      {
         isReversed = !isReversed;
      }

      if(isReversed) controller.print(0, 0, "REVERSED MODE    ");
      else controller.print(0, 0, "NORMAL MODE    ");
      
      //prints the time left in the match in the format MM:SS

      subsystem.drivetrain.run();
      subsystem.latch.run();
      // Intake controller, uses the X button holded down to push the 
   
      subsystem.intake.run();
      // Intake controller, moves the left and right intakes and stops them if
      // nothing is pressed.

      pros::delay(20);
   }
}