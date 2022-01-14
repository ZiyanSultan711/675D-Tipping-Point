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
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 19, 0);
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
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
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

void two_mogo_match_loads(){
  pros::Task start_timer(check_for_time);

  start_flipout();

  chassis.set_drive_pid(40.1, DRIVE_SPEED); //fwd towards yellow mogo
  chassis.wait_drive();

  claw_close();

  chassis.set_drive_pid(-41.1, DRIVE_SPEED); //drives bwd with mogo
  chassis.wait_until(-20);
  claw_open(); //drops off mogo in zone

  chassis.wait_drive(); //continues driving bwd

  chassis.set_turn_pid(-31.8, TURN_SPEED); //turns to face middle yellow mogo
  chassis.wait_drive();

  start_lift_to(0, 100);

  lift_l.set_brake_mode(MOTOR_BRAKE_HOLD);
  lift_r.set_brake_mode(MOTOR_BRAKE_HOLD);

  chassis.set_drive_pid(54, 100); //drives fwd to middle yellow mogo
  chassis.wait_until(30);
  chassis.set_max_speed(80);
  chassis.wait_drive();
  wait(200);

  claw_close(); //grabs middle yellow mogo

  chassis.set_drive_pid(-39, DRIVE_SPEED); //drives bwd holding middle yellow mogo
  chassis.wait_drive();

  claw_open();

  chassis.set_drive_pid(-21, DRIVE_SPEED); //drives bwd
  chassis.wait_drive();

  chassis.set_turn_pid(-145.5, TURN_SPEED); //turns to line up with alliance mogo
  start_mogo_down(200); //mogo tilter begins to come down
  chassis.wait_drive();

  chassis.set_drive_pid(-22, 80); //drives bwd into alliance mogo

  chassis.wait_drive();

  start_lift_to(520, -140); //lift comes up for match loads
  mogo_mid(200); //mogo is picked up

  start_intake(550); //intake starts running

  chassis.set_drive_pid(20, DRIVE_SPEED); //drives fwd to start match loads
  chassis.wait_drive();

  while(!is_time_up){ //match load process. continues until 13 seconds then exists loop
    if(!is_time_up){
      chassis.set_drive_pid(-10, 100);
      chassis.wait_drive();
      wait(300);
    }
    if(!is_time_up){
      chassis.set_drive_pid(10, 100);
      chassis.wait_drive();
      wait(300);
    }
  }

  stop_intake();
  start_lift_to(0, 200);
  mogo_down(45);
  mogo_is_down = true;
  mogo_is_sensed = true;
}

void prog_skills(){
  // robot starts plat up side, top right corner of 2nd tile, front facing the walls
  chassis.reset_gyro(-180);

  start_mogo_down(200);
  wait(300);

  chassis.set_turn_pid(-135, 70); //turns to face alliance mogo
  claw_open();
  chassis.wait_drive();

  chassis.set_drive_pid(-16, 55, true); //drives back into alliance goal
  chassis.wait_drive();

  mogo_mid(200); //picks up goal

  start_intake(260);

  chassis.set_swing_pid(ez::LEFT_SWING, -90, 85); //swings to face -90 degrees
  chassis.wait_drive();

  chassis.set_drive_pid(11, 88, true); //drives forward to allign with yellow mogo
  chassis.wait_drive();

  chassis.set_turn_pid(1, 90); //turns to face yellow mogo
  chassis.wait_drive();

  chassis.set_drive_pid(32, 95, true); //drives into  yellow mogo
  chassis.wait_drive();

  claw_close();
  wait(200);

  lift_to(120, 120);

  stop_intake();

  chassis.set_drive_pid(23, 70); //drives fwd after grabbing mogo
  chassis.wait_drive();

  chassis.set_turn_pid(-44, 70); //turns to face platform
  chassis.wait_drive();

  lift_to(580, 150);

  chassis.set_drive_pid(37, 80, true); //drives to the platform
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, -32, 50); //swings to adjust with platform
  chassis.wait_drive();

  chassis.set_drive_pid(2, 80, true);
  chassis.wait_drive();

  lift_to(435, 140);

  wait(400);

  claw_open();
  wait(300);

  // ----------------------------------------------------------------------
  // first neutral scored on plat

  lift_to(470, 80);

  chassis.set_drive_pid(-2, 60, true);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, -44, 50); //undo swing to adjust back
  chassis.wait_drive();

  chassis.set_turn_pid(-90, 70); //turns to face -90
  chassis.wait_drive();

  chassis.set_drive_pid(-36, 70, true); //drives backwards towards wall
  chassis.wait_drive();

  start_lift_to(0, 200);

  mogo_down(80);

  chassis.set_drive_pid(12, 70, true); //drives away from mogo
  chassis.wait_drive();

  start_mogo_up();

  chassis.set_turn_pid(90, 95); //spins to face mogo
  chassis.wait_drive();

  chassis.set_drive_pid(14, 90, true); //drives into mogo
  chassis.wait_until(10);
  chassis.set_max_speed(60);

  chassis.wait_drive();

  claw_close();
  wait(200);

  lift_to(120, 130);

  chassis.set_drive_pid(-27, 70, true);
  chassis.wait_drive();

  lift_to(550, 100);

  chassis.set_turn_pid(-45, 50);
  chassis.wait_drive();

  lift_to(510, 100);

  chassis.set_drive_pid(4, 70, true);
  chassis.wait_drive();

  claw_open();
  wait(300);

  // --------------------------------------------------------------
  // alliance mogo scored on plat

  chassis.set_drive_pid(-4, 70, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-90, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(-32, 70, true);
  chassis.wait_drive();

  lift_to(0, 200);

  chassis.set_turn_pid(-46, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(21, 60, true);
  chassis.wait_drive();

  claw_close();

  chassis.set_drive_pid(-6, 70, true);
  chassis.wait_drive();

  lift_to(120, 80);

  chassis.set_turn_pid(4, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(-115, 100, true);
  chassis.wait_drive();

  // -------------------------------------------------------------
  // alliance mogo brought back to zone

  chassis.set_turn_pid(0, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(42, 90, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-135, 50);
  chassis.wait_drive();

  lift_to(550, 80);

  chassis.set_drive_pid(30, 90, true);
  chassis.wait_drive();

  lift_to(430, 80);

  claw_open();
  wait(200);

  // ----------------------------------------------------------------
  // alliance mogo scored on plat

  lift_to(500, 80);

  chassis.set_drive_pid(-10, 90, true);
  chassis.wait_drive();
}
