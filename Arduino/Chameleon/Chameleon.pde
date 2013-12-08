/**
 * HACKWAW #3
 * Read data form Serial.
 * @author Szymon P. Peplinski
 */
import processing.serial.*;
import com.francisli.processing.http.*;
 
HttpClient client;

Serial serialDevice1;  // Create object from Serial class
Serial serialDevice2;  // Create object from Serial class
Serial serialDevice3;  // Create object from Serial class

String val;      // Data received from the serial port

String hostName = "localhost";
int interval = 50;
ArrayList<String> data;

float r = 150;

void setup() 
{
  size( 700, 700 );
  stroke( #97c6e5 );
  fill( #97c6e5 );
  frameRate( 60 );
  
  data = new ArrayList<String>();
  
  client = new HttpClient( this, hostName );
  
  println( Serial.list() );
  
  String sensorName1 = Serial.list()[ 6 ];
  serialDevice1 = new Serial( this, sensorName1, 19200 );
  serialDevice1.bufferUntil(10);
  serialDevice1.clear();
  
  String sensorName2 = Serial.list()[ 8 ];
  serialDevice2 = new Serial( this, sensorName2, 19200 );
  serialDevice2.bufferUntil(10);
  serialDevice2.clear();
  
  String sensorName3 = Serial.list()[ 10 ];
  serialDevice3 = new Serial( this, sensorName3, 19200 );
  serialDevice3.bufferUntil(10);
  serialDevice3.clear();
}

void draw()
{
  background( 255 );
  ellipse( 350, 350, r, r ); 
  
  int i1 = 0;
  int i2 = 0;
  int i3 = 0;
  
  if ( serialDevice1.available() > 0 ) // If data is available
  {
    val = serialDevice1.readStringUntil('\n');
    if( val != null )
    {
      String s = val.substring( 0, val.length() - 1 );
      if( s.length() > 3 )
      {
        s = s.substring( 3 );
        i1 = int( s.charAt( 0 ) ) == 48 ? 0 : 1;
      }
    }
  }
  
  if ( serialDevice2.available() > 0 ) // If data is available
  {
    val = serialDevice2.readStringUntil('\n');
    if( val != null )
    {
      String s = val.substring( 0, val.length() - 1 );
      if( s.length() > 3 )
      {
        s = s.substring( 3 );
        i2 = int( s.charAt( 0 ) ) == 48 ? 0 : 1;
      }
    }
  }
  
  if ( serialDevice3.available() > 0 ) // If data is available
  {
    val = serialDevice3.readStringUntil('\n');
    if( val != null )
    {
      String s = val.substring( 0, val.length() - 1 );
      if( s.length() > 3 )
      {
        s = s.substring( 3 );
        i3 = int( s.charAt( 0 ) ) == 48 ? 0 : 1;
      }
    }
  }
  
  int sum = i1 + i2 + i3;
  
  if( sum == 3 )
  {
    update( 1 );
  }
  else if( sum == 1 )
  {
    update( -1 );
  }
    
  println( sum );
  
  /*
  if( data.size() > interval )
  {
    String joinedArray = "";
    for( String s : data )
    {
      joinedArray += s + ";";
    }
    
    data.clear();
    //println( joinedArray );
    
    HashMap params = new HashMap();
    params.put( "data", joinedArray );
    client.GET( "/Hackwaw/FluAlert/Backend/public/site/insert", params );
  }
  */
}

void update( int v )
{
  r = r + v * 0.1;
  r = min( r, 50 );
}

void responseReceived( HttpRequest request, HttpResponse response )
{
  // print the json response as a string
  println( response.getContentAsString() );
}