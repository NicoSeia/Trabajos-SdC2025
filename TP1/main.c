

#include "stm32f1xx.h"

void SystemClock_Config(void);
void GPIO_Init(void);
void custom_delay(void);

int main(void) {
    HAL_Init();           // Initialize the HAL Library
    SystemClock_Config(); // Set system clock to 8 MHz
    GPIO_Init();          // Initialize GPIO for LED

    while (1) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // Toggle LED
        custom_delay();                       // Wait 10 seconds
    }
}

void GPIO_Init(void) {
    __HAL_RCC_GPIOC_CLK_ENABLE(); // Enable GPIOC clock

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // Push-Pull Output
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

void SystemClock_Config(void) {



	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	//----------Código que configura el clock en 8MHz----------

	/**
	// Configure the HSI oscillator (8 MHz)
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	HAL_RCC_OscConfig(&RCC_OscInitStruct);

	// Configure system clock
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
	                               RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
	HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);

	*/


	//  ----------Código que configura el clock en 16MHz----------

	// Enable HSI (8 MHz) and configure PLL to achieve 16 MHz system clock
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2; // HSI (8MHz) / 2 = 4 MHz input
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;              // 4 MHz * 4 = 16 MHz

	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		while (1); // Error handling: Stay here if initialization fails
	}

	// Configure the CPU clock
	RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
	                                   RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		while (1); // Error handling
	}


}


// delay de 10s (aprox) para 8MHz / 5s para 16MHz
void custom_delay(void){

    for(volatile int i=0;i<7000000;i++);

    return;
}
