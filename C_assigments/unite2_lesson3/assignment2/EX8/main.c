#include <stdio.h>
#include <stdlib.h>

int main()
{
   int op1 , op2 ,result ;
   char operation ;
   printf("please select the operation : +,-,*,\\ \n");
   scanf("%c",&operation);
   printf("enter operand 1 : ");
   scanf("%d",&op1);
   printf("enter operand 2 : ");
   scanf("%d",&op2);
   switch(operation)
   {
   case '+' :
    result = op1+op2 ;
    printf("%d %c %d = %d",op1,operation,op2,result);
    break ;
   case '-' :
    result = op1-op2 ;
    printf("%d %c %d = %d",op1,operation,op2,result);
    break;
   case '*' :
    result = op1 * op2 ;
    printf("%d %c %d = %d",op1,operation,op2,result);
    break;
    case '\\' :
    result = op1 / op2 ;
    printf("%d %c %d = %d",op1,operation,op2,result);
    break;
    default:
        printf("wrong input \n");


   }


    return 0;
}
