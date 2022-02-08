#include "main.h"

bool shift = false;
bool double_shift = false;

bool drive_lock_enabled = false;

bool mogo_is_down = true;
bool mogo_clamp_closed = false;

bool lift_manual_control_enabled = true;
bool lift_timed_out = false;

bool clamp_current_state = true;

int conveyor_speed = 600;

int lift_up_speed = 100;
int lift_down_speed = 100;
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
    chassis.reset_drive_sensor();
    chassis.set_active_brake(0.1);
    master.rumble("..");
  }
}

void drive_lock(){
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)){
    toggle_drive_lock();
  }
}


void mogo_control(){
  if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)){
    if(mogo_is_down == true){
      tilter_up();
    }
    else{
      tilter_down();
    }
  }
}

void lift_control_manual(){
  if(!shift && !double_shift)
  {
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
      lift.move_velocity(lift_down_speed);
    }
    else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
      lift.move_velocity(-lift_up_speed);
    }
    else{
      lift.move_velocity(0);
    }
  }
  else if(double_shift){
    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
      lift.move_velocity(lift_down_speed_slowed);
    }
    else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)){
      lift.move_velocity(-lift_up_speed_slowed);
    }
    else{
      lift.move_velocity(0);
    }
  }
  else{
    lift.move_velocity(0);
  }
}

int lift_timeout(){
  wait(2000);
  lift_timed_out = true;
  return 1;
}

int lift_task(){
  lift_manual_control_enabled = false;
  lift_task_running = true;

  master.rumble(".");

  lift.move_absolute(-1, 100);

  printf("task called");
  pros::Task timeout(lift_timeout);

  while(lift.get_position() < -6){
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
