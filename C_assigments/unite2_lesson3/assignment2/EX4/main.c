#include <stdio.h>
#include <stdlib.h>

int main()
{
    float x ;
    printf("please enter the number : ");
    scanf("%f",&x);
    if(x==0)
        printf("you entered zero \n");
    else if(x>0)
        printf("number is positive \n");
    else
        printf("number is negative \n");
    return 0 ;
}
