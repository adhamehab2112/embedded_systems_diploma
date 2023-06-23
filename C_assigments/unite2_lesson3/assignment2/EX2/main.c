#include <stdio.h>
#include <stdlib.h>

int main()
{   char letter ;
    printf("please enter the letter : ");
    scanf("%c",&letter);
    switch(letter) {
case 'A' :
    printf("%c is vowel \n",letter);
    break ;
    case 'a' :
    printf("%c is vowel \n",letter);
    break ;
    case 'i' :
    printf("%c is vowel \n",letter);
    break ;
    case 'I' :
    printf("%c is vowel \n",letter);
    break ;
    case 'e' :
    printf("%c is vowel \n",letter);
    break ;
    case 'E' :
    printf("%c is vowel \n",letter);
    break ;
    case 'o' :
    printf("%c is vowel \n",letter);
    break ;
    case 'O' :
    printf("%c is vowel \n",letter);
    break ;
    default :
        printf("%c is consonant \n",letter);
    }
    return 0;
}
