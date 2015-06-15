#include <stdlib.h>
#include <string.h>

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