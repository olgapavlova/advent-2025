#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IN_PATH "xup.txt"
#define OUT_PATH "bl.txt"

int main(void) {
  FILE* f = fopen(IN_PATH, "r");
  FILE* g = fopen(OUT_PATH, "w");

  // Записываем в файл результата только хорошие точки
  char* line;
  size_t len;
  size_t read;

  int xnow = 0;
  int ymax = -1;
  int change = 0;
  while ((read = getline(&line, &len, f)) != -1) {
    int x = atoi(strtok(line, ","));
    int y = atoi(strtok(NULL, ","));

    if (x > xnow) {
      if (change == 1)  // если в предыдущем диапазоне была хорошая точка
        fprintf(g, "%d,%d\n", xnow, ymax); // записываем хорошую точку предыдущего диапазона
      change = 0; // сбрасываем флаг «порог изменился»
      xnow = x;   // перемещаем диапазон
    }

    if (y > ymax) { // нас интересуют только хорошие точки
      ymax = y;     // сдвигаем порог
      change = 1;   // помечаем, что порог изменился
      printf("[%d:%d] → %d\n", x, y, ymax);
    }
  }
  if (change == 1)  // если в последнем диапазоне была хорошая точка
    fprintf(g, "%d,%d\n", xnow, ymax); // записываем хорошую точку последнего диапазона

  fclose(g);
  fclose(f);

  return 0;
}
