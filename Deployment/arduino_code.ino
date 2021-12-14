/*
 * HTTPS Secured Client POST Request
 * Copyright (c) 2019, circuits4you.com
 * All rights reserved.
 * https://circuits4you.com 
 * Connects to WiFi HotSpot. */

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h> 
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>


#include "DHT.h"
#define DHTPIN 0 //dht 11 sensor D3

const int ledPin = 16; 
const int ledPinRed = 5;
const int ldrPin = A0;  
String home="false";

#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);
/* Set these to your desired credentials. */
const char *ssid = "yusuf";  //ENTER YOUR WIFI SETTINGS
const char *password = "helloworld101";

//Link to read data from https://jsonplaceholder.typicode.com/comments?postId=7
//Web/Server address to read/write from 
const char *host = "group7iot.com";
const int httpsPort = 1880;  //HTTPS= 443 and HTTP = 80

//SHA1 finger print of certificate use web browser to view and copy
const char fingerprint[] PROGMEM = "46 79 F1 3D 16 80 01 69 F2 30 E1 5E 24 B9 B6 E0 73 9E F5 6A";
//=======================================================================
//                    Power on setup
//=======================================================================

void setup() {
  delay(1000);
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
  pinMode(ledPinRed, OUTPUT);
  dht.begin();

  
  WiFi.mode(WIFI_OFF);        //Prevents reconnection issue (taking too long to connect)
  delay(1000);
  WiFi.mode(WIFI_STA);        //Only Station No AP, This line hides the viewing of ESP as wifi hotspot
  
  WiFi.begin(ssid, password);     //Connect to your WiFi router
  Serial.println("");

  Serial.print("Connecting");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  //If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //IP address assigned to your ESP
  

}

//=======================================================================
//                    Main Program Loop
//=======================================================================
void loop() {
  WiFiClientSecure httpsClient;    //Declare object of class WiFiClient

  Serial.println(host);

  Serial.printf("Using fingerprint '%s'\n", fingerprint);
  httpsClient.setFingerprint(fingerprint);
  httpsClient.setTimeout(15000); // 15 Seconds
  delay(10000);
  
  Serial.print("HTTPS Connecting");
  int r=0; //retry counter
  while((!httpsClient.connect(host, httpsPort)) && (r < 30)){
      delay(100);
      Serial.print(".");
      r++;
  }
  if(r==30) {
    Serial.println("Connection failed");
  }
  else {
    Serial.println("Connected to web");
  }
  
  String getData, Link;
  
  //POST Data
  Link = "/publish/conditions/";

  Serial.print("requesting URL: ");
  Serial.println(host);
  /*
   POST /post HTTP/1.1
   Host: postman-echo.com
   Content-Type: application/x-www-form-urlencoded
   Content-Length: 13
  
   say=Hi&to=Mom
    
   */
   float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  int ldrStatus = analogRead(ldrPin);
  
  
  Serial.println(ldrStatus);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C \n"));
  Serial.println(ldrStatus);
  if(ldrStatus>800){
    home = "true";
    }
   else{
    home="false";
    }
    

    
  //case: temp is too high and someone is home
    if(t>25.0 && ldrStatus>500){
      digitalWrite(ledPin, HIGH);
      digitalWrite(ledPinRed, LOW);
      }
      //case: temp is too low and someone is home
    if(t<25.0 && ldrStatus>500){
      digitalWrite(ledPinRed, HIGH);
      digitalWrite(ledPin, LOW);
      }

      String string1 = "temperature=";
    String string2 = String(t);
    String string3 = "&humidity=";
    String string4 = String(h);
    String string5 = "&home=";
    String string6 = home;
    
    
    String string7 = String(string1 + string2);
    String string8 = String(string7+ string3);
    String string9 = String(string8+ string4);
    String string10 = String(string9+ string5);
    String string11 = String(string10+string6);

    Serial.println(home);

    
  
  int len = string11.length();
  
  httpsClient.print(String("POST ") + Link + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded"+ "\r\n" +
               "Content-Length: " +len + "\r\n\r\n" +
               string11 + "\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("request sent");
                  
  while (httpsClient.connected()) {
    String line = httpsClient.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }

  Serial.println("reply was:");
  Serial.println("==========");
  String line;
  while(httpsClient.available()){        
    line = httpsClient.readStringUntil('\n');  //Read Line by Line
    Serial.println(line); //Print response
  }
//  Serial.println("==========");
//  Serial.println("closing connection");
//    
  delay(2000);  //POST Data at every 2 seconds
}
