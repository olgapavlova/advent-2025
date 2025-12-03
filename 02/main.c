#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_PATH "input.txt"

typedef struct pair_s {
  char from[120];
  char to[120];
} pair_t;

int compare(char * a, char * b) {
  int result = 0;
  int len_a = strlen(a);
  int len_b = strlen(b);
  if(b[len_b - 1] == '\n') { b[len_b - 1] = '\0'; len_b--; }
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

void split(char * a, pair_t * p) {
  char * w = p->from;
  int j = 0;
  for(int i = 0; a[i] != '\0'; i++) {
    if (a[i] == '-') {w[j] = '\0'; w = p->to; j = 0; }
    else { w[j] = a[i]; j++; }
    w[j] = '\0';
  }
}


unsigned long long check(char * c, pair_t * d, int pq) {
    unsigned long long result = 0;
    for(int j = 0; j <= pq; j++) {
      if((compare(c, d[j].from) != -1) && (compare(c, d[j].to) != 1)) {
        sscanf(c, "%lld", &result);
        printf("%lld\n", result);  
        break;
      }
    }
  return result;
}

void save(char * c, pair_t * d, int pq) {
  static FILE * to = NULL;
  if (to == NULL) { to = fopen("out.txt", "w"); }
  unsigned long long is = check(c, d, pq);
  if (is != 0) { fprintf(to, "%lld\n", is);}
}

int main(void) {

  FILE * f = fopen(FILE_PATH, "r");
  if(!f) { abort(); }

  char * line;
  size_t len;
  getline(&line, &len, f);
  // printf("%d\t%s\n", (int)len, line);


  char * str;
  char delim[3] = ",";
  pair_t diap[50];
  int i = 0;
  str = strtok(line, delim);
  split(str, &diap[0]);
  // printf("%s\t%s\n", diap[i].from, diap[i].to);


  int max = 1;

  while(str = strtok(NULL, delim)) {
    i++;
    split(str, &diap[i]);
    // printf("%s\t%s\n", diap[i].from, diap[i].to);
    if(strlen(diap[i].to) > max) {
      max = strlen(diap[i].to);
    }
  }

  int pq = i;
  // printf("\n%d\n", pq);

  // printf("\n%d\n", max);

  char * strmax = malloc(sizeof(char) * 20);
  strmax[0] = '1';
  for(int i = 1; i < max/2 + 1; i++) { strmax[i] = '0'; }
  strmax[max/2 + 1] = '\0';
  // printf("\n%s\n", strmax);

  long realmax = 0;
  sscanf(strmax, "%ld", &realmax);
  // printf("\n%ld\n", realmax);


  for(long i = 1; i < realmax; i++) {
    char current[240] = {'\0'}; 
    sprintf(current, "%ld%ld", i, i);
    save(current, diap, pq);
    sprintf(current, "%ld%ld%ld", i, i, i);
    save(current, diap, pq);
    sprintf(current, "%ld%ld%ld%ld%ld", i, i, i, i, i);
    save(current, diap, pq);
    sprintf(current, "%ld%ld%ld%ld%ld%ld%ld", i, i, i, i, i, i, i);
    save(current, diap, pq);
  }

  unsigned long long zoom = 0;

  printf("\n%lld\n", zoom);

  free(strmax);
  fclose(f);
  return 0;
}
