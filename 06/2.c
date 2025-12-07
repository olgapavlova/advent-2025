#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "diapsort.txt"
#define OUT_PATH "diapfilter.txt"

typedef struct pair_s {
  char from[20];
  char to[20];
} pair_t;

static pair_t diap[200];
static pair_t dsafe[200];

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

int between(char * n, char * from, char * to) {
  int result = 0;
  result = (compare(n, from) != -1) && (compare(n, to) != 1);
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
  while ((read = getline(&line, &len, f)) != -1) {
    size_t ll = strlen(line);
    line[ll - 1] = '\0';
    ll--;
    split(line, &diap[pq++]);
  }


  for(int i = 0; i < pq; i++) {
      strcpy(dsafe[i].from, diap[i].from);
      strcpy(dsafe[i].to, diap[i].to);
  }

  for(int i = 0; i < pq; i++) {
    for(int j = i + 1; j < pq; j++) {
      if(compare(diap[j].to, diap[i].to) != 1) {
        strcpy(diap[j].from, "0");
        strcpy(diap[j].to, "0");
      } else {
        if (compare(diap[j].from, diap[i].to) == -1) {
          strcpy(diap[i].to, diap[j].to);
          strcpy(diap[j].from, "0");
          strcpy(diap[j].to, "0");
        } else if (compare(diap[j].from, diap[i].to) == 0) {
          strcpy(diap[i].to, diap[j].to);
          strcpy(diap[j].from, "0");
          strcpy(diap[j].to, "0");
        }
      }
    }
  }

  for(int i = 0; i < pq; i++) {
    printf("[%d]\t%s-%s\t%s-%s\n", i, diap[i].from, diap[i].to, dsafe[i].from, dsafe[i].to);
  }

  long long zoom = 0;
  for(int i = 0; i < pq; i++) {

    long long fr = 0;
    long long to = 0;
    long long dist = 0;

    sscanf(diap[i].from, "%lld", &fr);
    sscanf(diap[i].to, "%lld", &to);

    dist = to - fr + 1;
    if(fr != 0) {
      fprintf(g, "%lld\n", dist);
      zoom += dist;
      printf("[%d]\t%lld - %lld + 1 = %lld → %lld\n", i, to, fr, dist, zoom);
    }

  }


  fclose(g);
  fclose(f);
  return 0;
}
