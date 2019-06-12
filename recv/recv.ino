#include <Servo.h>


#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <ESP8266WiFi.h>

String  i;
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "16bec1225"
#define AIO_KEY  "77513e491e084d2ba78472b84611a31d"
WiFiClient client;
Servo myservo;

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe temps = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/feed_number");
boolean MQTT_connect();

boolean MQTT_connect() {  int8_t ret; if (mqtt.connected()) {    return true; }  uint8_t retries = 3;  while ((ret = mqtt.connect()) != 0) { mqtt.disconnect(); delay(2000);  retries--;if (retries == 0) { return false; }} return true;}


void setup() {
i = "";

Serial.begin(115200);

delay(1000);
  Serial.println("start");
 
  myservo.attach(2);
  int angle=0;
  myservo.write(angle);
   WiFi.begin("VITC-PGM","work@cse1831");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");
      }
  Serial.println("connected");
  Serial.println((WiFi.localIP().toString()));

  mqtt.subscribe(&temps);

}




void loop() {
if (MQTT_connect()) {
      Adafruit_MQTT_Subscribe *subscription_name;
      while ((subscription_name = mqtt.readSubscription(5000))) {
        if (subscription_name == &temps) {
          i = ((char *)temps.lastread);
          int temp=i.toInt();

          if (temp >55) {
            myservo.write(90);

          } else {
            myservo.write(0);

          }

        }

      }

    }


}
