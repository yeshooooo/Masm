#include <stdio.h>

int g_Num = 0x123;

typedef struct _INFO
{
	char a;
	short b;
	int c;
} INFO, *PINFO;
int main()
{
	// 1. [������]
	g_Num = 0xFF;

	// 2.[�Ĵ���]
	int a = 0;
	int* p = &a;
	*p = 0x12;

	// 3. [�Ĵ��� + ������]
	INFO info = { 0 };
	PINFO pInfo = &info;
	pInfo->b = 1;
	pInfo->c = 2;

	// 4. [�Ĵ��� + �Ĵ���*(1/2/4/8)]
	int Arr[2][3] = { 0 };
	for (size_t i = 0; i < 2; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			Arr[i][j] = i + j;
		}
	}

	// 5. [�Ĵ��� + �Ĵ���*(1/2/4/8) + ������]
	INFO Arr1[10] = { 0 };
	for (size_t i = 0; i < 10; i++)
	{
		Arr1[i].b = 1;
		Arr1[i].c = 1;
	}



	return 0;
}