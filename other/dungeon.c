#include <stdio.h>

int printIntro(void) {
  int choice;
  printf("===========================\n");
  printf("     Dungeon Adventure     \n");
  printf("===========================\n\n\n\n");
  printf("1.  Explore\n");
  printf("2.  Quit\n\n");
  printf("Choice?");
  scanf("%d", &choice);
  return choice;
}

int main() {
  int choice = printIntro();
  printf("%d", choice);

  return 0;
}
