/*
* ----------------------------------------------------------------------------
* “THE COFFEEWARE LICENSE” (Revision 1):
* <ihsan@kehribar.me> wrote this file. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a coffee in return.
* -----------------------------------------------------------------------------
* Please define your platform spesific functions in this file ...
* -----------------------------------------------------------------------------
*/

#define set_bit(reg,bit) reg |= (1<<bit)
#define clr_bit(reg,bit) reg &= ~(1<<bit)
#define check_bit(reg,bit) (reg&(1<<bit))

#include <avr/io.h>
#include "pins.h"

/* ------------------------------------------------------------------------- */
void nrf24_setupPins()
{
    set_bit(CE_DDR,CE);			// CE output
    set_bit(CSN_DDR,CSN);		// CSN output
    set_bit(SCK_DDR,SCK);		// SCK output
    set_bit(MOSI_DDR,MOSI);		// MOSI output
    clr_bit(MISO_DDR,MISO);		// MISO input
}
/* ------------------------------------------------------------------------- */
void nrf24_ce_digitalWrite(uint8_t state)	//CE
{
    if(state)
    {
        set_bit(CE_PORT,CE);
    }
    else
    {
        clr_bit(CE_PORT,CE);
    }
}
/* ------------------------------------------------------------------------- */
void nrf24_csn_digitalWrite(uint8_t state)	//CSN
{
    if(state)
    {
        set_bit(CSN_PORT,CSN);
    }
    else
    {
        clr_bit(CSN_PORT,CSN);
    }
}
/* ------------------------------------------------------------------------- */
void nrf24_sck_digitalWrite(uint8_t state)	//SCK
{
    if(state)
    {
        set_bit(SCK_PORT,SCK);
    }
    else
    {
        clr_bit(SCK_PORT,SCK);
    }
}
/* ------------------------------------------------------------------------- */
void nrf24_mosi_digitalWrite(uint8_t state)	//MOSI
{
    if(state)
    {
        set_bit(MOSI_PORT,MOSI);
    }
    else
    {
        clr_bit(MOSI_PORT,MOSI);
    }
}
/* ------------------------------------------------------------------------- */
uint8_t nrf24_miso_digitalRead()			//MISO
{
    return check_bit(MISO_PIN,MISO);
}
/* ------------------------------------------------------------------------- */
