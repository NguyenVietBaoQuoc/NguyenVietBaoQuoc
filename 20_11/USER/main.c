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
/*static void IWDG_Config(void) 
{
    
    IWDG->KR = IWDG_KEY_ENABLE;
    IWDG->KR = IWDG_WriteAccess_Enable;
    IWDG->PR = 0xFF;
    IWDG->PR = 0x6;
    IWDG->RLR = 255;
    IWDG->KR = IWDG_KEY_REFRESH;
}*/
uint8_t DATA = 0x32;
unsigned int i;
void delay(uint16_t milliseconds) {
  while (milliseconds--) {
      for (uint16_t i = 0; i < 2000; i++) {
          asm("nop"); 
      }
  }
}
void main(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_CPUDIV1);

    UART1_Init(115200, UART1_WORDLENGTH_8D, 
                  UART1_STOPBITS_1, UART1_PARITY_NO, 
                  UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE );
    GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
    delay(2000);
    GPIO_WriteLow(GPIOB, GPIO_PIN_5);
    delay(1000);
    GPIO_WriteHigh(GPIOB, GPIO_PIN_5);
    //IWDG_Config();
    /* Infinite loop */
    while (1)
    {
        //IWDG->KR = IWDG_KEY_REFRESH;
        //UART1_SendData8(DATA);
        GPIO_WriteHigh(GPIOC, GPIO_PIN_5);
        delay(1000);
        GPIO_WriteLow(GPIOC, GPIO_PIN_5);
        delay(200);
        i++;

  }
  
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
 // while (1)
 // {
  //}
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
