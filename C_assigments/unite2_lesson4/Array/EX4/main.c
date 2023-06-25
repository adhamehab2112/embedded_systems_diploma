#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arr[100];
    int size ;
    int index ;
    int element ;
    printf("please enter the size of array \n");
    scanf("%d",&size);
    if(size>100 || size <0)
        printf("error in size \n");
    else
    {
        for(int i=0 ; i<size ; i++)
        {
            printf("please enter the element : ");
            scanf("%d",&element);
            printf("please enter the location : ");
            scanf("%d",&index);
            arr[index] = element ;

        }

    }
    return 0;
}
