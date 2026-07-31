#include <stdio.h>
#include <string.h>

int main() {
  char string[10];
  printf("type a name: ");
  fgets(string, sizeof(string), stdin);
  char *verb = strtok(string, " ");
  char *arg = strtok(NULL, "\n");
  printf("you typed %s %s\n", verb, arg);
  return 0;
}
