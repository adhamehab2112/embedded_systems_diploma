#include <stdio.h>
#include <stdlib.h>

int main()
{
    char word[100];
    printf("please enter the string : \n");
    gets(word);
    printf("reverse string is : ");
    int length = strlen(word) ;
    for(int i = length  ; i>=0 ; i--)
    {
        printf("%c",word[i]);
    }
    return 0;
}
