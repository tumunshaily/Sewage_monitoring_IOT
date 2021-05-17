#include <ETH.h>
#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiSTA.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

long duration; int distance; int limit; int value;
#include <FirebaseESP32.h>
#include "FirebaseESP32.h"
#include <SD.h>
#include <String.h>
#define WIFI_SSID "Get_set"
#define WIFI_PASSWORD "shiva123"
#define FIREBASE_HOST "sewage-monitor-system.firebaseio.com"
#define FIREBASE_AUTH "tv9iUWSUKmK0H8EkwBMaG1TSVpBx5s5Z8Sx4WMjx"
#define PIN_TRIGGER 32
#define PIN_ECHO  36
#define DOUTpin  35
#define AOUTpin  39
FirebaseData firebaseData;
FirebaseJsonArray arr1;
FirebaseJsonArray arr2;
FirebaseJsonArray arr11;
FirebaseJsonArray arr22;
String path = "/Values";
String pathl="/type1";
void setup() {
Serial.begin (9600);
pinMode (PIN_TRIGGER, OUTPUT);
pinMode (PIN_ECHO, INPUT);
pinMode(DOUTpin, INPUT);
Serial.println("Setup..."); Serial.begin (9600) ;
WiFi.begin (WIFI_SSID, WIFI_PASSWORD) ;
Serial.print ("Connecting to Wi-F1");
 while (WiFi.status() != WL_CONNECTED) {
     Serial.print (".");
     delay (300);}
 Serial.println();
 Serial.print("Connected ");
 Serial.println (WiFi.localIP());
 Serial.println();
Firebase.begin (FIREBASE_HOST, FIREBASE_AUTH);
Firebase.reconnectWiFi(true);
Firebase.setReadTimeout(firebaseData, 1000*60);
Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
void loop () {
digitalWrite(PIN_TRIGGER, LOW); 
delayMicroseconds (2);
digitalWrite (PIN_TRIGGER, HIGH);
delayMicroseconds (10);
digitalWrite(PIN_TRIGGER, LOW);
  arr1.clear();
 arr2.clear();
duration = pulseIn(PIN_ECHO, HIGH);
distance= duration*0.1498/2;
value= analogRead(AOUTpin);
limit= digitalRead (DOUTpin);
arr1.set(0,distance);
arr2.set(0,value);
Serial.print("distance: ");
Serial.println (distance);
String waterlevel = String (distance);
Serial.print(" methane value: ");
Serial.println(value);
String methane = String (value);
Serial.print(" limit: ");
Serial.println(limit);
delay (4000);
arr11.add (arr1);
arr22.add (arr2);
Firebase.set(firebaseData, path + "/level", arr11);
Firebase.set(firebaseData, path + "/gas", arr22);
}
