#include<stdio.h>
int isAlphabet(char ch)
{
	if((ch>='A'&& ch<='Z')||(ch>='a'&& ch<='z'))
	return 1;
	else
	return 0;
}
int main()
{
	char ch;
	printf("enter a character:");
	scanf("%c",&ch);
	if(isAlphabet(ch))
printf("it is an alphabet");
else
printf("it is not alphabet");
return 0;
}
