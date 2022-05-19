//2. Use recursion to find the factorial of a number. 

#include <stdio.h>

int factorial(int n){
   if(n==0){
       return 1;
   }
   
    return n*factorial(n-1);

}

int main(){
    int n;
    scanf("%d",&n);
    printf("factorial of %d is %d",n,factorial(n));


}