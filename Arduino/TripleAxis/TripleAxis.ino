/**
 * HACKWAW #3
 * FluAlert
 * @author Szymon P. Peplinski
 *
 * HMC5883L -> Arduino Uno
 * VCC -> 3.3V
 * GND -> GND
 * SCL -> A5
 * SDA -> A4
 */

// Reference the I2C Library
#include <Wire.h>

// Reference the HMC5883L Compass Library
#include <HMC5883L.h>

// Store our compass as a variable.
HMC5883L compass;

// Record any errors that may occur in the compass.
int error = 0;

// Out setup routine, here we will configure the microcontroller and compass.
void setup()
{
  // Initialize the serial port.
  Serial.begin( 19200 );

  // Start the I2C interface.
  Wire.begin();

  // Construct a new HMC5883 compass.
  compass = HMC5883L();
  
  // Set the scale of the compass.
  error = compass.SetScale(1.3);
  
  // Set the measurement mode to Continuous
  error = compass.SetMeasurementMode(Measurement_Continuous);
}

// Our main program loop.
void loop()
{
  // Retrived the scaled values from the compass (scaled to the configured scale).
  MagnetometerScaled scaled = compass.ReadScaledAxis();

  // Output the data via the serial port.
  Output( scaled );

  // Normally we would delay the application by 66ms to allow the loop
  // to run at 15Hz (default bandwidth for the HMC5883L).
  // However since we have a long serial out (104ms at 9600) we will let
  // it run at its natural speed.
  // delay( 66 );
}

// Output the data down the serial port.
void Output(MagnetometerScaled scaled)
{
  Serial.print( "A4" );
  Serial.print( "," );   
  Serial.print( scaled.XAxis );
  Serial.print( "," );
  Serial.print( scaled.YAxis );
  Serial.print( "," );
  Serial.print( scaled.ZAxis );
  Serial.println();
}
