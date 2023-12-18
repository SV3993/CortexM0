#include "stm32g071xx.h"

void LCD_init (void);

void LCD_cmd (unsigned int comd); void LCD_disp (unsigned char char1);

void msdelay (uint32_t value);

int main (void)

{

  unsigned char msg1 [16] = "Dept of EC"; unsigned char msg2 [16] ="SVNIT";
  
  uint8_t j; LCD_init ();
  
  // Initialize LCD
  
  LCD_cmd (0x38); // 8-bit mode, 2 line, 5x7 dots LCD_cmd (0x0E); // display on, cursor on
  
  LCD_cmd (0x06);
  
  // auto increment cursor
  
  LCD_cmd (0x01); // clear display screen LCD_cmd (0x80);
  
  for (j=0; j<16; ++j) LCD_disp (msg1[j]); LCD_cmd (0xC0);
  
  for (j=0; j<16; ++j)
  
  LCD_disp (msg2[j]);
}

void LCD_init (void) {

  // Enable clock for Port A and B RCC->IOPENR |= RCC_IOPENR_GPIOAEN; RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
  
  // set pin 5,6 and 7 of port A as output mode (pull-push)
  
  GPIOA->MODER &= 0xFFFF03FF; GPIOA->MODER |= 0x00005400;
  
  GPIOA->OTYPER &= 0xFFFFFF1F;
  
  // clear required field
  
  // set required bits
  
  // use pull-push type
  
  GPIOB->PUPDR &= 0xFFFF03FF; // No pull up, no pull down
  
  // set pins 0 to 7 of port B as output
  
  GPIOB->MODER &= 0xFFFF0000;
  
  GPIOB->MODER |= 0x00005555;
  
  GPIOB->OTYPER &= 0xFFFFFF00;
  
  // clear required field
  
  // set required bits
  
  // use pull-push type
  
  GPIOB->PUPDR &= 0xFFFF0000; // No pull up, no pull down 
  GPIOA->ODR = GPIOA->ODR & 0xFFBF; //PA6 (R/W) low
} 

void LCD_cmd (unsigned int comd) { 
  GPIOB->ODR = GPIOBODR & 0xFF00;
  
  GPIOB->ODR = GPIOB->ODR | comd; // send command GPIOA->ODR = GPIOA ODR & 0xFF7F; // RS-0 on pin PA7
  
  msdelay(1);
  
  GPIOA ODR = GPIOA->ODR| 0x0020; // EN=1 on pin PA5 GPIOA->ODR = GPIOA->ODR & 0xFFDF; // EN=0 on pin PA5
  
  msdelay (50);
  
}
  
void LCD_disp (unsigned char chart) {
  
  GPIOB->ODR = GPIOB->ODR & 0xFF00; GPIOB->ODR = GPIOB->ODR | char1; GPIOA->ODR = GPIOA>ODR & 0x0080; // send ascii code // RS=1 on pin PA7
  
  GPIOA->ODR = GPIOA->ODR| 0x0020; // EN=1 on pin PA5
  
  msdelay(1);
  
  GPIOA->ODR = GPIOA->ODR & 0xFFDF; // EN=0 on pin PA5 msdelay (50);
}

void msdelay (uint32_t value) {
  long int loops;long int loops;
  
  loops = 850 value*4; while (loops--) {}

loops = 850 value*4; while (loops--) {}
}
