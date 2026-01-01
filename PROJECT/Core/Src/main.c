/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c

 ******************************************************************************
 */
 /* USER CODE END Header */

#include "main.h"
#include "my_lcd.h"
#include "dht11.h"
#include "buzzer.h"
#include <stdio.h>

ADC_HandleTypeDef hadc1;
I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);


int _write(int file, char *ptr, int len)
{
    HAL_UART_Transmit(&huart2, (uint8_t*)ptr, len, HAL_MAX_DELAY);
    return len;
}
int main(void)
{
    uint16_t gas_value;
    uint8_t temp, hum;
    char lcd_buf[20];

    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_I2C1_Init();
    MX_USART2_UART_Init();

    printf("System Started\r\n");

    if (!lcd16x2_i2c_init(&hi2c1))
    {
        printf("LCD not detected\r\n");
        while (1);
    }

    lcd16x2_i2c_clear();
    DHT11_Init();

    while (1)
    {

        gas_value = adc_conversion();
        printf("Gas = %d\r\n", gas_value);

        lcd16x2_i2c_setCursor(0, 0);
        sprintf(lcd_buf, "Gas: %d", gas_value);
        lcd16x2_i2c_printf(lcd_buf);

        if (gas_value > 1000)
        {
            gas_buzzer();
        }
        if (DHT11_Read(&temp, &hum) == 0)
        {
            printf("Temp=%dC Hum=%d%%\r\n", temp, hum);

            lcd16x2_i2c_setCursor(1, 0);
            sprintf(lcd_buf, "T:%dC H:%d%%", temp, hum);
            lcd16x2_i2c_printf(lcd_buf);
        }

        HAL_Delay(2000);
        lcd16x2_i2c_clear();
    }
}
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;

    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType =
        RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
        RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

static void MX_ADC1_Init(void)
{
    ADC_ChannelConfTypeDef sConfig = {0};

    hadc1.Instance = ADC1;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    HAL_ADC_Init(&hadc1);

    sConfig.Channel = ADC_CHANNEL_0;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}
static void MX_I2C1_Init(void)
{
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    HAL_I2C_Init(&hi2c1);
}

static void MX_USART2_UART_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&huart2);
}



	static void MX_GPIO_Init(void)
	{
	    GPIO_InitTypeDef GPIO_InitStruct = {0};

	    /* Enable GPIO clocks */
	    __HAL_RCC_GPIOA_CLK_ENABLE();
	    __HAL_RCC_GPIOB_CLK_ENABLE();
	    __HAL_RCC_GPIOD_CLK_ENABLE();

	    /* ================= BUZZER : PD13 ================= */
	    GPIO_InitStruct.Pin = GPIO_PIN_13;
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	    /* ================= DHT11 : PA1 ================= */
	    GPIO_InitStruct.Pin = GPIO_PIN_1;
	    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;   // will change dynamically in code
	    GPIO_InitStruct.Pull = GPIO_NOPULL;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	    /* ================= I2C LCD : PB6, PB7 ================= */
	    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
	    GPIO_InitStruct.Pull = GPIO_PULLUP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
	    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	}


/* ================== ERROR ================== */
void Error_Handler(void)
{
    __disable_irq();
    while (1);
}
