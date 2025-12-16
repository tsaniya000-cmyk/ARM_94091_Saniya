#include<stdio.h>
#include<stdint.h>
int main()
{
 uint8_t reg = 0xABCD;
	uint8_t lower4=reg & 0x000F;
	uint8_t upper4_lastbyte=(reg & 0x00F0)>>4;
	printf("lower 4 bits:0x%X\n",lower4);
	printf("upper 4 bits:0x%X\n",upper4_lastbyte);
	return 0;
}
