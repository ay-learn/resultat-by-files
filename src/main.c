#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 24

int main() {
  FILE *fp1, *fp2 = NULL;
  fp1 = fopen("1.txt", "r");
  fp2 = fopen("2.txt", "r");
  if (fp1 == NULL || fp2 == NULL) {
    perror("popen");
    exit(EXIT_FAILURE);
  }
  S1 s1[MAX];
  S2 s2[MAX];
  int i = 0;

  char line[500];
  while (!feof(fp1)) {
    if (fgets(line, sizeof(line), fp1)) {
      sscanf(line, "%f %f %f %f %f %f %[a-zA-Z\" ]\n", &s1[i].info, &s1[i].ray,
             &s1[i].nuc, &s1[i].elec, &s1[i].eng, &s1[i].anat, s1[i].name);
      i++;
    }
  }
  i=0;
  while (!feof(fp2)) {
    if (fgets(line, sizeof(line), fp2)) {
      sscanf(line, "%f %f %f %f %f %f %[a-zA-Z\" ]\n", &s2[i].ins, &s2[i].bio,
             &s2[i].met, &s2[i].img, &s2[i].info, &s2[i].fr, s2[i].name);
      i++;
    }
  }
  for (i = 0; i < MAX; i++) {
    printf("%2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %s\n", s1[i].info, s1[i].ray,
           s1[i].ray, s1[i].elec, s1[i].eng, s1[i].anat, s1[i].name);
    // printf("%2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %s\n", s2[i].ins, s2[i].bio,
    //        s2[i].met, s2[i].img, s2[i].info, s2[i].fr, s2[i].name);
  }


  int sum = 6;
  for (int i = 0; i < MAX; i++)
    s1[i].result = (s1[i].ray + s1[i].info + s1[i].nuc + s1[i].elec +
                    s1[i].eng + s1[i].anat) /
                   sum;

  // for (int i = 0; i < MAX - 1; i++)
  //   for (int j = i + 1; j < MAX; j++)
  //     if (s1[i].result < s1[j].result) {
  //       S1 tmp = s1[i];
  //       s1[i] = s1[j];
  //       s1[j] = tmp;
  //     }

  for (int i = 0; i < MAX; i++)
    s2[i].result = (s2[i].ins + s2[i].bio + s2[i].met + s2[i].img + s2[i].info +
                    s2[i].fr) /
                   sum;

  // for (int i = 0; i < MAX - 1; i++)
  //   for (int j = i + 1; j < MAX; j++)
  //     if (s2[i].result < s2[j].result) {
  //       S2 tmp = s2[i];
  //       s2[i] = s2[j];
  //       s2[j] = tmp;
  //     }

  S12 s12[MAX];
  for (int i = 0; i < MAX - 1; i++) {
    strcpy(s12[i].name, s1[i].name);
    s12[i].result = (s1[i].result + s2[i].result) / 2.0;
  }

  for (int i = 0; i < MAX - 1; i++)
    for (int j = i + 1; j < MAX; j++)
      if (s12[i].result < s12[j].result) {
        S12 tmp = s12[i];
        s12[i] = s12[j];
        s12[j] = tmp;
      }

  for (int i = 0; i < MAX; i++) {
    printf("%3d %2.2f \t %s\n", i + 1, s12[i].result, s12[i].name);
  }

  return 0;
}
