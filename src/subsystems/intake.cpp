#include "robot/intake.h"
#include "globals.h"

using namespace Robot;
using namespace Robot::Globals;

static const int intake_speed = 600;

Intake::Intake() {
   elevated = false;
   alliance_color = false;
   controller.print(0, 0, "Intake initialized");
}


void Intake::run() {
   if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
      intake.move_velocity(intake_speed);
   } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
      intake.move_velocity(-intake_speed);
   } else{
      intake.brake();
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
void Intake::score(int delay, int direction) 
{  
   intake.move_velocity(intake_speed * direction);
	pros::delay(delay);
	intake.brake();
}

void Intake::on(int speed)
{
   if(speed == 0)
   {
	   intake.brake();
      return;
   }
   
   intake.move_velocity(intake_speed);
}

void Intake::off()
{
   on(0);
}