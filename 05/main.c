#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "input.txt"
#define W 138

static int m[W+2][W+2] = {0};
static int a[W+2][W+2] = {0};


void printm(void) {
  for(int i = 1; i < W + 1; i++) {
    for(int j = 1; j < W + 1; j++) {
      printf("%2d", m[i][j]);
    }
    printf("\n");
  }
}

int count() {
  int result = 0;
  for(int i = 1; i < W + 1; i++) {
    for(int j = 1; j < W + 1; j++) {
      int s = m[i-1][j] + m[i-1][j-1] + m[i-1][j+1]
        + m[i][j-1] + m[i][j+1]
        + m[i+1][j] + m[i+1][j-1] + m[i+1][j+1];

      if ((s < 4) && (m[i][j] == 1)) {
        result++;
        a[i][j] = -1;
      }
    }
  }
  return result;
}

void copy(void) {
  for(int i = 1; i < W + 1; i++) {
    for(int j = 1; j < W + 1; j++) {
      if (a[i][j] == -1) { m[i][j] = 0; }
      a[i][j] = 0;
    }
  }
}

int main(void) {

  FILE * f = fopen(FILE_PATH, "r");

  char * line;
  size_t len;
  size_t read;

  int i = 1;
  while((read = getline(&line, &len, f)) != -1) {
    for(int j = 1; j < W + 1; j++) {
      m[i][j] = (line[j - 1] == '@') ? 1 : 0;
    }
    i++;
  }

  int zoom = 0;
  int sum = -1;
  while(sum != 0) {
    copy();
    sum = count(m);
    printm();
    printf("%d\n", sum);
    zoom += sum;
  }

  printf("%d\n", zoom);

  fclose(f);
  return 0;
}
