#include <check.h>

#include "polish.h"

START_TEST(calc_test_1) {
  int error = 0;
  char input_string[256] = "(5+5)*-2";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, -20.000000, 6);
}

START_TEST(calc_test_2) {
  int error = 0;
  char input_string[256] = "(10+10*2)/-3";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, -10.000000);
}

START_TEST(calc_test_3) {
  int error = 0;
  char input_string[256] = "2.0 / ( 3.0 + 2.0 ) * 5.0";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 2.000000, 6);
}

START_TEST(calc_test_4) {
  int error = 0;
  char input_string[256] = "10.0 + 10.0 * 10.0";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 110.000000, 6);
}

START_TEST(calc_test_5) {
  int error = 0;
  char input_string[256] = "-5 + -4 * -2";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 3.000000, 6);
}

START_TEST(calc_test_6) {
  int error = 0;
  char input_string[256] = "-5.0 mod -3.0";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, -2.000000);
}

START_TEST(calc_test_7) {
  int error = 0;
  char input_string[256] = "1.0 / 2.0 * ( 2.0 - 1.0 )";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, 0.500000);
}

START_TEST(calc_test_8) {
  int error = 0;
  char input_string[256] = "1.1 + 2.0 + ( 3.0 * 4.0 ) + ( 5.0 + 6.8 )";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, 26.900000);
}

START_TEST(calc_test_9) {
  int error = 0;
  char input_string[256] = "1.1 + 2.0 + (3.0 - 5.5) * (1.5 - 6.5)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, 15.600000);
}

START_TEST(calc_test_10) {
  int error = 0;
  char input_string[256] = "6.6 - 1.1 - 2.2 - 3.3 - 4.4 - 5.5";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, -9.900000);
}

START_TEST(calc_test_11) {
  int error = 0;
  char input_string[256] = "1.1 - 2.2 - 3.3 - 4.4 - 5.5 + 6.6";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, -7.7000000, 6);
}

START_TEST(calc_test_12) {
  int error = 0;
  char input_string[256] = "-1.1 * 5";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, -5.5);
}

START_TEST(calc_test_13) {
  int error = 0;
  char input_string[256] = "2^2";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, 4.000000);
}

START_TEST(calc_test_14) {
  int error = 0;
  char input_string[256] = "5^3";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, 125.000000);
}

START_TEST(calc_test_15) {
  int error = 0;
  char input_string[256] = "2^2^3";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, 256.000000);
}

START_TEST(calc_test_16) {
  int error = 0;
  char input_string[256] = "(2^2)^3";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, 64.000000);
}

START_TEST(calc_test_17) {
  int error = 0;
  char input_string[256] = "-5 + 3 * 2^2";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, 7.000000);
}

START_TEST(calc_test_18) {
  int error = 0;
  char input_string[256] = "(2^2^3 - 200) / 2";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, 28.000000);
}

START_TEST(calc_test_19) {
  int error = 0;
  char input_string[256] = "5 mod -1.5";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, 0.500000);
}

START_TEST(calc_test_20) {
  int error = 0;
  char input_string[256] = "(5 mod -1.5 * 4) ^ 2";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(res, 4.000000);
}

START_TEST(calc_test_21) {
  int error = 0;
  char input_string[256] = "sin(30)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, -0.988032, 6);
}

START_TEST(calc_test_22) {
  int error = 0;
  char input_string[256] = "sin(45)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.850904, 6);
}

START_TEST(calc_test_23) {
  int error = 0;
  char input_string[256] = "sin(60)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, -0.304811, 6);
}

START_TEST(calc_test_24) {
  int error = 0;
  char input_string[256] = "sin(90)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.893997, 6);
}

START_TEST(calc_test_25) {
  int error = 0;
  char input_string[256] = "sin(120)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.580611, 6);
}

START_TEST(calc_test_26) {
  int error = 0;
  char input_string[256] = "sin(180)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, -0.801153, 6);
}

START_TEST(calc_test_27) {
  int error = 0;
  char input_string[256] = "sin(270)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, -0.176046, 6);
}

START_TEST(calc_test_28) {
  int error = 0;
  char input_string[256] = "sin(360)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.958916, 6);
}

START_TEST(calc_test_29) {
  int error = 0;
  char input_string[256] = "sin(0)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.000000, 6);
}

START_TEST(calc_test_30) {
  int error = 0;
  char input_string[256] = "cos(30)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.154251, 6);
}

START_TEST(calc_test_31) {
  int error = 0;
  char input_string[256] = "cos(45)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.525322, 6);
}

