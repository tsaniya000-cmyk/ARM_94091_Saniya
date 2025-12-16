#include<stdio.h>
#include<stdint.h>
int main(void)
{
	uint8_t status=0x08;
	if(status & (1<<3))
{
	printf("bit 3 is set \n");
}
	else
	{
	printf("bit 3  is clr \n");
}
}
