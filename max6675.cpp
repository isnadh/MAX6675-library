// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple
// corrected by me: engineerscookbook191@gmail.com

#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif
#include <util/delay.h>
#include <stdlib.h>
#include "max6675.h"

MAX6675::MAX6675(int8_t SCLK, int8_t CS, int8_t MISO) 
{
  sclk = SCLK;
  cs = CS;
  miso = MISO;

  //define pin modes
  pinMode(cs, OUTPUT);
  pinMode(sclk, OUTPUT); 
  pinMode(miso, INPUT);

  digitalWrite(cs, HIGH);
}


double MAX6675::readCelsius(void) 
{

  uint16_t v;

//digitalWrite(cs, LOW);_delay_ms(1);digitalWrite(cs,HIGH);_delay_ms(220);


_delay_ms(220);
digitalWrite(cs, LOW);

  v = spiread();
  v <<= 8;
  v |= spiread();

  digitalWrite(cs, HIGH);

  if (v & 0x4) 
  {
    return NAN;// uh oh, no thermocouple attached! 
    //return -100;
  }

  v >>= 3;

  return v*0.25;
}


double MAX6675::readFahrenheit(void) 
{
  return readCelsius() * 9.0/5.0 + 32;
}


byte MAX6675::spiread(void) 
{ 
  int i;byte d = 0;

  for (i=7; i>=0; i--)
  {
    delayMicroseconds(100);
    digitalWrite(sclk, HIGH);  //its HIGH not LOW as with ladyada library
    delayMicroseconds(100);
    if (digitalRead(miso)) 
    { 
      d |= (1 << i);//set the bit to 0 no matter what 
    }
    digitalWrite(sclk, LOW);//its LOW not HIGH as with ladyada library  
  }   

  return d;  
}

