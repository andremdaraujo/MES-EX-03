#define _CRT_SECURE_NO_DEPRECATE	// Required to use fopen() in VS2022

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "flash_mem_sim.h"

void main(void)
{
	uint16_t i = 0;
	uint16_t j = 0;
	int test_var = 0;
	FILE* stream;

	uint8_t	tBuffer[2048];	// Test buffer to read, write and erase data
	uint16_t tReadAddr = 0;	// Test read address
	uint16_t tBTR = 0;		// Test Bytes to read

	printf("Trying to open test_mem.txt... \n\r");
	stream = fopen("test_mem.txt", "r");	// Try to open file emulating memory contents

	if (stream == NULL)					// If file does not exist
	{
		printf("test_mem.txt does not exist. \n\r");
		stream = fopen("test_mem.txt", "w");	// Create file emulating memory content
		printf("test_mem.txt created. Filling file with test data... \n\r");

		for (i = 0; i < 32; i++)
		{
			for (j = 0; j < 16; j++)
			{
				fprintf(stream, "%2X ", ((7*i + 3*j) & 0xFF));
			}
			fprintf(stream, "\n");
		}
		printf("test_mem.txt filled with test data. ");
		printf("%u rows x %u collumns. ", i, j);
		printf("Total: %u Bytes. \n\r", (i * j));
	}

	fclose(stream);



	tReadAddr = 16*(17-1) + 9;
	tBTR = 10;

	//TEST_FLASH_ReadBuffer(tBuffer, tReadAddr, tBTR);

		stream = fopen("test_mem.txt", "r");
		fseek(stream, ( (3 * tReadAddr) + ((tReadAddr) / 16)*2 ), SEEK_SET);
		
		for (i = 0; i < tBTR; i++)
		{
			fscanf(stream, "%X", &tBuffer[i]);
		}

		printf("Data read: ");
		for (i = 0; i < tBTR; i++)
		{
			printf("%2X ", tBuffer[i]);
		}
		printf("\n\n\r");

	printf("Hello! Test Var = %d \n", test_var);

	system("pause");
}
