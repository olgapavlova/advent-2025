#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "input.txt"
#define OUT_PATH "output.txt"
#define LINE 3785

static char * l[5];
static char op[1000] = {'\0'};


int digit(char a) {
  if((a < 59 ) && (a >= 48)) {
    return a - 48;
  } else { return 0; }
}


int getnum(int col) {
  int result = 0;
  char preres[4] = {'\0'};
  for(int i = 0; i < 4; i++) {
    preres[i] = l[i][col];
  }
  sscanf(preres, "%d", &result);
  return result;
}


int main(void) {
  FILE* f = fopen(FILE_PATH, "r");
  FILE* g = fopen(OUT_PATH, "w");

  for(int i = 0; i < 5; i++) {
    l[i] = calloc(LINE + 1, sizeof(char));
  }


  char * line;
  size_t len;
  size_t read;

  printf("%s\n", l[1]);

  int num = 0;
  while ((read = getline(&line, &len, f)) != -1) {
    size_t ll = strlen(line);
    line[ll - 1] = ' ';
    strcpy(l[num], line);
    num++;
  }

  printf("%d\n", num);

  int col = 1;
  while(l[4][col] != '\0') {
    if(l[4][col] != ' ') {
      long long sum = 0;
      long long mult = 1;
      int p = col - 2;
      do {
        int current = getnum(p);
        sum += current;
        mult *= current;
        p--;
      } while(l[4][p + 1] == ' ');
      if(l[4][p + 1] == '+') {
        fprintf(g, "%lld\n", sum);
      } else {
        fprintf(g, "%lld\n", mult);
      }
    }
    col++;
  }

      int p = col - 2;
      long long sum = 0;
      long long mult = 1;
      do {
        int current = getnum(p);
        sum += current;
        mult *= current;
        p--;
      } while(l[4][p + 1] == ' ');
      if(l[4][p + 1] == '+') {
        fprintf(g, "%lld\n", sum);
      } else {
        fprintf(g, "%lld\n", mult);
      }

  fclose(g);
  fclose(f);
  return 0;
}
