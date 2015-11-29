#include "jaro.h"

#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define SWAP(x, y) do{ __typeof__(x) SWAP = x; x = y; y = SWAP; }while(0)
#define DEFAULT_WEIGHT 0.1
#define DEFAULT_THRESHOLD 0.7

void string_to_codes(char *str, int length, unsigned long long **ret_codes, int *ret_length);

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


  unsigned long long *short_codes, *long_codes;
  int short_codes_len, long_codes_len;
  string_to_codes(short_str, short_str_len, &short_codes, &short_codes_len);
  string_to_codes(long_str, long_str_len, &long_codes, &long_codes_len);

  if(opt && opt->ignore_case){
    for(int i = 0; i < short_codes_len; i++) short_codes[i] = tolower(short_codes[i]);
    for(int i = 0; i < long_codes_len; i++) long_codes[i] = tolower(long_codes[i]);
  }

  int window_size = long_codes_len/2 - 1;
  if(window_size < 0) window_size = 0;

  char short_codes_flag[short_str_len];
  char long_codes_flag[long_str_len];
  memset(short_codes_flag, 0, short_str_len);
  memset(long_codes_flag, 0, long_str_len);

  // count number of matching characters
  int match_count = 0;
  for(int i = 0; i < short_codes_len; i++){
    int left = (i >= window_size) ? i - window_size : 0;
    int right = (i + window_size <= long_codes_len - 1) ? (i + window_size) : (long_codes_len - 1);
    if(right > long_codes_len - 1) right = long_codes_len - 1;
    for(int j = left; j <= right; j++){
      if(!long_codes_flag[j] && short_codes[i] == long_codes[j]){
        short_codes_flag[i] = long_codes_flag[j] = 1;
        match_count++;
        break;
      }
    }
  }
  if(!match_count){
    free(short_codes); free(long_codes);
    return 0.0;
  }

  // count number of transpositions
  int transposition_count = 0, j = 0, k = 0;
  for(int i = 0; i < short_codes_len; i++){
    if(short_codes_flag[i]){
      for(j = k; j < long_codes_len; j++){
        if(long_codes_flag[j]){
          k = j + 1;
          break;
        }
      }
      if(short_codes[i] != long_codes[j]) transposition_count++;
    }
  }

  // jaro distance
  double jaro_distance;
  double m = (double)match_count;
  double t = (double)(transposition_count/2);
  jaro_distance = (m/short_codes_len + m/long_codes_len + (m-t)/m) / 3;

  // jaro winkler distance
  if(!opt){
    static LibJaroOption default_opt = {.weight = DEFAULT_WEIGHT, .threshold = DEFAULT_THRESHOLD};
    opt = &default_opt;
  }
  if(jaro_distance < opt->threshold){
    free(short_codes); free(long_codes);
    return jaro_distance;
  }
  else{
    int prefix = 0;
    int max_4 = short_codes_len > 4 ? 4 : short_codes_len;
    for(prefix = 0; prefix < max_4 && short_codes[prefix] == long_codes[prefix]; prefix++);
    free(short_codes); free(long_codes);
    return jaro_distance + prefix*opt->weight*(1-jaro_distance);
  }
}

void string_to_codes(char *str, int length, unsigned long long **ret_codes, int *ret_length){
  unsigned int code;
  char byte_length;

  *ret_codes = malloc(length * sizeof(long long));
  *ret_length = 0;

  for(int i = 0; i < length;){
    unsigned char first_char = (unsigned char)str[i];
    if(first_char >= 252) byte_length = 6;      // 1111110x
    else if(first_char >= 248) byte_length = 5; // 111110xx
    else if(first_char >= 240) byte_length = 4; // 11110xxx
    else if(first_char >= 224) byte_length = 3; // 1110xxxx
    else if(first_char >= 192) byte_length = 2; // 110xxxxx
    else byte_length = 1;
    (*ret_codes)[*ret_length] = 0;
    memcpy(&(*ret_codes)[*ret_length], &str[i], byte_length);
    *ret_length += 1;
    i += byte_length;
  }
}