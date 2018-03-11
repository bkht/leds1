// Target Options -> Debug -> ST-Link Debugger Settings -> Flash Download tab
// Right click in projct tree on Target 1
// Options for Target 'Target 1'...
// Tab Debug
// Use: ST-Link Debugger
// Setting
// ST-Link/V2
// Flash Download
// Erase Sectors
// Program
// Verify
// Reset and Run

// Discovery F4 STM32F407VG
// LED Red    LD8 PD5  0=on
// LED Orange LD3 PD13 1=on
// LED Green  LD4 PD12 1=on
// LED Red    LD5 PD14 1=on
// LED Blue   LD6 PD15 1=on
// User Button    PA0  1=pressed

//#define RCC_AHB1ENR     0x40023830U
//#define GPIOD_MODER		0x40020C00U
//#define GPIOD_OTYPER	0x40020C04U
//#define GPIOD_OSPEEDR	0x40020C08U
//#define GPIOD_PUPDR		0x40020C0CU
//#define GPIOD_AFRL		0x40020C20U
//#define GPIOD_AFRH		0x40020C24U
//#define GPIOD_LCKR		0x40020C1CU
//#define GPIOD_IDR		0x40020C10U
//#define GPIOD_ODR		0x40020C14U
//#define GPIOD_BSRR		0x40020C18U

//#define AHB1ENR_GPIOAEN  (1U<<0)
//#define AHB1ENR_GPIODEN  (1U<<3)

#define LCKK (1U<<16)

#define LED_LD8_R (1U<<5)
#define LED_LD4_G (1U<<12)
#define LED_LD3_O (1U<<13)
#define LED_LD5_R (1U<<14)
#define LED_LD6_B (1U<<15)
#define USER_BUTTON (1U)

//#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"                  // Device header
#include "delay.h"

int main()
{
//	unsigned int *pt;

//	pt = (unsigned int *) RCC_AHB1ENR;
//	*pt |= AHB1ENR_GPIODEN;

//	pt = (unsigned int *) GPIOD_MODER;
//	*pt |= 0x55000000;	// Set bit 01010101 00000000 00000000 00000000
//	pt = (unsigned int *) GPIOD_OSPEEDR;
//	*pt &= 0x00U;	 // Clear bits, make Low speed
//	pt = (unsigned int *) GPIOD_OTYPER;
//	*pt &= 0x00U;	 // Clear bits, make PP
//	pt = (unsigned int *) GPIOD_PUPDR;
//	*pt |= 0xFFFFFFFFU;	 // Clear bits, make No pull-up
//	pt = (unsigned int *) GPIOD_ODR;
//	*pt |= (LED_LD5_R | LED_LD4_G | LED_LD6_B | LED_LD3_O);	 // Set bits, lit LEDs
//	pt = (unsigned int *) GPIOD_BSRR;
//	*pt = LED_LD5_R | LED_LD4_G | LED_LD6_B | LED_LD3_O;	 // Set bits, lit LEDs

    // Now, lock GPIOD configuration
//	pt = (unsigned int *) GPIOD_LCKR;
//	*pt = (LED_LD5_R | LED_LD4_G | LED_LD6_B | LED_LD3_O | LED_LD8_R | LCKK);
//	*pt = (LED_LD5_R | LED_LD4_G | LED_LD6_B | LED_LD3_O | LED_LD8_R);
//	*pt = (LED_LD5_R | LED_LD4_G | LED_LD6_B | LED_LD3_O | LED_LD8_R | LCKK);
//	uint32_t locked = *pt;
//	locked = *pt;    // 2nd read needed, as the LCKK bit is updated after the first read
//	if (locked & LCKK) {
//		pt = (unsigned int *) GPIOD_ODR;
//		*pt |= LED_LD3_O;	// Orange LED indicates successful lock
//	}
	
	// initialize the GPIO pins we need
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;            // enable clock for GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;            // enable clock for GPIOD

	GPIOD->MODER = 0x55000000;
	GPIOD->OSPEEDR = 0;
	GPIOD->OTYPER = 0;
	GPIOD->PUPDR = 0;
	GPIOD->BSRR = (LED_LD5_R | LED_LD4_G | LED_LD6_B | LED_LD3_O);

	// Now, lock GPIOD configuration
	GPIOD->LCKR = (LED_LD5_R | LED_LD4_G | LED_LD6_B | LED_LD3_O | LED_LD8_R | LCKK);
	GPIOD->LCKR = (LED_LD5_R | LED_LD4_G | LED_LD6_B | LED_LD3_O | LED_LD8_R);
	GPIOD->LCKR = (LED_LD5_R | LED_LD4_G | LED_LD6_B | LED_LD3_O | LED_LD8_R | LCKK);
	uint32_t locked = GPIOD->LCKR;
	locked = GPIOD->LCKR;	// 2nd read needed, as the LCKK bit is updated after the first read
	if (locked & LCKK) {
		GPIOD->BSRR = LED_LD3_O;	// Orange LED indicates successful lock
	}
	
	delay(1000000);

//	pt = (unsigned int *) GPIOD_BSRR;	// GPIOx_ODR
	while (1) {
		GPIOD->BSRR = LED_LD6_B; // Lit blue LED
//		*pt = LED_LD6_B;	 // Set bits, lit LEDs
		delay(1000000);

		GPIOD->BSRR = (LED_LD6_B<<16); // Dim blue LED
//		*pt = (LED_LD6_B<<16);	 // Reset bits, dim LEDs
		delay(1000000);
	}
}
