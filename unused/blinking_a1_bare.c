#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

void GPIO_Init(void) {
    __HAL_RCC_GPIOA_CLK_ENABLE();  // Enable GPIOA clock

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_1;  // Pin 1
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // Output push-pull mode
    GPIO_InitStruct.Pull = GPIO_NOPULL;  // No pull-up or pull-down
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;  // Low speed
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);  // Initialize GPIOA Pin 5
}

void Toggle_LED(void) {
    // HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_1);  // Toggle Pin 1
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);  // Set Pin 1
    // HAL_Delay(100);  // Delay for 500 ms
    for(volatile uint32_t i = 0; i < 1000000; i++) {};  // Simple delay loop
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);  // Reset Pin 1
    for(volatile uint32_t i = 0; i < 1000000; i++) {};  // Simple delay loop
    // HAL_Delay(100);  // Delay for 500 ms
}

int main(void) {
    // HAL_Init();  // Initialize the HAL Library
    // GPIO_Init();  // Initialize GPIO

    // while (1) {
    //     Toggle_LED();  // Toggle the LED
    //     // HAL_Delay(500);  // Delay for 500 ms
    // }

  // 1. Enable GPIOA clock (STM32F4 uses AHB1, not APB2 like F1)
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    
  // 2. Configure PA1 as push-pull output (STM32F4 uses MODER/OTYPER/OSPEEDR)
  GPIOA->MODER   &= ~(0x3 << (1 * 2));       // Clear mode bits for PA1
  GPIOA->MODER   |=  (0x1 << (1 * 2));       // Set PA1 as output (01)
  GPIOA->OTYPER  &= ~(0x1 << 1);             // Push-pull (0)
  GPIOA->OSPEEDR |=  (0x2 << (1 * 2));       // Medium speed (10)
  GPIOA->PUPDR   &= ~(0x3 << (1 * 2));       // No pull-up/pull-down (00)

  while (1) {
      GPIOA->ODR ^= (1 << 1);                // Toggle PA1
      for (volatile uint32_t i = 0; i < 1000000; i++); // Longer delay for F4's higher clock
  }
}