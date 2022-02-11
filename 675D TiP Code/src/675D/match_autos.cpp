#include "main.h"

void two_mogo_match_loads(){
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 22, 15);

  lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  pros::Task start_timer(check_for_time);

  start_flipout();
  blocker_down();

  chassis.set_drive_pid(40.1, 127); //fwd towards yellow mogo
  chassis.wait_drive();

  start_claw_close();
  wait(70);

  chassis.set_drive_pid(-40, 127); //drives bwd with mogo
  chassis.wait_until(-2);
  start_lift_to(30, 50);

  chassis.wait_until(-18);
  start_claw_open(); //drops off mogo in zone
  blocker_up();

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
  start_lift_to(20, 40);

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

  chassis.set_mode(ez::DISABLE);
  start_claw_open();
  tilter_down();
  blocker_down();

  chassis.set_tank(127, 127);
  while(chassis.right_sensor() < 1980){
    wait(2);
  }
  // chassis.set_tank(0, 0);

  start_claw_close();
  start_lift_to(20, 100);

  chassis.set_tank(-127, -127);

  lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  while(chassis.right_sensor() > 890){
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

  chassis.set_mode(ez::DISABLE);
  start_claw_open();
  tilter_down();
  blocker_down();

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

void mid_fake(){
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 22, 15);

  lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  // pros::Task start_timer(check_for_time);

  start_flipout();

  chassis.set_turn_pid(-35, 80);
  chassis.wait_drive();

  chassis.set_drive_pid(49, 120);
  chassis.wait_until(40);
  chassis.set_max_speed(100);
  chassis.wait_drive();

  claw_close();
  start_lift_to(20, 100);

  chassis.set_drive_pid(-29, 90);
  chassis.wait_drive();

  chassis.set_turn_pid(-90, 70);
  chassis.wait_drive();

  chassis.set_drive_pid(-28, 70);

  chassis.wait_until(-20);
  chassis.set_max_speed(50);
  start_lift_to(0, 100);
  chassis.wait_drive();

  tilter_up();
  wait(200);

  intake_for(3000, 500);


}

void right_awp(){
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.48, 0, 1.8, 0); //0.45
  //chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 22, 15);

  lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  tilter_down();

  chassis.set_drive_pid(17.5, 80, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-90, 80);
  chassis.wait_drive();

  chassis.set_drive_pid(-16, 55, true);
  chassis.wait_drive();

  tilter_up();
  wait(100);

  chassis.set_drive_pid(16.5, 80, true);
  chassis.wait_drive();


  chassis.set_turn_pid(90, 80);
  chassis.wait_drive();

  start_lift_to(400, 100);

  chassis.set_drive_pid(-65, 80, true);

  chassis.wait_until(-30);
  start_intake(550);

  chassis.wait_drive();

  chassis.set_turn_pid(180, 80);
  chassis.wait_drive();

  stop_intake();

  chassis.set_drive_pid(6, 80, true);
  chassis.wait_drive();

  lift_to(150, 100);
  claw_open();

  chassis.set_drive_pid(-6, 80, true);
  chassis.wait_drive();

  chassis.set_turn_pid(270, 80);
  chassis.wait_drive();

  start_lift_to(0, 100);
  tilter_down();

}

void left_awp(){
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.48, 0, 1.8, 0); //0.45
  //chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 22, 15);

  lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  tilter_down();

  start_lift_to(210, 100);
  wait(500);

  chassis.set_drive_pid(8, 90, true);
  chassis.wait_drive();

  claw_open();

  chassis.set_swing_pid(ez::RIGHT_SWING, 150, 105);
  chassis.wait_drive();

  chassis.set_drive_pid(-6, 90, true);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, 180, 105);
  chassis.wait_drive();

  chassis.set_drive_pid(-75, 110, true);
  chassis.wait_drive();

  chassis.set_turn_pid(178, 100);
  chassis.wait_drive();

  chassis.set_drive_pid(-17.5, 55, true);
  chassis.wait_drive();

  tilter_up();
  wait(400);

  chassis.set_swing_pid(ez::LEFT_SWING, 218, 105);
  chassis.wait_drive();
  start_intake_for(2500, 400);

  chassis.set_drive_pid(48, 90, true);
  start_lift_to(0, 100);

  chassis.wait_until(37);
  chassis.set_max_speed(65);
  chassis.wait_drive();

  claw_close();
  start_lift_to(20, 100);

  chassis.set_drive_pid(-42, 80, true);
  chassis.wait_drive();

 tilter_down();

}

void left_ring_and_yellow(){
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.48, 0, 1.8, 0); //0.45
  //chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 22, 15);

  lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  tilter_down();

  start_lift_to(210, 100);
  wait(500);

  chassis.set_drive_pid(9, 90, true);
  chassis.wait_drive();

  claw_open();
  wait(400);

  chassis.set_drive_pid(-4, 90, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-79, 90);
  chassis.wait_drive();

  chassis.set_drive_pid(44, 120, true);
  start_lift_to(0, 100);
  chassis.wait_drive();

  claw_close();
  start_lift_to(20, 100);

  chassis.set_drive_pid(-40, 110, true);
  chassis.wait_drive();
}

void left_ring_and_yellow_steal(){
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.48, 0, 1.8, 0); //0.45
  //chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 22, 15);

  lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  tilter_down();

  start_lift_to(210, 100);
  wait(500);

  chassis.set_drive_pid(9, 90, true);
  chassis.wait_drive();

  claw_open();
  wait(400);

  chassis.set_drive_pid(-4, 90, true);
  chassis.wait_drive();

  chassis.set_turn_pid(-79, 90);
  chassis.wait_drive();

  chassis.set_drive_pid(50, 110, true);
  start_lift_to(0, 100);
  chassis.wait_drive();

  chassis.set_turn_pid(-90, 70);
  chassis.wait_drive();

  chassis.set_drive_pid(22, 80, true);
  chassis.wait_drive();

  claw_close();
  start_lift_to(20, 100);

  chassis.set_drive_pid(-60, 110, true);
  chassis.wait_drive();
}

void left_finesse(){
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.48, 0, 1.8, 0); //0.45
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.48, 0, 1.8, 0); //0.45
  //chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 22, 15);

  lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  start_flipout();

  chassis.set_swing_pid(ez::LEFT_SWING, 60, 110);
  chassis.wait_drive();

  chassis.set_drive_pid(23, 110);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, 30, 110);
  chassis.wait_drive();

  chassis.set_drive_pid(25, 90);
  chassis.wait_drive();

  claw_close();
  start_lift_to(20, 100);

  chassis.set_drive_pid(-25, 100);

  chassis.wait_until(-18);
  chassis.set_max_speed(65);
  chassis.wait_drive();

  claw_open();
  wait(200);

  chassis.set_swing_pid(ez::RIGHT_SWING, 90, 110);
  chassis.wait_drive();

  chassis.set_drive_pid(-15, 120);
  chassis.wait_drive();

  chassis.set_turn_pid(3, 105);
  chassis.wait_drive();

  chassis.set_drive_pid(48, 120);
  start_lift_to(0, 100);
  chassis.wait_drive();

  claw_close();
  start_lift_to(20, 100);

  chassis.set_drive_pid(-55, 110);
  chassis.wait_drive();
}
