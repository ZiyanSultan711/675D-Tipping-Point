#include "main.h"

pros::Motor lift_l(4, MOTOR_GEARSET_18, false, MOTOR_ENCODER_DEGREES);
pros::Motor lift_r(5, MOTOR_GEARSET_18, true, MOTOR_ENCODER_DEGREES);
pros::Motor mogo(18, MOTOR_GEARSET_36, true, MOTOR_ENCODER_DEGREES);
pros::Motor conveyor(8, MOTOR_GEARSET_6, false, MOTOR_ENCODER_DEGREES);

pros::ADIDigitalOut piston_clamp('G', false);
