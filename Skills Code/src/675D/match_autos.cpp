#include "main.h"

void two_mogo_match_loads(){
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 22, 15);

  lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

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

  lift.set_brake_mode(MOTOR_BRAKE_HOLD);

  chassis.set_drive_pid(52, DRIVE_SPEED); //drives fwd to middle yellow mogo
  chassis.wait_until(40);
  chassis.set_max_speed(80);
  chassis.wait_drive();

  claw_close(); //grabs middle yellow mogo
  start_lift_to(10, 40);

  lift.set_brake_mode(MOTOR_BRAKE_COAST);

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

void left_auto(){
  lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  start_flipout();

  chassis.set_drive_pid(42, 127); //fwd towards yellow mogo
  chassis.wait_drive();

  start_claw_close();
  wait(100);
  start_lift_to(20, 50);

  chassis.set_drive_pid(-40, 127); //drives bwd with mogo
  chassis.wait_drive();
}

void fast_right_one_mogo(){
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 22, 15);

  chassis.set_mode(ez::DISABLE);
  start_claw_open();
  tilter_down();

  chassis.set_tank(127, 127);
  while(chassis.right_sensor() < 1980){
    wait(2);
  }
  // chassis.set_tank(0, 0);

  start_claw_close();
  start_lift_to(20, 100);

  chassis.set_tank(-127, -127);

  lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  while(chassis.right_sensor() > 950){
    wait(2);
  }
  chassis.set_tank(0, 0);
  wait(200);

  chassis.set_mode(ez::DRIVE);

  chassis.set_turn_pid(-90, 70);
  chassis.wait_drive();

  chassis.set_drive_pid(-14, 70);
  chassis.wait_drive();

  tilter_up();

  chassis.set_turn_pid(-135, 70);
  chassis.wait_drive();

  lift_to(500, 160);

  start_intake(450);
  wait(500);

  chassis.set_drive_pid(12, 70);
  chassis.wait_drive();

  wait(500);

  chassis.set_drive_pid(-12, 70);
  start_lift_to(0, 150);
  chassis.wait_drive();

  stop_intake();
}

void fast_left_one_mogo(){
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 22, 15);

  chassis.set_mode(ez::DISABLE);
  start_claw_open();
  tilter_down();

  chassis.set_tank(127, 127);
  while(chassis.right_sensor() < 2150){
    wait(2);
  }
  // chassis.set_tank(0, 0);

  start_claw_close();
  start_lift_to(20, 100);
  lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  chassis.set_tank(-127, -127);
  while(chassis.right_sensor() > 800){
    wait(2);
  }
  chassis.set_tank(0, 0);
  wait(200);
}
