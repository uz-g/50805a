#include "robot/intake.h"

#include <cassert>

#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;

Intake::Intake() {
   elevated = false;
   alliance_color = false;
   controller.print(0, 0, "Intake initialized");
}

void Intake::run() {
   if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
      TopIntakeMotor.move_velocity(-600);
   }
   else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      IntakeMotor.move_velocity(-200);
      TopIntakeMotor.move_velocity(420);
   } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      IntakeMotor.move_velocity(200);
      TopIntakeMotor.move_velocity(-420);
   } else{
	IntakeMotor.brake();
	TopIntakeMotor.brake();
   }
}

void Intake::toggle() {
   elevated = !elevated;
   IntakeToggle.toggle();
}

/**
 * @brief Runs the intake scoring sequence
 *
 * @param delay Time in milliseconds to delay after the intake is finished running
 * @param direction Direction of the intake, should be either 1 (into) or -1 (backward)
 */
void Intake::score(int delay, int direction) {  
   direction *= -1;
	IntakeMotor.move_velocity(direction * 200);
   TopIntakeMotor.move_velocity(direction * 600);
	pros::delay(delay);
	IntakeMotor.brake();
   TopIntakeMotor.brake();
}

void Intake::on(int speed)
{
   if(speed == 0)
   {
      IntakeMotor.brake();
      TopIntakeMotor.brake();
      return;
   }

   IntakeMotor.move_velocity(speed);
   TopIntakeMotor.move_velocity(speed);
}

void Intake::off()
{
   on(0);
}