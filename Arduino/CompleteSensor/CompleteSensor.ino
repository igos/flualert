/* BEGIN:  Axis sensor - Header */
// Reference the I2C Library
#include <Wire.h>
// Reference the HMC5883L Compass Library
#include <HMC5883L.h>
// Store our compass as a variable.
HMC5883L compass;
// Record any errors that may occur in the compass.
int error = 0;
/* END:  Axis sensor - Header */

/* BEGIN:  Temperature sensor - Header */
#include <math.h>
#define ThermistorPIN 0
float pad = 9850;
unsigned long thermistorTime = 0;
/* END:  Temperature sensor - Header */


/* BEGIN:  HearRate Sensor - Header */
int pulseSensor = A2;
int pulse = 0;
int counter = 0;

long timeBegin = millis();
long timeEnd = millis()+(15*1000);
/* END:  HearRate Sensor - Header */

void setup()
{
    
    Serial.begin(9600);
    /* BEGIN:  Axis sensor - Setup */
    // Start the I2C interface.
    Wire.begin();
    
    // Construct a new HMC5883 compass.
    compass = HMC5883L();
    
    // Set the scale of the compass.
    error = compass.SetScale(1.3);
    
    // Set the measurement mode to Continuous
    error = compass.SetMeasurementMode(Measurement_Continuous);
    /* BEGIN:  Axis sensor - Setup */
    
    /* BEGIN:  HearRate Sensor - Setup */
    timeEnd = millis()+(15*1000);
    /* END:  HearRate Sensor - Setup */
    
}


void loop() {
    
    
    /* BEGIN:  Axis sensor - loop */
    /*MagnetometerScaled scaled = compass.ReadScaledAxis();
    Output( scaled );*/
    /* END:  Axis sensor - loop */
    
    /* BEGIN:  Temperature Sensor - loop */
    OutputTemperature();
    /* END:  Temperature Sensor - loop */
    
    /* BEGIN:  HeartRate Sensor - loop */
    getPulse();
    /* END:  HeartRate Sensor - loop */
    
    
}


/* BEGIN:  Axis sensor - functions */
// Output the data down the serial port.
void Output(MagnetometerScaled scaled)
{
    
    Serial.print( "A" );
    Serial.print( "," );
    Serial.print( scaled.XAxis );
    Serial.print( "," );
    Serial.print( scaled.YAxis );
    Serial.print( "," );
    Serial.print( scaled.ZAxis );
    Serial.println();
    
}

/* END:  Axis sensor - functions */

/* BEGIN:  HearRate sensor - functions */
/*Function: calculate the heart rate*/
void getPulse() {
    
    int sensorValue = analogRead(pulseSensor);
    
    if(sensorValue == 0) {        
        pulse = 0;        
    }
    
    
    if(sensorValue > 400 && pulse == 0) {
        
        if(millis() >= timeEnd) {
            
            OutputHeartRate(counter*4);
            counter = 0;
            timeEnd = millis()+(15*1000);
            
        }
        else {
            
            counter++;
            
        }
        
        //Serial.print('.');
        pulse = 1;
        
    }
    
    
    //doTone();
    
}

void OutputHeartRate(int heartRate) {
    
    Serial.print( "H," );
    Serial.print( heartRate );
    Serial.println();
    
}

/* END:  HearRate sensor - functions */

/* BEGIN:  Temperature sensor - functions */
void OutputTemperature() {
    
    if(thermistorTime + 1000 < millis()) {
        
        thermistorTime = millis();
        float temp;
        temp = Thermistor(analogRead(ThermistorPIN));       // odczytaj
        Serial.print("T,");
        Serial.print(temp,1);                             // temperatura w st.C
        Serial.println();
        
    }
    
    
}

float Thermistor(int RawADC) {
    
    long Resistance;
    float Temp;
    Resistance = ((1024 * pad / RawADC) - pad);
    Temp = log(Resistance); //optymalizacja
    Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
    Temp = Temp - 273.15;
    return Temp;
    
}

/* END:  Temperature sensor - functions */
