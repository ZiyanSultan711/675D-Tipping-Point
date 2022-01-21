#include "api.h"

void claw_open();
void claw_close();
void bwd(double distance, int speed, bool slew);

void fwd(double distance, int speed, bool slew);

void point_turn(double angle, int speed);

void swing_right(double angle, int speed);

void swing_left(double angle, int speed);
////
// moves mogo to bottom position
// NON-BLOCKING
////
void start_mogo_down(int speed);

////
// moves mogo to middle position
// NON-BLOCKING
////
void start_mogo_mid(int speed);

////
// moves mogo to starting position
// NON-BLOCKING
////
void start_mogo_up();

////
// moves mogo to bottom position
// BLOCKING
////
void mogo_down(int speed);

////
// moves mogo to middle position
// BLOCKING
////
void mogo_mid(int speed);

////
// moves mogo to starting position
// BLOCKING
////
void mogo_up();

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
