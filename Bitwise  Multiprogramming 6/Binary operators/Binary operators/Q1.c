#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int pack4Chars2Int(char c1, char c2, char c3, char c4);
int checkEvenParity(short input);
void main()
{
    int num = pack4Chars2Int('a', 'b', 'c', 'd');
    int mask1 = 1;
    mask1 <<= 31;
    short input = 24;
    printf("\n%d", checkEvenParity(input));
}



int pack4Chars2Int(char c1, char c2, char c3, char c4)
{
    int sum = 0;
    int temp = 0;
    temp |= c1;
    temp <<= 24;
    sum = temp;
    temp = 0;
    temp |= c2;
    temp <<= 16;
    sum |= temp;
    temp = 0;
    temp |= c3;
    temp <<= 8;
    sum |= temp;
    temp = 0;
    sum |= c4;

    return sum;
}
int checkEvenParity(short input) {
    int sum = 0;
    short mask = 1;
    while (mask != 0)
    {
        if ((input & mask) == mask)
            sum++;
        mask <<= 1;
    }
    if (sum % 2 == 0)
        return 1;
    return 0;
}