#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "input.txt"
#define OUT_PATH "output.txt"

int main(void) {
  FILE* f = fopen(FILE_PATH, "r");
  FILE* g = fopen(OUT_PATH, "w");

  char* line;
  size_t len;
  size_t read;
  int pq = 0;  // количество диапазонов

  int d[3][1000] = {0};

  while ((read = getline(&line, &len, f)) != -1) {
    size_t ll = strlen(line);
    line[ll - 1] = '\0'; ll--;
    
    char a[10] = {'\0'};
    strtok(line, "\t", a);
    printf("%s\n", a);

  }

fclose(f);
return 0;
}
