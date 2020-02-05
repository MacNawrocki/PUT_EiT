#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "LCD/ili9163lcd.h"
#include "NRF/pins.h"
extern "C" {
#include "NRF/nrf24.h"
}

ILI9163 	lcd;
DigitalPin	pinSCK(&LCD_SCK_PORT, LCD_SCK), pinSDA(&LCD_MOSI_PORT, LCD_MOSI), pinA0(&LCD_AO_PORT, LCD_AO), pinRESET(&LCD_RST_PORT, LCD_RST), pinCS(&LCD_CSS_PORT, LCD_CSS);

uint8_t data_array[4];
uint8_t tx_address[5] = {0xD7,0xD7,0xD7,0xD7,0xD7};
uint8_t rx_address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};

int readyflag = 1;
int notreadyflag = 1;
uint8_t x=0;
volatile uint16_t fullval=0;
volatile uint32_t vin=0;
volatile uint32_t small=4000;
volatile uint16_t percent=0;
volatile uint16_t wetness=0;

unsigned char rgb=250;

char intStr1[10]="00000000";	//data_array[1]
char intStr2[10]="00000000";	//data_array[2]
char intStr3[10]="0";	//data_array[3]
char intStr4[17]="0000000000000000";	//fullval bin
char intStr5[10]="0";	//fullval dec
char intStr6[10]="0";	//Vin dec
char intStr7[10]="0";	//percent dec
char intStr8[10]="0";	//wetness dec
char intStr9[10]="0";	//wetness dec

void global_clear(){
data_array[0]=0;
data_array[1]=0;
data_array[2]=0;
data_array[3]=0;
fullval=0;
vin=0;
percent=0;
intStr1[0]=0;
intStr2[0]=0;
intStr3[0]=0;
intStr4[0]=0;
intStr5[0]=0;
_delay_ms(10);
}

int main(void) {
	lcd.setup(&pinSCK, &pinSDA, &pinA0, &pinRESET, &pinCS);
	lcd.init(ILI9163::TOP);
	lcd.clear(rgb24to16(0, 0, 0));
	lcd.drawString("BOOTING", textX(1), textY(1), rgb24to16(0, 0, 0), rgb24to16(255, 255, 255));
	lcd.drawString("Received 10bit ADC", textX(1), textY(2), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
	lcd.drawString("Hbyte:", textX(1), textY(3), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
	lcd.drawString("Lbyte:", textX(1), textY(4), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
	lcd.drawString("Count:", textX(1), textY(5), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
	lcd.drawString("Bin:", textX(1), textY(6), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
	lcd.drawString("Dec:", textX(1), textY(7), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
	lcd.drawString("Calculated Vin mV", textX(1), textY(8), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
	lcd.drawString("Dec:", textX(1), textY(9), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
	lcd.drawString("Percent:", textX(1), textY(10), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
	lcd.drawString("Is the soil wet?", textX(1), textY(11), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
	lcd.drawString("XX % wet", textX(1), textY(12), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
	
	nrf24_init();
	/* Channel #2 , payload length: 4 */
	nrf24_config(2,4);
	nrf24_tx_address(tx_address);
	nrf24_rx_address(rx_address);
	nrf24_powerUpRx();
	_delay_ms(10);
	
	while(1)
	{
		if(nrf24_dataReady()){
			if(readyflag){
				lcd.drawString("Data is ready!", textX(1), textY(1), rgb24to16(0x33, 0xFF, 0x33), rgb24to16(0, 0x99, 0));
				readyflag=0;
				notreadyflag=1;
			}
			nrf24_getData(data_array);
			/*
			data_array[0] = empty
			data_array[1] = High byte of ADC
			data_array[2] = Low bite of ADC
			data_array[3] = Counter
			*/
			_delay_ms(10);
			fullval=data_array[1];
			_delay_ms(10);
			fullval=fullval<<8;
			_delay_ms(10);
			fullval|=data_array[2];
			_delay_ms(10);
			//10 bit ADC=(Vin*1024)/Vref
			//Vin=(ADC*Vref)/1024
			vin=((fullval*33000)>>10)/10;
			percent=(((vin-789)*100)/(3300-789));
			wetness=(100-percent);
			if(vin<small) small=vin;

			utoa(data_array[1], intStr1, 2);
			utoa(data_array[2], intStr2, 2);
			utoa(data_array[3], intStr3, 10);
			utoa(fullval, intStr4, 2);
			utoa(fullval, intStr5, 10);
			utoa(vin, intStr6, 10);
			utoa(percent, intStr7, 10);
			utoa(wetness, intStr8, 10);
			utoa(small, intStr9, 10);

			lcd.drawString("  ", textX(7), textY(3), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			lcd.drawString(intStr1, textX(7), textY(3), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			lcd.drawString("        ", textX(7), textY(4), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			lcd.drawString(intStr2, textX(7), textY(4), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			lcd.drawString("  ", textX(7), textY(5), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			lcd.drawString(intStr3, textX(7), textY(5), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			lcd.drawString("          ", textX(5), textY(6), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			lcd.drawString(intStr4, textX(5), textY(6), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			lcd.drawString("    ", textX(5), textY(7), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			lcd.drawString(intStr5, textX(5), textY(7), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			lcd.drawString("    ", textX(5), textY(9), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			lcd.drawString(intStr6, textX(5), textY(9), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			lcd.drawString(intStr7, textX(9), textY(10), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			if(wetness<10){
			lcd.drawString("0", textX(1), textY(12), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			lcd.drawString(intStr8, textX(2), textY(12), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			}
			else lcd.drawString(intStr8, textX(1), textY(12), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			lcd.drawString(intStr9, textX(1), textY(13), rgb24to16(255, 255, 255), rgb24to16(0,0,0) );
			
			//global_clear();		
		}
		else{
			if(notreadyflag){
				lcd.drawString("Data not ready", textX(1), textY(1), rgb24to16(0xFF, 0x33, 0x33), rgb24to16(0x99, 0, 0));
				notreadyflag=0;
				readyflag=1;
			}			
			lcd.drawChar('0' + rand()%10, textX(x%21+1), textY(15), rgb24to16(rgb,rgb,rgb), rgb24to16(0,0,0));
			lcd.drawChar('0' + rand()%10, textX(x%20), textY(0), rgb24to16(0,0,rgb), rgb24to16(0,0,0));
			lcd.drawChar('0' + rand()%10, textX(20), textY(x%15), rgb24to16(0,rgb,0), rgb24to16(0,0,0));
			lcd.drawChar('0' + rand()%10, textX(0), textY(x%16+1), rgb24to16(rgb,0,0), rgb24to16(0,0,0));
			x++;
			rgb-=25;
		}
	}
}
