//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
//
// Copyright (c) 2013-2020 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.2.0.295 of the EK-TM4C1294XL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif

//*****************************************************************************
//
// Blink the on-board LED.
//
//*****************************************************************************
int main(void)
{
// 1. Reloj a 120 MHz

//    uint32_t g_ui32SysClock = SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480), 120000000);

    // 2. Habilitar energía de los tres puertos (N, F y J)
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);

    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION) || 
          !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF) || 
          !SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ))
    {
    }

    // 3. Configurar salidas (LEDs) y entradas con Pull-Up (Switches)
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4);

    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0 | GPIO_PIN_1, 
                     GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    // Variable entera solicitada por la guía
    int counter = 0;

    while(1)
    {
        // Switch 1 (PJ0): Incrementa el contador hasta un máximo de 15
        if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0) == 0)
        {
            SysCtlDelay(2000000); // Antirrebote (~50 ms)
            if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0) == 0)
            {
                if(counter < 15)
                {
                    counter++;
                }
                while(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_0) == 0); // Espera a soltar
            }
        }

        // Switch 2 (PJ1): Decrementa el contador hasta un mínimo de 0
        if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1) == 0)
        {
            SysCtlDelay(2000000); // Antirrebote (~50 ms)
            if(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1) == 0)
            {
                if(counter > 0)
                {
                    counter--;
                }
                while(GPIOPinRead(GPIO_PORTJ_BASE, GPIO_PIN_1) == 0); // Espera a soltar
            }
        }

        // Mapeo binario a los LEDs:
        // Bit 0 (1): PF0 (LED 4)
        // Bit 1 (2): PF4 (LED 3)
        // Bit 2 (4): PN0 (LED 2)
        // Bit 3 (8): PN1 (LED 1 - MSB)
        uint8_t valN = 0;
        uint8_t valF = 0;

        if(counter & 1) valF |= GPIO_PIN_0; // Bit 0
        if(counter & 2) valF |= GPIO_PIN_4; // Bit 1
        if(counter & 4) valN |= GPIO_PIN_0; // Bit 2
        if(counter & 8) valN |= GPIO_PIN_1; // Bit 3

        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0 | GPIO_PIN_1, valN);
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0 | GPIO_PIN_4, valF);
    }
}