#ifndef PINS_H_
#define PINS_H_

/*
Connection:
ATMega328PB	PIN	To
PB3	to	MOSI		programator/radio
PB4	to	MISO		programator/radio
PB5	to	SCK			programator/radio
PB6	to	CSN			radio
PB7	to	CE			radio
PC0	to	LCD_RST		wyœwietlacz
PC1	to	LCD_AO		wyœwietlacz
PC2	to	LCD_MOSI	wyœwietlacz
PC3	to	LCD_SCK		wyœwietlacz
PC4	to	LED			dioda na p³ytce
PC6	to	RESET		programator/radio
PD0	to	RX
PD1	to	TX
PD2	to	BUTTON1		guzik na p³ytce
PE3	to	LCD_CS		wyœwietlacz
*/ 

#define BIT(x)				1<<(x)
#define SET_BIT(x, y)		(x) |= (BIT(y))
#define CLEAR_BIT(x, y)		(x) &= (~(BIT(y)))
#define SET_OUTPUT(pin)		(pin ## _DDR)|=_BV(pin)
#define SET_INPUT(pin)		CLEAR_BIT((pin ## _DDR),(pin))
#define SET_HIGH(pin)		(pin ## _PORT)|=_BV(pin)
#define SET_LOW(pin)		(pin ## _PORT)&=!_BV(pin)

#define MOSI PB3
#define MOSI_DDR DDRB
#define MOSI_PORT PORTB

#define MISO PB4
#define MISO_DDR DDRB
#define MISO_PORT PORTB
#define MISO_PIN  PINB


#define SCK PB5
#define SCK_DDR DDRB
#define SCK_PORT PORTB

#define CSN PB6
#define CSN_DDR DDRB
#define CSN_PORT PORTB

#define CE PB7
#define CE_DDR DDRB
#define CE_PORT PORTB

#define LCD_RST PC0
#define LCD_RST_DDR DDRC
#define LCD_RST_PORT PORTC

#define LCD_AO PC1
#define LCD_AO_DDR DDRC
#define LCD_AO_PORT PORTC

#define LCD_MOSI PC2
#define LCD_MOSI_DDR DDRC
#define LCD_MOSI_PORT PORTC

#define LCD_SCK PC3
#define LCD_SCK_DDR DDRC
#define LCD_SCK_PORT PORTC

#define LED PC4
#define LED_DDR DDRC
#define LED_PORT PORTC

#define BUTTON PD2
#define BUTTON_DDR DDRD
#define BUTTON_PORT PORTD

#define LCD_CSS PE3
#define LCD_CSS_DDR DDRE
#define LCD_CSS_PORT PORTE

#endif /* PINS_H_ */