/**
 * HACKWAW #3
 * Read data form Serial.
 * @author Szymon P. Peplinski
 */
import processing.serial.*;

int inByte = 10;    // Linefeed in ASCII
String myString = null;
Serial myPort;  // The serial port

void setup()
{
  // List all the available serial ports
  println( Serial.list() );
  
  // Open the port you are using at the rate you want:
  myPort = new Serial( this, Serial.list()[ 2 ], 9600 );
  myPort.clear();
  
  // Throw out the first reading, in case we started reading 
  // in the middle of a string from the sender.
  byte temp[] = myPort.readBytesUntil( inByte );
  if( temp == null ) 
  {
    myString = null;
  }
  else
  {
    myString = new String( temp );
  }
  
  myString = null;
}

void draw()
{
  while( myPort.available() > 0 )
  {
    byte temp[] = myPort.readBytesUntil( inByte );
    if( temp == null ) 
    {
      myString = null;
    }
    else
    {
      myString = new String( temp );
    }
    
    if( myString != null )
    {
      println( myString );
    }
  }
}
