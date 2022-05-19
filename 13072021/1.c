// Accept two numbers and an operator (from +, -, *, /) and display the ansult after the operation.

#include <stdio.h>

int main()

{

  int a,b;
  char ch;
  printf ("\nEnter two numbers \n");
  scanf("%d%d",&a,&b);
  
  while(1)
  {
    printf ("Enter any one operator +, -, *, / \n");
    scanf("%c",&ch);
    switch(ch)
    {
      case'+': printf("\nThe sum is %d\n",a+b);
      break;

      case'-': printf("\nThe difference is %d\n",a-b);
      break;

      case'*': printf("\nThe product is %d\n",a*b);
      break;

      case'/': printf("\nThe quotient is %0.1f\n",(float)a/b);
      break;

      default: printf ("\nInvalid entry\n");
      continue;
    }
    break;
  }

  return 0;
}