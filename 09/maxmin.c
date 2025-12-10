#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IN_PATH "input.txt"


int main(void) {
  FILE* f = fopen(IN_PATH, "r");

  char * line;
  size_t len;
  size_t read;

  long xmin = 1000000, xmax = -1;
  long ymin = 1000000, ymax = -1;
  // Считываем координаты всех точек
  while((read = getline(&line, &len, f)) != -1) {
   int x = atoi(strtok(line, ","));
   int y = atoi(strtok(NULL, ","));
   if(xmin > x) xmin = x;
   if(xmax < x) xmax = x;
   if(ymin > y) ymin = y;
   if(ymax < y) ymax = y;
  }
  printf("xmin: %7ld\txmax: %7ld\n", xmin, xmax);
  printf("ymin: %7ld\tymax: %7ld\n", ymin, ymax);

  fclose(f);
  return 0;
}
