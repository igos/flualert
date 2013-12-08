/**
 * HACKWAW #3
 * Read data form Serial.
 * @author Szymon P. Peplinski
 */
import processing.serial.*;
import com.francisli.processing.http.*;
 
HttpClient client;

Serial serialDevice1;  // Create object from Serial class
String val;      // Data received from the serial port

String hostName = "localhost";
int interval = 50;
ArrayList<String> data;

void setup() 
{
  data = new ArrayList<String>();
  
  client = new HttpClient( this, hostName );
  
  println( Serial.list() );
  
  String sensorName1 = Serial.list()[ 4 ];
  serialDevice1 = new Serial( this, sensorName1, 9600 );
  serialDevice1.clear();
}

void draw()
{
  if ( serialDevice1.available() > 0 ) // If data is available
  {
    val = serialDevice1.readStringUntil('\n');
    if( val != null )
    {
      String s = val.substring( 0, val.length() - 1 );
      //println( s );
      data.add( s );
    }
  }
  
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
    client.GET( "php/sensor.php", params );
  }
}

void responseReceived( HttpRequest request, HttpResponse response )
{
  // print the json response as a string
  println( response.getContentAsString() );
}
