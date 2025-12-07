#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "input.txt"
#define OUT_PATH "output.txt"

static int d[4][1000] = {0};
static char op[1000] = {'\0'};

long long operate(int col) {
  long long result;
  if (op[col] == '+') {
    result = (long long)d[0][col] + (long long)d[1][col] + (long long)d[2][col] + (long long)d[3][col];
  } else if (op[col] == '*'){
    result = (long long)d[0][col] * (long long)d[1][col] * (long long)d[2][col] * (long long)d[3][col];
  }
  return result;
}


int main(void) {
  FILE* f = fopen(FILE_PATH, "r");
  FILE* g = fopen(OUT_PATH, "w");

  char* line;
  size_t len;
  size_t read;

  int num = 0;
  int cols = 0;
  while ((read = getline(&line, &len, f)) != -1) {
    size_t ll = strlen(line);
    line[ll - 1] = '\0';
    ll--;

    int col = 0;
    char* a = strtok(line, " ");
    if (num == 4) {
      op[col] = a[0];
    } else {
      d[num][col] = atoi(a);
    }
    col++;
    while (a = strtok(NULL, " ")) {
      if (num == 4) {
        op[col] = a[0];
      } else if (num < 4) {
        d[num][col] = atoi(a);
      }
      col++;
    }
    cols = (cols < col) ? col : cols;
    num++;
  }

  printf("%d\t%d\n", num, cols);
  for(int col = 0; col < cols; col++) {
    printf("[%d]\t%d %c %d %c %d %c %d\n", col, d[0][col], op[col], d[1][col], op[col], d[2][col], op[col], d[3][col]);
    fprintf(g, "%lld\n", operate(col));
  }
  fclose(g);
  fclose(f);
  return 0;
}
