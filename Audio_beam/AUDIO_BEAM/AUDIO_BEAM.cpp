//#ifndef F_CPU
//#define F_CPU 16000000UL
//#endif

#include <avr/io.h>
#include <math.h>
//#include <util/delay.h> 

//Chip Select 0
#define CSEL0 PA0
#define CSEL0_DDR	DDRA
#define CSEL0_PORT PORTA
//Chip Select 1
#define CSEL1 PA1
#define CSEL1_DDR	DDRA
#define CSEL1_PORT PORTA
//Chip Select 2
#define CSEL2 PA2
#define CSEL2_DDR	DDRA
#define CSEL2_PORT PORTA
//Chip Select 3
#define CSEL3 PA3
#define CSEL3_DDR	DDRA
#define CSEL3_PORT PORTA
//Chip Select 4
#define CSEL4 PA4
#define CSEL4_DDR	DDRA
#define CSEL4_PORT PORTA
//Chip Select 5
#define CSEL5 PA5
#define CSEL5_DDR	DDRA
#define CSEL5_PORT PORTA
//Chip Select 6
#define CSEL6 PA6
#define CSEL6_DDR	DDRA
#define CSEL6_PORT PORTA
//Chip Select 7
#define CSEL7 PA7
#define CSEL7_DDR	DDRA
#define CSEL7_PORT PORTA
//Chip Select 8
#define CSEL8 PC7
#define CSEL8_DDR	DDRC
#define CSEL8_PORT PORTC
//Chip Select 9
#define CSEL9 PC6
#define CSEL9_DDR	DDRC
#define CSEL9_PORT PORTC
//Chip Select 10
#define CSEL10 PC5
#define CSEL10_DDR	DDRC
#define CSEL10_PORT PORTC
//Chip Select 11
#define CSEL11 PC4
#define CSEL11_DDR	DDRC
#define CSEL11_PORT PORTC
//Chip Select 12
#define CSEL12 PC3
#define CSEL12_DDR	DDRC
#define CSEL12_PORT PORTC
//Chip Select 13
#define CSEL13 PC2
#define CSEL13_DDR	DDRC
#define CSEL13_PORT PORTC
//Chip Select 14
#define CSEL14 PC1
#define CSEL14_DDR	DDRC
#define CSEL14_PORT PORTC
//Chip Select 15
#define CSEL15 PC0
#define CSEL15_DDR	DDRC
#define CSEL15_PORT PORTC
//SCK do Software SPI
#define SCK PB3
#define SCK_DDR	DDRB
#define SCK_PORT PORTB
//SDATA do Software SPI
#define SDATA PB2
#define SDATA_DDR DDRB
#define SDATA_PORT PORTB
//CLK jako Fmclk czyli sygnał zegarowy referencyjny
#define CLK PB0
#define CLK_DDR DDRB
#define CLK_PORT PORTB

//Funkcje Software SPI 
//#define SET_INPUT(pin)			((pin ## _DDR) &= !_BV(pin) )
//#define SET_OUTPUT(ddr, pin)		(ddr |= (1<<pin))
#define SET_HIGH(pin)				((pin ## _PORT) |= _BV(pin))
#define SET_LOW(pin)				((pin ## _PORT) &= !_BV(pin))

#define TABSIZE 16
uint32_t phaseArray[TABSIZE];
//Czestotliwość fmclk - do przeliczania czestotliwosci oraz podawana na linii CLK
const float freqRef = 158000; 
uint16_t CalcPhase (uint32_t phase);
uint32_t CalcFreq(uint32_t freq);
void SPIconfig();
void SPIrefresh();
inline void SPIsend(uint16_t data); 
inline void SetAllCS_Low();
inline void SetAllCS_High();
void CalcPhaseVal(uint32_t freq, uint32_t dist);

//funkcja oblicza opóźnienia fazowe dla każdego generatora
void CalcPhaseVal(uint32_t freq, uint32_t dist)
{
	uint32_t spacing = 0.0725;//m    
    uint32_t speedSound = 343.0;// m/s
    uint32_t distxTab[TABSIZE];
    uint32_t maxdistx = spacing*7;
    for (int i = 0; i<TABSIZE; i++){
        if (i<7)distxTab[i]=(maxdistx-i*spacing)+spacing/2;
        if (i == 7)distxTab[i]=spacing/2;
        if (i == 8)distxTab[i]=spacing/2;
        if (i>8) distxTab[i]=spacing/2 + (i-8)*spacing;
    }
    uint32_t distRealTab[TABSIZE];
    for (int i = 0; i<TABSIZE; i++){
        distRealTab[i]=sqrt(pow(distxTab[i],2)+pow(dist,2));
    }
    uint32_t delayTab[TABSIZE];
    uint32_t delayzero=distRealTab[7]*speedSound;
    for (int i = 0; i<TABSIZE; i++){
        delayTab[i]=(distRealTab[i]*speedSound)-delayzero;
        phaseArray[i] = (1 - ((delayTab[i]/(1/freq))-floor((delayTab[i]/(1/freq)))))*2*3.14159265358979;
    }
}

