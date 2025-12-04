#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "input.txt"
#define W 138

int main(void) {

  FILE * f = fopen(FILE_PATH, "r");

  int m[W + 2][W + 2] = {0};

  char * line;
  size_t len;
  size_t read;

  int i = 1;
  while((read = getline(&line, &len, f)) != -1) {
    for(int j = 0; j < W; j++) {
      m[i][j + 1] = (line[j] == '@') ? 1 : 0;
      printf("%d", m[i][j + 1]);
    }
    printf("\n");
    i++;
  }

  int sum = 0;
  for(int i = 1; i < W + 1; i++) {
    for(int j = 1; j < W + 1; j++) {

      int s = m[i-1][j] + m[i-1][j-1] + m[i-1][j+1]
        + m[i][j-1] + m[i][j+1]
        + m[i+1][j] + m[i+1][j-1] + m[i+1][j+1];

      printf("%4d", s);

      if ((s < 4) && (m[i])[j] == 1) { sum++; }
    }
    printf("\n");
  }

  printf("%d\n", sum);

  fclose(f);
  return 0;
}
