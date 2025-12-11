#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IN_PATH "x-direct.txt"
#define COLS_PATH "cols-extra.txt"
#define OUT_PATH "squares.txt"
#define MAX 500

typedef struct segment_s {
  int x;
  int from;
  int to;
} segment_t;

typedef struct point_s {
  int x;
  int y;
} point_t;

static point_t p[MAX] = {0};
static segment_t cols[MAX] = {0};
static int idcolmax = MAX; 

int if_in(int x, int y) {
  int result = 1;
  int idcol = idcolmax;
  while((cols[idcol].x == 0) || (cols[idcol].x > x)) { idcol--; } 
  result &= (cols[idcol].from <= y);
  result &= (cols[idcol].to >= y);
  return result;
}


long long square(point_t a, point_t b) {
  int w = (a.x > b.x) ? (a.x - b.x + 1) : (b.x - a.x + 1);
  int h = (a.y > b.y) ? (a.y - b.y + 1) : (b.y - a.y + 1);
  return (long long)w * h;
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
  num = 0;
  while ((read = getline(&line, &len, f)) != -1) {
    cols[num].x = atoi(strtok(line, ","));
    cols[num].from = atoi(strtok(NULL, ","));
    cols[num].to = atoi(strtok(NULL, ","));
    num++;
  }

  while(p[idcolmax].x == 0) { idcolmax--; }

  FILE* g = fopen(OUT_PATH, "w");
  for(int ax = 0; ax < idcolmax; ax++) {
    for(int bx = ax + 1; bx < idcolmax; bx++) {
      int in = if_in(p[ax].x, p[bx].y) && if_in(p[bx].x, p[ax].y);
      if(in) {
        long long s = square(p[ax], p[bx]);
        fprintf(g, "%d,%d,%d,%d:%lld\n", p[ax].x, p[ax].y, p[bx].x, p[bx].y, s);
      }
    }
  }
  fclose(g);
  return 0;
}
