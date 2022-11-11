#include "main.h"
//test2

void initialize(){

	pros::lcd::initialize();
	pros::lcd::set_text(1, "Habibi");
	pros::lcd::set_text(2, "Analog Sticks to Drive");
	pros::lcd::set_text(3, "L1 - Slow down on turns");
	pros::lcd::set_text(4, "R1 - Rollers");
	pros::delay(1);

}

void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor topleft(3, false);
	pros::Motor topright(7, false);	
	pros::Motor bottleft(2, true);
	pros::Motor bottright(1, true);
	pros::Motor roller(13, false);

	bool rollerbool = false;

	int ymotion;
	int xmotion;

	while (true) {

	pros::Controller master(pros::E_CONTROLLER_MASTER);

	// default movement control
	ymotion = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	xmotion = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

	int right = -xmotion + ymotion; //-power + turn
	int left = xmotion + ymotion; //power + turn

	topleft.move(left); //tells which motor to move at what voltage/direction
	bottleft.move(-left);
	bottright.move(right);
	topright.move(-right);
	pros::delay(1);

	////

		//Runs rollers motors while holding R1 
		if(master.get_digital(DIGITAL_R1)){ //rollers

			roller.move_velocity(120);

		} else {

			roller.move_velocity(0);
		}
	
		// Slowdown feature (Cuts robots speed in half while holding down L1 on controller)
		if(master.get_digital(DIGITAL_L1)) { 

			int right = (-xmotion + ymotion)/2; //-power + turn
			int left = (xmotion + ymotion)/2; //power + turn

			topleft.move(left);
			bottleft.move(-left);
			bottright.move(right);
			topright.move(-right);

		}

	}

}