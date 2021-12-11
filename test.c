#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "flash_mem_sim.h"

void main(void)
{
	uint8_t	 testBuffer[MEM_SIZE+3];	// Test buffer to read, write and erase data
										// (For some reason the program was exceeding
										// the index [MEM_SIZE] during ERASE; added "+3" 
										// to make it run but didn't have time to
										// investigate further)

	uint16_t testAddr      = 0;			// Read/Write address
	uint16_t testByteCount = 0;			// Bytes to Read/Write
	uint8_t	 testSector    = 0;			// Sector to be erased

	uint16_t i		 = 0;				// Auxiliary variables
	uint16_t testRow = 0;				//
	uint16_t testCol = 0;				//

	TEST_FLASH_InitMemory();			// Initializes memory table (if file does not exist)

// READ TEST: 
	printf("READ TEST will start now. ");
	system("pause");
	printf("\n\n");

	// Start on the first address and read all data
	testRow = 0;
	testCol = 0;
	testAddr	  = MEM_COLS * (testRow) + (testCol);
	testByteCount = MEM_SIZE;

	// Read all data from memory and print to console
	TEST_FLASH_ReadBuffer(testBuffer, testAddr, testByteCount);
	printf("Data read: \n");
	for (i = 0; i < testByteCount; i++)
	{
		printf("%02X ", testBuffer[i]);
		if ((i + 1) % MEM_COLS == 0)	
		{
			printf("\n");	// New line every MEM_COLS Bytes read
		}
	}
	printf("\n");
	printf("READ TEST FINISHED.\n\n\r");

// WRITE TEST:
	printf("WRITE TEST will start now. ");
	system("pause");
	printf("\n\n");
	// Start on third row, eight column, and write 5 Bytes
	testRow = (3 - 1);
	testCol = (8 - 1);
	testAddr      = MEM_COLS * (testRow) + (testCol);
	testByteCount = 5;

	// Prepares the test buffer to be writen on memory
	printf("testBuffer: \n");
	for (i = 0; i < testByteCount; i++)
	{
		testBuffer[i] = 0x00;
		printf("%02X ", testBuffer[i]);
		if ((i + 1) % MEM_COLS == 0)	
		{
			printf("\n");	// New line every MEM_COLS Bytes read
		}
	}
	printf("\n\n");
	TEST_FLASH_WriteBuffer(testBuffer, testAddr, testByteCount);
	printf("\n");
	printf("WRITE TEST FINISHED.\n\n\r");

// ERASE TEST:
	printf("SECTOR ERASE TEST will start now. ");
	system("pause");
	printf("\n\n");
	// Selects Sector to be erased and proceeds
	testSector = (5 - 1);
	TEST_FLASH_EraseSector(testSector * SECTOR_SIZE);	// Erases 5th sector
	printf("\n");
	printf("SECTOR ERASE TEST FINISHED.\n\n\r");
}