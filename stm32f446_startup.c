#include <stdint.h>



/**Build:
main.o :  arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 main.c -o main.o
stm32f411_startup.o : arm-none-eabi-gcc -c -mcpu=cortex-m4 -mthumb -std=gnu11 stm32f446_startup.c -o stm32f446_startup.o
stm32_blink.elf : arm-none-eabi-gcc -nostdlib -T stm32_ls.ld *.o -o stm32_blink.elf -Wl,-Map=stm32_blink.map

Load:

openocd -f board/st_nucleo_f4.cfg
**/

/*Symbols defined in the linker script */

extern uint32_t _estack;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

/* Function prototypes */

void Reset_Handler(void);
int main(void);

/* Exception and Interrupt Handlers */
/*
__attribute__: tells compiler that the declaration that its applied to has certain properties
that affect hows it treated by the linker and potentially at runtime

weak: it does not prevent the linker from using another symbol of the same name with a stronger
linkage, use this to specify default implementations that can be overridden

marking them as weak allows us to define default handlers in our startup file, 
which application-specific handlers can override without modifying
the startup file.

alias: creates an alias for another symbol, in this case "Default_Handler"

It means that the symbol (e.g., NMI_Handler) is not just weak, but it is also an alias for the
Default_Handler function.

This means that when an interrupt occurs, and a specific handler (such as NMI_Handler) has
not been defined elsewhere in the application with stronger linkage (non-weak), the program
will use Default_Handler in its place. This ensures that all interrupts have a handler,
preventing the system from crashing due to unhandled events.
*/
void NMI_Handler					(void)__attribute__((weak,alias("Default_Handler")));
void HardFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void MemManage_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void BusFault_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void UsageFault_Handler 			(void) __attribute__ ((weak, alias("Default_Handler")));
void SVC_Handler 					(void) __attribute__ ((weak, alias("Default_Handler")));
void DebugMon_Handler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void PendSV_Handler   				(void) __attribute__ ((weak, alias("Default_Handler")));
void SysTick_Handler  				(void) __attribute__ ((weak, alias("Default_Handler")));
void WWDG_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));
void PVD_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));             
void TAMP_STAMP_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));      
void RTC_WKUP_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));                               
void FLASH_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));             
void RCC_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));             
void EXTI0_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI1_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI3_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void EXTI4_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));           
void DMA1_Stream0_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream1_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream2_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream3_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream4_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream5_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void DMA1_Stream6_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));    
void ADC_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler"))); 
void CAN1_TX_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler"))); 
void CAN1_RX0_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler"))); 
void CAN1_RX1_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN1_SCE_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));         
void EXTI9_5_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));        
void TIM1_BRK_TIM9_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));   
void TIM1_UP_TIM10_IRQHandler 		(void) __attribute__ ((weak, alias("Default_Handler")));   
void TIM1_TRG_COM_TIM11_IRQHandler 	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM1_CC_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void TIM2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));            
void TIM3_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));            
void TIM4_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));            
void I2C1_EV_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C1_ER_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C2_EV_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void I2C2_ER_IRQHandler 			(void) __attribute__ ((weak, alias("Default_Handler")));         
void SPI1_IRQHandler  				(void) __attribute__ ((weak, alias("Default_Handler")));           
void SPI2_IRQHandler 				(void) __attribute__ ((weak, alias("Default_Handler")));            
void USART1_IRQHandler  			(void) __attribute__ ((weak, alias("Default_Handler")));         
void USART2_IRQHandler  			(void) __attribute__ ((weak, alias("Default_Handler")));        
void EXTI15_10_IRQHandler   		(void) __attribute__ ((weak, alias("Default_Handler")));     
void RTC_Alarm_IRQHandler    		(void) __attribute__ ((weak, alias("Default_Handler")));    
void OTG_FS_WKUP_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void TIM8_BRK_TIM12_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler"))); 
void TIM8_UP_TIM13_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler"))); 
void TIM8_TRG_COM_TIM14_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler"))); 
void TIM8_CC_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA1_Stream7_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void SDIO_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void TIM5_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void SPI3_IRQHandler             	(void) __attribute__ ((weak, alias("Default_Handler")));
void UART4_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void UART5_IRQHandler             (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM6_DAC_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void TIM7_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream0_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream1_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream2_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream3_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream4_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_TX_IRQHandler           (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX0_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_RX1_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void CAN2_SCE_IRQHandler          (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_FS_IRQHandler           	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream5_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream6_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void DMA2_Stream7_IRQHandler     	(void) __attribute__ ((weak, alias("Default_Handler")));
void USART6_IRQHandler           	(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_EV_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void I2C3_ER_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_EP1_OUT_IRQHandler    (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_EP1_IN_IRQHandler     (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_WKUP_IRQHandler       (void) __attribute__ ((weak, alias("Default_Handler")));
void OTG_HS_IRQHandler          	(void) __attribute__ ((weak, alias("Default_Handler")));
void DCMI_IRQHandler              (void) __attribute__ ((weak, alias("Default_Handler")));
void FPU_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void SPI4_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void SAI1_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void SAI2_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void QuadSPI_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void HDMI_CEC_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void SPDIF_Rx_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void FMPI2C1_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler"))); 
void FMPI2C1_error_IRQHandler              	(void) __attribute__ ((weak, alias("Default_Handler"))); 

/* Vector Table */
__attribute__((section(".isr_vector_tbl")))
uint32_t vector_tbl[] = {
    /* Stack pointer */
    (uint32_t)&_estack,

    /* Cortex-M core exceptions */
    (uint32_t)&Reset_Handler,          /* Reset */
    (uint32_t)&NMI_Handler,            /* NMI */
    (uint32_t)&HardFault_Handler,      /* HardFault */
    (uint32_t)&MemManage_Handler,      /* MemManage */
    (uint32_t)&BusFault_Handler,       /* BusFault */
    (uint32_t)&UsageFault_Handler,     /* UsageFault */
    0, 0, 0, 0,                        /* reserved */
    (uint32_t)&SVC_Handler,            /* SVCall */
    (uint32_t)&DebugMon_Handler,       /* DebugMon */
    0,                                 /* reserved */
    (uint32_t)&PendSV_Handler,         /* PendSV */
    (uint32_t)&SysTick_Handler,        /* SysTick */

    /* External interrupts */
    (uint32_t)&WWDG_IRQHandler,              /* Window Watchdog */
    (uint32_t)&PVD_IRQHandler,               /* PVD through EXTI Line detect */
    (uint32_t)&TAMP_STAMP_IRQHandler,        /* Tamper and TimeStamp */
    (uint32_t)&RTC_WKUP_IRQHandler,          /* RTC Wakeup */
    (uint32_t)&FLASH_IRQHandler,             /* FLASH */
    (uint32_t)&RCC_IRQHandler,               /* RCC */
    (uint32_t)&EXTI0_IRQHandler,             /* EXTI Line0 */
    (uint32_t)&EXTI1_IRQHandler,             /* EXTI Line1 */
    (uint32_t)&EXTI2_IRQHandler,             /* EXTI Line2 */
    (uint32_t)&EXTI3_IRQHandler,             /* EXTI Line3 */
    (uint32_t)&EXTI4_IRQHandler,             /* EXTI Line4 */
    (uint32_t)&DMA1_Stream0_IRQHandler,      /* DMA1 Stream0 */
    (uint32_t)&DMA1_Stream1_IRQHandler,      /* DMA1 Stream1 */
    (uint32_t)&DMA1_Stream2_IRQHandler,      /* DMA1 Stream2 */
    (uint32_t)&DMA1_Stream3_IRQHandler,      /* DMA1 Stream3 */
    (uint32_t)&DMA1_Stream4_IRQHandler,      /* DMA1 Stream4 */
    (uint32_t)&DMA1_Stream5_IRQHandler,      /* DMA1 Stream5 */
    (uint32_t)&DMA1_Stream6_IRQHandler,      /* DMA1 Stream6 */
    (uint32_t)&ADC_IRQHandler,               /* ADC1 */
    /* no DAC on F411: slot left reserved */
    0,                                       /* Reserved */
    0,                                       /* Reserved */
    0,                                       /* Reserved */
    0,                                       /* Reserved */
    (uint32_t)&EXTI9_5_IRQHandler,           /* EXTI Lines 9:5 */
    (uint32_t)&TIM1_BRK_TIM9_IRQHandler,     /* TIM1 Break & TIM9 */
    (uint32_t)&TIM1_UP_TIM10_IRQHandler,     /* TIM1 Update & TIM10 */
    (uint32_t)&TIM1_TRG_COM_TIM11_IRQHandler,/* TIM1 Trigger & Commutation & TIM11 */
    (uint32_t)&TIM1_CC_IRQHandler,           /* TIM1 Capture Compare */
    (uint32_t)&TIM2_IRQHandler,              /* TIM2 */
    (uint32_t)&TIM3_IRQHandler,              /* TIM3 */
    (uint32_t)&TIM4_IRQHandler,              /* TIM4 */
    (uint32_t)&I2C1_EV_IRQHandler,           /* I2C1 Event */
    (uint32_t)&I2C1_ER_IRQHandler,           /* I2C1 Error */
    (uint32_t)&I2C2_EV_IRQHandler,           /* I2C2 Event */
    (uint32_t)&I2C2_ER_IRQHandler,           /* I2C2 Error */
    (uint32_t)&SPI1_IRQHandler,              /* SPI1 */
    (uint32_t)&SPI2_IRQHandler,              /* SPI2 */
    (uint32_t)&USART1_IRQHandler,            /* USART1 */
    (uint32_t)&USART2_IRQHandler,            /* USART2 */
    0,                                       /* Reserved */
    (uint32_t)&EXTI15_10_IRQHandler,         /* EXTI Lines 15:10 */
    (uint32_t)&RTC_Alarm_IRQHandler,         /* RTC Alarm (A and B) */
    (uint32_t)&OTG_FS_WKUP_IRQHandler,       /* USB OTG FS Wakeup */
    
    /* F411 has no TIM8/9... leave these reserved or rename if not used */
    (uint32_t)&TIM8_BRK_TIM12_IRQHandler,    /* TIM8 Break & TIM12 */
    (uint32_t)&TIM8_UP_TIM13_IRQHandler,     /* TIM8 Update & TIM13 */
    (uint32_t)&TIM8_TRG_COM_TIM14_IRQHandler,/* TIM8 Trigger & Commutation & TIM14 */
    (uint32_t)&TIM8_CC_IRQHandler,           /* TIM8 Capture Compare */
    
    (uint32_t)&DMA1_Stream7_IRQHandler,      /* DMA1 Stream7 */
    (uint32_t)&SDIO_IRQHandler,              /* SDIO (if present) */
    (uint32_t)&TIM5_IRQHandler,              /* TIM5 */
    (uint32_t)&SPI3_IRQHandler,              /* SPI3 */
    (uint32_t)&UART4_IRQHandler,             /* UART4 */
    (uint32_t)&UART5_IRQHandler,             /* UART5 */
    (uint32_t)&TIM6_DAC_IRQHandler,          /* TIM6 & DAC */
    (uint32_t)&TIM7_IRQHandler,              /* TIM7 */
    (uint32_t)&DMA2_Stream0_IRQHandler,      /* DMA2 Stream0 */
    (uint32_t)&DMA2_Stream1_IRQHandler,      /* DMA2 Stream1 */
    (uint32_t)&DMA2_Stream2_IRQHandler,      /* DMA2 Stream2 */
    (uint32_t)&DMA2_Stream3_IRQHandler,      /* DMA2 Stream3 */
    (uint32_t)&DMA2_Stream4_IRQHandler,      /* DMA2 Stream4 */
    (uint32_t)&CAN2_TX_IRQHandler,           /* CAN2 TX */
    (uint32_t)&CAN2_RX0_IRQHandler,          /* CAN2 RX0 */
    (uint32_t)&CAN2_RX1_IRQHandler,          /* CAN2 RX1 */
    (uint32_t)&CAN2_SCE_IRQHandler,          /* CAN2 SCE */
    (uint32_t)&OTG_FS_IRQHandler,            /* USB OTG FS */
    (uint32_t)&DMA2_Stream5_IRQHandler,      /* DMA2 Stream5 */
    (uint32_t)&DMA2_Stream6_IRQHandler,      /* DMA2 Stream6 */
    (uint32_t)&DMA2_Stream7_IRQHandler,      /* DMA2 Stream7 */
    (uint32_t)&USART6_IRQHandler,            /* USART6 */
    (uint32_t)&I2C3_EV_IRQHandler,           /* I2C3 Event */
    (uint32_t)&I2C3_ER_IRQHandler,           /* I2C3 Error */
    (uint32_t)&OTG_HS_EP1_OUT_IRQHandler,    /* OTG HS EP1 OUT */
    (uint32_t)&OTG_HS_EP1_IN_IRQHandler,     /* OTG HS EP1 IN */
    (uint32_t)&OTG_HS_WKUP_IRQHandler,       /* OTG HS Wakeup */
    (uint32_t)&OTG_HS_IRQHandler,            /* OTG HS */
    (uint32_t)&DCMI_IRQHandler,              /* DCMI */
    (uint32_t)&FPU_IRQHandler,               /* FPU global */
    (uint32_t)&SPI4_IRQHandler,              /* SPI4 */
    (uint32_t)&SAI1_IRQHandler,              /* SAI1 */
    (uint32_t)&SAI2_IRQHandler,              /* SAI2 */
    (uint32_t)&QuadSPI_IRQHandler,           /* QUADSPI */
    (uint32_t)&HDMI_CEC_IRQHandler,          /* HDMI CEC */
    (uint32_t)&SPDIF_Rx_IRQHandler,          /* SPDIF Rx */
    (uint32_t)&FMPI2C1_IRQHandler,           /* FMPI2C1 Event */
    (uint32_t)&FMPI2C1_error_IRQHandler,     /* FMPI2C1 Error */
};

/* Default handler that enters an infinite loop */

void Default_Handler(void)
{
	while(1)
	{
		
	}
}




/* Reset Handler */
void Reset_Handler(void)
{
	// Calculate the sizes of the .data and .bss sections
	uint32_t data_mem_size =  (uint32_t)&_edata - (uint32_t)&_sdata;
	uint32_t bss_mem_size  =   (uint32_t)&_ebss - (uint32_t)&_sbss;
    
	// Initialize pointers to the source and destination of the .data section
	uint32_t *p_src_mem =  (uint32_t *)&_etext;
	uint32_t *p_dest_mem = (uint32_t *)&_sdata;
	
	/*Copy .data section from FLASH to SRAM*/
	for(uint32_t i = 0; i < data_mem_size; i++  )
	{
		
		 *p_dest_mem++ = *p_src_mem++;
	}
	
	// Initialize the .bss section to zero in SRAM
	p_dest_mem =  (uint32_t *)&_sbss;
	
	for(uint32_t i = 0; i < bss_mem_size; i++)
	{
		 /*Set bss section to zero*/  
		*p_dest_mem++ = 0;
	}
	
	    // Call the application's main function.

	main();
}



