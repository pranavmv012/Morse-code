/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * FILE           : main.c
  * PROJECT        : vasudevan_assignment
  * PROGRAMMER     : Pranav Manakkulamparambil Vasudevan
  * FIRST VERSION  : 2020-02-11
  * DESCRIPTION    : Code for embedded systems that writes the initial of any
  *                  name(hard coded) on the RGB led in international morse code.
  *                  first name initial displays on red led which is excited
  *                  by PB4 and last name initial is displays on green led which
  *                  is excited by PB5.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
//time delay constants
int dotTime   = 500; //the length of dot in Morse code
int dashTime  = 1500;//the length of dash in Morse code
int partSpace = 500;//The space between parts(dash and dot) of the same letter
int lettSpace = 1500;//The space between tow letters
int iniSpace  = 2500;//The space between two consecutive initials
//function declarations

void fdotCode();
void fdashCode();
void fspaceCode();
void ldotCode();

void ldashCode();

void lspaceCode();

char nameExtract(char fName[50], char lName[50]);//function to extract the initial from the first name and last name

void fgenerateMorse(char fInitial);

void lgenerateMorse(char lInitial);
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */
 
 

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  nameExtract("pranav","vasudevan");//The function call to extract initials from first name and last name.

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pins : PB4 PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/*FUNCTION      : nameExtract
 * DESCRIPTION  :function to extract the initial from the first name and last name and
 *               doesn't return any values
 * PARAMETERS   :char fName : first name
 *               char lName : last name
 */
char nameExtract(char fName[50], char lName[50])
{
	char firstInitial = fName[0];//extracting the initial of first name
	char lastInitial = lName[0];//extracting the initial of last name
	fgenerateMorse(firstInitial);//function call to generate morse code for first initial
	HAL_Delay(lettSpace);//delay between initials
	lgenerateMorse(lastInitial);//function call to generate morse code for last initial
	HAL_Delay(iniSpace);//delay between Consecutive initials

}
/*FUNCTION      : fdotCode
 * DESCRIPTION  :function to generate a dot in the Morse code for first initial with no
 *               parameters and function doesn't return any values
 */
void fdotCode()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);
	HAL_Delay(dotTime);
}
/*FUNCTION      : fdashCode
 * DESCRIPTION  :function to generate a dash in the Morse code for first initial with no
 *               parameters and function doesn't return any values
 */
void fdashCode()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, SET);
    HAL_Delay(dashTime);
}
/*FUNCTION      : fspaceCode
 * DESCRIPTION  :function to generate the gap between dot and dash for first initial with no
 *               parameters and function doesn't return any values
 */
void fspaceCode()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, RESET);
    HAL_Delay(partSpace);
}
/*FUNCTION      : ldotCode
 * DESCRIPTION  :function to generate a dot in the Morse code for last initial with no
 *               parameters and function doesn't return any values
 */
void ldotCode()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, SET);
	HAL_Delay(dotTime);
}
/*FUNCTION      : ldashCode
 * DESCRIPTION  :function to generate a dash in the Morse code for last initial with no
 *               parameters and function doesn't return any values
 */
void ldashCode()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, SET);
    HAL_Delay(dashTime);
}
/*FUNCTION      : lspaceCode
 * DESCRIPTION  :function to generate the gap between dot and dash for last initial with no
 *               parameters and function doesn't return any values
 */
void lspaceCode()
{
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, RESET);
    HAL_Delay(partSpace);
}
/*FUNCTION      : fgenerateMorse
 * DESCRIPTION  :function to generate Morse code for the first name initial
 *               doesn't return any values
 * PARAMETERS   : fInitial : the first name initial
 */
