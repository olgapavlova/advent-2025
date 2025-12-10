#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COLS_PATH "cols-pure.txt"
#define ROWS_PATH "rows-pure.txt"
#define OUT_PATH "cols-extra.txt"
#define MAX 990000

typedef struct segment_s {
  int from;
  int to;
} segment_t;

static segment_t rows[MAX] = {0};

int main(void) {
  FILE* fc = fopen(COLS_PATH, "r");
  FILE* fr = fopen(ROWS_PATH, "r");
  FILE* g = fopen(OUT_PATH, "w");

  // Читаем горизонтали 
  char* line; size_t len; size_t read;
  while ((read = getline(&line, &len, fr)) != -1) {
    int y = atoi(strtok(line, ","));
    rows[y].from = atoi(strtok(NULL, ","));
    rows[y].to = atoi(strtok(NULL, ","));
  }

  // Насыщаем вертикали
  while ((read = getline(&line, &len, fc)) != -1) {
    int x = atoi(strtok(line, ","));
    int from = atoi(strtok(NULL, ","));
    int to = atoi(strtok(NULL, ","));
    for(int y = 0; y < from; y++) {
      if((rows[y].from <= x) && (rows[y].to >= x)) {
        from = y;
        break;
      }
    }
    for(int y = MAX - 1; y >= to; y--) {
      if((rows[y].from <= x) && (rows[y].to >= x)) {
        to = y;
        break;
      }
    }
    fprintf(g, "%d,%d,%d\n", x, from, to);
  }

  fclose(g);
  fclose(fr);
  fclose(fc);

  return 0;
}
