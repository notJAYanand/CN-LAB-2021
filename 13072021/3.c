//3. Accept a sentence and print the average number of letters in each word.


#include<stdio.h> 
#include<string.h> 
void main() 
{ 
	char ch[100]; 
	printf("Enter a sentence "); 
	fgets(ch,sizeof(ch),stdin); 
	int count=0,sum=0,word=1; 
	for(int i=0;ch[i]!='\0';i++){ 
		if(ch[i]!=' ') 
		{ count++; 
		}
		else 
		{word++; 
		sum=sum+count; 
		count=0; 
		} 
	} 
	sum=sum+count; 
	printf("Average: %.2f",(float)sum/word); 
}