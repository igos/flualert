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
  #define LED 4//indicator, Grove - LED is connected with D4 of Arduino
  boolean led_state = LOW;
  unsigned char counter;
  unsigned long temp[21];
  unsigned long sub;
  bool data_effect=true;
  unsigned int heart_rate;//the measurement result of heart rate
  const int max_heartpluse_duty = 2000;
/* END:  HearRate Sensor - Header */

void setup()
{
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
        pinMode(LED, OUTPUT);
	Serial.begin(9600);
	Serial.println("Please ready your chest belt.");
	delay(5000);
	arrayInit();
	Serial.println("Heart rate test begin.");
	attachInterrupt(0, interrupt, RISING);//set interrupt 0,digital port 2
/* END:  HearRate Sensor - Setup */
}

void loop() {
/* BEGIN:  Axis sensor - loop */
  MagnetometerScaled scaled = compass.ReadScaledAxis();
  Output( scaled );
/* END:  Axis sensor - loop */
  
/* BEGIN:  Temperature Sensor - loop */
  OutputTemperature();
/* END:  Temperature Sensor - loop */
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
void sum()
{
 if(data_effect)
    {
      heart_rate=1200000/(temp[20]-temp[0]);//60*20*1000/20_total_time 
      Serial.print("Heart_rate_is:\t");
      //Serial.println(heart_rate);
      OutputHeartRate(heart_rate);
    }
   data_effect=1;//sign bit
}
/*Function: Interrupt service routine.Get the sigal from the external interrupt*/
void interrupt()
{
    temp[counter]=millis();
	//Serial.println(counter,DEC);
    //Serial.println(temp[counter]);
    switch(counter)
	{
		case 0:
			sub=temp[counter]-temp[20];
			Serial.print(".");
			break;
		default:
			sub=temp[counter]-temp[counter-1];
			Serial.print(".");
			break;
	}
    if(sub>max_heartpluse_duty)//set 2 seconds as max heart pluse duty
	{
		data_effect=0;//sign bit
		counter=0;
		Serial.println("Heart rate measure error,test will restart!" );
		arrayInit();
	}
    if (counter==20&&data_effect)
    {
		counter=0;
		sum();
    }
    else if(counter!=20&&data_effect)
    counter++;
    else 
    {
		counter=0;
		data_effect=1;
    }
    
}
/*Function: Initialization for the array(temp)*/
void arrayInit()
{
	for(unsigned char i=0;i < 20;i ++)
	{
		temp[i]=0;
	}
	temp[20]=millis();
}

void OutputHeartRate(int heartRate) {
   Serial.print("H,");
   Serial.print(heartRate);
   Serial.println();  
}
/* END:  HearRate sensor - functions */

/* BEGIN:  Temperature sensor - functions */
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
float Thermistor(int RawADC) {
  long Resistance;  
  float Temp;
  Resistance=((1024 * pad / RawADC) - pad); 
  Temp = log(Resistance); //optymalizacja
  Temp = 1 / (0.001129148 + (0.000234125 * Temp) + (0.0000000876741 * Temp * Temp * Temp));
  Temp = Temp - 273.15;
  return Temp;
}
/* END:  Temperature sensor - functions */
