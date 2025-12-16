#include<stdio.h>
#include<stdint.h>
void binary(uint8_t value)
{
	int i;
	
	for( i=7;i>=0;i--)
	{
		printf("%d",(value>>i)&1);
	}

}
int main(void)
{
	uint8_t reg =0x2A;
	reg |=(1<<4);
	printf("\nset bit 4:0x%02X\n",reg);
	binary(reg);
	printf("\n\n");
	reg&= ~(1<<1);
	printf("\nclear bit 1:0x%02X\n",reg);
	binary(reg);
	printf("\n\n");
	reg^=(1<<5);
	printf("\ntoggle bit 5:0x%02X\n",reg);
	binary(reg);
		printf("\n\n");
		return 0;
    }

