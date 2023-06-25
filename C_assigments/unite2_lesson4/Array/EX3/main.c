#include <stdio.h>
#include <stdlib.h>

int main()
{
    int matrix[100][100] ;
    int transpose[100][100];
    int rows ;
    int col ;
    printf("please enter the size of matrix\n");
    printf("rows :");
    scanf("%d",&rows);
    printf("coloumns :");
    scanf("%d",&col);
    if((rows<0 || rows>100) || (col<0 || col>100 ))
        printf("error in size \n");
    else
    {
        printf("enter the elements of matrix : \n");
        for(int i=0 ; i<rows ; i++)
            for(int j=0 ; j<col ; j++)
        {
            printf("a%d%d : ",(i+1),j+1);
            scanf("%d",&matrix[i][j]);
        }
        printf("the entered matrix : \n");
        for(int i=0 ; i<rows ; i++)
            for(int j=0 ; j<col ; j++)
            {
                printf("%d \t",matrix[i][j]);
                if(j==(col-1))
                    printf("\n");
            }
        for(int i=0 ; i<rows ; i++)
            for(int j=0 ; j<col ; j++)
            {
                transpose[j][i] = matrix[i][j];
            }
        printf("the transpose matrix : \n");
        for(int i=0 ; i<col ; i++)
            for(int j=0 ; j<rows ; j++)
            {
                printf("%d \t",transpose[i][j]);
                if(j==(rows-1))
                    printf("\n");
            }

    }
    return 0;
}
