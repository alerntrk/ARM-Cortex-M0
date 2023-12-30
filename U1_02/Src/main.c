#include <stdint.h>
#include <stdio.h>

//IRQ numbers
#define USART1_IRQ	0x1B
#define TIM2_IRQ	0x0F

//Regs address declarations
uint32_t* pISPR =  (uint32_t*)0xE000E200;
uint32_t* pISER =  (uint32_t*)0xE000E100;
uint32_t* pIPR  =  (uint32_t*)0xE000E400;
uint8_t bitField;

void Config_IntPrio(uint8_t IRQ_Num,uint8_t PrioVal){

	uint32_t RegPos = IRQ_Num / 4;
	bitField = ((IRQ_Num % 4) * 8);
	*(pIPR + RegPos) =  (PrioVal << (bitField));



}
int main(void){



	Config_IntPrio(USART1_IRQ, 0x80);
	Config_IntPrio(TIM2_IRQ ,  0x70);

	// MAnually pend the pending bit of the USART3 IRQ number in NVIC
	*pISPR |= (0x01 << USART1_IRQ );
	*pISER |= (0x01 << TIM2_IRQ   );
	//Enable this IRQ number in NVIC
	*pISER |= (0x01 << USART1_IRQ );




	while(1);



}
void USART1_IRQHandler(void){

	printf("hello world from UART1_ISR");

	*pISPR |= (0x01 << TIM2_IRQ );
	while(1);


}
void TIM2_IRQHandler(void){

	printf("hello world from TIM2_ISR");
	while(1);

}

