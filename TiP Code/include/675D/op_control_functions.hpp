#include "api.h"

extern bool shift;

extern bool drive_lock_enabled;

extern bool mogo_is_down;
extern bool mogo_is_sensed;

extern bool lift_manual_control_enabled;

extern bool clamp_current_state;

extern int mogo_start_pos;
extern int mogo_mid_pos;
extern int mogo_bottom_pos;

extern int conveyor_speed;

extern int lift_up_speed;
extern int lift_down_speed;
extern bool lift_task_running;

extern pros::Task mogo_control_task();
extern pros::Task lift_control_task();

void shift_key();
void drive_lock();
void mogo_control();
void lift_control();
void clamp_control();
void conveyor_control();
