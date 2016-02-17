
#include <max6675.h>

int thermoDO = 28;
int thermoCS = 30;  
int thermoCLK = 29;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);
void setup()  
{
 Serial.begin(9600);  
}


void loop() 
{  
 Serial.print("Temp:  ");
 Serial.print(thermocouple.readCelsius()); Serial.print(char(223)); Serial.print("C  ");
 Serial.print(thermocouple.readFahrenheit());Serial.print(char(223)); Serial.println("F");
 delay(2);
}
