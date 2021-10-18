//#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
//#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
//#include <ESP8266HTTPClient.h>
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11
#define FIREBASE_HOST "smartbro-b07ee.firebaseio.com"
#define FIREBASE_AUTH "2BPtxbEZK2B3cqNO97DHBk9Xa2iElhr78vYoR1R5"
#define WIFI_SSID "Robotics and Automation Center"
#define WIFI_PASSWORD "qlkywvtj"
 
String stringH;
String stringT;
String stringS;
DHT dht(DHTPIN, DHTTYPE);
void setup()
{
  Serial.begin(9600);
  pinMode(D0,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED)
      {
    Serial.print(".");
    delay(500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  dht.begin();
  pinMode(A0,INPUT);
 
}
 
void loop()
{
  delay(1000);
  int soil_value = analogRead(A0);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print(F("The Humidity is: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.println(t);
  Serial.print("Soil value: ");
  Serial.println(soil_value);
stringH = String(h);
stringT = String(t);
stringS  = String(soil_value);
Firebase.setString("Humidity/Value",stringH);
Firebase.setString("Temperature/Value",stringT);
Firebase.setString("Soil moisture value/Value",stringS);
delay(1000);            
}
