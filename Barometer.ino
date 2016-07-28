/*
Barometer BMP180
 Auteur		: Henk Siewert
 Datum		: 28 juli 2016
 Sensor		: Bosch BMP180
 Versie		: 01
 MCU		: Atmel ATMega328
 Language	: Arduino C++
 Compiler	: Arduino 1.6.10
 Editor		: NotePad++
 Systeem	: Windows XP Pro SP3
 WWW		: http://www.swtcomp.com

Aansluitingen
SDA naar Pin 27 = A4
SCL naar Pin 28 = A5
*/

#include <Wire.h>		    // I2C bibliotheek
#include <SWTBMP180.h>	    // BMP180 bibliotheek

SWTBMP180 pressure;

void setup()
{
  Serial.begin(9600);       // Start seriele communicatie
  pressure.begin();
}

void loop()
{
  double P = getPressure();	// Haal een nieuwe waarde op
  Serial.print( P,1 );
  Serial.print( "," );      // Separator for Python graphics
  Serial.println ( 0 );     // Dummy for Python graphics
  delay(1000);				// Wait 1 second
}

double getPressure()
{
  char status;
  double T,P;

  // You must first get a temperature measurement to perform a pressure reading.
  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(3);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P, T);
        if (status != 0)
        {
          return(P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}
