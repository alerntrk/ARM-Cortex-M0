#include <stdint.h>
#include <stdio.h>
#define USART1_IRQ	27
uint32_t* pISPR = (uint32_t*)0xE000E200;
uint32_t* pISER = (uint32_t*)0xE000E100;


int main(void){

	// MAnually pend the pending bit of the USART3 IRQ number in NVIC
	*pISPR = (0x01 << USART1_IRQ );

	//Enable this IRQ number in NVIC
	*pISER = (0x01 << USART1_IRQ );

	while(1);



}
void USART1_IRQHandler(void){

	printf("hello world from UART1_ISR");

}
