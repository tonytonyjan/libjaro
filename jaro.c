#include "jaro.h"

#include <string.h>

#define SWAP(x, y) do{ __typeof__(x) SWAP = x; x = y; y = SWAP; }while(0)
#define MAX_WORD_LENGTH 64
#define DEFAULT_WEIGHT 0.1
#define DEFAULT_THRESHOLD 0.7

double jaro_winkler_distance(char *str1, char *str2){
  return jaro_winkler_distance2(str1, str2, NULL);
}

double jaro_winkler_distance2(char *str1, char *str2, LibJaroOption *opt){
  return jaro_winkler_distance3(str1, strlen(str1), str2, strlen(str2), opt);
}

double jaro_winkler_distance3(char* short_str, int short_str_len, char* long_str, int long_str_len, LibJaroOption *opt){
  if(!short_str_len || !long_str_len) return 0.0;

  if(short_str_len > long_str_len){
    SWAP(short_str, long_str);
    SWAP(short_str_len, long_str_len);
  }

  int window_size = long_str_len/2 - 1;
  if(window_size < 0) window_size = 0;

  char short_str_flag[MAX_WORD_LENGTH];
  char long_str_flag[MAX_WORD_LENGTH];
  memset(short_str_flag, 0, MAX_WORD_LENGTH);
  memset(long_str_flag, 0, MAX_WORD_LENGTH);

  // count number of matching characters
  int match_count = 0;
  for(int i = 0; i < short_str_len; i++){
    int left = (i >= window_size) ? i - window_size : 0;
    int right = (i + window_size <= long_str_len - 1) ? (i + window_size) : (long_str_len - 1);
    if(right > long_str_len - 1) right = long_str_len - 1;
    for(int j = left; j <= right; j++){
      if(!long_str_flag[j] && short_str[i] == long_str[j]){
        short_str_flag[i] = long_str_flag[j] = 1;
        match_count++;
        break;
      }
    }
  }
  if(!match_count) return 0.0;

  // count number of transpositions
  int transposition_count = 0, j = 0, k = 0;
  for(int i = 0; i < short_str_len; i++){
    if(short_str_flag[i]){
      for(j = k; j < long_str_len; j++){
        if(long_str_flag[j]){
          k = j + 1;
          break;
        }
      }
      if(short_str[i] != long_str[j]) transposition_count++;
    }
  }

  // jaro distance
  double jaro_distance;
  double m = (double)match_count;
  double t = (double)(transposition_count/2);
  jaro_distance = (m/short_str_len + m/long_str_len + (m-t)/m) / 3;

  // jaro winkler distance
  if(!opt){
    static LibJaroOption default_opt = {.weight = DEFAULT_WEIGHT, .threshold = DEFAULT_THRESHOLD};
    opt = &default_opt;
  }
  if(jaro_distance < opt->threshold) return jaro_distance;
  else{
    int prefix = 0;
    int max_4 = short_str_len > 4 ? 4 : short_str_len;
    for(prefix = 0; prefix < max_4 && short_str[prefix] == long_str[prefix]; prefix++);
    return jaro_distance + prefix*opt->weight*(1-jaro_distance);
  }
}