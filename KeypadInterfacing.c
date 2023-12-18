#include "stm32g071xx.h"

#define KEYPAD_PORT GPIOA
#define ROWS_PIN_MASK 0x0F
#define COLS_PIN_MASK 0xF0

// Function prototypes
void delay_ms(uint32_t ms);
char readKeypad();

int main(void) {
    // Enable GPIOA clock
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;

    // Configure keypad rows as inputs (PA0-PA3)
    KEYPAD_PORT->MODER &= ~(GPIO_MODER_MODE0_Msk | GPIO_MODER_MODE1_Msk | GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk);

    // Configure keypad columns as outputs (PA4-PA7)
    KEYPAD_PORT->MODER |= (GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0);

    while (1) {
        char key = readKeypad();

        if (key != '\0') {
            // Key pressed, perform action based on the key
            // Example: Toggle an LED based on the key
            GPIOB->ODR ^= (1 << 0); // Toggle LED on GPIOB Pin 0
        }
    }
}

char readKeypad() {
    // Scan rows
    for (int row = 0; row < 4; row++) {
        // Drive the current row low
        KEYPAD_PORT->ODR &= ~(1 << row);

        // Read columns
        uint8_t columns = (KEYPAD_PORT->IDR & COLS_PIN_MASK) >> 4;

        // Wait for debounce delay
        delay_ms(10);

        // Check if any key is pressed
        if ((KEYPAD_PORT->IDR & COLS_PIN_MASK) != COLS_PIN_MASK) {
            // Key pressed, determine the pressed key
            for (int col = 0; col < 4; col++) {
                if (!(columns & (1 << col))) {
                    // Key pressed, return the corresponding character
                    return '1' + (row * 4) + col;
                }
            }
        }

        // Disable the current row
        KEYPAD_PORT->ODR |= (1 << row);
    }

    // No key pressed
    return '\0';
}

void delay_ms(uint32_t ms) {
    // Simple delay function (for demonstration purposes)
    for (volatile uint32_t i = 0; i < ms * 8000; i++) {
        // Adjust the loop count for your specific clock frequency
    }
}
