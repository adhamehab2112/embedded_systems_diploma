#include <stdio.h>
#include <stdlib.h>

int main()
{
    int decimal=5 , binary[10], i = 0;
    printf("Enter a decimal: ");
    while (decimal > 0) {
        binary[i] = decimal%2;
        decimal /=2;
        i++;
    }
    printf("binary=: ");
    for (int k= 9; k >= 0; k --) {
        printf(" %d", binary[k]);
    }
    return 0 ;

}



