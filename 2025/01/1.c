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
  int position = 50;
  int shift;
  char sign;

  while((read = getline(&line, &len, f)) != -1) {
    sscanf(line, "%c%d", &sign, &shift);

    position += (sign == 'L' ? 1 : -1) * shift;

    position = (position + 100) % 100;

    printf("%c%d\t%d\t%c\t%s", (sign == 'L' ? '+' : '-'), shift, position, (position == 0 ? '!' : ' '), line);
   }


  fclose(f);
  return 0;
}
