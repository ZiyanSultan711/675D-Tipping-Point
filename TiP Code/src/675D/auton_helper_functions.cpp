#include "main.h"

bool is_time_up = false;

void bwd(double distance, int speed, bool slew){
  chassis.set_drive_pid(-distance, speed, slew);
}

void fwd(double distance, int speed, bool slew){
  chassis.set_drive_pid(distance, speed, slew);
}

void point_turn(double angle, int speed){
  chassis.set_turn_pid(angle, speed);
}

void swing_right(double angle, int speed){
  chassis.set_swing_pid(ez::RIGHT_SWING, angle, speed);
}

void swing_left(double angle, int speed){
  chassis.set_swing_pid(ez::LEFT_SWING, angle, speed);
}

void claw_open(){
  piston_clamp.set_value(true);
  clamp_current_state = true;
}
void claw_close(){
  piston_clamp.set_value(false);
  clamp_current_state = false;
}

void start_mogo_down(int speed){
  mogo.move_absolute(mogo_bottom_pos, speed);
}
void start_mogo_mid(int speed){
  mogo.move_absolute(mogo_mid_pos, speed);
}
void start_mogo_up(){
  mogo.move_absolute(mogo_start_pos, 200);
}

void mogo_down(int speed){
  mogo.move_absolute(mogo_bottom_pos, speed);
  while(mogo.get_position() < (mogo_bottom_pos - 3)){
    wait(5);
  }
}
void mogo_mid(int speed){
  mogo.move_absolute(mogo_mid_pos, speed);
  while(mogo.get_position() > (mogo_mid_pos + 3)){
    wait(5);
  }
}
void mogo_up(){
  mogo.move_absolute(mogo_start_pos, 200);
  while(mogo.get_position() > (mogo_start_pos + 3)){
    wait(5);
  }
}

void start_lift_to(int pos, int speed){
  lift_l.move_absolute(-pos, speed);
  lift_r.move_absolute(-pos, speed);
}
void lift_to(int pos, int speed){
  lift_l.move_absolute(-pos, speed);
  lift_r.move_absolute(-pos, speed);

  while(fabs(lift_l.get_position() - lift_l.get_target_position()) > 5){
    wait(5);
  }
}

void start_intake(int speed){
  conveyor.move_velocity(speed);
}
void stop_intake(){
  conveyor.move_velocity(0);
}
void start_intake_for(int deg, int speed){
  conveyor.move_relative(deg, speed);
}

void intake_for(int deg, int speed){
  conveyor.tare_position();
  conveyor.move_absolute(deg, speed);

  while(fabs(conveyor.get_position() - conveyor.get_target_position()) > 2){
    wait(5);
  }
}

void wait(int time){
  pros::delay(time);
}

void start_flipout(){
  claw_open();
  start_intake_for(-320, 600);
}

int check_for_time(){
  is_time_up = false;
  wait(13300);
  is_time_up = true;
  master.rumble("---");
  return 1;
}
