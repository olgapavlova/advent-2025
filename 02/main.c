#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "input.txt"

int compare(char * a, char * b) {
  int result = 0;
  int len_a = strlen(a);
  int len_b = strlen(b);
  if(len_a < len_b) { result = -1; }
  else if(len_a > len_b) { result = 1; }
  else {
    for(int i = 0; i < len_a; i++) {
      if (a[i] < b[i]) { result = -1; break; }
      if (a[i] > b[i]) { result = 1; break; }
    }
  }

  return result;
}

int main(void) {

  printf("%d\n", compare("1", "12"));
  printf("%d\n", compare("12", "12"));
  printf("%d\n", compare("1212", "1210"));
  printf("%d\n", compare("1212", "121"));

#if 0
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
#endif
  return 0;
}
