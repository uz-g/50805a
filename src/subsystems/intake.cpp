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
   if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
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

void Intake::score() {
	IntakeMotor.move(127);
	pros::delay(1500);
	IntakeMotor.brake();
}