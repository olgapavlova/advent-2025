#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "input.txt"

char * digit(char * line, char * start, int position) {
  char * result = start;
  char * p = start;
  while(*(p + position) != '\0') {
    if(*p > *result) { result = p; }
    p++;
  }
  return result;
}

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
  unsigned long long jo = 0;
  char sj[13] = {'\0'};

  while((read = getline(&line, &len, f)) != -1) {
    size_t l = strlen(line);
    if(line[l - 1] == '\n') {
      line[l - 1] = '\0'; l--;
    }

    char * prev;
    char * next;
    char * a = digit(line, line, 11);
    sj[0] = *a;
    prev = a;
    for(int i = 10; i >= 0; i--) {
      char * next = digit(line, prev + 1, i);
      sj[11 - i] = *next;
      prev = next;
    }

    sscanf(sj, "%lld", &jo);
    sum += jo;

    printf("%lld\t%s\n", jo, line);
  }

  printf("%lld\n", sum);

  fclose(f);
  return 0;
}
