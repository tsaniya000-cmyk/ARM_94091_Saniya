#include <stdio.h>
unsigned char evenparity(unsigned char data)
{
	int count=0;
	for(int i = 0;i<8;i++)
	{
		{
			if(data&(1<<i))
			count++;
		}
		if(count%2!=0)
		data=data|0x80;
		return data;
	}
	
}
	int main()
	{
		unsigned char data=0x25;
		unsigned char result;
		result=evenparity(data);
		printf("original data:0x%X\n",data);
			printf("after parity:0x%X\n",result);
		
		return 0;
	
}

