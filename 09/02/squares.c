#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IN_PATH "x-direct.txt"
#define COLS_PATH "cols-extra.txt"
#define OUT_PATH "squares.txt"
#define MAX 500

typedef struct segment_s {
  int from;
  int to;
} segment_t;

typedef struct point_s {
  int x;
  int y;
} point_t;

static point_t p[MAX] = {0};
static segment_t cols[MAX] = {0};

int if_in(int x, int y) {
  int result = 1;
  int xcol = x;
  while(cols[xcol].from == 0) { xcol--; } 
  result &= (cols[xcol].from <= y);
  result &= (cols[xcol].to >= y);
  return result;
}


int main(void) {
  FILE* f = fopen(IN_PATH, "r");

  // Читаем красные метки 
  char* line; size_t len; size_t read;
  int num = 0;
  while ((read = getline(&line, &len, f)) != -1) {
    p[num].x = atoi(strtok(line, ","));
    p[num].y = atoi(strtok(NULL, ","));
    num++;
  }
  fclose(f);

  // Читаем вертикали 
  f = fopen(COLS_PATH, "r");
  while ((read = getline(&line, &len, f)) != -1) {
    int x = atoi(strtok(line, ","));
    cols[x].from = atoi(strtok(NULL, ","));
    cols[x].to = atoi(strtok(NULL, ","));
  }

  int xmax = MAX; while(p[xmax].x == 0) { xmax--; }

  FILE* g = fopen(OUT_PATH, "w");
  for(int ax = 0; ax < xmax; ax++) {
    for(int bx = 0; bx < xmax; bx++) {
      if((p[ax].x != 0) && (p[bx].x != 0)
          && (p[ax].x <= p[bx].x) && (p[ax].y <= p[bx].y)) {
        int in = if_in(p[ax].x, p[bx].y) && if_in(p[bx].x, p[ax].y);
        if(in) {
          fprintf(g, "%d,%d,%d,%d\n", p[ax].x, p[ax].y, p[bx].x, p[bx].y);
        }
      }
    }
  }
  fclose(g);

  return 0;
}
