#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COLS_PATH "cols-pure.txt"
#define ROWS_PATH "rows-pure.txt"
#define OUT_PATH "rows-extra.txt"
#define MAX 990000

typedef struct segment_s {
  int from;
  int to;
} segment_t;

static segment_t cols[MAX] = {0};

int main(void) {
  FILE* fc = fopen(COLS_PATH, "r");
  FILE* fr = fopen(ROWS_PATH, "r");
  FILE* g = fopen(OUT_PATH, "w");

  for(int i = 0; i < MAX; i++) {
    cols[i].from = -1;
    cols[i].to = -1;
  }

  // Читаем вертикали 
  char* line; size_t len; size_t read;
  while ((read = getline(&line, &len, fc)) != -1) {
    int x = atoi(strtok(line, ","));
    cols[x].from = atoi(strtok(NULL, ","));
    cols[x].to = atoi(strtok(NULL, ","));
  }

  // Насыщаем горизонтали
  while ((read = getline(&line, &len, fr)) != -1) {
    int y = atoi(strtok(line, ","));
    int from = atoi(strtok(NULL, ","));
    int to = atoi(strtok(NULL, ","));
    for(int x = 0; x < from; x++) {
      if((cols[x].from <= y) && (cols[x].to >= y)) {
        from = x;
        break;
      }
    }
    for(int x = MAX - 1; x >= to; x--) {
      if((cols[x].from <= y) && (cols[x].to >= y)) {
        to = x;
        break;
      }
    }
    fprintf(g, "%d,%d,%d\n", y, from, to);
  }

  fclose(g);
  fclose(fr);
  fclose(fc);

  return 0;
}
