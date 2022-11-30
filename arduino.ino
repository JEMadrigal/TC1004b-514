#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
//Firebase settings
#define FIREBASE_HOST "****************************"
#define FIREBASE_AUTH "*********************"
//Wi-Fi settings
#define WIFI_SSID "Tec-Residencias"
#define WIFI_PASSWORD "*******"
#define trigger_pin D0
#define trigger_pin2 D1
#define trigger_pin3 D2
#define trigger_pin4 D3
#define Echo_pin D5
#define Echo_pin2 D6
#define Echo_pin3 D7
#define Echo_pin4 D8

bool place1 = false;
bool place2 = false;

/* two variables to store duraion and distance value */
long duration;
int distance;
long duration2;
int distance2;
long duration3;
int distance3;
long duration4;
int distance4;

/* configure D9 and D11 as digital input and output respectively */
void setup() {
  pinMode(trigger_pin, OUTPUT); // configure the trigger_pin(D9) as an Output
  pinMode(Echo_pin, INPUT);
  pinMode(trigger_pin2, OUTPUT); // configure the trigger_pin(D9) as an Output
  pinMode(Echo_pin2, INPUT);
  pinMode(trigger_pin3, OUTPUT); // configure the trigger_pin(D9) as an Output
  pinMode(Echo_pin3, INPUT);
  pinMode(trigger_pin4, OUTPUT); // configure the trigger_pin(D9) as an Output
  pinMode(Echo_pin4, INPUT); // configure the Echo_pin(D11) as an Input
  Serial.begin(9600); // Enable the serial with 9600 baud rate
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
    
  digitalWrite(trigger_pin, LOW);
  digitalWrite(trigger_pin2, LOW);
  digitalWrite(trigger_pin3, LOW);
  digitalWrite(trigger_pin4, LOW); //set trigger signal low for 2us
  delayMicroseconds(2);

  /*send 10 microsecond pulse to trigger pin of HC-SR04 */
  digitalWrite(trigger_pin, HIGH);
  digitalWrite(trigger_pin2, HIGH);
  digitalWrite(trigger_pin3, HIGH);
  digitalWrite(trigger_pin4, HIGH);  // make trigger pin active high
  delayMicroseconds(10);            // wait for 10 microseconds
  digitalWrite(trigger_pin, LOW);
  digitalWrite(trigger_pin2, LOW);
  digitalWrite(trigger_pin3, LOW);
  digitalWrite(trigger_pin4, LOW);   // make trigger pin active low

  /*Measure the Echo output signal duration or pulss width */
  duration = pulseIn(Echo_pin, HIGH); // save time duration value in "duration variable
  distance= duration*0.034/2;
  duration2 = pulseIn(Echo_pin2, HIGH); // save time duration value in "duration variable
  distance2= duration2*0.034/2;
  duration3 = pulseIn(Echo_pin3, HIGH); // save time duration value in "duration variable
  distance3= duration3*0.034/2;
  duration4 = pulseIn(Echo_pin4, HIGH); // save time duration value in "duration variable
  distance4= duration4*0.034/2; //Convert pulse duration into distance

  if(distance < 10){
    place1 = true;
    // handle error
    if (Firebase.failed()) {
        Serial.print("setting /number failed:");
        Serial.println(Firebase.error());  
        return;
    }
    delay(1000);
  }else{
    place1 = false;

  }
  Firebase.setBool("Lugar 1", place1);  

  if(distance2 < 10){
    place2 = true;
    if (Firebase.failed()) {
        Serial.print("setting /number failed:");
        Serial.println(Firebase.error());  
        return;
    }
    delay(1000);  
  }else{
    place2 = false;
  }
  Firebase.setBool("Lugar 2", place2);
  // print measured distance value on Arduino serial monitor
  Serial.print("Distance 1: ");
  Serial.print(distance);
  Serial.println(" cm");
  Serial.print("Distance 2: ");
  Serial.print(distance2);
  Serial.println(" cm");
  Serial.print("Distance 3: ");
  Serial.print(distance3);
  Serial.println(" cm");
  Serial.print("Distance 4: ");
  Serial.print(distance4);
  Serial.println(" cm");
  delay(1000);
}