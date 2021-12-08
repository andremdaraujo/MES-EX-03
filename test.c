#define _CRT_SECURE_NO_DEPRECATE	// Required to use fopen() in VS2022

#define MEM_ROWS	256				// Rows in the memory table
#define MEM_COLS	 16				// Columns in the memory table

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "flash_mem_sim.h"

void main(void)
{
	uint16_t i = 0;
	uint16_t j = 0;
	
	uint16_t test_row = 0;
	uint16_t test_col = 0;

	uint8_t	 tBuffer[2048];			// Test buffer to read, write and erase data
	uint16_t tReadAddr = 0;			// Test read address
	uint16_t tBTR = 0;				// Test Bytes to read

	FILE* stream;					// File emulating memory contents

	printf("Trying to open test_mem.txt... \n\n\r");
	stream = fopen("test_mem.txt", "r");	// Try to open file emulating memory contents

	if (stream == NULL)							// If file does not exist
	{
		printf("test_mem.txt does not exist. \n\r");
		stream = fopen("test_mem.txt", "w");	// Create file emulating memory content
		printf("test_mem.txt created. Filling file with test data... \n\r");

		for (i = 0; i < MEM_ROWS; i++)
		{
			for (j = 0; j < MEM_COLS; j++)
			{
				fprintf(stream, "%02X ", ((7*i + 3*j) & 0xFF));
			}
			fprintf(stream, "\n");
		}
		printf("test_mem.txt filled with test data. ");
		printf("%u rows x %u collumns. ", i, j);
		printf("Total: %u Bytes. \n\r", (MEM_ROWS * MEM_COLS));
	}

	fclose(stream);

	test_row = 1;
	test_col = 1;

	tReadAddr = MEM_COLS*(test_row - 1) + (test_col - 1);
	tBTR = 49;

	printf("\n");
	printf("Trying to read %u Bytes from memory, starting on address %u. \n", tBTR, tReadAddr);
	printf("Starting position: Row %u, Column %u. \n\n", test_row, test_col);

	if ((tReadAddr + tBTR) > (MEM_ROWS * MEM_COLS))
	{
		tBTR = (MEM_ROWS * MEM_COLS) - tReadAddr;
		printf("'Bytes To Read' exceeds memory addresses. BTR reduced to %d. \n\n", tBTR);
	}

	//TEST_FLASH_ReadBuffer(tBuffer, tReadAddr, tBTR);

		stream = fopen("test_mem.txt", "r");
		fseek(stream, ( (3 * tReadAddr) + ((tReadAddr) / MEM_COLS)*2 ), SEEK_SET);
		
		for (i = 0; i < tBTR; i++)
		{
			fscanf(stream, "%X", &tBuffer[i]);
		}

		printf("Data read: \n");
		for (i = 0; i < tBTR; i++)
		{
			printf("%02X ", tBuffer[i]);
			if ( (i + 1) % 16 == 0)			// New line every 16 Bytes read
			{
				printf("\n");
			}
		}
		printf("\n\n\r");

		//system("pause");
}