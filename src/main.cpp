#include "main.h"
//test
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
	topleft.move(left);
	bottleft.move(-left);
	bottright.move(right);
	topright.move(-right);
	pros::delay(10);

	if(master.get_digital(DIGITAL_R1)){ //intake

        roller.move_velocity(120);
		pros::delay(10);
    } else {
		roller.move_velocity(0);
		pros::delay(10);
	}


	}

}