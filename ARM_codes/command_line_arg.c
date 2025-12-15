#include<stdio.h>
#include<stdlib.h>
void binary(unsigned char num)
{
for(int i=7;i>=0;i--)
{
    
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

unsigned char evenparity(unsigned char data)
{
    int count = 0;

    for (int i = 0; i < 8; i++)
    {
        if (data & (1 << i))
            count++;
    }

    if (count % 2 != 0)
        data = data | 0x80;  

    return data;
}

int main(int argc, char *argv[])
{
    unsigned char data, result;

    if (argc != 2)
    {
        printf("Usage: program_name <number>\n");
        return 1;
    }

    data = (unsigned char)atoi(argv[1]);

    printf("Original data (binary): ");
    binary(data);

    result = evenparity(data);

    printf("After parity (binary):  ");
    binary(result);

    return 0;
}
