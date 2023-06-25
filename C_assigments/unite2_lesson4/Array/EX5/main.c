#include <stdio.h>
#include <stdlib.h>

int main()
{
  int arr[100];
    int size ;
    int element ;
    printf("please enter the size of array \n");
    scanf("%d",&size);
    if(size>100 || size <0)
        printf("error in size \n");
    else
    {
        for(int i=0 ; i<size ; i++)
        {
            printf("please enter the element a%d : ",i+1);
            scanf("%d",&arr[i]);


        }
        printf("enter the element to be searched : ");
        scanf("%d",&element);
        for(int i=0 ; i<size ; i++)
        {
            if(arr[i]==element)
            {
                printf("number found at location : %d \n",i+1);
                return 0;
            }


        }

    printf("number not found");
    return 0;
    }
    return 0;
}
