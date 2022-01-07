#include <IRremote.h>
#include <WiFi.h>

//Pin der IR Diode am digitalen Pin 3 angeschlossen
int irSendPin = 3;
int ID = 1;

const char* ssid = "lasertec";
const char* password =  "lasertec";



IRsend irSender;

void setup() {
   //beginn der seriellen Kommunikation mit 9600 baud
    Serial.begin(9600);
   //verbinden mit Wifi
     WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("connecting with Wifi...");
  }
  Serial.println("Succesfully connected!");
}

void loop() {
    //Das char Array durchlaufen...
        int value = ID;
        //Absenden des Zahlenwertes
        irSender.sendSony(value,12);
        //eine Pause von 25ms.
        delay(25);    
    //eine Pause von 500ms.
    delay(500);
}
