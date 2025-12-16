#include<stdio.h>
#include<stdint.h>
int main()
{
	uint8_t value=5;
	uint8_t leftshift=value<<2;
	uint8_t rightshift=value>>1;
	printf("original value=%u\n",value);
	printf("after left shift by 2 = %u\n",leftshift);
	printf("after right shift by 1 = %u\n",rightshift);	
	return 0;	
}
