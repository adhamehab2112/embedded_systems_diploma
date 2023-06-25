#include <stdio.h>
#include <stdlib.h>

int main()
{
    char word[100];
    char letter ;
    int count = 0 ;
    printf("pleas enter the string : \n");
    gets(word);
    printf("enter the character to find frequency : ");
    scanf("%c",&letter);
    for(int i=0 ; i< strlen(word) ; i++ )
    {
        if(word[i] == letter)
            count++ ;
        if(word[i]== '\0')
            break;
    }
    printf("frequency of %c = %d ",letter,count);

    return 0;
}
