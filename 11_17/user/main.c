/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.3.0
  * @date    16-June-2017
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
int Error = 0;
uint8_t receivedData;
void UART1_RX_IRQHandler(void);
volatile uint16_t pulseCount = 0;
uint8_t data = 123;
void WWDG_setup(void);
 void int_all(void){
   CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
   GPIO_Init(GPIOD, GPIO_PIN_1, GPIO_MODE_OUT_PP_LOW_FAST);
   GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
   UART1_Init(9600, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
              UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);
   UART1_ITConfig(UART1_IT_RXNE, ENABLE);
   UART1->SR &= ~(1 << 2);
   UART1->SR &= ~(1 << 1);
   UART1->SR &= ~(1 << 0);
   UART1->CR2 |= (1 << 3);
   UART1_Cmd(ENABLE);
   enableInterrupts(); 
}

void delay(uint16_t milliseconds) {
  while (milliseconds--) {
        for (uint16_t i = 0; i < 2000; i++) {
          asm("nop"); 
        }
  }
}
void softwareReset() {

    disableInterrupts();
    IWDG->KR = 0xCC; 
    while (1);
}
void main(void)
{
    int_all();
    GPIO_WriteHigh(GPIOD, GPIO_PIN_1);
    GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
    delay(100);
    GPIO_WriteLow(GPIOD, GPIO_PIN_1);
    GPIO_WriteLow(GPIOB, GPIO_PIN_5);
    delay(200);
    GPIO_WriteHigh(GPIOD, GPIO_PIN_1);
    GPIO_WriteHigh(GPIOB, GPIO_PIN_5);

  /* Infinite loop */
    while (1)
    {
        IWDG->KR = IWDG_KEY_REFRESH;
        delay(5000); 
        if( pulseCount > 0 ){
            pulseCount = 0;
            Error = 0 ;
            GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
        }
        else{
            UART1_SendData8(data);
            Error++;
            GPIO_WriteHigh(GPIOD, GPIO_PIN_1);
            GPIO_WriteLow(GPIOB, GPIO_PIN_5);
            delay(100);
            GPIO_WriteLow(GPIOD, GPIO_PIN_1);
            delay(200);
            GPIO_WriteHigh(GPIOD, GPIO_PIN_1);
            delay(100);
            if( Error > 10){
                softwareReset();
            }
            pulseCount = 0;
        }
        
    }
  
}
void IDWDG_setup(void)
{
    IWDG->KR = IWDG_KEY_ENABLE;
    IWDG->KR = IWDG_WriteAccess_Enable;
    IWDG->PR = IWDG_Prescaler_256;
    IWDG->RLR = 255;
    IWDG->KR = IWDG_KEY_REFRESH;
}
#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  //while (1)
  //{
  //}
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
