#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IN_PATH "i.txt"
#define ISX_PATH "isx.txt"
#define ISY_PATH "isy.txt"
#define W 99000
#define H 99000


// Пустые колонки
static int empty_cols[W] = 0;

// Поиск пустых колонок
int find_empty_cols(void) {
  int xprev = -1;
  char * line; size_t len; size_t read;
  FILE* f = fopen(ISX_PATH, "r");
  while((read = getline(&line, &len, f)) != -1) {
   int x = atoi(strtok(line, ","));
   int delta = x - xprev;
   if(delta != 1) {
     result += delta - 1;
   }
   xprev = x;
  }
  fclose(f);
}




int main(void) {
  char mm[W][H] = {0};
  char m[W][H] = {0};
  char dely[W] = {0}; 
  // char * dely = malloc(W * sizeof(char));
  // char delx[H] = {0};
  int mx = 0;
  int my = 0;

  // printf("%d\t%d\n", W, H);

  // Считываем координаты всех точек
  char * line;
  size_t len;
  size_t read;
  FILE* f = fopen(IN_PATH, "r");
  while((read = getline(&line, &len, f)) != -1) {
   int x = atoi(strtok(line, ","));
   int y = atoi(strtok(NULL, ","));
   mm[x][y] = 1;
  }
  fclose(f);

  // Убираем дырки
  
  // Сначала убираем пустые колонки
  for(int x = 0; x < W; x++) {
    dely[x] = 1;
    for(int y = 0; y < H; y++) {
      dely[x] &= (!(mm[x][y]));
    }
    printf("%d\n", dely[x]);
  }

  // mx = dely[W - 1];

  return 0;

#if 0
  // Выводим матрицу
  for(int y = 0; y < H; y++) {
    for(int x = 0; x < W; x++) {
      printf("%c", (m[x][y] == 1) ? '#' : '.');
    }
    printf("\n");
  }
#endif

// Интересующие нас точки
// Потом будем связывать tr&bl и tl&br в прямоугольники
int tl[W] = {0};  // сверху слева пусто
int br[W] = {0};  // снизу справа пусто
int tr[W] = {0};  // сверху справа пусто
int bl[W] = {0};  // снизу слева пусто

  // Собираем tl
  int ymin = H;
  for(int x = 0; x < W; x++) {
    tl[x] = -1;
    for(int y = 0; y < H; y++) {
      if((m[x][y]) && (y < ymin)) {
        ymin = y;
#if 0
        tl[x] = y;
        printf("[%d:%d] → %d\n", x, y, ymin);
#endif
        break;
      }
    }
  }
  // printf("\n");

#if 0
  printf("tl\t");
  for(int x = 0; x < W; x++) printf("%3d ", tl[x]);
  printf("\n");
#endif

  // Собираем br
  int ymax = -1;
  for(int x = W - 1; x >= 0; x--) {
    br[x] = -1;
    for(int y = H - 1; y >= 0; y--) {
      if((m[x][y]) && (y > ymax)) {
        br[x] = y;
        ymax = y;
        // printf("[%2d:%2d] → %2d\n", x, y, ymax);
        break; 
      }
    }
  }
  // printf("\n");

#if 0
  printf("br\t");
  for(int x = 0; x < W; x++) printf("%3d ", br[x]);
  printf("\n");
#endif

  // Собираем tr
  ymin = H;
  for(int x = W - 1; x >= 0; x--) {
    tr[x] = -1;
    for(int y = 0; y < H; y++) {
      if((m[x][y]) && (y < ymin)) {
        tr[x] = y;
        ymin = y;
        // printf("[%2d:%2d] → %2d\n", x, y, ymin);
        break; 
      }
    }
  }
  // printf("\n");

#if 0
  printf("tr\t");
  for(int x = 0; x < W; x++) printf("%3d ", tr[x]);
  printf("\n");
#endif


  // Собираем bl
  ymax = -1;
  for(int x = 0; x < W; x++) {
    bl[x] = -1;
    for(int y = H - 1; y >= 0; y--) {
      if((m[x][y]) && (y > ymax)) { 
        bl[x] = y; 
        ymax = y; 
        // printf("[%2d:%2d] → %2d\n", x, y, ymax);
        break; 
      }

    }
  }
  // printf("\n");

#if 0
  printf("bl\t");
  for(int x = 0; x < W; x++) printf("%3d ", bl[x]);
  printf("\n");
#endif

  // Ищем максимальную площадь для tl & br
  long long smaxtlbr = -1;
  for (int xtl = 0; xtl < W; xtl++) {
    for(int xbr = xtl + 1; xbr < W; xbr++) {
      if((tl[xtl] != -1) &&
         (br[xbr] != -1) &&
         (tl[xtl] < br[xbr])) {
        long long s = (long long)(xbr - xtl + 1) * (long long)(br[xbr] - tl[xtl] + 1);
        if(s > smaxtlbr) smaxtlbr = s;
        // printf("[%3d:%3d]\t[%3d:%3d] → %4lld | %4lld\n", xtl, tl[xtl], xbr, br[xbr], s, smaxtlbr);
      }
    }
  }
  // printf("\n");


  // Ищем максимальную площадь для tr & bl
  long long smaxtrbl = -1;
  for (int xtr = W - 1; xtr >= 0; xtr--) {
    for(int xbl = 0; xbl < xtr; xbl++) {
      if((tr[xtr] != -1) &&
         (bl[xbl] != -1) &&
         (tr[xtr] < bl[xbl])) {
        long long s = (long long)(xtr - xbl + 1) * (long long)(bl[xbl] - tr[xtr] + 1);
        if(s > smaxtrbl) smaxtrbl = s;
        // printf("[%3d:%3d]\t[%3d:%3d] → %4lld | %4lld\n", xtr, tr[xtr], xbl, bl[xbl], s, smaxtrbl);
      }
    }
  }
  // printf("\n");

  // Печатаем максимум
  if(smaxtrbl > smaxtlbr) printf("%lld\n", smaxtrbl);
  else printf("%lld\n", smaxtlbr);

  return 0;
}
