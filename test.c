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

	uint8_t	 testBuffer[MEM_SIZE+3];	// Test buffer to read, write and erase data
	uint16_t testReadAddr = 0;			// Test read address
	uint16_t testBTR = 0;				// Test Bytes to read

	test_row = 1;
	test_col = 1;

	testReadAddr = MEM_COLS*(test_row - 1) + (test_col - 1);
	testBTR = MEM_SIZE;

	TEST_FLASH_InitMemory();			// Initializes memory table, if it's the first time

	TEST_FLASH_ReadBuffer(testBuffer, testReadAddr, testBTR);

	printf("Data read: \n");
	for (i = 0; i < testBTR; i++)
	{
		printf("%02X ", testBuffer[i]);
		if ((i + 1) % MEM_COLS == 0)	// New line every MEM_COLS Bytes read
		{
			printf("\n");
		}
	}
	printf("\n\n\r");

	system("pause");

	printf("testBuffer: \n");

	for (i = 0; i < 5; i++)
	{
		testBuffer[i] = 0;// i + i * i;

		printf("%02X ", testBuffer[i]);
		if ((i + 1) % MEM_COLS == 0)	// New line every MEM_COLS Bytes read
		{
			printf("\n");
		}
	}
	TEST_FLASH_WriteBuffer(testBuffer, 0xFF0, 5);

	system("pause");

	TEST_FLASH_EraseSector(15*SECTOR_SIZE);
}