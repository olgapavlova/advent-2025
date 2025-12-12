#include <stdio.h>
#include <stdlib.h>
#define FILE_PATH "input.txt"

int main(void) {

  FILE * f = fopen(FILE_PATH, "r");
  if(!f) { abort(); }

  char * line;
  size_t len;
  size_t read;

  int code = 0;
  int code_prev = 0;
  int prev = 50;  
  int next;
  int shift;
  char sign;

  while((read = getline(&line, &len, f)) != -1) {
    sscanf(line, "%c%d", &sign, &shift);

    next = prev + (sign == 'L' ? -1 : 1) * shift;

    // p > 0;  n >= 100
    // p > 0;  n <= 0
    // p == 0; n <= -100

    if (next >= 100) {
      code += next / 100;
    }
    if ((next <= 0) && (prev != 0)) {
      code += (-1) * next / 100 + 1;
    }
    if ((next <= 100) && (prev == 0)) {
      code += (-1) * next / 100;
    }
      printf("%2d\t%c%3d\t%4d\t\e[%dm%5d\e[0m\t%s",
          prev,
          (sign == 'L' ? '-' : '+'),
          shift,
          next,
          (code != code_prev ? 32 : 0),
          code,
          line);
    next = (next + 10000) % 100;
    prev = next;
    code_prev = code;
   }

  fclose(f);
  return 0;
}
