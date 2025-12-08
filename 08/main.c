#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "input.txt"
#define Q 1000
#define TOP "1000"
#define DIST_PATH "dist.txt"
#define PAIRS_PATH "pairs.txt"
#define PSORT_PATH "psort.txt"

// Тип точки
typedef struct point_s {
  long x;
  long y;
  long z;
  int group;
} point_t;

// Все точки
static point_t p[Q] = {0};
static point_t null = {.x = 0, .y = 0, .z = 0};

// Квадрат расстояния
long long dist(point_t a, point_t b) {
  long long result = 0;
  result += (a.x - b.x) * (a.x - b.x);
  result += (a.y - b.y) * (a.y - b.y);
  result += (a.z - b.z) * (a.z - b.z);
  return result;
}

int main(void) {
  FILE* f = fopen(FILE_PATH, "r");

  char * line;
  size_t len;
  size_t read;

  // Считываем координаты всех точек
  for(int ln = 0; ln < Q; ln++) {
   read = getline(&line, &len, f);
   p[ln].x = atoi(strtok(line, ","));
   p[ln].y = atoi(strtok(NULL, ","));
   p[ln].z = atoi(strtok(NULL, "\n"));
   p[ln].group = 0;
  }

  // Считаем расстояния и выводим матрицу расстояний + список расстояний в парах
  FILE* g = fopen(DIST_PATH, "w");
  FILE* h = fopen(PAIRS_PATH, "w");
  for(int i = 0; i < Q; i++) {
    fprintf(g, "%d\t", i);
   for(int j = 0; j <= i; j++) {
    fprintf(g, "0\t");
   }
   for(int j = i + 1; j < Q; j++) {
    long long d = dist(p[i], p[j]);
    fprintf(g, "%lld\t", d);
    fprintf(h, "%d-%d-%lld\n", i, j, d);
   }
   fprintf(g, "\t\n");
  }
  fclose(h);
  fclose(g);

  // Сортировка средствами системы
  int sysres = system("sort -t- -k3,3n " PAIRS_PATH " > " PSORT_PATH);
  if(sysres != 0) { perror("Не удалось отсортировать пары."); }
  

  // Подготовка к разбиению на группы 
  int current = 1;     // прорабатываемая группа
  int gcount[Q] = {0}; // счётчик членов групп
  int incl[Q] = {0};   // вектор включённости
  int conn[Q] = {0};   // вектор итоговой достижимости
  int check[Q] = {0};  // вектор текущей проверки (поиска в ширину)
  int step[Q] = {0};   // вектор шага проверки (точно понадобится!)
  int zero[Q] = {0};   // нулевой вектор (для очистки)

  for(int i = 0; i < Q; i++) {
    zero[i] = 0;
  }

  // Постепенно расширяем матрицу связности
  g = fopen(PSORT_PATH, "r");
  int m[Q][Q] = {0};
  while((read = getline(&line, &len, g)) != -1) {
    int a = atoi(strtok(line, "-"));
    int b = atoi(strtok(NULL, "-"));
    m[a][b] = 1;
    m[a][b] = 1;

    // стартуем построение связей с точки a
    int point = a; incl[a] = 1;

    // инициируем проверку
    memcpy(conn, m[point], Q * sizeof(int));
    conn[point] = 1; check[point] = 1;

    // наращиваем группу, пока есть что проверять
    int moresteps = 1;
    while(moresteps == 1) {
      moresteps = 0;
      for(int i = 0; i < Q; i++) { step[i] = 0; }

      // собираем шаг проверки
      for(int i = 0; i < Q; i++) {
        if((conn[i] == 1) && (check[i] == 0)) {
          moresteps = 1;  // есть что проверять
          step[i] = 1;
        }
      }

      // добавляем связи шага
      for(int i = 0; i < Q; i++) {
        if(step[i] == 1) {
          conn[i] = 1;
          incl[i] = 1;
          for(int j = 0; j < Q; j++) {
            if(m[i][j] == 1) {
              conn[j] = 1;
              incl[j] = 1;
            }
          } 
          check[i] = 1;
        }
      }

    }

    // ищем первую всё ещё невключённую точку
    point = -1;
    for(int i = 0; i < Q; i++) {
      if(conn[i] == 0) { point = i; break; }
    }

    // если все точки включены — останавливаем рост матрицы
    if(point == -1) {
      printf("a[%d]: %ld\t%ld\t%ld\n", a, p[a].x, p[a].y, p[a].z);
      printf("b[%d]: %ld\t%ld\t%ld\n", b, p[b].x, p[b].y, p[b].z);
      printf("%lld\n", (long long)p[a].x * (long long)p[b].x);
      break;
    }

  }

  fclose(g);
  fclose(f);
  return 0;
}
