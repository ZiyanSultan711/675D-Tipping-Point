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

void two_mogo_match_loads(){
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 22, 15);

  lift_r.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  lift_l.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  pros::Task start_timer(check_for_time);

  start_flipout();

  chassis.set_drive_pid(40.1, 127); //fwd towards yellow mogo
  chassis.wait_drive();

  start_claw_close();
  wait(70);

  chassis.set_drive_pid(-40, 127); //drives bwd with mogo
  chassis.wait_until(-2);
  start_lift_to(20, 50);

  chassis.wait_until(-18);
  start_claw_open(); //drops off mogo in zone

  chassis.wait_drive(); //continues driving bwd

  chassis.set_turn_pid(-34, TURN_SPEED); //turns to face middle yellow mogo
  chassis.wait_drive();

  start_lift_to(0, 100);

  lift_l.set_brake_mode(MOTOR_BRAKE_HOLD);
  lift_r.set_brake_mode(MOTOR_BRAKE_HOLD);

  chassis.set_drive_pid(52, DRIVE_SPEED); //drives fwd to middle yellow mogo
  chassis.wait_until(40);
  chassis.set_max_speed(80);
  chassis.wait_drive();

  claw_close(); //grabs middle yellow mogo
  start_lift_to(10, 40);

  lift_l.set_brake_mode(MOTOR_BRAKE_COAST);
  lift_r.set_brake_mode(MOTOR_BRAKE_COAST);

  chassis.set_drive_pid(-34, DRIVE_SPEED); //drives bwd holding middle yellow mogo
  chassis.wait_drive();

  claw_open();

  chassis.set_drive_pid(-19, DRIVE_SPEED); //drives bwd
  chassis.wait_drive();

  chassis.set_turn_pid(-127, TURN_SPEED); //turns to line up with alliance mogo
  chassis.wait_until(-90);
  tilter_down();

  chassis.wait_drive();

  chassis.set_drive_pid(-22, 60); //drives bwd into alliance mogo
  chassis.wait_drive();

  start_lift_to(520, -140); //lift comes up for match loads
  tilter_up();
  wait(200);

  start_intake(550); //intake starts running

  chassis.set_drive_pid(20, DRIVE_SPEED); //drives fwd to start match loads
  chassis.wait_drive();

  while(!is_time_up){ //match load process. continues until 13 seconds then exists loop
    if(!is_time_up){
      chassis.set_drive_pid(-10, 100);
      chassis.wait_drive();
      wait(200);
    }
    if(!is_time_up){
      chassis.set_drive_pid(10, 100);
      chassis.wait_drive();
    }
  }

  chassis.set_drive_pid(3, 100);
  stop_intake();
  start_lift_to(0, 200);
  tilter_down();

  chassis.wait_drive();
}