START_TEST(calc_test_32) {
  int error = 0;
  char input_string[256] = "cos(90)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, -0.448074, 6);
}

START_TEST(calc_test_33) {
  int error = 0;
  char input_string[256] = "cos(120)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.814181, 6);
}

START_TEST(calc_test_34) {
  int error = 0;
  char input_string[256] = "cos(180)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, -0.598460, 6);
}

START_TEST(calc_test_35) {
  int error = 0;
  char input_string[256] = "cos(270)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.984382, 6);
}

START_TEST(calc_test_36) {
  int error = 0;
  char input_string[256] = "cos(360)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, -0.283691, 6);
}

START_TEST(calc_test_37) {
  int error = 0;
  char input_string[256] = "cos(0)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 1.000000, 6);
}

START_TEST(calc_test_38) {
  int error = 0;
  char input_string[256] = "tan(90)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, -1.995200, 6);
}

START_TEST(calc_test_39) {
  int error = 0;
  char input_string[256] = "tan(90) * sin(30) + (cos(45)^2)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, -1.695358, 6);
}

START_TEST(calc_test_40) {
  int error = 0;
  char input_string[256] = "(sin(45) + cos(30) + tan(45) + tan(90)) * 2";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 1.25946, 6);
}

START_TEST(calc_test_41) {
  int error = 0;
  char input_string[256] = "tan(180)^2";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 1.792091, 6);
}

START_TEST(calc_test_43) {
  int error = 0;
  char input_string[256] = "asin(0.5)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 1.25946, 6);
}

START_TEST(calc_test_44) {
  int error = 0;
  char input_string[256] = "acos(0.5)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 1.047198, 6);
}

START_TEST(calc_test_45) {
  int error = 0;
  char input_string[256] = "acos(1)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.000000, 6);
}

START_TEST(calc_test_46) {
  int error = 0;
  char input_string[256] = "atan(0)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.000000, 6);
}

START_TEST(calc_test_47) {
  int error = 0;
  char input_string[256] = "atan(1)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.785398, 6);
}

START_TEST(calc_test_48) {
  int error = 0;
  char input_string[256] = "sqrt(100) / sqrt(25) * sqrt(121)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 22.000000, 6);
}

START_TEST(calc_test_49) {
  int error = 0;
  char input_string[256] = "ln(5)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 1.609438, 6);
}

START_TEST(calc_test_50) {
  int error = 0;
  char input_string[256] = " -5.0 mod -3.0";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, -2.000000, 6);
}

START_TEST(calc_test_51) {
  int error = 0;
  char input_string[256] = "log(10)";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 1.000000, 6);
}

START_TEST(calc_test_52) {
  int error = 0;
  char input_string[256] = "1.0 / 2.0 * ( 2.0 - 1.0 )";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.500000, 6);
}

START_TEST(calc_test_53) {
  int error = 0;
  char input_string[256] = "1.1 + 2.0 + ( 3.0 * 4.0 ) + ( 5.0 + 6.8 )";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 26.880000, 6);
}

START_TEST(calc_test_54) {
  int error = 0;
  char input_string[256] = "10^10";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 10000000000.000000, 6);
}

START_TEST(calc_test_55) {
  int error = 0;
  char input_string[256] = "10000000000 - 10000000000";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.000000, 6);
}

START_TEST(calc_test_56) {
  int error = 0;
  char input_string[256] =
      "1+2+3+4+5+6+7+8+9+10+100-3-2-10-3*2+12+15+16+17+18/2";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 203.000000, 6);
}

START_TEST(calc_test_57) {
  int error = 0;
  char input_string[256] =
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+"
      "1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1+1";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 128.000000, 6);
}

START_TEST(calc_test_58) {
  int error = 0;
  char input_string[256] =
      "1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*"
      "1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*"
      "1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*1*"
      "1*1*1*1*1*1*1*1*1*1*1*1*1*1";
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 1.000000, 6);
}

START_TEST(calc_test_59) {
  char input_string[50] = "log(1)";
  int error = 0;
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq_tol(res, 0.0, 6);

  char input_string1[50] = "log(1.5)";
  error = 0.0;
  parse_str(input_string1, &error, 0);
  ck_assert_double_eq_tol(res, 0.17609125905, 6);
}

START_TEST(calc_test_70) {
  char input_string[50] = "c\0";
  int error = 0;
  double res = parse_str(input_string, &error, 0);
  ck_assert_int_eq(1, error);
}

START_TEST(calc_test_67) {
  char input_string[50] = "+8+9mod 5";
  int error = 0;
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(12, res);
}

