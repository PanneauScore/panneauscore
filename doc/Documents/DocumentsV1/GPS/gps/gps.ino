
#include <SoftwareSerial.h>

#define txPin 9      //tx pin into RX GPS connection
#define rxPin 8      //rx pin into TX GPS connection

SoftwareSerial serialGps(rxPin, txPin);  // RX, TX for GPS

String time;
String flag;
String date;
String lat;
String ns;
String lon;
String ew;
String spd;
String alt;
String course;
String sats;


String readParamGps() {
  return  serialGps.readStringUntil(',');
}


bool getGps () {
  while (serialGps.read() != '$') {
    delay(1);
    //Serial.println('S');
  } //Wait for start
  String nmea = readParamGps();
  if (nmea == "GPRMC") {
    //Process a GPS recommended minimum data message.
    readParamGps(); //skip any parameters not required
    flag = readParamGps();
    lat = readParamGps();
    ns = readParamGps();
    lon = readParamGps();
    ew = readParamGps();
    spd = readParamGps();
    course = readParamGps(); //skip any parameters not required
    date = readParamGps();
  }
  if (nmea == "GPGGA") {
    //Process a GPS fix data message.
    time = readParamGps();
    readParamGps(); //skip any parameters not required
    readParamGps();
    readParamGps();
    readParamGps();
    readParamGps();
    //    fix = readParam();
    sats = readParamGps();
    readParamGps();
    alt = readParamGps();
    if (flag == "A") { //If the data is valid it is good to go
      return true;
    }
  }
  return false;
}


void printGps()
{
  Serial.print(date);
  Serial.print(",");
  Serial.print(time);
  Serial.print(",");
  Serial.print(flag);
  Serial.print(",");
  Serial.print(lat);
  Serial.print(ns);
  Serial.print(",");
  Serial.print(lon);
  Serial.print(ew);
  Serial.print(",");
  Serial.print(spd);
  Serial.print("knots,");
  Serial.print(course);
  Serial.print(" degrees,");
  Serial.print(alt);
  Serial.print("m,");
  Serial.println(sats);
}


void gpsDecimal(String longitud, String ew, String latitud, String ns)
{
  double longitude, latitude;

  longitude = longitud.substring(0, 3).toFloat() + (longitud.substring(3, 10).toFloat() / 60);
  latitude = latitud.substring(0, 2).toFloat() + (latitud.substring(2, 9).toFloat() / 60);

  if (ew.equals("W")) longitude = longitude * -1;
  if (ns.equals("S"))  latitude = latitude * -1;


  Serial.println(longitude, 5);
  Serial.println(latitude, 5);

}




void setup() {
  // put your setup code here, to run once:
  serialGps.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  if (getGps()) {
    printGps();
    gpsDecimal(lon, ew, lat, ns);
  }
}
