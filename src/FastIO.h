#ifndef __FASTIO_H__
#define __FASTIO_H__

//
// Faster replacement for accessing digital pins on Arduino AVR MCUs
// The digital I/O functions provided by the Arduino core library are much
// slower than they can be due to pin number translation, boundary checking
// and ensuring that ports are accessed while interrupts are disabled. For
// most projects, all of these precautions are not necessary and this allows
// code which calls the FastIO functions to generate much faster signals.
// The standard digital pin numbers of each Arduino board map to different
// port addresses depending on the chipset in use. FastIO changes the pin
// numbering to be based on the AVR port and not the virtual I/O pin.
// The pin numbers are specified as port (B/C/D/E/F/G) plus bit
// For example, on the ATmega32u4 (Leonardo / Pro Micro), digital pin 2
// is actually bit 1 of port D. To access that pin with the FastIO library
// you would specify pin number 0xD1. For port G on the ATmega128, use
// pin numbers 0xA0 through 0xA7.
//
void Fast_pinMode(uint8_t iPin, uint8_t iMode);
void Fast_digitalWrite(uint8_t iPin, uint8_t iValue);
uint8_t Fast_digitalRead(uint8_t iPin);

#endif // __FASTIO_H__

