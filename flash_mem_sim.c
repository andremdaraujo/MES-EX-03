#define _CRT_SECURE_NO_DEPRECATE	// Required to use fopen() in VS2022

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "flash_mem_sim.h"

void TEST_FLASH_InitMemory(void)
{
	FILE*    stream;				// File emulating memory contents
	uint16_t i = 0;
	uint16_t j = 0;

	printf("Trying to open test_mem.txt... ");
	stream = fopen("test_mem.txt", "r");	// Try to open file emulating memory contents

	if (stream == NULL)							// If file does not exist
	{
		printf("Failed! test_mem.txt does not exist. \n\n");
		stream = fopen("test_mem.txt", "w");	// Create file emulating memory content
		printf("test_mem.txt created. Filling file with test data... \n");

		for (i = 0; i < MEM_ROWS; i++)		// Fill file with data calculated according to its address
		{
			for (j = 0; j < MEM_COLS; j++)
			{
				fprintf(stream, "%02X ", ((7 * i + 3 * j) & 0xFF));
			}
			fprintf(stream, "\n");
		}
		printf("test_mem.txt filled with test data; ");
		printf("%u rows x %u columns; ", MEM_ROWS, MEM_COLS);
		printf("total: %u Bytes; ", (MEM_ROWS * MEM_COLS));
		printf("%u Sectors of %u Bytes each. \n\n", (MEM_SIZE / SECTOR_SIZE), SECTOR_SIZE);
	}
	else
	{
		printf("Success! test_mem.txt initialized previously.\n\n");
	}
	fclose(stream);
}

void TEST_FLASH_ReadBuffer(uint8_t* pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead)
{
	FILE*	 stream;					// File emulating memory contents
	uint16_t i = 0;

	// Checks if number of Bytes to read exceeds memory bounds; if so, reduces BTR
	if ((ReadAddr + NumByteToRead) > MEM_SIZE)
	{
		NumByteToRead = MEM_SIZE - ReadAddr;
		printf("Number of Bytes to read exceeds memory addresses. ");
		printf("BTR reduced to %d. \n", NumByteToRead);
	}
	printf("\n");

	// Opens file for read and sets cursor to desired address
	stream = fopen("test_mem.txt", "r");
	fseek(stream, ((3 * ReadAddr) + ((ReadAddr) / MEM_COLS) * 2), SEEK_SET);

	for (i = 0; i < NumByteToRead; i++)
	{
		fscanf(stream, "%X", &pBuffer[i]);
	}
}

void TEST_FLASH_WriteBuffer(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite)
{
	FILE*	 stream;					// File emulating memory contents
	uint8_t	 auxBuffer[MEM_SIZE + 3];
	uint16_t i = 0;
	uint16_t j = 0;

	TEST_FLASH_ReadBuffer(auxBuffer, 0x00, MEM_SIZE);	// Reads whole memory table

	for (i = 0; i < NumByteToWrite; i++)				// Prepares buffer with data to be writen
	{
		auxBuffer[i + WriteAddr] = pBuffer[i];
	}

	stream = fopen("test_mem.txt", "w");
	for (i = 0; i < MEM_ROWS; i++)
	{
		for (j = 0; j < MEM_COLS; j++)
		{
			fprintf(stream, "%02X ", (auxBuffer[i * MEM_COLS + j]));
			printf (		"%02X ", (auxBuffer[i * MEM_COLS + j]));
		}
		fprintf(stream, "\n");
		printf("\n");
	}
	fclose(stream);
}

void TEST_FLASH_EraseSector(uint32_t SectorAddr)
{
	uint8_t	 zeros[SECTOR_SIZE];
	uint16_t i = 0;

	for (i = 0; i < SECTOR_SIZE; i++)	// Prepares an array of zeros to erase memory Sector
	{
		zeros[i] = 0;
	}
	TEST_FLASH_WriteBuffer(zeros, SectorAddr, SECTOR_SIZE);
}
