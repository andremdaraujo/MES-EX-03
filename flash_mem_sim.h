#ifndef FLASH_MEM_SIM_H_
#define FLASH_MEM_SIM_H_

void TEST_FLASH_EraseSector	(uint32_t SectorAddr);
void TEST_FLASH_WriteBuffer	(uint8_t* pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void TEST_FLASH_ReadBuffer	(uint8_t* pBuffer, uint32_t ReadAddr , uint16_t NumByteToRead );

#endif	// FLASH_MEM_SIM_H_