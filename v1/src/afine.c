#include "afine.h"

void flip_rel_z(double *cords, int dots_amount, float flip_angle) {
  for (int i = 0; i < dots_amount; i += 3) {
    double rem_cur = cords[i];
    cords[i] = rem_cur * cos(flip_angle) - cords[i + 1] * sin(flip_angle);
    cords[i + 1] = rem_cur * sin(flip_angle) + cords[i + 1] * cos(flip_angle);
  }
}

void flip_rel_x(double *cords, int dots_amount, float flip_angle) {
  for (int i = 0; i < dots_amount; i += 3) {
    double rem_cur = cords[i + 1];
    cords[i + 1] = rem_cur * cos(flip_angle) - cords[i + 2] * sin(flip_angle);
    cords[i + 2] = rem_cur * sin(flip_angle) + cords[i + 2] * cos(flip_angle);
  }
}

void flip_rel_y(double *cords, int dots_amount, float flip_angle) {
  for (int i = 0; i < dots_amount; i += 3) {
    double rem_cur = cords[i];
    cords[i] = rem_cur * cos(flip_angle) - cords[i + 2] * sin(flip_angle);
    cords[i + 2] = rem_cur * sin(flip_angle) + cords[i + 2] * cos(flip_angle);
  }
}

void move_x(double *cords, int dots_amount, float movement) {
  for (int i = 0; i < dots_amount; i += 3) {
    cords[i] += movement;
  }
}

void move_y(double *cords, int dots_amount, float movement) {
  for (int i = 1; i < dots_amount; i += 3) {
    cords[i] += movement;
  }
}

void move_z(double *cords, int dots_amount, float movement) {
  for (int i = 2; i < dots_amount; i += 3) {
    cords[i] += movement * 10;
  }
}

void increase_size(double *cords, int dots_amount) {
  for (int i = 0; i < dots_amount; i++) {
    cords[i] *= SCALE;
  }
}

void deacrease_size(double *cords, int dots_amount) {
  for (int i = 0; i < dots_amount; i++) {
    cords[i] /= SCALE;
  }
}
