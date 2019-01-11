#include <FastIO.h>
//
// Running on an Arduino Pro Micro (32u4, aka Leonardo)
// Digital pin 2 is actually bit 1 of port D
// This is specified as 'pin' 0xD1 to FastIO
// 
#define SERVO_PIN 0xD1

void setup() {
  // put your setup code here, to run once:
  Fast_pinMode(SERVO_PIN, OUTPUT);
}

void pulseTrain(int iWidth_in_us, int iCount)
{
int i;
  for (i=0; i<iCount; i++)
  {
    Fast_digitalWrite(SERVO_PIN, HIGH);
    delayMicroseconds(iWidth_in_us);
    Fast_digitalWrite(SERVO_PIN, LOW);
    // Send the pulse train at around 50hz (20ms)
    delay(19);
  }
} /* pulseTrain() */

void loop() {
  // put your main code here, to run repeatedly:
int i, j;

// my particular SG90 servo seems to only recognize pulse trains of 0.5ms to 2.5ms for its full range
  pulseTrain(500, 100);
  delay(2000);
  pulseTrain(1500, 100);
  delay(2000);
  pulseTrain(2500, 100);
  delay(2000);  
}
