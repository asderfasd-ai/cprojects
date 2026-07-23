#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int read_guess (void){
int guess = 0;
char extra;
    while (1){
        printf("Guess a number:");  
        if(scanf("%d%c", &guess, &extra) == 2 && extra == '\n'){   //checks for anything except a number and newline
            return guess;
        }
        printf("Enter one integer only\n");
        while ((extra = getchar()) != '\n' && extra != EOF)  // these 3 lines will not break if wrong input
            ;
     }
}

void check_guess(int guess, int secret){
    if (guess > secret){
        printf("Too high\n");
    }
    else if (guess < secret) {
        printf("Too low\n");
    }
}

int main(void){
srand(time(NULL));                  //Seed the generator
int secret = rand() % 100 + 1;      //random number between 1 and 100, will always be same number unless...
int count = 0;
int guess;

while (1){

    guess = read_guess();
    count++;                // only use count once, cleaner
    check_guess(guess,secret);

    if (guess == secret){
         printf("You got it after %d tries\n",count);
        break;
        }
    }
  
return 0;
}

