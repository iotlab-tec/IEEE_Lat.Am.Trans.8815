#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include "DHT.h"
TinyGPS gps;
SoftwareSerial ss(4, 5);
#define DHTPIN 0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "..."; const char* password = "...";
String temperature; String humidity; int year;
byte month, day, hour, minute, second, hundredths;
char sz[32];
static void smartdelay(unsigned long ms);
static void print_date(TinyGPS &gps);
void setup() {
  Serial.begin(115200);
  ss.begin(9600);
  Serial.println();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status()!=WL_CONNECTED);
  dht.begin();
}
void loop() {
  float flat, flon;
  unsigned long age, date, time;
  temperature=String(dht.readTemperature());
  humidity=String(dht.readHumidity());
  gps.f_get_position(&flat, &flon, &age);
  print_date(gps);
  smartdelay(1000);
  WiFiClient client;
  const char * host = "192.168.0.94";
  const int httpPort = 80;
  if (!client.connect(host, httpPort)){ return; }
  String url = "/DATA/";
  url += "?ID=1"; url += "&Temp="; url += temperature; url += "&Hum=";
  url += humidity; url += "&Lat="; url += String(flat,6); url += "&Lon=";
  url += String(flon,6); url += "&Day="; url += day; url += "&Month=";
  url += month; url += "&Year="; url += year; url += "&Time=";
  url += String(hour) + ":" + String(minute) + ":" + String(second);
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      client.stop();
      return;
    }  }  }
static void smartdelay(unsigned long ms){
  unsigned long start = millis();
  do 
  {
    while (ss.available()){
      gps.encode(ss.read());
  } while (millis() - start < ms);
}
static void print_date(TinyGPS &gps){
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
  else
  {
    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d ",
        day, month, year, hour, minute, second);
  }}