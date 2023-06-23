#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num , fact = 1 ;
    printf("please enter an integer : ");
    scanf("%d",&num);
    if(num<0)
    {
      printf("error!! please enter a positive number \n");
       return 0;

    }

    else if(num==0)
    {
       printf("factorial = 1 \n");
        return 0;

    }

    else
    {
        for(int i=1 ; i<=num ; i++)
            fact *= i ;

    }
    printf("factorial = %d",fact);
    return 0;
}