void fgenerateMorse(char fInitial)
{
switch (fInitial)
{
         case 'a':
             fdotCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'b':
	  		 fdashCode();
	         fspaceCode();
	         fdotCode();
	         fspaceCode();
	         fdotCode();
             fspaceCode();
             fdotCode();
             fspaceCode();
            break;
	  	 case 'c':
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdotCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdotCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'd':
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdotCode();
	  		 fspaceCode();
	  		 fdotCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'e':
	  		 fdotCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'f':
	  		 fdotCode();
	  		 fspaceCode();
	  		 fdotCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdotCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'g':
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdotCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'h':
	  		 fdotCode();
	  		 fspaceCode();
	  		 fdotCode();
	  		 fspaceCode();
	  		 fdotCode();
	  		 fspaceCode();
	  		 fdotCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'i':
	  		 fdotCode();
	  		 fspaceCode();
	  		 fdotCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'j':
	  		 fdotCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'k':
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdotCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'l':
	  	     fdotCode();
	  	     fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  	     break;
	  	 case 'm':
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'n':
	  		 fdashCode();
	  		 fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  	     break;
	  	 case 'o':
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'p':
	  	     fdotCode();
	  	     fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  	     break;
	  	 case 'q':
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'r':
	  	     fdotCode();
	  	     fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  		 break;
	  	 case 's':
	  	     fdotCode();
	  	     fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  	     break;
	  	 case 't':
	  		 fdashCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'u':
	  	     fdotCode();
	  	     fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'v':
	  	     fdotCode();
	  	     fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'w':
	  	     fdotCode();
	  	     fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'x':
	  		 fdashCode();
	  		 fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'y':
	  		 fdashCode();
	  		 fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  		 break;
	  	 case 'z':
	  		 fdashCode();
	  		 fspaceCode();
	  		 fdashCode();
	  		 fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  	     fdotCode();
	  	     fspaceCode();
	  	     break;
	  	}
	  }
/*FUNCTION      : lgenerateMorse
 * DESCRIPTION  :function to generate Morse code for the last name initial
 *               doesn't return any values
 * PARAMETERS   :lInitial: the last name initial
 */
void lgenerateMorse(char lInitial)
{
  switch (lInitial)
  {
	  	 case 'a':
	  		 ldotCode();
	  		 lspaceCode();
	  	 	 ldashCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'b':
	  		 ldashCode();
	           lspaceCode();
	           ldotCode();
	           lspaceCode();
	           ldotCode();
	           lspaceCode();
	           ldotCode();
	           lspaceCode();
	           break;
	  	 case 'c':
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldotCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldotCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'd':
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldotCode();
	  		 lspaceCode();
	  		 ldotCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'e':
	  		 ldotCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'f':
	  		 ldotCode();
	  		 lspaceCode();
	  		 ldotCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldotCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'g':
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldotCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'h':
	  		 ldotCode();
	  		 lspaceCode();
	  		 ldotCode();
	  		 lspaceCode();
	  		 ldotCode();
	  		 lspaceCode();
	  		 ldotCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'i':
	  		 ldotCode();
	  		 lspaceCode();
	  		 ldotCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'j':
	  		 ldotCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'k':
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldotCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'l':
	  	     ldotCode();
	  	     lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  	     break;
	  	 case 'm':
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'n':
	  		 ldashCode();
	  		 lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  	     break;
	  	 case 'o':
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'p':
	  	     ldotCode();
	  	     lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  	     break;
	  	 case 'q':
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'r':
	  	     ldotCode();
	  	     lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  		 break;
	  	 case 's':
	  	     ldotCode();
	  	     lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  	     break;
	  	 case 't':
	  		 ldashCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'u':
	  	     ldotCode();
	  	     lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'v':
	  	     ldotCode();
	  	     lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'w':
	  	     ldotCode();
	  	     lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'x':
	  		 ldashCode();
	  		 lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'y':
	  		 ldashCode();
	  		 lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  		 break;
	  	 case 'z':
	  		 ldashCode();
	  		 lspaceCode();
	  		 ldashCode();
	  		 lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  	     ldotCode();
	  	     lspaceCode();
	  	     break;
	  	}

	  }
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(char *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
