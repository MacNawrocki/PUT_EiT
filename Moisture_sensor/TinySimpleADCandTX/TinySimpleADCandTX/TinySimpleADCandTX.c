/*
Connection:
ATTiny84 PIN To 
1         To +3.3V
2  [PB0]  To XTAL1      (kwarc-nieu?ywany)
3  [PB1]  To XTAL2      (kwarc-nieu?ywany)
4  [PB3]  To RESET      (USBasp)
5  [PB2]  To GEN        (czujnik)
6  [PA7]  To ZAS_RADIO  (nRF24L01)
7  [PA6]  To MOSI       (nRF24L01)&(USBasp)
8  [PA5]  To MISO       (nRF24L01)&(USBasp)
9  [PA4]  To SCK        (nRF24L01)&(USBasp)
10 [PA3]  To CE	        (nRF24L01)
11 [PA2]  To CSN        (nRF24L01)
12 [PA1]  To pinHL      (czujnik)
13 [PA0]  To czujnik    (czujnik)
14        To GND
 */ 

//#define F_CPU 10000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include <stdint.h>
#include "nrf24.h"
#include "pins.h"

volatile uint16_t input_voltage;
volatile uint8_t hbyte=0; 
volatile uint8_t lbyte=0;
uint8_t q = 0;
uint8_t data_array[4];
uint8_t tx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};
uint8_t rx_address[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};


uint16_t measure_ADC_input(){
	  ADMUX =
	  (0 << REFS1) |     // Sets ref. voltage to VCC, bit 1
	  (0 << REFS0) |     // Sets ref. voltage to VCC, bit 0
	  (0 << MUX5)  |     // use ADC0 for input (PA0), MUX bit 5
	  (0 << MUX4)  |     // use ADC0 for input (PA0), MUX bit 4
	  (0 << MUX3)  |     // use ADC0 for input (PA0), MUX bit 3
	  (0 << MUX2)  |     // use ADC0 for input (PA0), MUX bit 2
	  (0 << MUX1)  |     // use ADC0 for input (PA0), MUX bit 1
	  (0 << MUX0);       // use ADC0 for input (PA0), MUX bit 0
	  //ADCSRA – ADC Control and Status Register A
	  ADCSRA =
	  (1 << ADEN)  |     // Enable ADC
	  (0 << ADPS2) |     // set prescaler to 8, bit 2
	  (1 << ADPS1) |     // set prescaler to 8, bit 1
	  (1 << ADPS0);      // set prescaler to 8, bit 0
	ADCSRB = 0;
    _delay_ms(10);
	
	//ADC Start Conversion
    ADCSRA |= (1<<ADSC);
    while((ADCSRA & (1<<ADSC)))// wait till conversion complete 
        {
        }
	//ADC disable
    ADCSRA = 0;
	//10 bit value stored in ADC
    return ADC; // ADC=(Vin*1024)/Vref
}

void nrf24_basic_send(){
		nrf24_powerUpTx();
		_delay_ms(10);
		nrf24_send(data_array);
		while(nrf24_isSending());
		nrf24_powerDown();
		_delay_ms(10);
}

int main(void) {
    nrf24_init();
    nrf24_config(2,4);
	nrf24_tx_address(tx_address);
	nrf24_rx_address(rx_address);
	nrf24_powerDown();
	SET_OUTPUT(GEN);
	SET_LOW(GEN);
	SET_OUTPUT(PINHL);
	SET_HIGH(PINHL);

	_delay_ms(10);
	while(1)
	{
			input_voltage = measure_ADC_input();
	        //input_voltage = 0x88ff;
			hbyte=input_voltage >> 8;
			lbyte=input_voltage & 0x00ff;
			_delay_ms(10);
			/*
			data_array[0] = empty
			data_array[1] = High byte of ADC
			data_array[2] = Low bite of ADC
			data_array[3] = Counter
			*/
			data_array[0] = 0;
			data_array[1] = hbyte;
			data_array[2] = lbyte;
			data_array[3] = q;
			_delay_ms(10);
			nrf24_basic_send();
			q++;
			input_voltage=0;
			hbyte=0;
			lbyte=0;
			_delay_ms(1000);
	}
}
