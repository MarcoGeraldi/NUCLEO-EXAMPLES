/*
 * MAX7219.h
 *
 *  Created on: 31 lug 2021
 *      Author: Marco Geraldi
 */

#ifndef MAX7219_H_
#define MAX7219_H_

#include <stdbool.h>
#include <stm32f4xx_hal.h>

// REGISTER ADDRESS MAP - D11 TO D8
#define noOP 0x0
#define registerAddressMask 8
#define digit0 0x1<<registerAddressMask
#define digit1 0x2<<registerAddressMask
#define digit2 0x3<<registerAddressMask
#define digit3 0x4<<registerAddressMask
#define digit4 0x5<<registerAddressMask
#define digit5 0x6<<registerAddressMask
#define digit6 0x7<<registerAddressMask
#define digit7 0x8<<registerAddressMask
#define decodeMode 0x9<<registerAddressMask
#define intensity  0xA<<registerAddressMask
#define scanLimit  0xB<<registerAddressMask
#define shutdown   0xC<<registerAddressMask
#define displayTest 0xF<<registerAddressMask

// SHUTDOWN REGISTER FORMAT - D0
#define shutdownMode 0x0
#define normalOperation 0x1

// DECODE-MODE REGISTER EXAMPLES - D7 TO D0
#define noDecode 0x00 /*No decode for digits 7–0*/
#define bDecAll  0xFF /*Code B decode for digits 7–0*/
#define bDec0_0  0x01 /*Code B decode for digit 0 - No decode for digits 7–1 */
#define bDec3_0  0x0F /*Code B decode for digits 3–0 - No decode for digits 7–4*/

// CODE B FONT D3 to D0
#define char0 0x0
#define char1 0x1
#define char2 0x2
#define char3 0x3
#define char4 0x4
#define char5 0x5
#define char6 0x6
#define char7 0x7
#define char8 0x8
#define char9 0x9
#define char_ 0xA
#define charE 0xB
#define charH 0xC
#define charL 0xD
#define charP 0xE
#define charBlank 0xF
#define chardp 0x1 << 7

// INTENSITY REGISTER - D3 TO D0
#define intensity_1_32 0x0
#define intensity_3_32 0x1
#define intensity_5_32 0x2
#define intensity_7_32 0x3
#define intensity_9_32 0x4
#define intensity_11_32 0x5
#define intensity_13_32 0x6
#define intensity_15_32 0x7
#define intensity_17_32 0x8
#define intensity_19_32 0x9
#define intensity_21_32 0xA
#define intensity_23_32 0xB
#define intensity_25_32 0xC
#define intensity_27_32 0xD
#define intensity_29_32 0xE
#define intensity_31_32 0xF

// SCAN LIMIT REGISTER - D2 TO D0
#define scanLimit_d0_0 0x0
#define scanLimit_d0_1 0x1
#define scanLimit_d0_2 0x2
#define scanLimit_d0_3 0x3
#define scanLimit_d0_4 0x4
#define scanLimit_d0_5 0x5
#define scanLimit_d0_6 0x6
#define scanLimit_d0_7 0x7

struct MAX7219_hw {
	GPIO_TypeDef* SPI_CS_PORT;
	uint16_t SPI_CS_PIN;
	//SPI_HandleTypeDef* spiHandle;
} my7seg;

//void MAX7219_init(struct MAX7219_hw* _MAX7219, SPI_HandleTypeDef* spiHandle,GPIO_TypeDef* SPI_CS_PORT,uint16_t SPI_CS_PIN);
void MAX7219_SPISend(struct MAX7219_hw* _MAX7219,uint16_t _data);

void MAX7219_displayTest(struct MAX7219_hw* _MAX7219);
void MAX7219_shutDown(struct MAX7219_hw* _MAX7219);
void MAX7219_decodeMode(struct MAX7219_hw* _MAX7219,uint8_t _opt);
void MAX7219_scanLimit(struct MAX7219_hw* _MAX7219,uint8_t _opt);
void MAX7219_setIntensity(struct MAX7219_hw* _MAX7219,uint8_t _opt);

void MAX7219_displayChar(struct MAX7219_hw* _MAX7219,char _char);
void MAX7219_displayNum(struct MAX7219_hw* _MAX7219,uint32_t _num);
void MAX7219_displayString(struct MAX7219_hw* _MAX7219,const char* _string, uint8_t _digits, bool _scrolling, bool _iterate);

#endif /* MAX7219_H_ */
