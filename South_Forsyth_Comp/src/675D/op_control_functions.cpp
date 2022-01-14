#include "main.h"

bool shift = false;
bool double_shift = false;

bool drive_lock_enabled = false;

bool mogo_is_down = false;
bool mogo_is_sensed = false;

bool lift_manual_control_enabled = true;

bool clamp_current_state = true;

int mogo_start_pos = 0;
int mogo_mid_pos = 210;
int mogo_bottom_pos = 455;
// SAM WAS HERE
int conveyor_speed = 500; //380

int lift_up_speed = 200;
int lift_down_speed = 195;
int lift_up_speed_slowed = 100;
int lift_down_speed_slowed = 100;
bool lift_task_running = false;

void shift_key(){
  if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == true && master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == false){
    shift = true;
    double_shift = false;
  }
  else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) == true && master.get_digital(pros::E_CONTROLLER_DIGITAL_L2) == true){
    shift = false;
    double_shift = true;
  }
  else{
    shift = false;
    double_shift = false;
  }
}

void toggle_drive_lock(){
  if(drive_lock_enabled){
    drive_lock_enabled=!drive_lock_enabled;
    chassis.set_drive_brake(MOTOR_BRAKE_COAST);
    chassis.set_active_brake(0.0);
    master.rumble("-");
  }
  else{
    drive_lock_enabled=!drive_lock_enabled;
    chassis.set_drive_brake(MOTOR_BRAKE_HOLD);
    chassis.set_active_brake(0.1);
    master.rumble("..");
  }
}

void drive_lock(){
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
    toggle_drive_lock();
  }
}

int mogo_task(){
  if(mogo_is_down){
    if(mogo_is_sensed){
      mogo.move_absolute(mogo_mid_pos, 80);
    }
    else{
      mogo.move_absolute(mogo_start_pos, 100);
    }
    mogo_is_down = false;
  }
  else if(!mogo_is_down){
    if(mogo_is_sensed){
      mogo.move_absolute(mogo_bottom_pos, 40);
    }
    else{
      mogo.move_absolute(mogo_bottom_pos, 100);
      mogo_is_sensed = true;
    }

    mogo_is_down = true;
  }

  master.rumble(".");
  return 1;
}

void mogo_control(){
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
    pros::Task mogo_control_task(mogo_task);
  }
  else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)){
    mogo_is_down = true;
    mogo_is_sensed = false;
    pros::Task mogo_control_task(mogo_task);
  }
}

void lift_control_manual(){
  if(!shift && !double_shift)
  {
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
      lift_r.move_velocity(lift_down_speed);
      lift_l.move_velocity(lift_down_speed);
    }
    else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
      lift_r.move_velocity(-lift_up_speed);
      lift_l.move_velocity(-lift_up_speed);
    }
    else{
      lift_r.move_velocity(0);
      lift_l.move_velocity(0);
    }
  }
  else if(double_shift){
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
      lift_r.move_velocity(lift_down_speed_slowed);
      lift_l.move_velocity(lift_down_speed_slowed);
    }
    else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
      lift_r.move_velocity(-lift_up_speed_slowed);
      lift_l.move_velocity(-lift_up_speed_slowed);
    }
    else{
      lift_r.move_velocity(0);
      lift_l.move_velocity(0);
    }
  }
  else{
    lift_r.move_velocity(0);
    lift_l.move_velocity(0);
  }
}

int lift_task(){
  lift_manual_control_enabled = false;
  lift_task_running = true;

  master.rumble(".");

  lift_l.move_absolute(-1, 200);
  lift_r.move_absolute(-2, 200);

  printf("task called");

  while(lift_l.get_position() < -6){
    pros::delay(2);
  }

  lift_manual_control_enabled = true;
  lift_task_running = false;

  return 1;
}

void lift_control(){
    if(lift_manual_control_enabled == true){
      lift_control_manual();
    }

    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)){
      pros::Task lift_control_task(lift_task);
    }

}

void clamp_control(){
  if(!shift && !double_shift)
  {
    if(master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)){
      if(clamp_current_state == true){
        piston_clamp.set_value(false);
        master.rumble(".");
        clamp_current_state = false;
      }
      else if(clamp_current_state == false){
        piston_clamp.set_value(true);
        master.rumble(".");
        clamp_current_state = true;
      }
    }
  }
}

void conveyor_control(){
  if(shift && !double_shift)
  {
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
      conveyor.move_velocity(conveyor_speed);
    }
    else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
      conveyor.move_velocity(-conveyor_speed);
    }
    else{
      conveyor.move_velocity(0);
    }
  }
  else{
    conveyor.move_velocity(0);
  }
}
