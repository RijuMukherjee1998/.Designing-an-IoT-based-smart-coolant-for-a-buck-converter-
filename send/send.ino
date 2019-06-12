#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
#include<SPI.h>

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"


#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "16bec1225"
#define AIO_KEY  "77513e491e084d2ba78472b84611a31d"
WiFiClient client;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

boolean MQTT_connect();

boolean MQTT_connect() {  int8_t ret; if (mqtt.connected()) {    return true; }  uint8_t retries = 3;  while ((ret = mqtt.connect()) != 0) { mqtt.disconnect(); delay(2000);  retries--;if (retries == 0) { return false; }} return true;}

Adafruit_MQTT_Publish Temperature_Monitor = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/Temperature_Monitor/feed_number");
void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.print("start");
   WiFi.begin("VITC-PGM","work@cse1831");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }
  Serial.println("connected");
  Serial.println(WiFi.localIP());

}


void loop()
{
    if (MQTT_connect()) {
      float a=round((1/(log((float)(1023-analogRead(A0))*10000/analogRead(A0))/10000)/3975+1/298.15)-273.15);
      Temperature_Monitor.publish(a);
    }

}
