/*
 * MAX7219.c
 *
 *  Created on: 31 lug 2021
 *      Author: Marco Geraldi
 */

#include "MAX7219.h"

/*Initialize Display Hardware*/
//void MAX7219_init(struct MAX7219_hw* _MAX7219, SPI_HandleTypeDef* spiHandle,GPIO_TypeDef* SPI_CS_PORT,uint16_t SPI_CS_PIN){
//	_MAX7219->spiHandle=spiHandle;
//	_MAX7219->SPI_CS_PORT=SPI_CS_PORT;
//	_MAX7219->SPI_CS_PIN=SPI_CS_PIN;
//	HAL_GPIO_WritePin(_MAX7219->SPI_CS_PORT, _MAX7219->SPI_CS_PIN, GPIO_PIN_SET);
//}

/*Send Data over SPI*/
void MAX7219_SPISend(struct MAX7219_hw* _MAX7219,uint16_t _data){
	HAL_GPIO_WritePin(_MAX7219->SPI_CS_PORT, _MAX7219->SPI_CS_PIN, GPIO_PIN_RESET);
	//HAL_SPI_Transmit(_MAX7219->spiHandle,(uint8_t*)&_data, 1,100);
	HAL_GPIO_WritePin(_MAX7219->SPI_CS_PORT, _MAX7219->SPI_CS_PIN, GPIO_PIN_SET);
}
