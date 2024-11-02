#include "robot/auton.h"
#include "globals.h"
#include "main.h" // IWYU pragma: export
#include "pros/rtos.hpp"
#include "robot/drivetrain.h"

using namespace Robot;
using namespace Robot::Globals;

Autonomous::AUTON_ROUTINE Autonomous::auton = BLUE_RIGHT;
std::string				  Autonomous::autonName;

void Autonomous::Auton1(Intake &intake, Latch &latch)
{
   //Autonomous A: Mobile Goal Steal Blue
   chassis.setPose(-60, -36, 90);

   //Move to an angle to steal mogo and create clearance
   chassis.moveToPose(-12, -36, 90, 3000);

   //Move the intake up to release the stage 1 
   intake.score(700, -1);

   //Move to pick up the mobile goal
   chassis.turnToHeading(315, 1000, {}, false);

   chassis.moveToPoint(-5, -42, 5000, {.forwards=false}, false);
   //pick up mogo
   latch.toggle();

   pros::delay(5200);
   intake.score(1000, -1);


}

void Autonomous::Auton2(Intake &intake, Latch &latch)
{
   //Autonmous B: red mogo steal

   //Move to mobile goal line
   chassis.setPose(-36, 60, 180);
   chassis.moveToPose(-36, 16, 45, 5000);
   intake.score(800, -1);

   //Move to mobile goal
   chassis.moveToPose(-48, 8, 45, 5000);

   //Clamp the mobile goal
   latch.toggle();

   //Score preloaded ring
   intake.score(3000, 1);

   //Touch the bar
   chassis.moveToPoint(60, 0, 5000);
}

void Autonomous::Auton3(Intake &intake, Latch &latch)
{
   //Autonomous C: Rings Scoring Blue 
   intake.toggle();
   intake.score(700, -1);

   //Move to mobile goal line
   chassis.setPose(-150, 60, 180);
   chassis.moveToPose(-60, 60, 180, 5000); 
   latch.toggle();

   //turn and pick up rings
   chassis.moveToPose(-60, 120, 90, 5000);
   intake.score(5000, 1);
   
   //pick up rings from center 
   chassis.moveToPose(0, -130, 0, 5000);
   intake.score(5000, 1);

   //Go touch the bar
   chassis.moveToPoint(0, 60, 5000);
}

void Autonomous::Auton4(Intake &intake, Latch &latch)
{
   //Autonomous D: Rings Scoring Red
   intake.toggle();
   intake.score(700, -1);

   //Move to mobile goal line
   chassis.setPose(150, -60, 180);
   chassis.moveToPose(60, -60, 180, 5000); 
   latch.toggle();

   //turn and pick up rings
   chassis.moveToPose(60, -120, 270, 5000);
   intake.score(5000, 1);
   
   //pick up rings from center 
   chassis.moveToPose(0, 130, 360, 5000);
   intake.score(5000, 1);
}

void Autonomous::Auton5(Intake &intake, Latch &latch)
{
   //Skills challenge autonomous

   //Chassis position: coordinate from the back of the drivetrain 
   //Chassis heading: front intake is direction

   // Step 1. We start under the red alliance stake. 
   // With the preloaded ring, we will score on the stake using our wall stake mechanism.

   chassis.setPose(-165, 0, 90, false);
   
   // -- TODO: Score on the red alliance stake

   // Step 2. We will go to pick up the top left mobile goal 
   // with our clamp facing into the mobile goal.

   chassis.turnToHeading(180, 5000, {}, false);

   chassis.moveToPoint(-120, 60, 5000, {.forwards=false}, false);
   pros::delay(200);

   latch.toggle();   

   // Step 3. We will go and score the 6 rings around the mobile goal onto our robot. 
   // This will take a lot of precise coding and movement to nail autonomously

   intake.on(600);

   // -- Score bottom right ring (1)

   chassis.turnToHeading(90, 5000, {}, false);

   chassis.moveToPoint(-60, 60, 5000, {.forwards=true}, false);
   pros::delay(200);

   // -- Score second top ring (2)

   chassis.turnToHeading(0, 5000, {}, false);

   chassis.moveToPoint(-60, 120, 5000, {.forwards=true}, false);
   pros::delay(200);

   // -- Score center top ring (3)

   chassis.turnToHeading(90, 5000, {}, false);

   chassis.moveToPoint(0, 150, 5000, {.forwards=true}, false);
   pros::delay(200);

   // -- Score corner center ring (4)

   chassis.turnToHeading(270, 5000, {}, false);

   chassis.moveToPoint(-120, 120, 5000, {.forwards=true}, false);
   pros::delay(200);

   // -- Score corner back left ring (5)

   chassis.moveToPoint(-150, 120, 5000, {.forwards=true}, false);
   pros::delay(200);

   // -- Score corner top ring (6)

   chassis.moveToPoint(-120, 150, 5000, {.forwards=true}, false);
   pros::delay(200);

   // Step 4. We will go and put the fully scored out mobile goal into the top right corner to double its points.

   chassis.moveToPose(-168, -168, 135, 5000, {.forwards=false}, false);
   pros::delay(200);

   latch.toggle();

   // Step 5. We will go to the center, and pick up the center ring on our robot. 
   // This will later be used to score on the bottom right mobile goal.

   chassis.moveToPose(0, 0, 0, 5000, {.forwards=true}, false);
   pros::delay(500);
   intake.off();

   // Step 6. We will pick up the bottom right’s mobile goal to score more rings onto.

   chassis.moveToPose(-120, 60, 45, 5000, {.forwards=false}, false);
   latch.toggle();

   // Step 7. We will pick up all of the rings in the bottom right corner. 
   // This will required high precision and a well-tuned autonomous to accomplish quickly.
}


// Takes in two parameters: The autonomous value as well as the puncher object.
void Autonomous::AutoDrive(Intake &intake, Latch &latch)
{
	// Keep the switcher running while the controller down button has not been pressed and the time period is not
	// autonomous Compare the current auton value to run the auton routine
	
	Auton1(intake, latch);
}

void Autonomous::AutonSwitcher(int autonNum)
{
	switch (autonNum) {
	case 1:
		Autonomous::autonName = "Red Left";
		Autonomous::auton	  = RED_LEFT;
		break;
	case 2:
		Autonomous::autonName = "Red Right";
		Autonomous::auton	  = RED_RIGHT;
		break;
	case -1:
		Autonomous::autonName = "Blue Left";
		Autonomous::auton	  = BLUE_LEFT;
		break;
	case -2:
		Autonomous::autonName = "Blue Right";
		Autonomous::auton	  = BLUE_RIGHT;
		break;
	}
	std::cout << "Current auton: " + Autonomous::autonName << std::endl;
}