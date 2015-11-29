#include "jaro.h"
#include <check.h>

static char within(double expected, double actual){
  return (actual > expected-0.001 && actual < expected+0.001);
}

START_TEST (test_jaro_winkler_distance)
{
  ck_assert(within(0.9667, jaro_winkler_distance("henka", "henkan")));
  ck_assert(within(1.0, jaro_winkler_distance("al",  "al")));
  ck_assert(within(0.9611, jaro_winkler_distance("martha",  "marhta")));
  ck_assert(within(0.8324, jaro_winkler_distance("jones", "johnson")));
  ck_assert(within(0.9583, jaro_winkler_distance("abcvwxyz", "cabvwxyz")));
  ck_assert(within(0.84, jaro_winkler_distance("dwayne", "duane")));
  ck_assert(within(0.8133, jaro_winkler_distance("dixon", "dicksonx")));
  ck_assert(within(0.0, jaro_winkler_distance("fvie", "ten")));
  ck_assert(within(0.8180, jaro_winkler_distance("Santa Monica", "San Francisco")));
  ck_assert(within(0.9818, jaro_winkler_distance("變形金剛4:絕跡重生", "變形金剛4: 絕跡重生")));
  ck_assert(within(0.8222, jaro_winkler_distance("連勝文", "連勝丼")));
  ck_assert(within(0.8222, jaro_winkler_distance("馬英九", "馬英丸")));
  ck_assert(within(0.6666, jaro_winkler_distance("良い", "いい")));

  LibJaroOption opt = {.ignore_case = 1, .weight = 0.1, .threshold = 0.7};
  ck_assert(within(0.9667, jaro_winkler_distance2("HENKA", "henkan", &opt)));
  ck_assert(within(1.0, jaro_winkler_distance2("AL",  "al", &opt)));
  ck_assert(within(0.9611, jaro_winkler_distance2("MARTHA",  "marhta", &opt)));
  ck_assert(within(0.8324, jaro_winkler_distance2("JONES", "johnson", &opt)));
  ck_assert(within(0.9583, jaro_winkler_distance2("ABCVWXYZ", "cabvwxyz", &opt)));
  ck_assert(within(0.84, jaro_winkler_distance2("DWAYNE", "duane", &opt)));
  ck_assert(within(0.8133, jaro_winkler_distance2("DIXON", "dicksonx", &opt)));
  ck_assert(within(0.0, jaro_winkler_distance2("FVIE", "ten", &opt)));
}
END_TEST

int main(void){
  return 0;
}