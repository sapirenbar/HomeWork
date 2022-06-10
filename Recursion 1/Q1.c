#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int numOfDivisible(int num, int dig);
void main()
{
	int num, dig;
	printf("enter a number:\n");
	scanf(" %d", &num);
	printf("enter a divider:\n");
	scanf(" %d", &dig);
	printf("the number of digits divided is: %d", numOfDivisible(num, dig));
}

int numOfDivisible(int num, int dig)
{
	if (!num)
		return 0;
	int temp = num % 10;
	if (temp % dig == 0)
		return 1 + numOfDivisible(num / 10, dig);
	else return numOfDivisible(num / 10, dig);
}