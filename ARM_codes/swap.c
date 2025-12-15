#include<stdio.h>
void swap(int *num1,int *num2)
{
	*num1=*num1^*num2;
	*num2=*num1^*num2;
	*num1=*num1^*num2;
}
int main()
{
	int num1,num2;
	printf("enter 1st and 2nd  no:");
	scanf("%d%d",&num1,&num2);
	swap(&num1,&num2);
	printf("after swap:%d %d",num1,num2);
	return 0;
}
