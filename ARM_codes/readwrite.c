#include<stdio.h>
#include<stdint.h>
int main()
{
	uint8_t reg=0xAA;
	printf("before modification:0x%02X\n",reg);
	uint8_t readvalue=(reg>>2) & 0x07;
	printf("read bits[4:2]:%u(0b%d%d%d)\n",readvalue,(readvalue>>2)&1,(readvalue>>1)&1,readvalue&1);
	reg  &=~(0x07<<2);
	reg |=(0x03<<2);
	printf("after modification:0x%02X\n",reg);
	return 0;
}
