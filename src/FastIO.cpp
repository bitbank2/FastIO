//
// FastIO Library
// Copyright (c) 2019 BitBank Software, Inc.
// Written by Larry Bank (bitbank@pobox.com)
// Project started 1/9/2019
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#include <Arduino.h>
#include <FastIO.h>

#ifdef __AVR__
volatile uint8_t *iDDR, *iPort;
static uint8_t iPin, iLastPin, iBit;

//
// Private function to convert our pin number into the correct port and bit
//
static uint8_t getPinInfo(uint8_t pin, volatile uint8_t **iDDR, volatile uint8_t **iPort, int bInput)
{
  uint8_t port, bit;

  port = (pin & 0xf0); // hex port (A,B,D,E,F)
  pin &= 0xf;
  if (pin > 7) // invalid bit number (valid values -> 0 through 7 only)
     return 255;
  bit = 1<<(pin & 0x7);

  switch (port)
  {
#ifdef PORTE
    case 0xE0:
      *iPort = (bInput) ? &PINE : &PORTE;
      *iDDR = &DDRE;
      break;
#endif
#ifdef PORTF
    case 0xF0:
      *iPort = (bInput) ? &PINF : &PORTF;
      *iDDR = &DDRF;
      break;
#endif
#ifdef PORTG
    case 0xA0: // really port G
      *iPort = (bInput) ? &PING : &PORTG;
      *iDDR = &DDRG;
      break;
#endif
#ifdef PORTC
    case 0xC0:
      *iPort = (bInput) ? &PINC : &PORTC;
      *iDDR = &DDRC;
      break;
#endif
#ifdef PORTB
    case 0xB0:
      *iPort = (bInput) ? &PINB : &PORTB;
      *iDDR = &DDRB;
      break;
#endif
#ifdef PORTD
    case 0xD0:
      *iPort = (bInput) ? &PIND : &PORTD;
      *iDDR = &DDRD;
      break;
#endif
    default: // invalid pin for this architecture
      *iPort = NULL;
      *iDDR = NULL;
      bit = 255;
      break;
  }
  return bit;
} /* getPinInfo() */

//
// Set the pin mode and configure the internal variables for this pin
//
void Fast_pinMode(uint8_t iPin, uint8_t iMode)
{
  iLastPin = iPin;
  switch (iMode)
  {
     case OUTPUT:
        iBit = getPinInfo(iPin, &iDDR, &iPort, 0);
	if (iBit != 255)
	{
        	*iDDR |= iBit;
	}
        break;
     case INPUT:
        iBit = getPinInfo(iPin, &iDDR, &iPort, 1);
	if (iBit != 255)
	{
        	*iDDR &= ~iBit;
	}
        break;
     case INPUT_PULLUP:
        iBit = getPinInfo(iPin, &iDDR, &iPort, 0); // set as output first
	if (iBit != 255)
	{
        	*iDDR |= iBit;
        	*iPort |= iBit; // and set the output to high
        	getPinInfo(iPin, &iDDR, &iPort, 1); // then set to input
        	*iDDR &= ~iBit;
	}
        break;
    } // switch
} /* Fast_pinMode() */

//
// Write a single bit to a digital port
//
void Fast_digitalWrite(uint8_t iPin, uint8_t iValue)
{
    if (iPin != iLastPin)
    {
       iBit = getPinInfo(iPin, &iDDR, &iPort, 0);
       if (iBit == 255) // invalid pin
          return;
       iLastPin = iPin;
    }
    if (iValue)
       *iPort |= iBit;
    else
       *iPort &= ~iBit;

} /* Fast_digitalWrite() */

//
// Read a single bit from a port
//
uint8_t Fast_digitalRead(uint8_t iPin)
{
    if (iPin != iLastPin)
    {
       iBit = getPinInfo(iPin, &iDDR, &iPort, 1);
       if (iBit == 255) // invalid pin
          return LOW;
       iLastPin = iPin;
    }
    if (*iPort & iBit)
       return HIGH;
    else
       return LOW;

} /* Fast_digitalRead() */
#else
#error This library only works on AVR microcontrollers
#endif // __AVR__
