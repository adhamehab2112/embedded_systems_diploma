#include <stdio.h>
#include <stdlib.h>

int main()
{   int x , r=0;
    printf("please enter an integer : ");
    scanf("%d",&x);
    for(int i=0 ; i<=x ; i++)
        r+=i ;
    printf("sum = %d",r);
    return 0;
}
