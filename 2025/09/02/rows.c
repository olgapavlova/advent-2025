#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IN_PATH "y-direct.txt"
#define OUT_PATH "rows.txt"

int main(void) {
  FILE* f = fopen(IN_PATH, "r");
  FILE* g = fopen(OUT_PATH, "w");

  // Записываем в файл результата границы интервалов
  char* line; size_t len; size_t read;

  int ynow = -1;
  int xmax = -1;
  int xmin = INT_MAX;
  while ((read = getline(&line, &len, f)) != -1) {
    int x = atoi(strtok(line, ","));
    int y = atoi(strtok(NULL, ","));

    if (y != ynow) {
      if(ynow != -1) fprintf(g, "%d,%d,%d\n", ynow, xmin, xmax); // записываем диапазон предыдущей горизонтали
      ynow = y; xmin = INT_MAX; xmax = -1;
    }

    if (x < xmin) xmin = x;
    if (x > xmax) xmax = x;
  }
  fprintf(g, "%d,%d,%d\n", ynow, xmin, xmax); // записываем диапазон последней горизонтали

  fclose(g);
  fclose(f);

  return 0;
}
