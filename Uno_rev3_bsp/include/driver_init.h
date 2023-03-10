/**
 * \file
 *
 * \brief Driver initialization.
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/*
 * Code generated by START.
 *
 * This file will be overwritten when reconfiguring your START project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#ifndef DRIVER_INIT_H_INCLUDED
#define DRIVER_INIT_H_INCLUDED

/* Default init: Usart and I2C enabled.
 * These settings may be overridden by
 * passing these defines in CmakeLists.txt as Compiler defines*/
#ifndef USE_USART
#define USE_USART 1
#endif
#ifndef USE_SPI
#define USE_SPI 0
#endif
#ifndef USE_TIMER
#define USE_TIMER 0
#endif
#ifndef USE_WDT
#define USE_WDT 0
#endif
#ifndef USE_ADC
#define USE_ADC 0
#endif
#ifndef USE_AC
#define USE_AC 0
#endif
#ifndef USE_PWM
#define USE_PWM 0
#endif
#ifndef USE_I2C
#define USE_I2C 1
#endif

#include <atmel_start_pins.h>
#include <clock_config.h>
#include <compiler.h>
#include <port.h>

#include <nvmctrl_basic.h>
#include <sysctrl.h>

#if USE_WDT
#include <wdt.h>
#endif
#include <protected_io.h>
#if USE_ADC
#include <adc_basic.h>
#endif
#if USE_AC
#include <ac.h>
#endif
#if USE_I2C
#include <i2c_master.h>
#endif
#if USE_SPI
#include <spi_basic.h>
#endif
#include <interrupt_avr8.h>
#if USE_PWM
#include <pwm_basic.h>
#endif
#if USE_TIMER
#include <tc16.h>
#endif
#if USE_USART
#include <usart_basic.h>
#endif
#ifdef __cplusplus
extern "C" {
#endif

void system_init(void);

#ifdef __cplusplus
}
#endif

#endif /* DRIVER_INIT_H_INCLUDED */
