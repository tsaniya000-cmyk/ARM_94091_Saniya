#include<stdio.h>
unsigned char evenParity(unsigned char data)
{
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        if (data & (1 << i))
            count++;
    }
if (count % 2 != 0)
        data = data | 0x80;   // 0x80 = 10000000

    return data;
}


int main()
{
    unsigned char data = 0x25;  
    unsigned char result;

    result = evenParity(data);

    printf("Original data : 0x%X\n", data);
    printf("After parity  : 0x%X\n", result);

  
}
