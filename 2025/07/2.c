#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "output.txt"
#define LINE 150

int main(void) {

  long prev[LINE];
  long curr[LINE];

  int num = 0;

  for (int i = 0; i < LINE; ++i) {
    prev[i] = 0;
    curr[i] = prev[i];
  }

  FILE* f = fopen(FILE_PATH, "r");
  if (f == NULL) {
    perror("!");
  }

  char* line;
  size_t len;
  size_t read;

  read = getline(&line, &len, f);
  printf("[%d]\t", num);
  for (int i = 0; line[i] != '\0'; i++) {
    prev[i] = (line[i] == '|') ? 1 : 0;
    curr[i] = 0;
    printf("%2ld ", prev[i]);
  }

  printf("\n---\n");


  while ((read = getline(&line, &len, f)) != -1) {
    num++;
    size_t ll = strlen(line);
    if(ll < 2) break;
    line[ll - 1] = '\0'; ll--;
    printf("[%d:%ld]\t%s", num, ll, line);
    for(int i = 0; i < ll; i++) {
      if(line[i] == '^') {
        curr[i] = -1;
        if(i > 0) curr[i - 1] += prev[i];
        curr[i + 1] += prev[i];
      } else if(line[i] == '.') {
        curr[i] = 0;
      } else if(prev[i] >= 0) {
        curr[i] += prev[i];
      }
    }
    for(int i = 0; i < ll; i++) {
      prev[i] = curr[i];
      curr[i] = 0;
      printf("%2ld ", prev[i]);
    }
    printf("\n");
    strcpy(line, "");
  }

  // long long zoom = 0;
  for(int j = 1; j < LINE; j++) {
    prev[0] += prev[j];
  }
  printf("\n%ld\n", prev[0]);

  fclose(f);
  return 0;
}
