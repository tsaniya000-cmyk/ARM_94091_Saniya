/*
 * switchh.c
 *
 *  Created on: Dec 18, 2025
 *      Author: hp
 */

#include<stdint.h>
#include<stdio.h>
#include"stm32f407xx.h"
#include "switchh.h"


void switchh_init(void)
{
	RCC ->AHB1ENR |=BV(0);
	GPIOA->MODER &=~(BV(0)|BV(1));

	GPIOA->OSPEEDR &=~(BV(0)|BV(1));

	GPIOA->PUPDR &=~(BV(0)|BV(1));
}
int switch_status(void)
{
	if((GPIOA ->IDR) & BV(0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
