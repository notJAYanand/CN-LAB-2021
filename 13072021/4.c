#include <stdio.h>
#include<stdlib.h>

#define N 3
#define MAX 100

typedef struct{
    char name[MAX];
    int id;
    int phone;
}student;

void main() {
    student *s= (student *)malloc(N*sizeof(student));    
    for(int i=0;i<N;i++){
        printf("Enter id,name,phone number \n");
        scanf("%d",&s[i].id);
        scanf("%s",s[i].name);
        scanf("%d",&s[i].phone);
    }

    for(int i=0;i<N;i++){
        printf("Name: %s\nID: %d\nPhone: %d\n",s[i].name,s[i].id,s[i].phone);
    }

}