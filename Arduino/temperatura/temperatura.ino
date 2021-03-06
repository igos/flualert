/**
 * HACKWAW #3
 * FluAlert
 * @author Igor Sawczuk
 *                     /-ANALOG
 *   VCC ---- Thermo -/--------- 10kOhm -- GND
 * 
 * VCC -> 5V
 * GND -> GND
 * ANALOG -> A3
 */
#include <math.h>
#define ThermistorPIN 0                 // Analog Pin 0
float pad = 9850;                       // balance/pad resistor value, set this to
                                        // the measured resistance of your pad resistor
unsigned long thermistorTime = 0;
                                        

float Thermistor(int RawADC) {
  long Resistance;  
  float Temp;
  Resistance=((1024 * pad / RawADC) - pad); 
  Temp = log(Resistance); //optymalizacja
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;
  return Temp;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  OutputTemperature();
}


void OutputTemperature() {
  if(thermistorTime + 1000 < millis()) {
    thermistorTime = millis();
    float temp;
    temp=Thermistor(analogRead(ThermistorPIN));       // odczytaj
    Serial.print("T,"); 
    Serial.print(temp,1);                             // temperatura w st.C
    Serial.println();
  }
}
