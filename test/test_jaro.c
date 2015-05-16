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
  return 0;
}