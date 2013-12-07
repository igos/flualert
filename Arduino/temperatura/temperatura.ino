#include <math.h>
#define ThermistorPIN 0                 // Analog Pin 0
float pad = 9850;                       // balance/pad resistor value, set this to
                                        // the measured resistance of your pad resistor
float thermr = 10000;                   // nomilana rezystancja thermistor

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
  float temp;
  temp=Thermistor(analogRead(ThermistorPIN));       // odczytaj
  Serial.print("Celsius: "); 
  Serial.print(temp,1);                             // temperatura w st.C
  Serial.println("");                                   
  delay(500);
}
