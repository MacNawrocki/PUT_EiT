#ifndef PINS_H_
#define PINS_H_

/*
Connection:
ATTiny84 PIN To 
1         To +3.3V
2  [PB0]  To XTAL1      (kwarc-nieu¿ywany)
3  [PB1]  To XTAL2      (kwarc-nieu¿ywany)
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

#define BIT(x)				1<<(x)
#define SET_BIT(x, y)		(x) |= (BIT(y))
#define CLEAR_BIT(x, y)		(x) &= (~(BIT(y)))
#define SET_OUTPUT(pin)		(pin ## _DDR)|=_BV(pin)
#define SET_INPUT(pin)		CLEAR_BIT((pin ## _DDR),(pin))
#define SET_HIGH(pin)		(pin ## _PORT)|=_BV(pin)
#define SET_LOW(pin)		(pin ## _PORT)&=!_BV(pin)
#define IS_LOW(pin)			!((pin ## _PIN) & _BV(pin))
#define IS_HIGH(pin)		((pin ## _PIN) & _BV(pin))

//Generator - obecnie dioda LED
#define GEN PB2
#define GEN_DDR	DDRB
#define GEN_PORT PORTB
//Zasilanie radia - bramka MOSFETa
#define ZASRAD PA7
#define ZASRAD_DDR DDRA
#define ZASRAD_PORT PORTA
//MOSI
#define MOSI PA6
#define MOSI_DDR DDRA
#define MOSI_PORT PORTA
//MISO
#define MISO PA5
#define MISO_DDR DDRA
#define MISO_PORT PORTA
#define MISO_PIN PINA
//SCK
#define SCK PA4
#define SCK_DDR DDRA
#define SCK_PORT PORTA
//CE
#define CE PA3
#define CE_DDR DDRA
#define CE_PORT PORTA
//CSN
#define CSN PA2
#define CSN_DDR DDRA
#define CSN_PORT PORTA
//Czujnik
#define CZUJ PA0
#define CZUJ_DDR DDRA
#define CZUJ_PORT PORTA
#define CZUJ_PCINT PCINT0 
#define CZUJ_PIN PINA


//Generator - obecnie dioda LED
#define PINHL PA1
#define PINHL_DDR	DDRA
#define PINHL_PORT PORTA

#endif /* PINS_H_ */