/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "fatfs.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fatfs_sd.h"
#include "string.h"
#include "stdio.h"
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

/******************************** SD CARD VARIABLES ********************************/
FATFS fs;  // file system
FIL fil;  // file
FRESULT fresult;  // to store the result
char buffer[1024]; // to store data
char To_Open[1024];
UINT br, bw;   // file read/write count

/* capacity related variables */
FATFS *pfs;
DWORD fre_clust;
uint32_t total, free_space;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

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
  MX_USART2_UART_Init();
  MX_FATFS_Init();
  MX_SPI2_Init();
  /* USER CODE BEGIN 2 */
  /* Mount SD Card */
  	fresult = f_mount(&fs, "", 0);
  	//if (fresult != FR_OK)
  		//send_uart("error in mounting SD CARD, check connection...\n");
  	//else
  		//send_uart("SD CARD mounted successfully...\n");

  	/*************** Card capacity details ********************/
  	/* Check free space */
  	f_getfree("", &fre_clust, &pfs);
  	total = (uint32_t) ((pfs->n_fatent - 2) * pfs->csize * 0.5);
  	if (total < 32000000) {
  		sprintf(buffer, "SD CARD Total Size: \t%lu\n", total);
  		//send_uart(buffer);
  		bufclear();
  		free_space = (uint32_t) (fre_clust * pfs->csize * 0.5);
  		sprintf(buffer, "SD CARD Free Space: \t%lu\n", free_space);
  		//send_uart(buffer);
  	} else {
  		//send_uart("ERROR: can't read SD CARD, check SD...\n");

  	}

  	/************* The following operation is using PUTS and GETS *********************/

  	/* Open file to write/ create a file if it doesn't exist */
  	strcpy(To_Open,"file1.txt");
  	if( f_open(&fil, To_Open, FA_OPEN_ALWAYS | FA_READ | FA_WRITE) != FR_OK ) {
  		char error [1024];
  		strcpy(error,"ERROR: can't open ");
  		strcat(error, To_Open);
  		strcat(error, "\n\n");
  		//send_uart(error);
  	}

  	/* Read string from the file */
  		while (f_gets(buffer, sizeof(buffer), &fil)) {
  			/* SWV output */
  		//	send_uart(buffer);
  			fflush(stdout);
  		}

  	/* Writing text */
  	fresult = f_lseek(&fil, fil.fptr);
  	fresult = f_puts("Hello World!\n", &fil);

  	/* Close file */
  	f_close(&fil);

  	bufclear();

  	/**************** The following operation is using f_write and f_read **************************/

  	/* Create second file with read write access and open it */
  	fresult = f_open(&fil, "file2.txt", FA_OPEN_ALWAYS | FA_READ | FA_WRITE);

  	/* Writing text */
  	strcpy(buffer, "This is File 2 and it says Hello from controllerstech\n");
  	fresult = f_write(&fil, buffer, bufsize(buffer), &bw);

  	//send_uart("File2.txt created and data is written\n");

  	/* Close file */
  	f_close(&fil);

  	// clearing buffer to show that result obtained is from the file
  	bufclear();

  	/* Open second file to read */
  	fresult = f_open(&fil, "file2.txt", FA_READ);

  	/* Read data from the file
  	 * Please see the function details for the arguments */
  	while (f_gets(buffer, sizeof(buffer), &fil)) {
  		/* SWV output */
  	//	send_uart(buffer);
  		fflush(stdout);
  	}

  	/* Close file */
  	f_close(&fil);
  	bufclear();

  	/************************REMOVING FILES FROM THE DIRECTORY ****************************/
  	fresult = f_unlink("/file1.txt");
  	if (fresult == FR_OK)// send_uart("file1.txt removed successfully...\n");

  	/* Unmount SDCARD */
  	fresult = f_mount(NULL, "", 1);
  	if (fresult == FR_OK)
  		//send_uart("SD CARD UNMOUNTED successfully...\n");

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
/* to find the size of data in the buffer */
int bufsize(char *buf) {
	int i = 0;
	while (*buf++ != '\0')
		i++;
	return i;
}

/*Clear the buffer*/
void bufclear(void)  {
	for (int i = 0; i < 1024; i++) {
		buffer[i] = '\0';
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
