#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define _CRT_SECURE_NO_WARNINGS


int main()
{
	system("chcp 1251");
	system("cls");
	unsigned char chk = 0;
	unsigned char state = 0x1;
	unsigned int sec = 0;
	/*
	State can be:
	0x1 | 0x11 - 1st floor door close/open
	0x2 | 0x12 - 2st floor door close/open
	0x3 | 0x13 - 3st floor door close/open
	0x4 | 0x14 - 4st floor door close/open
	*/
	printf("Команды лифта:\n");
	printf("1 - вызов с 1 этажа/поехать на 1 этаж \n");
	printf("2 - вызов со 2 этажа/поехать на 2 этаж \n");
	printf("3 - вызов с 3 этажа/поехать на 3 этаж \n");
	printf("4 - вызов с 4 этажа/поехать на 4 этаж \n");
	printf("5 - завершение работы\n");

	//Внешняя кнопка вызова совмещена с внутренней
	while (chk != 5)
	{
		printf("\n");
		if (state > 4) printf("Лифт на этаже: %x\n", state-16);
		else printf("Лифт на этаже: %x\n", state);
		printf("\n");
		printf("Введите команду \n");
		scanf("%d", &chk);
		switch (chk)
		{
		case 1:
			switch (state)
			{
			case 0x1:
				state = 0x11;
				printf("Лифт на 1 этаже - двери открыты\n");

				break;
			case 0x2:
				state = 0x11;
				printf("Лифт спустился со второго этажа на первый, двери открыты\n");
				break;
			case 0x3:
				state = 0x11;
				printf("Лифт спустился с третьего этажа на первый, двери открыты\n");
				break;
			case 0x4:
				state = 0x11;
				printf("Лифт спустился со четвертого этажа на первый, двери открыты\n");
				break;
			case 0x11:
				printf("Двери открыты\n");
				break;
			case 0x12:
				//state = 0x2
				state = 0x11;
				printf("Лифт спустился со второго этажа на первый, двери открыты\n");
				break;
			case 0x13:
				//state = 0x3
				state = 0x11;
				printf("Лифт спустился со второго этажа на первый, двери открыты\n");
				break;
			case 0x14:
				//state = 0x4
				state = 0x11;
				printf("Лифт спустился со второго этажа на первый, двери открыты\n");
				break;
			}
			break;
		case 2:
			switch (state)
			{
			case 0x1:
				state = 0x12;
				printf("Лифт поднялся с 1 на 2 этаж - двери открыты\n");
				break;
			case 0x2:
				state = 0x12;
				printf("Лифт на 2 этаже - двери открыты\n");
				break;
			case 0x3:
				state = 0x12;
				printf("Лифт спустился с 3 этажа на 2, двери открыты\n");
				break;
			case 0x4:
				state = 0x12;
				printf("Лифт спустился со 4 этажа на 2, двери открыты\n");
				break;
			case 0x11:
				//state = 0x1
				state = 0x12;
				printf("Лифт поднялся с 1 на 2 этаж - двери открыты\n");
				break;
			case 0x12:
				//state = 0x2
				printf("Лифт на 2 этаже - двери открыты\n");
				break;
			case 0x13:
				//state = 0x3
				state = 0x12;
				printf("Лифт спустился с 3 этажа на 2, двери открыты\n");
				break;
			case 0x14:
				//state = 0x4
				state = 0x12;
				printf("Лифт спустился со 4 этажа на 2, двери открыты\n");
				break;
			}
			break;
		case 3:
			switch (state)
			{
			case 0x1:
				state = 0x13;
				printf("Лифт поднялся с 1 на 3 этаж - двери открыты\n");
				break;
			case 0x2:
				state = 0x13;
				printf("Лифт поднялся с 2 на 3 этаж - двери открыты\n");
				break;
			case 0x3:
				state = 0x13;
				printf("Лифт на 3 этаже, двери открыты\n");
				break;
			case 0x4:
				state = 0x13;
				printf("Лифт спустился со 4 этажа на 3, двери открыты\n");
				break;
			case 0x11:
				//state = 0x1
				state = 0x13;
				printf("Лифт поднялся с 1 на 3 этаж - двери открыты\n");
				break;
			case 0x12:
				//state = 0x2
				state = 0x13;
				printf("Лифт поднялся с 2 на 3 этаж - двери открыты\n");
				break;
			case 0x13:
				//state = 0x3
				printf("Лифт на 3 этаже, двери открыты\n");
				break;
			case 0x14:
				//state = 0x4
				state = 0x13;
				printf("Лифт спустился со 4 этажа на 3, двери открыты\n");
				break;
			}
			break;
		case 4:
			switch (state)
			{
			case 0x1:
				state = 0x14;
				printf("Лифт поднялся с 1 на 4 этаж - двери открыты\n");
				break;
			case 0x2:
				state = 0x14;
				printf("Лифт поднялся с 2 на 4 этаж - двери открыты\n");
				break;
			case 0x3:
				state = 0x14;
				printf("Лифт поднялся с 3 этажа на 4, двери открыты\n");
				break;
			case 0x4:
				state = 0x14;
				printf("Лифт на 4 этаже, двери открыты\n");
				break;
			case 0x11:
				//state = 0x1
				state = 0x14;
				printf("Лифт поднялся с 1 на 4 этаж - двери открыты\n");
				break;
			case 0x12:
				//state = 0x2
				state = 0x14;
				printf("Лифт поднялся с 2 на 4 этаж - двери открыты\n");
				break;
			case 0x13:
				//state = 0x3
				state = 0x14;
				printf("Лифт поднялся с 3 этажа на 4, двери открыты\n");
				break;
			case 0x14:
				//state = 0x4
				printf("Лифт на 4 этаже, двери открыты\n");
				break;
			}
			break;
		}
		
	}
	printf("\n"); printf("\n");
	printf("Отработало нормально\n");

	system("pause");
	return 0;
}
