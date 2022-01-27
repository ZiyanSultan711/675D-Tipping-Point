#include "main.h"

bool is_time_up = false;

void claw_open(){
  piston_clamp.set_value(true);
  clamp_current_state = true;
}

void claw_close(){
  piston_clamp.set_value(false);
  clamp_current_state = false;
}

int co_task(){
  claw_open();

  return 1;
}

int cc_task(){
  claw_close();

  return 1;
}

void start_claw_open(){
  pros::Task co(co_task);
}

void start_claw_close(){
  pros::Task cc(cc_task);
}

int td_task(){
  tilter_l.set_value(true);
  tilter_r.set_value(true);
  mogo_is_down = true;

  wait(500);
  tilter_clamp.set_value(false);
  mogo_clamp_closed = false;

  return 1;
}

int tu_task(){
  tilter_clamp.set_value(true);
  mogo_clamp_closed = true;


  tilter_l.set_value(false);
  tilter_r.set_value(false);
  mogo_is_down = false;

  return 1;
}

void tilter_down(){
  pros::Task td(td_task);
}

void tilter_up(){
  pros::Task tu(tu_task);
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
  tilter_down();
}

int check_for_time(){
  is_time_up = false;
  wait(13700);
  is_time_up = true;
  master.rumble("---");
  return 1;
}
