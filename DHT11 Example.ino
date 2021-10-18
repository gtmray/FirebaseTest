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
#define WIFI_SSID "KR"
#define WIFI_PASSWORD "kapilrohit"
 
String stringH;
String stringT;

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
    delay(1500);
      }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  dht.begin();
 
}
 
void loop()
{
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
stringH = String(h);
stringT = String(t);
Firebase.setString("Humidity/Value",stringH);
Firebase.setString("Temperature/Value",stringT);
delay(900);
delay(500);
}
