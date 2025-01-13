/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "string.h"
#include "motor.h"
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
uint8_t rxData;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1) // USART1인지 확인
    {
        switch (rxData)
        {
        case 'a': // 전진
            motor_forward();  // 모터 전진 함수 호출
            HAL_UART_Transmit(huart, (uint8_t*)"forward\r\n", strlen("forward\r\n"), HAL_MAX_DELAY);
            break;

        case 'b': // 후진
            motor_backward();  // 모터 후진 함수 호출
            HAL_UART_Transmit(huart, (uint8_t*)"backward\r\n", strlen("backward\r\n"), HAL_MAX_DELAY);
            break;

        case 'r': // 우회전
            motor_turn_right();  // 우회전 함수 호출
            HAL_UART_Transmit(huart, (uint8_t*)"turn_right\r\n", strlen("turn_right\r\n"), HAL_MAX_DELAY);
            break;

        case 'l': // 좌회전
            motor_turn_left();  // 좌회전 함수 호출
            HAL_UART_Transmit(huart, (uint8_t*)"turn_left\r\n", strlen("turn_left\r\n"), HAL_MAX_DELAY);
            break;

        case 'c': // 정지
            motor_stop();  // 정지 함수 호출
            HAL_UART_Transmit(huart, (uint8_t*)"stop\r\n", strlen("stop\r\n"), HAL_MAX_DELAY);
            break;

        case 'd': // 전원 차단
            motor_power_off();  // 전원 차단 함수 호출
            HAL_UART_Transmit(huart, (uint8_t*)"power_off\r\n", strlen("power_off\r\n"), HAL_MAX_DELAY);
            break;

        default:
            HAL_UART_Transmit(huart, (uint8_t*)"error\r\n", strlen("error\r\n"), HAL_MAX_DELAY);
            return;
        }
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//    if (huart->Instance == USART1) // USART2인지 확인
//    {
//      HAL_UART_Receive_IT(&huart1, &rxData, sizeof(rxData));
//
//        switch (rxData)
//        {
//        case 'a': // 전진
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
//            htim2.Instance->CCR1 = 300;  // 오른쪽 바퀴 속도 (느리게)
//            htim4.Instance->CCR2 = 300;
//            HAL_UART_Transmit(&huart1, (uint8_t*)"forward\r\n", strlen("forward\r\n"), 0xFFFF);
//
//            break;
//
//        case 'b': // 후진
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
//            htim2.Instance->CCR1 = 300;  // 오른쪽 바퀴 속도 (느리게)
//            htim4.Instance->CCR2 = 300;
//            HAL_UART_Transmit(&huart1, (uint8_t*)"backward\r\n", strlen("backward\r\n"), 0xFFFF);
//
//            break;
//
//        case 'r': // 우회전
//                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);   // 오른쪽 바퀴 후진
//                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
//                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);   // 왼쪽 바퀴 전진
//                    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
//                    htim2.Instance->CCR1 = 300;  // 오른쪽 바퀴 속도 (느리게)
//                    htim4.Instance->CCR2 = 700;  // 왼쪽 바퀴 속도 (빠르게)
//                    HAL_UART_Transmit(&huart1, (uint8_t*)"turn_right\r\n", strlen("turn_right\r\n"), 0xFFFF);
//                    break;
//
//        case 'l': // 좌회전
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);   // 오른쪽 바퀴 전진
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET); // 왼쪽 바퀴 후진
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
//            htim2.Instance->CCR1 = 700;  // 오른쪽 바퀴 속도 (빠르게)
//            htim4.Instance->CCR2 = 300;  // 왼쪽 바퀴 속도 (느리게)
//            HAL_UART_Transmit(&huart1, (uint8_t*)"turn_left\r\n", strlen("turn_left\r\n"), 0xFFFF);
//            break;
//
//        case 'c': // 정지
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_SET);
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_SET);
//            HAL_UART_Transmit(&huart1, (uint8_t*)"stop\r\n", strlen("stop\r\n"), 0xFFFF);
//
//            break;
//
//        case 'd': // 전원 차단
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_2, GPIO_PIN_RESET);
//            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, GPIO_PIN_RESET);
//            HAL_UART_Transmit(&huart1, (uint8_t*)"power_off\r\n", strlen("power_off\r\n"), 0xFFFF);
//
//            break;
//
//        default:
//          HAL_UART_Transmit(&huart1, (uint8_t*)"error\r\n", strlen("error\r\n"), 0xFFFF);
//            return;
//        }

        // 다음 데이터를 계속 수신하기 위해 인터럽트 재설정
        HAL_UART_Receive_IT(&huart1, &rxData, sizeof(rxData));

    }
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


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
  MX_USART1_UART_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, &rxData, sizeof(rxData));

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 100;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
