#include <stdio.h>

int main(){

char name[50];
int age;
double height;

printf("What is your name?\n");
scanf("%50s",name);
printf("What is your age?\n");
scanf("%d",&age);
printf("What is your height in feet?\n");
scanf("%lf",&height);

printf("Hello %s!\n",name);
printf("You are %d years old.\n",age);
printf("You are %.2f feet tall.\n",height);

return 0;

}
