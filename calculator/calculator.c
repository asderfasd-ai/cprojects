#include <stdio.h>

int main(void){

char operator;
double num1, num2, result;
char extra;

printf("Enter first number:");
if(scanf("%lf%c", &num1, &extra) != 2 || extra != '\n')
{
    printf("Invalid number\n");
   return 1;
}

printf("Enter operator:");
scanf(" %c", &operator);
printf("Enter second number:");
if(scanf("%lf%c", &num2, &extra) != 2 || extra != '\n')
{
   printf("Invalid number\n");
   return 1;
}

switch (operator) {
    case '*': 
        result = num1 * num2;
        break; 
    case '-': 
        result = num1 - num2;
        break; 
    case '+': 
        result = num1 + num2;
        break; 
    case '/': 
        if (num2 == 0){
            printf("Cannot divide by 0\n");
            return 1;
        }
        result = num1 / num2;
        break;
    default:
        printf("Invalid operator\n");
        break;
    }
printf("%.2lf %c %.2lf = %.2lf\n", num1, operator, num2, result);


/*
if (operator == '*') {
    result = num1 * num2;
    printf("%lf * %lf = %lf\n", num1, num2, result);

    }
if (operator == '/') {
    result = num1 / num2;
    printf("%lf / %lf = %lf\n", num1, num2, result);

    }
if (operator == '+') {
    result = num1 + num2;
    printf("%lf + %lf = %lf\n", num1, num2, result);

    }
if (operator == '-') {
    result = num1 - num2;
    printf("%lf - %lf = %lf\n", num1, num2, result);

    }
*/
return 0;
}
