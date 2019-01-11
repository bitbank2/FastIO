FastIO<br>
Project started 1/9/2019<br>
Copyright (c) 2019 BitBank Software, Inc.<br>
Written by Larry Bank<br>
bitbank@pobox.com<br>
<br>
Faster replacement for accessing digital pins on Arduino AVR MCUs
The digital I/O functions provided by the Arduino core library are much
slower than they can be due to pin number translation, boundary checking
and ensuring that ports are accessed while interrupts are disabled. For
most projects, all of these precautions are not necessary and this allows
code which calls the FastIO functions to generate much faster signals.
The standard digital pin numbers of each Arduino board map to different
port addresses depending on the chipset in use. FastIO changes the pin
numbering to be based on the AVR port and not the virtual I/O pin.
The pin numbers are specified as port (B/C/D/E/F/G) plus bit
For example, on the ATmega32u4 (Leonardo / Pro Micro), digital pin 2
is actually bit 1 of port D. To access that pin with the FastIO library
you would specify pin number 0xD1.<br>

Features:<br>
---------<br>
- Supports fast access to digital ports on all AVR microcontrollers<br>
- pinMode, digitalRead and digitalWrite work the same as the originals<br>
- Repeated accesses to the same pin number only require a few clock cycles<br>
<br>

