#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define SIZE 100
int strcmp(char str1, char str2);
void main()
{
	char str1[SIZE];
	char str2[SIZE];
	printf("enter the first string:\n");
	gets(str1);
	printf("enter the second string:\n");
	gets(str2);
	int res = strcmp(str1, str2);
	if (!res) printf("the strings are equal");
	if (res > 0) printf("the first string is bigger");
	if (res < 0) printf("the second string is bigger");
}

int strcmp(char str1[], char str2[])
{
	if (str1[0] == '\0' && str1[0] != '\0') return -1;
	if (str1[0] != '\0' && str1[0] == '\0') return 1;
	if (str1[0] == '\0' && str1[0] == '\0') return 0;
	if (str1[0] == str2[0])
		return strcmp(str1 + 1, str2 + 1);
	if (str1[0] > str2[0]) return 1;
	if (str1[0] < str2[0]) return -1;
}