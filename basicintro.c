
#include <stdio.h>
#include <stdbool.h>

int main (void){

int num = 1;
char asd[] = "asdasd";
long bignum = 12345678910111213;
float dec = 123.45f;
double money = 12.22;
bool truefalse = true;

printf("hello %d %s\n",num,asd);
printf("long %ld\n",bignum);
printf("float %.2f\n",dec);
printf("double %.4f\n",money);
printf("int size: %zu %zu\n",sizeof(int),sizeof(num));
printf("char size: %zu string size: %zu\n",sizeof(char),sizeof(asd));
printf("long size: %zu\n",sizeof(long));
printf("float size: %zu\n",sizeof(float));
printf("double size: %zu\n",sizeof(double));
printf("%d\n",truefalse);

return 0;
}
