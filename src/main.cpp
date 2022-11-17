#include "main.h"
#include <string>
#define startingv 50
// test2

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor topleft(3, false);
pros::Motor topright(7, false);
pros::Motor bottleft(2, true);
pros::Motor bottright(1, true);
pros::Motor roller(13, false);
pros::Vision vision_sensor(16);
pros::Distance dist_sensor(8);

bool rollerbool = false;
int distance = 700;
int vision = 0;
int ymotion;
int xmotion;

void initialize() {

  pros::lcd::initialize();
  pros::lcd::set_text(1, "Habibi");
  pros::lcd::set_text(2, "Analog Sticks to Drive");
  pros::lcd::set_text(3, "L1 - Slow down on turns");
  pros::lcd::set_text(4, "R1 - Rollers");
  pros::delay(1);
}

void moveToPos1() {
  topleft.move_absolute(7, startingv);
  bottleft.move_absolute(7, startingv);
  bottright.move_absolute(7, startingv);
  topright.move_absolute(7, startingv);
  pros::delay(200);
  topleft.move_velocity(0);
  bottleft.move_velocity(0);
  bottright.move_velocity(0);
  topright.move_velocity(0);
}

void crabWalkRight() {}
void crabWalkLeft() {}
void lookForBig() {
  // use the vision sensor to look for red.
}
void lookForDisks() {
  /*
  ok bati, the plan is to make the lil boy crab walk, the other Indians are
  gonna add the motor in the middle and make it crab walk. So write this code
  assuming it crab walks. Im sending it to preset location, then have it look
  for disks in this function (obv) the sensor will look for yellow in front of
  it, now what we have to do is tell it to only count the disks that are (lets
  say for ex) 15 cm away, if it doesnt find the disks, it will crabwalk left
  fofr x centimeters, if no find, it will crab walk the other direction in 2x
  (cuz need to move x to go back to origin). After if finds the disk, we have it
  do a quick scoop action, then look for red, and go to big bot, BOOM BB WE GO
  IT.
  */

  /*
  Im writing this for u bati in case the other indians dont explain it right
  out plan for the scoop changed, its just gonnna be 3 walls that will hold the
  disks, thats much easier for us actually. for now we have been talking ab
  where to put the Vision sensor, one option is to put it in the back of the
  bot, under the rollers, or put it somewhere else. I told them to talk to u ab
  that cuz idk the range or scope of the sensor. so yay, we got better plan.
  */
  bool lookFoDisk = true;
  while (lookFoDisk == true) {
    distance = dist_sensor.get();
    pros::vision_object_s_t color = vision_sensor.get_by_sig(0, 1);
    pros::lcd::set_text(6, "Detected?: " + std::to_string(color.signature));
    vision = color.signature;
    bool detectYellow =
        color.signature; // make this so that its true when vision sensor
                         // detects yellow, for now its true
    if (detectYellow == true && distance < 100) {
      // scoop function
      break;
    } else {
      crabWalkLeft();
      crabWalkRight();
      // place holders for the functions we gone use
      break;
    }
  }
}
void autonomous() {
  // want the bot to go to a preset location, look for the yellow disks, after
  // picking them up, turns around and looks at the general area where the big
  // bot will be, it will look for the color red. the challenge is to time both
  // bots so they do not collide with eachother. a solution for this is to have
  // a similar system with the big bot, attach a vision sensor, and have it pick
  // up disks a couple sencds after it sees them, not the best solution....but
  // its all I got so fuckin deal w it bitch

  // move to preset location:
  moveToPos1();
  lookForDisks();
  lookForBig();
}

void opcontrol() {

    // for op control I was thinking ab making it more user friendly,
    // idk how to do it but I have ideas, lez finish auton forst bb
    while (true) {

      pros::Controller master(pros::E_CONTROLLER_MASTER);

      // default movement control
      ymotion = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
      xmotion = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

      int right = -xmotion + ymotion; //-power + turn
      int left = xmotion + ymotion;   // power + turn

      topleft.move(left); // tells which motor to move at what voltage/direction
      bottleft.move(-left);
      bottright.move(right);
      topright.move(-right);
      pros::delay(1);

      ////

      // Runs rollers motors while holding R1
      if (master.get_digital(DIGITAL_R1)) { // rollers

        roller.move_velocity(120);

      } else {

        roller.move_velocity(0);
      }

      // Slowdown feature (Cuts robots speed in half while holding down L1 on
      // controller)
      if (master.get_digital(DIGITAL_L1)) {

        int right = (-xmotion + ymotion) / 2; //-power + turn
        int left = (xmotion + ymotion) / 2;   // power + turn

        topleft.move(left);
        bottleft.move(-left);
        bottright.move(right);
        topright.move(-right);
      }
    }
  }
