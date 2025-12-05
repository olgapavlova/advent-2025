#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "input.txt"
#define OUT_PATH "output.txt"

typedef struct pair_s {
  char from[20];
  char to[20];
} pair_t;

static pair_t diap[200];

int compare(char* a, char* b) {
  int result = 0;
  int len_a = strlen(a);
  int len_b = strlen(b);
  if (b[len_b - 1] == '\n') {
    b[len_b - 1] = '\0';
    len_b--;
  }
  if (len_a < len_b) {
    result = -1;
  } else if (len_a > len_b) {
    result = 1;
  } else {
    for (int i = 0; i < len_a; i++) {
      if (a[i] < b[i]) {
        result = -1;
        break;
      }
      if (a[i] > b[i]) {
        result = 1;
        break;
      }
    }
  }

  return result;
}

void split(char* a, pair_t* p) {
  char* w = p->from;
  int j = 0;
  for (int i = 0; a[i] != '\0'; i++) {
    if (a[i] == '-') {
      w[j] = '\0';
      w = p->to;
      j = 0;
    } else {
      w[j] = a[i];
      j++;
    }
    w[j] = '\0';
  }
}

int main(void) {
  FILE* f = fopen(FILE_PATH, "r");
  FILE* g = fopen(OUT_PATH, "w");

  char* line;
  size_t len;
  size_t read;
  int pq = 0;  // количество диапазонов

  bool interval = true;
  while ((read = getline(&line, &len, f)) != -1) {
    size_t ll = strlen(line);
    line[ll - 1] = '\0'; ll--;
    if (ll == 0) {
      interval = false;
    } else if (interval) {
        split(line, &diap[pq++]);
      } else {
        for (int j = 0; j < pq; j++) {
          if ((compare(line, diap[j].from) != -1) &&
              (compare(line, diap[j].to) != 1)) {
            // fprintf(g, "%s-%s\t%s\n", diap[j].from, diap[j].to, line);
            fprintf(g, "%s\n", line);
          } else { printf("NO\n"); }
        }
      }
  }

  printf("%d\n", pq);

fclose(f);
return 0;
}
