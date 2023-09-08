#ifndef AFINE_H
#define AFINE_H

#include <math.h>
#define SCALE 1.1
#define MOVEMENT 0.01
#define FLIP_ANGLE_L 0.1
#define FLIP_ANGLE_R -0.1

void flip_rel_z(double *cords, int dots_amount, float flip_angle);

void flip_rel_x(double *cords, int dots_amount, float flip_angle);
void flip_rel_y(double *cords, int dots_amount, float flip_angle);

void move_x(double *cords, int dots_amount, float movement);

void move_y(double *cords, int dots_amount, float movement);

void move_z(double *cords, int dots_amount, float movement);

void increase_size(double *cords, int dots_amount);

void deacrease_size(double *cords, int dots_amount);

#endif