void prog_skills(){
  // robot starts plat up side, top right corner of 2nd tile, front facing the wall
  tilter_down();

  chassis.set_drive_pid(17.5, 95);
  chassis.wait_drive();

  chassis.set_turn_pid(-90, 80);
  start_claw_open();

  chassis.wait_drive();

  chassis.set_drive_pid(-16, 60);
  chassis.wait_drive();

  tilter_up();

  // first alliance goal has been picked up with tilter
  chassis.set_drive_pid(16, 80);
  chassis.wait_drive();

  chassis.set_turn_pid(0, 70);
  chassis.wait_drive();

  chassis.set_drive_pid(23.5, 70);
  chassis.wait_drive();

  claw_close();
  wait(200);



  // first yellow picked up
  start_lift_to(120, 120);

  chassis.set_drive_pid(23, 70); //drives fwd after grabbing mogo
  chassis.wait_drive();

  chassis.set_turn_pid(-44, 75); //turns to face platform
  chassis.wait_drive();

  lift_to(580, 180);

  chassis.set_drive_pid(37, 80, true); //drives to the platform
  chassis.wait_drive();

  chassis.set_swing_pid(ez::LEFT_SWING, -32, 50); //swings to adjust with platform
  chassis.wait_drive();

  chassis.set_drive_pid(2, 80, true); //drives to the platform
  chassis.wait_drive();

  lift_to(415, 140);

  wait(400);

  claw_open();
  wait(300);

  // ----------------------------------------------------------------------
  // first neutral scored on plat

  lift_to(450, 80);

  chassis.set_drive_pid(-20, 80, true);
  chassis.wait_until(-6);
  start_lift_to(0, 150);
  tilter_down();

  chassis.wait_drive();

  // alliance goal has been droped
  chassis.set_drive_pid(4, 85, true); //drives away from mogo
  chassis.wait_drive();

  chassis.set_turn_pid(156, 95); //spins to face mogo
  chassis.wait_drive();

  chassis.set_drive_pid(5, 65, true); //drives into mogo
  chassis.wait_drive();

  claw_close();
  wait(200);

  lift_to(480, 130);

  chassis.set_turn_pid(-22, 65);
  chassis.wait_drive();

  chassis.set_drive_pid(17, 70, true);
  chassis.wait_drive();

  claw_open();
  wait(300);

  // --------------------------------------------------------------
  // alliance picked up and scored on platform (80)

  chassis.set_turn_pid(-90, 100);
  chassis.wait_drive();

  chassis.set_drive_pid(-35, 110, true);
  start_lift_to(0, 200);

  chassis.wait_drive();

  chassis.set_turn_pid(-42, 85);
  chassis.wait_drive();

  chassis.set_drive_pid(21, 60, true);
  chassis.wait_drive();

  claw_close();


  // grabs alliance goal near platform


  chassis.set_drive_pid(-3, 70, true);
  chassis.wait_drive();

  lift_to(120, 80);

  chassis.set_swing_pid(ez::RIGHT_SWING, 9, 70);
  chassis.wait_drive();

  chassis.set_drive_pid(-60, 100, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-140, 70);
  chassis.wait_until(-100);
  chassis.set_max_speed(60);

  chassis.wait_drive();
  //
  lift_to(600, 110);
  //
  chassis.set_drive_pid(31, 70, true);
  chassis.wait_until(24);
  chassis.set_max_speed(50);
  chassis.wait_drive();

  lift_to(405, 80);

  claw_open();
  wait(400);

  // ----------------------------------------------------------------
  // 2rd alliance mogo scored on plat (120)

  lift_to(500, 80);

  chassis.set_drive_pid(-20, 90, true);

  chassis.wait_until(-16);
  start_lift_to(0, 140);
  chassis.wait_drive();

  chassis.set_turn_pid(-44, 90);
  chassis.wait_drive();

  chassis.set_drive_pid(100, 90, true);
  chassis.wait_until(23);
  claw_close();

  start_lift_to(140, 80);

  chassis.wait_drive();

  start_lift_to(10, 80);

  wait(1400);
  claw_open();

  // ------------------------------------------------------------------
  // tall yellow scored in zone (140)

  chassis.set_drive_pid(-17, 70, true);
  chassis.wait_drive();

  chassis.set_turn_pid(90, 80);
  chassis.wait_drive();

  chassis.set_drive_pid(-19, 55);
  chassis.wait_drive();

  tilter_up();


  // alliance goal picked up with tilter


  chassis.set_drive_pid(14.5, 80);
  chassis.wait_drive();

  chassis.set_turn_pid(180, 80);
  chassis.wait_drive();

  chassis.set_drive_pid(41, 80);
  chassis.wait_until(24);
  claw_close();

  start_lift_to(140, 80);


  // yellow goal picked up while driving forward


  chassis.wait_drive();

  chassis.set_turn_pid(141, 80);
  chassis.wait_drive();

  start_lift_to(480, 80);

  chassis.set_drive_pid(45, 80);
  chassis.wait_until(30);
  chassis.set_max_speed(60);

  chassis.wait_drive();

  start_lift_to(450, 80);
  wait(500);
  claw_open();

  //3rd yellow goal has been scored on close platform
  chassis.set_drive_pid(-21, 80, true);
  chassis.wait_until(-6);
  start_lift_to(0, 150);
  tilter_down();

  chassis.wait_drive();

  chassis.set_drive_pid(4, 85, true); //drives away from mogo
  chassis.wait_drive();

  chassis.set_turn_pid(-39, 100); //spins to face mogo
  chassis.wait_drive();

  chassis.set_drive_pid(8, 65, true); //drives into mogo
  chassis.wait_drive();

  claw_close();
  wait(200);

  lift_to(480, 130);

  chassis.set_turn_pid(-217, 50);
  chassis.wait_drive();

  chassis.set_drive_pid(20, 60);
  chassis.wait_drive();

  claw_open();

  //3rd alliance mogo has been scored on close platform
  chassis.set_turn_pid(-270, 100);
  chassis.wait_drive();

  chassis.set_drive_pid(-34, 110, true);
  start_lift_to(0, 200);

  chassis.wait_drive();

  chassis.set_turn_pid(-221, 85);
  chassis.wait_drive();

  chassis.set_drive_pid(21, 60, true);
  chassis.wait_drive();

  claw_close();


  // grabs alliance goal near platform
  chassis.set_drive_pid(-3, 70, true);
  chassis.wait_drive();

  lift_to(120, 80);

  chassis.set_swing_pid(ez::RIGHT_SWING, -175, 80);
  chassis.wait_drive();

  chassis.set_drive_pid(-60, 127, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-195, 100);
  chassis.wait_drive();

  chassis.set_drive_pid(-40, 127, true);
  chassis.wait_drive();

  intake_for(4000, 600);
  //4th alliance goal scored in far zone

}

void left_auto(){
  lift_r.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  lift_l.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  start_flipout();

  chassis.set_drive_pid(42, 127); //fwd towards yellow mogo
  chassis.wait_drive();

  start_claw_close();
  wait(100);
  start_lift_to(20, 50);

  chassis.set_drive_pid(-40, 127); //drives bwd with mogo
  chassis.wait_drive();
}
