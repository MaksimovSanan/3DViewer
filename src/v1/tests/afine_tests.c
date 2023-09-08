#include "tests.h"

START_TEST(square_test) {
  char *path = "square.obj";
  data my_data = {0};
  parse(path, &my_data);
  ck_assert_int_eq(my_data.count_of_vertexes, 8);
  ck_assert_int_eq(my_data.count_of_facets, 6);
  double cords[] = {-0.666667, -0.666667, 0.000000,  -0.666667, -0.666667,
                    0.000000,  0.666667,  -0.666667, 0.000000,  0.666667,
                    0.666667,  0.000000,  -0.666667, 0.666667,  0.000000,
                    -0.333333, -0.333333, 0.666667,  1.000000,  -0.333333,
                    0.66667,   1.000000,  1.000000,  0.666667};
  for (int i = 0; i < 24; i++) {
    ck_assert_double_eq_tol((double)cords[i],
                            (double)(*(my_data.matrix_3d.matrix))[i], 3);
  }
}
END_TEST

START_TEST(square_test_1) {
  char *path = "square.obj";
  data my_data = {0};
  parse(path, &my_data);
  move_x(*(my_data.matrix_3d.matrix), my_data.count_of_vertexes * 3, 0.1);
  double cords[] = {-0.566667, -0.666667, 0.000000,  -0.566667, -0.666667,
                    0.000000,  0.766667,  -0.666667, 0.000000,  0.766667,
                    0.666667,  0.000000,  -0.566667, 0.666667,  0.000000,
                    -0.233333, -0.333333, 0.666667,  1.100000,  -0.333333,
                    0.666667,  1.100000,  1.000000,  0.666667};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(cords[i], my_data.matrix_3d.matrix[i][j], 3);
    }
  }
}
END_TEST

START_TEST(square_test_2) {
  char *path = "square.obj";

  data my_data = {0};
  parse(path, &my_data);
  move_y(*(my_data.matrix_3d.matrix), my_data.count_of_vertexes * 3, 0.1);
  double cords[] = {-0.666667, -0.566667, 0.000000,  -0.666667, -0.566667,
                    0.000000,  0.666667,  -0.566667, 0.000000,  0.666667,
                    0.766667,  0.000000,  -0.666667, 0.766667,  0.000000,
                    -0.333333, -0.233333, 0.666667,  1.000000,  -0.233333,
                    0.666667,  1.000000,  1.100000,  0.666667};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(cords[i], my_data.matrix_3d.matrix[i][j], 3);
    }
  }
}
END_TEST

START_TEST(square_test_3) {
  char *path = "square.obj";
  data my_data = {0};
  parse(path, &my_data);
  move_z(*(my_data.matrix_3d.matrix), my_data.count_of_vertexes * 3, 0.1);
  double cords[] = {-0.666667, -0.666667, 1.000000,  -0.666667, -0.666667,
                    1.000000,  0.666667,  -0.666667, 1.000000,  0.666667,
                    0.666667,  1.000000,  -0.666667, 0.666667,  1.000000,
                    -0.333333, -0.333333, 1.666667,  1.000000,  -0.333333,
                    1.666667,  1.000000,  1.000000,  1.666667};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(cords[i], my_data.matrix_3d.matrix[i][j], 3);
    }
  }
}
END_TEST

START_TEST(square_test_4) {
  char *path = "square.obj";
  data my_data = {0};
  parse(path, &my_data);
  flip_rel_x(*(my_data.matrix_3d.matrix), my_data.count_of_vertexes * 3, 0.1);
  double cords[] = {-0.666667, -0.663336, -0.066556, -0.666667, -0.663336,
                    -0.066556, 0.666667,  -0.663336, -0.066556, 0.666667,
                    0.663336,  0.066556,  -0.666667, 0.663336,  0.066556,
                    -0.333333, -0.398224, 0.630058,  1.000000,  -0.398224,
                    0.630058,  1.000000,  0.928449,  0.763170};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(cords[i], my_data.matrix_3d.matrix[i][j], 3);
    }
  }
}
END_TEST

START_TEST(square_test_5) {
  char *path = "square.obj";
  data my_data = {0};
  parse(path, &my_data);
  flip_rel_y(*(my_data.matrix_3d.matrix), my_data.count_of_vertexes * 3, 0.1);
  double cords[] = {-0.663336, -0.666667, -0.066556, -0.663336, -0.666667,
                    -0.066556, 0.663336,  -0.666667, 0.066556,  0.663336,
                    0.666667,  0.066556,  -0.663336, 0.666667,  -0.066556,
                    -0.398224, -0.333333, 0.630058,  0.928449,  -0.333333,
                    0.763170,  0.928449,  1.000000,  0.763170};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(cords[i], my_data.matrix_3d.matrix[i][j], 3);
    }
  }
}
END_TEST

START_TEST(square_test_6) {
  char *path = "square.obj";
  data my_data = {0};
  parse(path, &my_data);
  flip_rel_z(*(my_data.matrix_3d.matrix), my_data.count_of_vertexes * 3, 0.1);
  double cords[] = {-0.596780, -0.729892, 0.000000,  -0.596780, -0.729892,
                    0.000000,  0.729892,  -0.596780, 0.000000,  0.596780,
                    0.729892,  0.000000,  -0.729892, 0.596780,  0.000000,
                    -0.298390, -0.364946, 0.666667,  1.028282,  -0.231835,
                    0.666667,  0.895171,  1.094838,  0.666667};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(cords[i], my_data.matrix_3d.matrix[i][j], 3);
    }
  }
}
END_TEST

START_TEST(square_test_7) {
  char *path = "square.obj";
  data my_data = {0};
  parse(path, &my_data);
  increase_size(*(my_data.matrix_3d.matrix), my_data.count_of_vertexes * 3);
  double cords[] = {-0.733333, -0.733333, 0.000000,  -0.733333, -0.733333,
                    0.000000,  0.733333,  -0.733333, 0.000000,  0.733333,
                    0.733333,  0.000000,  -0.733333, 0.733333,  0.000000,
                    -0.366667, -0.366667, 0.733333,  1.100000,  -0.366667,
                    0.733333,  1.100000,  1.100000,  0.733333};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(cords[i], my_data.matrix_3d.matrix[i][j], 3);
    }
  }
}
END_TEST

START_TEST(square_test_8) {
  char *path = "square.obj";
  data my_data = {0};
  parse(path, &my_data);
  deacrease_size(*(my_data.matrix_3d.matrix), my_data.count_of_vertexes * 3);
  double cords[] = {-0.606061, -0.606061, 0.000000,  -0.606061, -0.606061,
                    0.000000,  0.606061,  -0.606061, 0.000000,  0.606061,
                    0.606061,  0.000000,  -0.606061, 0.606061,  0.000000,
                    -0.303030, -0.303030, 0.606061,  0.909091,  -0.303030,
                    0.606061,  0.909091,  0.909091,  0.606061};
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(cords[i], my_data.matrix_3d.matrix[i][j], 3);
    }
  }
}
END_TEST

Suite *s_calc() {
  Suite *s;
  TCase *tc;
  s = suite_create("suite");
  tc = tcase_create("case");
  tcase_add_test(tc, square_test);
  tcase_add_test(tc, square_test_1);
  tcase_add_test(tc, square_test_2);
  tcase_add_test(tc, square_test_3);
  tcase_add_test(tc, square_test_4);
  tcase_add_test(tc, square_test_5);
  tcase_add_test(tc, square_test_6);
  tcase_add_test(tc, square_test_7);
  tcase_add_test(tc, square_test_8);

  suite_add_tcase(s, tc);

  return s;
}