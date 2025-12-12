#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IN_PATH "x-direct.txt"
#define COLS_PATH "cols.txt"
#define ROWS_PATH "rows.txt"
#define OUT_PATH "squares.txt"
#define MAX 500

// Направления
typedef enum { COL, ROW } DIRS;

// Точка
typedef struct point_s {
  int x;
  int y;
} point_t;

// Сегмент
typedef struct segment_s {
  DIRS dir;
  point_t from;  // указатели на точки
  point_t to;
} segment_t;

static point_t p[MAX] = {0};       // красные точки (они же — повороты границ)
static segment_t cols[MAX] = {0};  // вертикальные границы фигуры
static segment_t rows[MAX] = {0};  // горизонтальные границы фигуры
static int idcolmax = MAX;         // количество вертикальных границ
static int idrowmax = MAX;         // количество горизонтальных границ

// Рассчитать площадь прямоугольника по диагональным точкам
long long square(point_t a, point_t b) {
  long long w = (a.x > b.x) ? (a.x - b.x + 1) : (b.x - a.x + 1);
  long long h = (a.y > b.y) ? (a.y - b.y + 1) : (b.y - a.y + 1);
  return w * h;
}

// Создать сегмент по двум точкам
segment_t segment_init(point_t a, point_t b) {
  if ((a.x != b.x) && (a.y != b.y)) {
    perror("Попытка создать диагональный сегмент");
  }
  segment_t result = {0};
  result.from = ((a.x < b.x) || (a.y < b.y)) ? a : b;
  result.to = (memcmp(&result.from, &a, sizeof(point_t)) == 0) ? b : a;
  return result;
}

// Посчитать, сколько раз сегмент пересекается с границей
// ? Как учитывать точки пересечения, лежащие на сегменте?
int segment_cross_border(segment_t seg) {
  int result = 0;
  if (seg.dir == COL) {  // вертикальный сегмент
    for (int n = 0; n < idrowmax; n++) {
      if ((rows[n].from.y > seg.from.y) &&
          (rows[n].from.y < seg.to.y)) {  // горизонталь может пересечь сегмент
        if ((rows[n].from.x < seg.from.x) &&
            (rows[n].to.x > seg.from.x)) {  // пересекла
          result++;
          // TODO Не учитывает ситуацию, когда между горизонталями нет интервала
          // — проверить
        }
      }
    }
  } else {  // горизонтальный сегмент
    for (int n = 0; n < idcolmax; n++) {
      if ((cols[n].from.x > seg.from.x) &&
          (cols[n].from.x < seg.to.x)) {  // вертикаль может пересечь сегмент
        if ((cols[n].from.y < seg.from.y) &&
            (cols[n].to.y > seg.from.y)) {  // пересекла
          result++;
          // TODO Не учитывает ситуацию, когда между вертикалями нет интервала —
          // проверить
        }
      }
    }
  }

  printf("[%d:%d] [%d:%d] → %d\n", seg.from.x, seg.from.y, seg.to.x, seg.to.y, result);
  return result;
}

// Найти горизонтальный сегмент границы по значению y
segment_t* row_by_y(int y) {
  segment_t* result = NULL;
  int num = 0;
  while (rows[num].from.y != y) {
    num++;
  }
  result = &rows[num];
}

// Найти вертикальный сегмент границы по значению x
segment_t* col_by_x(int x) {
  segment_t* result = NULL;
  int num = 0;
  while (cols[num].from.x != x) {
    num++;
  }
  result = &cols[num];
  // TODO С 3808 разобраться отдельно
}

// Прочитать красные метки
void read_points(void) {
  char* line;
  size_t len;
  size_t read;
  int num = 0;
  FILE* f = fopen(IN_PATH, "r");
  while ((read = getline(&line, &len, f)) != -1) {
    p[num].x = atoi(strtok(line, ","));
    p[num].y = atoi(strtok(NULL, ","));
    num++;
  }
  fclose(f);
}

// Прочитать однотипные границы из файла
void read_borders(DIRS dir, char* F_PATH) {
  segment_t* arr = (dir == COL) ? cols : rows;
  char* line;
  size_t len;
  size_t read;
  int num = 0;
  FILE * f = fopen(F_PATH, "r");
  while ((read = getline(&line, &len, f)) != -1) {
    arr[num].dir = dir;
    switch (dir) {
      case COL: {
        arr[num].from.x = atoi(strtok(line, ","));
        cols[num].to.x = arr[num].from.x;
        arr[num].from.y = atoi(strtok(NULL, ","));
        arr[num].to.y = atoi(strtok(NULL, ","));
        break;
      }
      case ROW: {
        arr[num].from.y = atoi(strtok(line, ","));
        arr[num].to.y = arr[num].from.y;
        arr[num].from.x = atoi(strtok(NULL, ","));
        arr[num].to.x = atoi(strtok(NULL, ","));
        break;
      }
      default:
        perror("Выбрано странное направление.");
    }
    num++;
  }
  fclose(f);
}

// Проверить луч из точки
int check_ray(DIRS dir, point_t a) {
  int result;

  segment_t * seg = (dir == COL) ? col_by_x(a.x) : row_by_y(a.y);
  segment_t ray = {dir, {0}, {0}};
  ray.from.x = (dir == COL) ? a.x : 0;
  ray.from.y = (dir == COL) ? 0 : a.y;
  ray.to = a;

  int sum = segment_cross_border(ray);

  // printf("%d\n", sum);

  result = sum % 2;

  return result;
}

// Проверить, хорош ли прямоугольник
int is_square_inside(point_t a, point_t b) {
  int result = 1;
  point_t ab = { a.x, b.y };
  point_t ba = { b.x, a.y };
  segment_t ah = segment_init(a, ab);
  segment_t bh = segment_init(b, ba);
  segment_t av = segment_init(a, ba);
  segment_t bv = segment_init(b, ab);

  result &= ((segment_cross_border(ah) == 0) &&
            (segment_cross_border(av) == 0) &&
            (segment_cross_border(bh) == 0) &&
            (segment_cross_border(bv) == 0));

  printf("R1: %d\n", result);

  result &= ((check_ray(COL, ab) == 1) &&
            (check_ray(ROW, ab) == 1) &&
            (check_ray(COL, ba) == 1) &&
            (check_ray(ROW, ba) == 1));

  printf("R2: %d\n\n", result);

  return result;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Точка входа в программу
int main(void) {
  read_points();
  while (p[idcolmax].x == 0) {
    idcolmax--;
  }
  while (p[idrowmax].y == 0) {
    idrowmax--;
  }

  read_borders(COL, COLS_PATH);
  read_borders(ROW, ROWS_PATH);

  // Сохраняем «хорошие» прямоугольники
  FILE* g = fopen(OUT_PATH, "w");
  for (int na = 0; na < idcolmax; na++) {
    for (int nb = na + 1; nb < idcolmax; nb++) {
      int ok = is_square_inside(p[na], p[nb]);
      // printf("\n[%d:%d] [%d:%d]\t", p[na].x, p[na].y, p[nb].x, p[nb].y);
      if (ok == 1) {
      printf("*");
        long long s = square(p[na], p[nb]);
        fprintf(g, "%d,%d,%d,%d:%lld\n", p[na].x, p[na].y, p[nb].x, p[nb].y, s);
      }
    }
  }
  fclose(g);
  return 0;
}
