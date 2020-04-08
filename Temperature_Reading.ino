#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#include <stdlib.h>

int  in1, in2, in3;

//Initializing the ADC module
void ADC_init(void){
    
    ADMUX |= (1 << REFS0); //• Select AVCC as the reference voltage. 
    ADCSRA |= (1 << ADEN); // Enable ADC
    ADSCRA |= (1 << ADCSP2) | (0 << ADCSP1) | (1 << ADCSP0); //• Enable ADC clock prescaler 32
    ADSCRA |= ~(1 << ADIE); //• Disable ADC Interrupt
  }

  //Reading input from analog port
  uint16_t readADC (uint8_t channel){
    
      ADMUX = (0b01000000 & ADMUX) | channel;
      ADMUX = ~(1 << ADLAR); //• ADC result is right justified.
      ADCSRA |= (1 << ADSC); // Start the ADC conversion

      while (ADCSRA & (1<<ADSC)) {};

      return (ADC);
    }


    int main (void){
        DDRD |= (1 << PD3);

        while(1){
          
            in1 = readADC(0);
            in2 = readADC(1);
            in3 = readADC(2);


//The if statement below checks the values of the three sensors. If none are equal, then the LED on port 3 pin 3 will turn on.
            if ((in1 != in2) || (in1 != in3) || (in2 != in3)){
               
                PORTD = 0x04;
              
              }

              else {
                PORTD = 0x00;
                }
          }
        return 0;
      }
