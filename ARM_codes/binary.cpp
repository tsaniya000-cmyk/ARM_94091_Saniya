#include<stdio.h>
void binary(unsigned int num)
{
	int i;
	for(i=7;i>=0;i--)
	{
		printf("%d",(num>>i)&1);
	}
	printf("\n");
}
int main()
{
	unsigned int num=7;
	printf("binary of %u is",num);
	 binary(num);
	 return 0;
}
