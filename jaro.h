#ifndef LIBJARO_JARO_H
#define LIBJARO_JARO_H

typedef struct LibJaroOption{
  double weight, threshold;
  char ignore_case;
} LibJaroOption;

double jaro_winkler_distance(char *str1, char *str2);
double jaro_winkler_distance2(char *str1, char *str2, LibJaroOption *opt);
double jaro_winkler_distance3(char *str1, int len1, char *str2, int len2, LibJaroOption *opt);

#endif