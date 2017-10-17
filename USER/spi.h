#ifndef __SPI_H
#define __SPI_H

#include "include.h"

void SPIInit(void);
u8 SPISendByte(u8 byte);
u16 SPISendHalfWord(u16 HalfWord);
void SPISendBytes(uint8_t *bytes, uint8_t len);
#endif /* __SPI_H */

