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

  // Сортировка средствами системы + оставляем первую 1000 связей
  int sysres = system("sort -t- -k3,3n " PAIRS_PATH " | head -n " TOP " > " PSORT_PATH);
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

  // Матрица связности
  g = fopen(PSORT_PATH, "r");
  int m[Q][Q] = {0};
  while((read = getline(&line, &len, g)) != -1) {
    int i = atoi(strtok(line, "-"));
    int j = atoi(strtok(NULL, "-"));
    m[i][j] = 1;
    m[j][i] = 1;
  }

  
  for(int gr = 0; gr < Q; gr++) { // для каждой группы…
    // берём первую невключённую точку
    int point = -1;
    gcount[point] = 0;
    for(int i = 0; i < Q; i++) {
      if(incl[i] == 0) { point = i; break; }
    }

    // если все точки включены — останавливаем перебор групп
    if(point == -1) break;

    // фиксируем первую точку как включённую
    incl[point] = 1;

    // проверка всей группы

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

    // выводим цепочку
    int sum = 0;
    //printf("%d-", gr);
    for(int i = 0; i < Q; i++) {
      if(conn[i] == 1) {
        // printf("%d ", i);
        sum++;
        // gcount[gr]++;
      }
    }
    gcount[gr] = sum;
    printf("%d\n", sum);

  }

  fclose(f);
  return 0;
}
