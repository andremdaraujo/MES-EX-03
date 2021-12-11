#ifndef FLASH_MEM_SIM_H
#define FLASH_MEM_SIM_H

#define MEM_ROWS	32U	// Rows in the memory table
#define MEM_COLS	16U	// Columns in the memory table

#define MEM_SIZE	 (MEM_ROWS * MEM_COLS)	// Memory size in Bytes
#define SECTOR_SIZE	 (MEM_SIZE / 16)		// Sector size in Bytes

void TEST_FLASH_InitMemory  (void);
void TEST_FLASH_ReadBuffer	(uint8_t* pBuffer, uint32_t ReadAddr , uint16_t NumByteToRead );
void TEST_FLASH_WriteBuffer	(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void TEST_FLASH_EraseSector	(uint32_t SectorAddr);

#endif	// FLASH_MEM_SIM_H