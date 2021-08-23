/*
 *  LTC4332.h
 *
 *  Created on: Augest 1, 2021
 *      Author: Benson Yang
 */

#include "LTC4332.h"

void LTC4332_Read_All(LTC4332_t *device)
{
    uint8_t data;
    Read_Reg(device, CONFIG_REG, &data);
    device->config = data;
    Read_Reg(device, STATUS_REG, &data);
    device->status = data;
    Read_Reg(device, EVENT_REG, &data);
    device->event = data;
    Read_Reg(device, FAULT_REG, &data);
    device->fault = data;
    Read_Reg(device, WORD_LENGTH_REG, &data);
    device->word_length = data;
    Read_Reg(device, SCRATCH_REG, &data);
    device->scratch = data;
}

int8_t Read_Reg(LTC4332_t *device, uint8_t addr, uint8_t *receive)
{
    HAL_GPIO_WritePin(device->GPIOx, device->GPIO_PIN, 0);

    uint8_t Tx_tmp = 0, Rx_tmp = 0;
    Tx_tmp = (addr << 1) | 0x01;
    Rx_tmp = ADI_flame_TandR(device, Tx_tmp);
    Tx_tmp = 0;
    *receive = ADI_flame_TandR(device, 0);

    HAL_GPIO_WritePin(device->GPIOx, device->GPIO_PIN, 1);
    sb_delay(150);
    return 0;
}

/* 
@parameter:
    device  device data structure
    addr    target register address
    value   the data that you want to transfer
*/
int8_t Write_Reg(LTC4332_t *device, uint8_t addr, uint8_t value)
{
    HAL_GPIO_WritePin(device->GPIOx, device->GPIO_PIN, 0);

    uint8_t Tx_tmp = (addr << 1) & 0xFE;
    ADI_flame_TandR(device, Tx_tmp);
    ADI_flame_TandR(device, value);

    HAL_GPIO_WritePin(device->GPIOx, device->GPIO_PIN, 1);
    sb_delay(150);
    return 0;
}

uint8_t flame_TandR(LTC4332_t *device, uint8_t trans)
{
    uint8_t result;
    static HAL_StatusTypeDef state;
    state = HAL_SPI_TransmitReceive(device->hspi, (uint8_t *)&trans, (uint8_t *)&result, 1, 0xFFFF);
    if (state != HAL_OK)
    {
        while (1)
            ;
    }
    return result;
}
void sb_delay(volatile uint32_t t)
{
    while (t--)
        ;
}