#include <stdio.h>
#include <stdlib.h>

int main()
{
    char word[100];
    int length = 0 ;
    printf("please enter the string : \n");
    gets(word);
    for(int i=0 ; i<100 ; i++)
    {
        if(word[i]== '\0')
            break;
        else
            length++;
    }
    printf("the length of string = %d",length);
    return 0;
}
