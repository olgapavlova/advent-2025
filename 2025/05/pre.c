#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define FILE_PATH "input.txt"

int main(void) {

  FILE * f = fopen(FILE_PATH, "r");

  char * line;
  size_t len;
  size_t read;

  bool interval = true;
  while((read = getline(&line, &len, f)) != -1) {
    size_t ll = strlen(line);
    printf("%d\n", ll);
    if(ll == 1) { interval = false; }
    switch (ll) {
      case 32: {
                
               }
      case 16:
      default: break;
    }
  }

  printf("%d\n", interval);

  fclose(f);
  return 0;
}
