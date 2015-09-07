//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "diag/Trace.h"
#include "stm32f4xx.h"
//#include "stm32f4xx_hal.h"

// ----------------------------------------------------------------------------
//
// Standalone STM32F4 empty sample (trace via NONE).
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the NONE output,
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

int
main(int argc, char* argv[])
{
  // At this stage the system clock should have already been configured
  // at high speed.
  GPIO_InitTypeDef GPIO_InitStructure;

  // Enable GPIO Peripheral clock
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

  // Configure pin in output push/pull mode
  GPIO_InitStructure.Pin = GPIO_PIN_5;
  GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
  GPIO_InitStructure.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStructure);

  // Set timer frequency to 1000 Hz. 1 tick = 1 ms
  trace_printf("System clock: %u Hz\n", SystemCoreClock);
  SysTick_Config (SystemCoreClock / 1000u);

  // Infinite loop
  while (1)
    {
      // Turn GPIOA PIN_5 ON
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);

      /* Insert delay 1000 ms */
      HAL_Delay(100);

      // Turn GPIOA PIN_5 ON
      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);

      /* Insert delay 1000 ms */
      HAL_Delay(900);
    }
}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
