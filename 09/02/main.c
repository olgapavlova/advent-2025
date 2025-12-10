#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TR_PATH "tr.txt"
#define TL_PATH "tl.txt"
#define BR_PATH "br.txt"
#define BL_PATH "bl.txt"
#define MAX 55

// Тип точки
typedef struct point_s {
  int x;
  int y;
} point_t;

// Массивы хороших точек
static point_t tr[MAX] = {0};
static point_t tl[MAX] = {0};
static point_t br[MAX] = {0};
static point_t bl[MAX] = {0};

void clear(point_t * arr) {
  for(int i = 0; i < MAX; i++) {
    arr[i].x = -1;
    arr[i].y = -1;
  }
}

void read(char * path, point_t * arr) {
  FILE * f = fopen(path, "r");

  char* line; size_t len; size_t read;
  int num = 0;
  while ((read = getline(&line, &len, f)) != -1) {
    arr[num].x = atoi(strtok(line, ","));
    arr[num].y = atoi(strtok(NULL, ","));
    // printf("(%d)\t[%d:%d]\n", num, arr[num].x, arr[num].y);
    num++;
  }
  fclose(f);
}

long long square(point_t a, point_t b) {
  int w = (a.x > b.x) ? (a.x - b.x + 1) : (b.x - a.x + 1);
  int h = (a.y > b.y) ? (a.y - b.y + 1) : (b.y - a.y + 1);
  return (long long)w * h;
}

int main(void) {
  clear(tr);
  clear(tl);
  clear(br);
  clear(bl);

  read(TR_PATH, tr);
  read(TL_PATH, tl);
  read(BR_PATH, br);
  read(BL_PATH, bl);

  long long smax_trbl = -1;
  point_t t;
  point_t b;
  for(int n = 0; n < MAX; n++) {
    for(int m = 0; m < MAX; m++) {
      if((tr[n].x != -1) && (bl[m].x != -1) && (tr[n].x > bl[m].x)) {
        long long s = square(tr[n], bl[m]);
        if(s > smax_trbl) {
          smax_trbl = s;
          t = tr[n];
          b = bl[m];
        }
      }
    }
  }
  printf("[%d:%d]\t[%d:%d] → %lld\n", t.x, t.y, b.x, b.y, smax_trbl);

  long long smax_tlbr = -1;
  for(int n = 0; n < MAX; n++) {
    for(int m = 0; m < MAX; m++) {
      if((tl[n].x != -1) && (br[m].x != -1) && (tl[n].x < br[m].x)) {
        long long s = square(br[m], tl[n]);
        if(s > smax_tlbr) {
          smax_tlbr = s;
          t = tl[n];
          b = br[m];
        }
      }
    }
  }
  printf("[%d:%d]\t[%d:%d] → %lld\n", t.x, t.y, b.x, b.y, smax_tlbr);

  return 0;
}
