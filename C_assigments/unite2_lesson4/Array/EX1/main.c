#include <stdio.h>
#include <stdlib.h>

int main()
{
    int mat1[2][2];
    int mat2[2][2];
    int sum[2][2];
    printf("please enter the elements of 1st matrix\n");
    for(int i=0 ; i<2 ; i++)
        for(int j=0 ; j<2 ; j++)
        {
            printf("enter a%d %d : ",i,j);
            scanf("%d",&mat1[i][j]);
        }
    printf("please enter the elements of 2nd matrix\n");
    for(int i=0 ; i<2 ; i++)
        for(int j=0 ; j<2 ; j++)
        {
            printf("enter b%d %d : ",i,j);
            scanf("%d",&mat2[i][j]);
        }


    for(int i=0 ; i<2 ; i++)
        for(int j=0 ; j<2 ; j++)
            sum[i][j] = mat1[i][j]+mat2[i][j];
    printf("sum : \n");
    for(int i=0 ; i<2 ;i++)
            for(int j=0 ; j<2 ; j++)
            {
                printf("%d \t",sum[i][j]);
                if(j==1)

                   printf("\n");


            }


    return 0;
}
