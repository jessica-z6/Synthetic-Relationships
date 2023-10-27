#include "config.h"
#include <AdafruitIO_WiFi.h>
#include <AdafruitIO_Data.h>

const int trigPin = 14;
const int echoPin = 15;
//const int buzzer = 11;
const int ledPin = 13;
const int LIGHT_PIN = 27;  // 替换成您的灯泡引脚


//AdafruitIO_WiFi io(AIO_USERNAME, AIO_KEY, WIFI_SSID, WIFI_PASS);
AdafruitIO_Feed *potfeed = io.feed("project1");
AdafruitIO_Feed *counter = io.feed("buttonfeed","zoeydong");
//AdafruitIO_Feed *lightControl;

long duration;
int distance;
float otherFeedValue = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  //pinMode(LIGHT_PIN, OUTPUT);

  Serial.begin(115200);
  while (!Serial);

  Serial.print("Trying to connect to Adafruit IO");
  io.connect();
  while (io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println(io.statusText());

 // lightControl = io.feed("light-control");

  potfeed = io.feed("pot_feed");
  counter->onMessage(handleData);
  //lightControl->onMessage(handleLightControl);
}

void loop() {
  io.run();

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  Serial.println(duration);
  distance = duration * 0.0343 / 2;

//  if (otherFeedValue >= 100) {
//    digitalWrite(buzzer, HIGH);
//  } else {
//    digitalWrite(buzzer, LOW);
//  }

  Serial.print("Sending this: ");
  Serial.println(distance);

  potfeed->save(distance);
  if (otherFeedValue >= 1000) {
   digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  delay(3000);
}

void handleData(AdafruitIO_Data *data) {
  Serial.print("Received: ");
  Serial.println(data->value());
  otherFeedValue = data->toFloat();
}

void handleLightControl(AdafruitIO_Data *data) {
  Serial.print("Light Control Received: ");
  String value = data->value();
 // if (value == "on") {
 //   digitalWrite(LIGHT_PIN, HIGH);
  //} else if (value == "off") {
    //digitalWrite(LIGHT_PIN, LOW);
  
}
