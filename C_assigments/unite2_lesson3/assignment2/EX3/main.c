#include <stdio.h>
#include <stdlib.h>

int main()
{   float x,y,z ;
    printf("please enter the 3 numbers : \n");
    scanf("%f",&x);
    scanf("%f",&y);
    scanf("%f",&z);
    float max = 0.0 ;
    if(x>max)
        max=x ;
    if(y>max)
        max=y;
    if(z>max)
        max=z;
    printf("largest number = %.2f",max);
    return 0;
}
