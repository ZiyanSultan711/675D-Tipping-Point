#include "api.h"

void claw_open();
void claw_close();

void start_claw_open();
void start_claw_close();

void tilter_down();

void tilter_up();

////
// moves lift to the specified position at the specified speed
// NON-BLOCKING
////
void start_lift_to(int pos, int speed);

////
// moves lift to the specified position at the specified speed
// BLOCKING
////
void lift_to(int pos, int speed);

////
// begins running the intake at the specified speed
// NON-BLOCKING
////
void start_intake(int speed);

////
// stops the intake
// NON-BLOCKING
////
void stop_intake();

////
// moves conveyor for the specified distance at the specified speed
// NON-BLOCKING
////
void start_intake_for(int deg, int speed);

////
// moves conveyor for the specified distance at the specified speed
// BLOCKING
////
void intake_for(int deg, int speed);

////
// wait block
////
void wait(int time);

////
// begins the flipout for the robot
// NON-BLOCKING
////
void start_flipout();

extern bool is_time_up;
int check_for_time();
pros::Task start_timer();