START_TEST(calc_test_68) {
  char input_string[50] = "8+9mod +5";
  int error = 0;
  double res = parse_str(input_string, &error, 0);
  ck_assert_double_eq(12, res);
}

START_TEST(calc_test_69) {
  char input_string[50] = "x";
  int error = 0;
  double res = parse_str(input_string, &error, 5);
  ck_assert_double_eq(5, res);
}

START_TEST(calc_test_71) {
  char input_string[50] = "+\0";
  int error = 0;
  double res = parse_str(input_string, &error, 0);
  ck_assert_int_eq(1, error);
}

START_TEST(calc_test_72) {
  char input_string[50] = "2^4 + 2x + 2";
  int error = 0;
  double res = parse_str(input_string, &error, 0);
  ck_assert_int_eq(1, error);
}

Suite *suite_polish(void) {
  Suite *s;
  TCase *tc;
  s = suite_create("polish_notation");
  tc = tcase_create("polish_notation");

  tcase_add_test(tc, calc_test_1);
  tcase_add_test(tc, calc_test_2);
  tcase_add_test(tc, calc_test_3);
  tcase_add_test(tc, calc_test_4);
  tcase_add_test(tc, calc_test_5);
  tcase_add_test(tc, calc_test_6);
  tcase_add_test(tc, calc_test_7);
  tcase_add_test(tc, calc_test_8);
  tcase_add_test(tc, calc_test_9);
  tcase_add_test(tc, calc_test_10);
  tcase_add_test(tc, calc_test_11);
  tcase_add_test(tc, calc_test_12);
  tcase_add_test(tc, calc_test_13);
  tcase_add_test(tc, calc_test_14);
  tcase_add_test(tc, calc_test_15);
  tcase_add_test(tc, calc_test_16);
  tcase_add_test(tc, calc_test_17);
  tcase_add_test(tc, calc_test_18);
  tcase_add_test(tc, calc_test_19);
  tcase_add_test(tc, calc_test_20);
  tcase_add_test(tc, calc_test_21);
  tcase_add_test(tc, calc_test_22);
  tcase_add_test(tc, calc_test_23);
  tcase_add_test(tc, calc_test_24);
  tcase_add_test(tc, calc_test_25);
  tcase_add_test(tc, calc_test_26);
  tcase_add_test(tc, calc_test_27);
  tcase_add_test(tc, calc_test_28);
  tcase_add_test(tc, calc_test_29);
  tcase_add_test(tc, calc_test_30);
  tcase_add_test(tc, calc_test_31);
  tcase_add_test(tc, calc_test_32);
  tcase_add_test(tc, calc_test_33);
  tcase_add_test(tc, calc_test_34);
  tcase_add_test(tc, calc_test_35);
  tcase_add_test(tc, calc_test_36);
  tcase_add_test(tc, calc_test_37);
  tcase_add_test(tc, calc_test_38);
  tcase_add_test(tc, calc_test_39);
  tcase_add_test(tc, calc_test_40);
  tcase_add_test(tc, calc_test_41);
  tcase_add_test(tc, calc_test_43);
  tcase_add_test(tc, calc_test_44);
  tcase_add_test(tc, calc_test_45);
  tcase_add_test(tc, calc_test_46);
  tcase_add_test(tc, calc_test_47);
  tcase_add_test(tc, calc_test_48);
  tcase_add_test(tc, calc_test_49);
  tcase_add_test(tc, calc_test_50);
  tcase_add_test(tc, calc_test_51);
  tcase_add_test(tc, calc_test_52);
  tcase_add_test(tc, calc_test_53);
  tcase_add_test(tc, calc_test_54);
  tcase_add_test(tc, calc_test_55);
  tcase_add_test(tc, calc_test_56);
  tcase_add_test(tc, calc_test_57);
  tcase_add_test(tc, calc_test_58);
  tcase_add_test(tc, calc_test_59);
  tcase_add_test(tc, calc_test_67);
  tcase_add_test(tc, calc_test_68);
  tcase_add_test(tc, calc_test_69);
  tcase_add_test(tc, calc_test_70);
  tcase_add_test(tc, calc_test_71);
  tcase_add_test(tc, calc_test_72);

  suite_add_tcase(s, tc);
  return s;
}

void case_test(Suite *s, int *fail) {
  SRunner *runner = srunner_create(s);
  srunner_set_fork_status(runner, CK_NOFORK);
  srunner_run_all(runner, CK_NORMAL);
  *fail = srunner_ntests_failed(runner);
  srunner_free(runner);
}

int main() {
  int fail = 0;

  case_test(suite_polish(), &fail);

  return fail;
}