//funkcja przelicza częstotliwość w Hz na dane do generatora
uint32_t CalcFreq(uint32_t freq)
{
	//f = fMCLK/2^28 × FREQREG
	float freqRes = 0x10000000;
	float stepSize;
	stepSize = freqRes/freqRef;
	
	uint32_t freqWord;
	freqWord = stepSize*freq;
	return freqWord;
}

//funkcja przelicza fazę na dane do generatora, faza podana w radianach
uint16_t CalcPhase (uint32_t phase)
{
	//2π/4096 × PHASEREG
	float phaseRes; 
	phaseRes = 4096/(2*3.14159265358979);
	uint16_t phaseWord;
	phaseWord = phase*phaseRes;
	return phaseWord;
}

//Konfiguracja pinów i ich rejestrów do SPI
void SPIconfig() 
{
	SCK_DDR|=1<<3; // SET_OUTPUT(SCK_DDR, SCK);
	SDATA_DDR|=1<<2; // SET_OUTPUT(SDATA_DDR,SDATA);
	//Rejestr DDR portu A zapełniony 1 - piny CSel0-7
	DDRA = 0b11111111;
	//Rejestr DDR portu C zapełniony 1 - piny CSel8-15
	DDRC = 0b11111111;
	SET_HIGH(SCK);
	SET_HIGH(SDATA);
	//Stan wysoki wszystkich FSYNC 
	PORTA = 0b11111111;
	PORTC = 0b11111111;
}

//Ustanowienie domyślnych wartości na portach SPI
void SPIrefresh()
{
	//Stan wysoki wszystkich FSYNC 
	PORTA = 0b11111111;
	PORTC = 0b11111111;
	SET_LOW(SDATA);
	SET_HIGH(SCK);
}

//Stan niski wszystkich FSYNC - dane odbierają wszystkie generatory
inline void SetAllCS_Low()
{
	PORTA = 0b00000000;
	PORTC = 0b00000000;
}

//Stan wysoki wszystkich FSYNC 
inline void SetAllCS_High()
{
	PORTA = 0b11111111;
	PORTC = 0b11111111;
}

//Funkcja software'owo realizuje komunikacje SPI - wysyła jeden wyraz
inline void SPIsend(uint16_t data) 
{
	for(uint16_t mask= 0x8000; mask; mask>>=1) 
	{
		SET_HIGH(SCK);
		if(data & mask) SET_HIGH(SDATA);
		else SET_LOW(SDATA);
		SET_LOW(SCK);
	}
}



