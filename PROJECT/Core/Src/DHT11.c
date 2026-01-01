/*
 * dht11.c
 *
 * Created on: Dec 22, 2025
 * Author: Administrator
 *
 * Tested with STM32F407 + HAL
 */

#include "dht11.h"
#include "main.h"

/* ================= MICROSECOND DELAY USING DWT ================= */

static void DWT_Delay_Init(void)
{
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void delay_us(uint32_t us)
{
    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = us * (SystemCoreClock / 1000000);
    while ((DWT->CYCCNT - start) < ticks);
}

/* ================= GPIO MODE CONTROL ================= */

static void DHT11_Pin_Output(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

static void DHT11_Pin_Input(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = DHT11_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(DHT11_PORT, &GPIO_InitStruct);
}

/* ================= INITIALIZATION ================= */

void DHT11_Init(void)
{
    DWT_Delay_Init();
}

/* ================= READ ONE BYTE ================= */

static uint8_t DHT11_ReadByte(void)
{
    uint8_t i, byte = 0;

    for (i = 0; i < 8; i++)
    {
        /* Wait for pin to go HIGH */
        while (!HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));

        /* Wait 40 us */
        delay_us(40);

        if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
        {
            byte |= (1 << (7 - i));
            while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));
        }
    }
    return byte;
}

/* ================= MAIN READ FUNCTION ================= */

uint8_t DHT11_Read(uint8_t *temperature, uint8_t *humidity)
{
    uint8_t data[5] = {0};

    /* ---- START SIGNAL ---- */
    DHT11_Pin_Output();
    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_RESET);
    HAL_Delay(18);

    HAL_GPIO_WritePin(DHT11_PORT, DHT11_PIN, GPIO_PIN_SET);
    delay_us(30);
    DHT11_Pin_Input();

    /* ---- SENSOR RESPONSE ---- */
    if (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN))
        return 1;   // No response

    while (!HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN)); // LOW → HIGH
    while (HAL_GPIO_ReadPin(DHT11_PORT, DHT11_PIN));  // HIGH → LOW

    /* ---- READ 5 BYTES ---- */
    for (uint8_t i = 0; i < 5; i++)
        data[i] = DHT11_ReadByte();

    /* ---- CHECKSUM ---- */
    if (data[4] != (data[0] + data[1] + data[2] + data[3]))
        return 2;   // Checksum error

    *humidity = data[0];
    *temperature = data[2];

    return 0;       // Success
}
