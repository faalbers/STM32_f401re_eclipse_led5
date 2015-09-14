//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "stm32f4xx.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via DEBUG).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the DEBUG output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

/* Private function prototypes -----------------------------------------------*/
static void Error_Handler(void);

int
main(int argc, char* argv[])
{
  if(HAL_Init()!= HAL_OK)
  {
    /* Start Conversation Error */
    Error_Handler();
  }

  // At this stage the system clock should have already been configured
  // at high speed.
  trace_printf("System clock: %u Hz\n", SystemCoreClock);

  uint32_t PCLK1CLK, PCLK2CLK;
  PCLK1CLK = HAL_RCC_GetPCLK1Freq();
  PCLK2CLK = HAL_RCC_GetPCLK2Freq();

  trace_printf("PCLK1  clock: %u Hz\n", PCLK1CLK);
  trace_printf("PCLK2  clock: %u Hz\n", PCLK2CLK);

  GPIO_InitTypeDef GPIO_InitStructure;

  // Enable GPIOA Peripheral clock
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = GPIO_PIN_5;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  // Enable GPIOC Peripheral clock
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;

  // Configure pin in input push/pull mode
  GPIO_InitStructure.Pin = GPIO_PIN_13;
  GPIO_InitStructure.Mode = GPIO_MODE_INPUT;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStructure);

 // Infinite loop
  while (1)
    {
      if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == 0)
      {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

        /* Insert delay 1000 ms */
        HAL_Delay(1000);

        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
      }

    }
}

static void Error_Handler(void)
{
  while(1)
  {
  }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
