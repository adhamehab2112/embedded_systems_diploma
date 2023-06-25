#include <stdio.h>
#include <stdlib.h>

int main()
{
    float arr[100];
    int size ;
    float sum =0 ;
    float avg ;
    printf("please enter the size of array\n");
    scanf("%d",&size);
    if(size>100 || size<0)
        printf("error : range must be from (0:100) \n");
    else
    {
        for(int i=0 ; i<size ; i++)
        {
            printf("%d.",i+1);
            scanf("%f",&arr[i]);
        }
        for(int i=0 ; i<size ; i++)
        {
            sum += arr[i];
        }
        avg = sum/size ;
        printf("avg = %.2f",avg);

    }


    return 0;
}
