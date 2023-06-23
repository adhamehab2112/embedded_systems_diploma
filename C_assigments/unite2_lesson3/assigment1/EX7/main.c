#include <stdio.h>
#include <stdlib.h>

int main()
{
    float num1 , num2 ;
    printf("please enter the 2 float values \n");
    printf("the value of a : ");
    scanf("%f",&num1);
    printf("the value of b : ");
    scanf("%f",&num2);
    num1 = num1+num2 ;
    num2 = num1 - num2 ;
    num1 = num1 - num2 ;
    printf("after swap , value of a = %.2f \n",num1);
    printf("after swap , value of b = %.1f \n",num2);
    return 0;
}
