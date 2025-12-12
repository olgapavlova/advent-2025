#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "input.txt"
#define OUT_PATH "output.txt"


int main(void) {
  FILE* f = fopen(FILE_PATH, "r");
  FILE* g = fopen(OUT_PATH, "w");

  char * prev = calloc(142, sizeof(char));
  char * curr = calloc(142, sizeof(char));
  char * next = calloc(142, sizeof(char));

  char * line;
  size_t len;
  size_t read;

  read = getline(&prev, &len, f);

  int num = 0;
  while ((read = getline(&curr, &len, f)) != -1) {
    for(int i = 0; prev[i] != '\0'; i++) {
      if((i > 0) && (prev[i-1] == '|') && (curr[i-1] == '^')) { next[i] = '|'; }
      if((prev[i+1] == '|') && (curr[i+1] == '^')) { next[i] = '|'; }
    }
    for(int i = 0; curr[i] != '\0'; i++) {
      if((curr[i] == '.') && (prev[i] == '|')) { curr[i] = '|'; }
      if((curr[i] == '.') && (prev[i] == 'S')) { curr[i] = '|'; }
    }
    for(int i = 0; curr[i] != '\0'; i++) {
      if((next[i] == '|') && (curr[i] == '.')) { curr[i] = '|'; }
      next[i] = '\0';
    }
    fprintf(g, "%s", curr); 

    strcpy(prev, curr);
    strcpy(curr, next);
    num++;
  }

  fclose(g);

  g = fopen(OUT_PATH, "r");
  int sum = 0;
  read = getline(&prev, &len, g);
  while ((read = getline(&curr, &len, g)) != -1) {
    for(int i = 0; curr[i] != '\0'; i++) {
      if((curr[i] == '^') && (prev[i] == '|')) { sum++; }
    }
    strcpy(prev, curr);
  }

  printf("\n%d\n", sum);

  fclose(g);
  fclose(f);
  return 0;
}
