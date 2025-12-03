#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "input.txt"

int main(void) {

  FILE * f = fopen(FILE_PATH, "r");

  char * line;
  size_t len;
  size_t read;

  int code = 0;
  int position = 50;
  int shift;
  char sign;


  unsigned long long sum = 0;
  char sj[3] = {'\0'};
  int jo = 0;

  while((read = getline(&line, &len, f)) != -1) {
    size_t l = strlen(line);
    if(line[l - 1] == '\n') {
      line[l - 1] = '\0'; l--;
    }

    char * p = line;
    char * q = line;
    while(*(q+1) != '\0') {
      if(*p < *q) { p = q; }
      q++;
    }

    char * r = p + 1;
    q = r;
    while(*q != '\0') {
      if (*r < *q) { r = q; }
      q++;
    }

    sprintf(sj, "%c%c", *p, *r);
    sscanf(sj, "%d", &jo);
    sum += jo;

    printf("%c%c\t%s\n", *p, *r, line);
  }

  printf("%lld\n", sum);

  fclose(f);
  return 0;
}
