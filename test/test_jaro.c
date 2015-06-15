#include "jaro.h"

#include <assert.h>

static char within(double expected, double actual){
  return (actual > expected-0.001 && actual < expected+0.001);
}

int main(void){
  assert(within(0.9667, jaro_winkler_distance("henka", "henkan")));
  assert(within(1.0, jaro_winkler_distance("al",  "al")));
  assert(within(0.9611, jaro_winkler_distance("martha",  "marhta")));
  assert(within(0.8324, jaro_winkler_distance("jones", "johnson")));
  assert(within(0.9583, jaro_winkler_distance("abcvwxyz", "cabvwxyz")));
  assert(within(0.84, jaro_winkler_distance("dwayne", "duane")));
  assert(within(0.8133, jaro_winkler_distance("dixon", "dicksonx")));
  assert(within(0.0, jaro_winkler_distance("fvie", "ten")));
  assert(within(0.8180, jaro_winkler_distance("Santa Monica", "San Francisco")));
  assert(within(0.9818, jaro_winkler_distance("變形金剛4:絕跡重生", "變形金剛4: 絕跡重生")));
  assert(within(0.8222, jaro_winkler_distance("連勝文", "連勝丼")));
  assert(within(0.8222, jaro_winkler_distance("馬英九", "馬英丸")));
  assert(within(0.6666, jaro_winkler_distance("良い", "いい")));

  LibJaroOption opt = {.ignore_case = 1, .weight = 0.1, .threshold = 0.7};
  assert(within(0.9667, jaro_winkler_distance2("HENKA", "henkan", &opt)));
  assert(within(1.0, jaro_winkler_distance2("AL",  "al", &opt)));
  assert(within(0.9611, jaro_winkler_distance2("MARTHA",  "marhta", &opt)));
  assert(within(0.8324, jaro_winkler_distance2("JONES", "johnson", &opt)));
  assert(within(0.9583, jaro_winkler_distance2("ABCVWXYZ", "cabvwxyz", &opt)));
  assert(within(0.84, jaro_winkler_distance2("DWAYNE", "duane", &opt)));
  assert(within(0.8133, jaro_winkler_distance2("DIXON", "dicksonx", &opt)));
  assert(within(0.0, jaro_winkler_distance2("FVIE", "ten", &opt)));

  return 0;
}