int main(void)
{ 
	uint32_t freq = 5000; // częstotliwość generowanych sygnałów w Hz
	uint32_t dist = 2; // odległość punktu wzmocnienia sygnału od środka wektora głośników w m
	
	//kalkulowanie częstotliwości
	uint32_t freqWord = CalcFreq(freq);
	//wielkosc przesylanych danych do rejestru częstotliwości to 2 x 14 bit
	uint16_t freqWordMSB;
	uint16_t freqWordLSB;
	freqWordMSB = (int)((freqWord & 0xFFFC000)>>14);
	freqWordLSB = (int)(freqWord & 0x3FFF);
	//bity D15 i D14 - 01 wybierają rejestr FREQ0
	//freqWordLSB |= 0x4000;
	//freqWordMSB |= 0x4000; 
	freqWordLSB |= 0x4FFF;
	freqWordMSB |= 0x4FFF;
	
	//kalkulowanie fazy
	//wielkość przesyłanych danych do rejestru fazy to 12 bit 
	CalcPhaseVal(freq, dist);
	uint16_t phaseWordArray[TABSIZE];
	for (int i = 0; i<TABSIZE; i++){
        phaseWordArray[i]=CalcPhase(phaseArray[i]);
		//bity D15, D14, D13- 110 wybierają rejestr PHASE0
		phaseWordArray[i]|= 0xC000;
    }
	
	uint16_t initWord = 0x2100;	// bity D13 i D8 - zapis danych i RESET=1
	// RESET=0, bity D11 i  D10 = 00 - rejsestry FREQ0 i PHASE0
	uint16_t resetWordSin = 0x2000; // wyjście to sin
	uint16_t resetWordSqr = 0x2020; // wyjście to prostokąt
	uint16_t resetWordTri = 0x2002; // wyjście to trójkąt
	
	SPIconfig();
	
	//Podanie do wszystkich generatorów informacji o częstotliwości i RESET = 1
	//SetAllCS_Low();
	SET_LOW(CSEL0);	
	SPIsend(initWord); 
	SET_HIGH(CSEL0);
	//SetAllCS_High();
	SPIrefresh();
	SetAllCS_Low();	
	SPIsend(freqWordLSB);
	SetAllCS_High();
	SPIrefresh();
	SetAllCS_Low();	
	SPIsend(freqWordMSB);
	SetAllCS_High();
	SPIrefresh();
	
	/*
	//podanie do Generatora 0 informacji o fazie
	SET_LOW(CSEL0);
	SPIsend(phaseWordArray[0]);
	SET_HIGH(CSEL0);
	SPIrefresh();
	//podanie do Generatora 1 informacji o fazie
	SET_LOW(CSEL1);
	SPIsend(phaseWordArray[1]);
	SET_HIGH(CSEL1);
	SPIrefresh();
	//podanie do Generatora 2 informacji o fazie
	SET_LOW(CSEL2);
	SPIsend(phaseWordArray[2]);
	SET_HIGH(CSEL2);
	SPIrefresh();
	//podanie do Generatora 3 informacji o fazie
	SET_LOW(CSEL3);
	SPIsend(phaseWordArray[3]);
	SET_HIGH(CSEL3);
	SPIrefresh();
	//podanie do Generatora 4 informacji o fazie
	SET_LOW(CSEL4);
	SPIsend(phaseWordArray[4]);
	SET_HIGH(CSEL4);
	SPIrefresh();
	//podanie do Generatora 5 informacji o fazie
	SET_LOW(CSEL5);
	SPIsend(phaseWordArray[5]);
	SET_HIGH(CSEL5);
	SPIrefresh();
	//podanie do Generatora 6 informacji o fazie
	SET_LOW(CSEL6);
	SPIsend(phaseWordArray[6]);
	SET_HIGH(CSEL6);
	SPIrefresh();
	//podanie do Generatora 7 informacji o fazie
	SET_LOW(CSEL7);
	SPIsend(phaseWordArray[7]);
	SET_HIGH(CSEL7);
	SPIrefresh();
	//podanie do Generatora 8 informacji o fazie
	SET_LOW(CSEL8);
	SPIsend(phaseWordArray[8]);
	SET_HIGH(CSEL8);
	SPIrefresh();
	//podanie do Generatora 9 informacji o fazie
	SET_LOW(CSEL9);
	SPIsend(phaseWordArray[9]);
	SET_HIGH(CSEL9);
	SPIrefresh();
	//podanie do Generatora 10 informacji o fazie
	SET_LOW(CSEL10);
	SPIsend(phaseWordArray[10]);
	SET_HIGH(CSEL10);
	SPIrefresh();
	//podanie do Generatora 11 informacji o fazie
	SET_LOW(CSEL11);
	SPIsend(phaseWordArray[11]);
	SET_HIGH(CSEL11);
	SPIrefresh();
	//podanie do Generatora 12 informacji o fazie
	SET_LOW(CSEL12);
	SPIsend(phaseWordArray[12]);
	SET_HIGH(CSEL12);
	SPIrefresh();
	//podanie do Generatora 13 informacji o fazie
	SET_LOW(CSEL13);
	SPIsend(phaseWordArray[13]);
	SET_HIGH(CSEL13);
	//podanie do Generatora 14 informacji o fazie
	SET_LOW(CSEL14);
	SPIsend(phaseWordArray[14]);
	SET_HIGH(CSEL14);
	SPIrefresh();
	//podanie do Generatora 15 informacji o fazie
	SET_LOW(CSEL15);
	SPIsend(phaseWordArray[15]);
	SET_HIGH(CSEL15);	*/
	SPIrefresh();

	//Podanie do wszystkich generatorów informacji o trybie pracy i RESET = 0
	SetAllCS_Low();
	SPIsend(resetWordSin); 
	SetAllCS_High();
	
	//Po podaniu danych do generatorów uruchamiany jest generator CLK
	//CLK generowane tą metodą ma częstotliwość 158 kHz
	CLK_DDR|=1; // SET_OUTPUT(CLK_DDR, CLK);
	while(1)
    {
		SET_HIGH(CLK);
		SET_LOW(CLK);	
	}
	
}
