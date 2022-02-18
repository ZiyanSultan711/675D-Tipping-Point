#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 122; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 95;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 23, 0); //kd was 19
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 1.8, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 1.8, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 29, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 35, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}


void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}


///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees.
// If interfered, robot will drive forward and then attempt to drive backwards.
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .

void prog_skills(){
  // robot starts plat up side, top right corner of 2nd tile, front facing the wall
  tilter_down();

  chassis.set_drive_pid(17.5, 90, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-90, 90);
  start_claw_open();

  chassis.wait_drive();

  chassis.set_drive_pid(-16, 55, true);
  chassis.wait_drive();

  tilter_up();
  wait(100);

  // first alliance goal has been picked up with tilter
  chassis.set_drive_pid(16.5, 80, true);
  chassis.wait_drive();

  chassis.set_turn_pid(0, 70);
  chassis.wait_drive();

  start_lift_to(0, 100);

  chassis.set_drive_pid(24, 80, true);
  chassis.wait_drive();

  claw_close();
  wait(200);



  // first yellow picked up
  start_lift_to(150, 100);

  chassis.set_drive_pid(23, 80, true); //drives fwd after grabbing mogo
  chassis.wait_drive();

  chassis.set_turn_pid(-44, 60); //turns to face platform
  chassis.wait_drive();

  start_lift_to(580, 100);
  wait(300);

  chassis.set_drive_pid(39, 80, true); //drives to the platform
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, -32, 60); //swings to adjust with platform
  chassis.wait_drive();

  chassis.set_drive_pid(2, 80, true); //drives to the platform
  chassis.wait_drive();

  lift_to(410, 100);

  wait(300);

  claw_open();
  wait(200);

  // ----------------------------------------------------------------------
  // first neutral scored on plat

  lift_to(450, 100);

  chassis.set_drive_pid(-20, 80, true);
  chassis.wait_until(-5);
  start_lift_to(0, 100);
  tilter_down();

  chassis.wait_drive();

  // alliance goal has been droped
  chassis.set_drive_pid(7.5, 85, true); //drives away from mogo
  chassis.wait_drive();

  chassis.set_turn_pid(154, 90); //spins to face mogo
  chassis.wait_drive();

  chassis.set_drive_pid(8, 60, true); //drives into mogo
  chassis.wait_drive();

  claw_close();
  wait(200);

  lift_to(492, 100);

  chassis.set_turn_pid(-25, 65);
  chassis.wait_drive();

  chassis.set_drive_pid(19, 80, true);
  chassis.wait_drive();

  claw_open();
  wait(300);

  // // --------------------------------------------------------------
  // // alliance picked up and scored on platform (80)

  chassis.set_turn_pid(-90, 90);
  chassis.wait_drive();

  chassis.set_drive_pid(-37, 90, true);
  start_lift_to(0, 100);

  chassis.wait_drive();

  chassis.set_turn_pid(-42, 80);
  chassis.wait_drive();

  chassis.set_drive_pid(21, 60, true);
  chassis.wait_drive();

  claw_close();


  // grabs alliance goal near platform


  chassis.set_drive_pid(-3, 70, true);
  chassis.wait_drive();

  lift_to(155, 100);

  chassis.set_swing_pid(ez::RIGHT_SWING, 8, 70);
  chassis.wait_drive();

  chassis.set_drive_pid(-60, 90, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-141, 70);
  chassis.wait_until(-100);
  chassis.set_max_speed(60);

  chassis.wait_drive();

  start_lift_to(600, 100);
  wait(300);

  chassis.set_drive_pid(33, 70, true);
  chassis.wait_until(24);
  chassis.set_max_speed(50);
  chassis.wait_drive();

  lift_to(405, 100);

  claw_open();
  wait(500);

  // // ----------------------------------------------------------------
  // // 2rd alliance mogo scored on plat (120)

  start_lift_to(500, 100);
  wait(400);

  chassis.set_drive_pid(-21, 90, true);

  chassis.wait_until(-12);
  start_lift_to(0, 100);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, 90);
  chassis.wait_drive();

  chassis.set_drive_pid(100, 100, true);
  chassis.wait_until(23);
  claw_close();

  start_lift_to(140, 100);

  chassis.wait_until(85);
  chassis.set_max_speed(70);

  chassis.wait_drive();

  start_lift_to(10, 100);

  wait(1000);
  claw_open();

  // // ------------------------------------------------------------------
  // // tall yellow scored in zone (140)

  chassis.set_drive_pid(-14.5, 90, true);
  chassis.wait_drive();

  chassis.set_turn_pid(90, 100);
  chassis.wait_drive();

  chassis.set_drive_pid(-18, 55);
  chassis.wait_drive();

  tilter_up();


  // alliance goal picked up with tilter


  chassis.set_drive_pid(17, 80);
  chassis.wait_drive();

  chassis.set_turn_pid(180, 90);
  chassis.wait_drive();

  chassis.set_drive_pid(41, 70);
  chassis.wait_until(24);
  claw_close();

  chassis.set_max_speed(60);

  start_lift_to(155, 100);


  // yellow goal picked up while driving forward


  chassis.wait_drive();

  chassis.set_turn_pid(140, 60);
  chassis.wait_drive();

  start_lift_to(480, 100);
  wait(200);

  chassis.set_drive_pid(43, 80);
  chassis.wait_until(30);
  chassis.set_max_speed(60);

  chassis.wait_drive();

  start_lift_to(450, 100);
  wait(300);
  claw_open();

  //3rd yellow goal has been scored on close platform
  chassis.set_drive_pid(-21, 80, true);
  chassis.wait_until(-5);
  start_lift_to(0, 90);
  tilter_down();

  chassis.wait_drive();

  chassis.set_drive_pid(8, 85, true); //drives away from mogo
  chassis.wait_drive();

  chassis.set_turn_pid(-39, 95); //spins to face mogo
  chassis.wait_drive();

  chassis.set_drive_pid(8, 65, true); //drives into mogo
  chassis.wait_drive();

  claw_close();
  wait(200);

  lift_to(485, 100);

  chassis.set_turn_pid(-217, 55);
  chassis.wait_drive();

  chassis.set_drive_pid(24, 60);
  chassis.wait_drive();

  claw_open();
  wait(100);
  start_lift_to(530, 100);

  //3rd alliance mogo has been scored on close platform
  chassis.set_drive_pid(-5, 110, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-270, 90);
  chassis.wait_drive();

  chassis.set_drive_pid(-36, 110, true);
  start_lift_to(0, 100);

  chassis.wait_drive();

  chassis.set_turn_pid(-223, 90);
  chassis.wait_drive();

  chassis.set_drive_pid(24, 60, true);
  chassis.wait_drive();

  claw_close();


  // grabs alliance goal near platform
  chassis.set_drive_pid(-3, 70, true);
  chassis.wait_drive();

  lift_to(155, 100);

  chassis.set_swing_pid(ez::RIGHT_SWING, -179, 80);
  chassis.wait_drive();

  chassis.set_drive_pid(-60, 120, true);
  chassis.wait_drive();


  chassis.set_turn_pid(-331, 70);
  chassis.wait_until(-100);
  chassis.set_max_speed(60);

  chassis.wait_drive();

  start_lift_to(485, 100);
  wait(400);

  chassis.set_drive_pid(32, 70, true);
  chassis.wait_until(20);
  chassis.set_max_speed(50);
  chassis.wait_drive();

  lift_to(410, 80);

  claw_open();
  wait(100);
  start_lift_to(500, 100);

  chassis.set_drive_pid(-15, 10, true);
  chassis.wait_drive();


}
