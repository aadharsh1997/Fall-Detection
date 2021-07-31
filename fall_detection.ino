#include <SoftwareSerial.h>
#include <TinyGPS++.h>

SoftwareSerial gsmports(6, 5);
SoftwareSerial gpsports(4, 7);

TinyGPSPlus gps;

//float latitude=12.9910147;
//float longitude=77.7273623;

int power=A5;
int gnd=A1;
int x=A4;
int y=A3;
int z=A2;
int valx=0;
int valy=0;
int valz=0;
float out=0;
int x1,x2,y1,y2,z1,z2;
double lat_val,lng_val;
volatile float minutes, seconds;
volatile int degree, secs, mins;
int buzzer=13;
int gnd2=12;

void setup() {
   Serial.begin(9600);
   pinMode(gnd, OUTPUT);
   pinMode(power, OUTPUT);
   digitalWrite(gnd, LOW);
   digitalWrite(power, HIGH);
   pinMode(gnd2, OUTPUT);
   pinMode(buzzer, OUTPUT);
   digitalWrite(gnd2, LOW);
   digitalWrite(buzzer,LOW);
   while(!Serial);
   gsmports.begin(9600);
   gpsports.begin(9600);

}

void loop() {

  float reading1=fallread();
  //Serial.println(reading1);
  //Serial.print(reading1);
  if(reading1<=0.8){
    while(1){
       float reading2=fallread();
       //Serial.println(reading2);
       if(reading2>2.45){
        Serial.println("fallen");
        digitalWrite(buzzer,HIGH);
        //gpsportscall();
        gsmcall(lat_val,lng_val);
       break;
    }
  }
 }  

  //Serial.print(x1);
  //Serial.print("\t");
  //Serial.print(y1);
  //Serial.print("\t");
  //Serial.print(z1);
  //Serial.println("\t");
  delay(10);

}

float fallread(){
   valx=analogRead(x);
   valy=analogRead(y);
   valz=analogRead(z);

  
   x1=(((valx*3.3)/1024)-1.5)/0.33;
   y1=(((valy*3.3)/1024)-1.5)/0.33;
   z1=(((valz*3.3)/1024)-1.5)/0.33;

   out=sqrt(sq(x1)+sq(y1)+sq(z1));
   //Serial.print("out= ");
   //Serial.println(out);
   return(out);
}

void gpsportscall(){
        smartdelay(1000); /* Generate precise delay of 1ms */
        unsigned long start;
        //double lat_val, lng_val, alt_m_val;
        uint8_t hr_val, min_val, sec_val;
        bool loc_valid, alt_valid, time_valid;
        lat_val = gps.location.lat(); /* Get latitude data */
        loc_valid = gps.location.isValid(); /* Check if valid location data is available */
        lng_val = gps.location.lng(); /* Get longtitude data */
        //alt_m_val = gps.altitude.meters();  /* Get altitude data in meters */
        alt_valid = gps.altitude.isValid(); /* Check if valid altitude data is available */
        hr_val = gps.time.hour(); /* Get hour */
        min_val = gps.time.minute();  /* Get minutes */
        sec_val = gps.time.second();  /* Get seconds */
        time_valid = gps.time.isValid();  /* Check if valid time data is available */
        /*if (!loc_valid)
        {          
        }*/
        //else
        //{
          DegMinSec(lat_val);
          Serial.println(lat_val);
          Serial.println(lng_val);
          
          
              
            
          //}
          /* Convert the decimal degree value into degrees minutes seconds form */
                    
        }


static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (gpsports.available())  /* Encode data read from gpsports while data is available on serial port */
      gps.encode(gpsports.read());
/* Encode basically is used to parse the string received by the gpsports and to store it in a buffer so that information can be extracted from it */
  } while (millis() - start < ms);
}

void DegMinSec( float tot_val)   /* Convert data in decimal degrees into degrees minutes seconds form */
{  
  degree = (int)tot_val;
  minutes = tot_val - degree;
  seconds = 60 * minutes;
  minutes = (int)seconds;
  mins = (int)minutes;
  seconds = seconds - minutes;
  seconds = 60 * seconds;
  secs = (int)seconds;
}

void gsmcall(float latitude,float longitude){
  gsmports.write("AT+CMGF=1\r\n");
  delay(1000);
 
  //Send new SMS command and message number
  gsmports.write("AT+CMGS=\"+918197237472\"\r\n");
  delay(1000);
   
  //Send SMS content
  gsmports.print("Hi, a fall has occured. Find spot using link: http://maps.google.com/maps?q=loc:");
  gsmports.print(latitude,7);
  gsmports.print(",");
  gsmports.print(longitude,7);
  //delay(1000);
   
  //Send Ctrl+Z / ESC to denote SMS message is complete
  gsmports.write((char)26);
  //delay(1000);

  Serial.println("SMS sent");
}
