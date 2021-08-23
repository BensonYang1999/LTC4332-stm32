/*
 *  LTC4332.h
 *
 *  Created on: Augest 1, 2021
 *      Author: Benson Yang
 */

#ifndef LTC4332_H
#define LTC4332_H
#endif

#include "spi.h"
#include "stm32f4xx_hal.h"

#define CONFIG_REG 0x00
#define STATUS_REG 0x01
#define EVENT_REG 0x02
#define INT_EN_REG 0x03
#define FAULT_REG 0x04
#define WORD_LENGTH_REG 0x05
#define SCRATCH_REG 0x06

typedef struct
{
    SPI_HandleTypeDef *hspi; //SPI handle
    GPIO_TypeDef *GPIOx;     //CS pin GPIOx
    uint16_t GPIO_PIN;       //CS pin number

    uint8_t config;
    uint8_t status;
    uint8_t event;
    uint8_t fault;
    uint8_t word_length;
    uint8_t scratch;
} LTC4332_t;

void LTC4332_Read_All(LTC4332_t *device);
int8_t Read_Reg(LTC4332_t *device, uint8_t addr, uint8_t *receive);
int8_t Write_Reg(LTC4332_t *device, uint8_t addr, uint8_t value);
uint8_t flame_TandR(LTC4332_t *device, uint8_t trans);
void sb_delay(volatile uint32_t t);
/*
 * config register bit map (RW)
 * 7  NAN
 * 6  NAN
 * 5  remote SS1 CPHA
 * 4  remote SS1 CPOL
 * 3  remote SS2 CPHA
 * 2  remote SS2 CPOL
 * 1  remote SS3 CPHA
 * 0  remote SS3 CPOL
 */

/*
 * status register bit map (RO)
 * 7 speed index (4 bits)
 * 6 .
 * 5 .
 * 4 .
 * 3 Reserved
 * 2 remote INT
 * 1 local INT
 * 0 LINK
 */

/*
 * event register bit map (WOC)
 * 7 6 5 4 3 NAN
 * 2 any fault in FAULT register
 * 1 link is lost
 * 0 link is good
 */

/*
 * asserts INT if corresponding EVENT bit is set (RW)
 */

/*
 * event register bit map (EO)
 * 4 receive buffer overflowed
 * 3 transmit buffer overflowed
 * 2 fault or stuck bus timeout on remote SPI bus
 * 1 link communication corruption
 * 0 incomplete write transfer
 */

/*
 * word length (RW)
 * 5~0  8 ≤ WORD_LENGTH ≤ 32
 */

/*
 * scratch (RW)
 * 7~0  test read/write access to the control interface
 */