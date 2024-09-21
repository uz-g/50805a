#include "robot/auton.h"
#include "globals.h"
#include "main.h" // IWYU pragma: export

using namespace Robot;
using namespace Robot::Globals;

Autonomous::AUTON_ROUTINE Autonomous::auton = RED_LEFT;
std::string				  Autonomous::autonName;

ASSET(red_right_pt1_txt);
ASSET(red_right_pt2_txt);
ASSET(red_right_pt3_txt);
ASSET(red_right_pt4_txt);
ASSET(red_right_pt5_txt);

ASSET(red_left_pt1_txt);
ASSET(red_left_pt2_txt);
ASSET(red_left_pt3_txt);
ASSET(red_left_pt4_txt);
ASSET(red_left_pt5_txt);

// Red Left
void Autonomous::Auton1(Intake &intake, Latch &latch)
{
	chassis.setPose(-150, 60, 0);
	
	//drop intake
	// chassis.moveToPoint(-120, 60, 500);

	drive_left.move_relative(1000, 600);
	drive_right.move_relative(-1000, 600);
	TopIntakeMotor.move_relative(560, 350); 



	
}

// Red Right
void Autonomous::Auton2(Intake &intake, Latch &latch)
{
	
}

// AWP (stealing cetner mogo)
void Autonomous::Auton3(Intake &intake, Latch &latch)
{
	
}

// AWP (not stealing cetner mogo)
void Autonomous::Auton4(Intake &intake, Latch &latch)
{
	
}


// Takes in two parameters: The autonomous value as well as the puncher object.
void Autonomous::AutoDrive(Intake &intake, Latch &latch)
{
	// Keep the switcher running while the controller down button has not been pressed and the time period is not
	// autonomous Compare the current auton value to run the auton routine
	
	switch (Autonomous::auton) {
	case RED_LEFT:
		Auton1(intake, latch);
		break;
	case RED_RIGHT:
		Auton2(intake, latch);
		break;
	case BLUE_LEFT:
		Auton3(intake, latch);
		break;
	case BLUE_RIGHT:
		Auton4(intake, latch);
		break;
	}
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
	case 0:
		Autonomous::autonName = "Skills";
		Autonomous::auton	  = SKILLS;
	}
	std::cout << "Current auton: " + Autonomous::autonName << std::endl;
}