#ifndef SRC_TESTS_TESTS_H_
#define SRC_TESTS_TESTS_H_

#include <check.h>

#include "../afine.h"
#include "../parser.h"

Suite *s_calc(void);

void run_testcase(Suite *testcase);

#endif  // SRC_TESTS_TESTS_H_
