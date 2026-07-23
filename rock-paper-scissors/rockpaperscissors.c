#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROCK 1
#define PAPER 2
#define SCISSORS 3
#define QUIT 4
int get_player_choice(void) {
  char pchoice;
  char extra;

  while (1) {

    printf("Choose (R)ock, (P)aper, (S)cissors or (Q) to quit:");
    if (scanf("%c%c", &pchoice, &extra) == 2 && extra == '\n') {
      switch (pchoice) {
      case 'r':
      case 'R':
        return ROCK;

      case 'p':
      case 'P':
        return PAPER;

      case 's':
      case 'S':
        return SCISSORS;

      case 'q':
      case 'Q':
        return QUIT;
      }
    }
    printf("Not a valid option\n");
    while ((extra = getchar()) != '\n' && extra != EOF)
      ;
  }
}

int get_computer_choice(void) { return rand() % 3 + 1; }

void print_choice(int choice, const char *player) {
  printf("%s chose ", player);

  switch (choice) {
  case ROCK:
    printf("rock\n");
    break;
  case PAPER:
    printf("paper\n");
    break;
  case SCISSORS:
    printf("scissors\n");
    break;
  case QUIT:
    break;
  default:
    printf("invalid choice\n");
    break;
  }
}

void determine_winner(int pchoice, int cchoice, int *win, int *loss) {
  if (pchoice == cchoice) {
    printf("Stalemate\n");
  } else if ((pchoice == ROCK && cchoice == SCISSORS) ||
             (pchoice == PAPER && cchoice == ROCK) ||
             (pchoice == SCISSORS && cchoice == PAPER)) {
    printf("Player wins!\n");
    (*win)++;
  } else {
    printf("Player loses!\n");
    (*loss)++;
  }
  printf("Wins: %d - Losses %d\n", *win, *loss);
}

int main(void) {

  int pchoice;
  int cchoice;
  int win = 0;
  int loss = 0;

  srand(time(NULL));
  while (1) {

    pchoice = get_player_choice();
    cchoice = get_computer_choice();

    if (pchoice == QUIT) {
      break;
    }
    print_choice(pchoice, "Player");
    print_choice(cchoice, "Computer");

    determine_winner(pchoice, cchoice, &win, &loss);
  }
  return 0;
}
