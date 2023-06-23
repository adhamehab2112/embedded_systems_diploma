#include <stdio.h>
#include <stdlib.h>

int main()
{   int num ;
    printf("please enter the number : ");
    scanf("%d",&num);
    if(num%2 == 0)
        printf("the number %d is even \n",num);
    else
        printf("the number %d is odd \n",num);
    return 0;
}
