#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include <zlib.h>

#define _CRT_SECURE_NO_WARNINGS
unsigned int crc32b(unsigned char *message) {
	int i, j;
	int byte, crc, mask;

	i = 0;
	crc = 0xFFFFFFFF;
	while (message[i] != 0) {
		byte = message[i];            // Get next byte.
		crc = crc ^ byte;
		for (j = 7; j >= 0; j--) {    // Do eight times.
			mask = -(crc & 1);
			crc = (crc >> 1) ^ (0xEDB88320 & mask);
		}
		i = i + 1;
	}
	return ~crc;
}
unsigned short swap_uint16(unsigned short x)
{
	return ((x >> 8) | (x << 8));

}
unsigned long long swap_uint32(unsigned long x)
{
	return (((x >> 24) & 0x000000ff) | ((x >> 8) & 0x0000ff00) | ((x << 8) & 0x00ff0000) | ((x << 24) & 0xff000000));
}
unsigned long long swap_uint64(unsigned long long val)
{
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL) | ((val >> 8) & 0x00FF00FF00FF00FFULL);
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL) | ((val >> 16) & 0x0000FFFF0000FFFFULL);
	return (val << 32) | (val >> 32);
}
struct fin_inf
{
	unsigned char data[146];
	unsigned long long MAC;
	unsigned long long MACs;
};
chck(unsigned char *buf, long lSize)
{
	char flag = 1;
	unsigned char actualSFD = 0xAB;
	unsigned long long actual_pream = 0xaaaaaaaaaaaaaa;
	unsigned long long actualMAC = 0xffffffffffff;
	unsigned short actualL = *((unsigned short*)buf + 10);
	unsigned long long Pream = *((unsigned long long*)buf);
	unsigned long long MAC = *((unsigned long long*)buf + 1);
	unsigned long inCRC = *((unsigned long*)buf + 6);
	struct fin_inf fin_inf1;
	//Проверка PREAMBULE
	if (((swap_uint64(Pream) >> 8) == actual_pream) && (flag = 1)) puts("RIGHT PREAMBULE.");
	else
	{
		//puts("WRONG PREAMBULE.");
		return(-1);
	}
	//Checking SFD	
	if ((*(buf + 7) == actualSFD && (flag = 1)) && (flag = 1)) puts("RIGHT SFD.");
	else
	{
		//puts("WRONG SFD.");
		return(-1);
	}
	//Проерка конечного MAC
	if (((swap_uint64(MAC) >> 16) == actualMAC) && (flag = 1)) puts("RIGHT MAC.");
	else
	{
		//puts("WRONG MAC.");
		return(-1);
	}
	//Проверка длины
	if ((swap_uint16(actualL) == (lSize - 22)) && (flag = 1)) puts("RIGHT L.");
	else
	{
		//puts("WRONG Length.");
		return(-1);
	}
	//Проверка CRC
	if ((swap_uint32(inCRC) == (crc32b(buf))) && (flag = 1)) puts("RIGHT CRC.");
	else
	{
		//puts("WRONG CRC.");
		return(-1);
	}
	unsigned long long MACs_bg = *((unsigned long long*)buf + 1);
	unsigned long long MACs_end = *((unsigned long long*)buf + 2);
	fin_inf1.MAC = (swap_uint64(MAC) >> 16);
	fin_inf1.MACs = (((swap_uint64(MACs_bg) << 48) | (swap_uint64(MACs_end) >> 16)) >> 16);
	unsigned char data_real[146] = "\0";
	unsigned char data_temp = *(buf + 22);
	for (int i = 0; i < (lSize - 26); i++)
	{
		fin_inf1.data[i] = data_temp + i;
		fin_inf1.data[i + 1] = "\0";
	}
	printf("MAC dest -> 0x%I64x\n", fin_inf1.MAC);
	printf("MAC source -> 0x%I64x\n", fin_inf1.MACs);
	printf("Data -> ");
	for (int i = 0; i < (lSize - 26); i++)
	{
		printf("%x", fin_inf1.data[i]);
	}

	return(0);
};


main() {
	
	system("chcp 1251");
	system("cls");
	struct fin_inf fin_inf2;
	FILE* f = fopen("C:/Users/Nikita/Desktop/test", "rb");
	fseek(f, 0, SEEK_END);                          // устанавливаем позицию в конец файла
	long lSize = ftell(f);                            // получаем размер в байтах
	fseek(f, 0, SEEK_SET);
	unsigned char * buf = (unsigned char*)malloc(sizeof(unsigned char) * lSize); // выделить память для хранения содержимого файла
	fread(buf, 1, lSize, f);
	fclose(f);
	chck(buf, lSize);
	free(buf);
	getchar();
	return 0;
}
