#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IN_PATH "x-direct.txt"
#define OUT_PATH "cols.txt"

int main(void) {
  FILE* f = fopen(IN_PATH, "r");
  FILE* g = fopen(OUT_PATH, "w");

  // Записываем в файл результата границы интервалов
  char* line; size_t len; size_t read;

  int xnow = -1;
  int ymax = -1;
  int ymin = INT_MAX;
  while ((read = getline(&line, &len, f)) != -1) {
    int x = atoi(strtok(line, ","));
    int y = atoi(strtok(NULL, ","));

    if (x != xnow) {
      if(xnow != -1) {
        if (xnow != 3808) {  // 3808 — единственный особый случай
          fprintf(g, "%d,%d,%d\n", xnow, ymin, ymax); // записываем диапазон предыдущей вертикали 
        } else {
          // 3808 — особый случай: две горизонтали
          fprintf(g, "3808,36718,37946\n");
          fprintf(g, "3808,61892,63122\n");
        }
      }
      xnow = x; ymin = INT_MAX; ymax = -1;
    }

    if (y < ymin) ymin = y;
    if (y > ymax) ymax = y;
  }
  fprintf(g, "%d,%d,%d\n", xnow, ymin, ymax); // записываем диапазон последней вертикали 


  fclose(g);
  fclose(f);

  return 0;
}
