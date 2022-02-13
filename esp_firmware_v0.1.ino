#include <IRremote.h>
#include <WiFi.h>

//Pin der IR Diode am digitalen Pin 3 angeschlossen
int irPin = 9; //Pin am ESP für den IR Receiver
int irSendPin = 21;
int ID = 1;
const int button1 = 2; //Knopf zum schießen
const int ledPin =  13;      // the number of the LED pin
int buttonState = 0; //variable für den status des Buttons
IRrecv irrecv(irPin); //Objekt initialisieren für die IR Übertragung
decode_results results;



const char* ssid = "lasertec";
const char* password =  "pyhZvGQtD20kS8rg9W0NQprxqu4DDo9KfF0YJAtdmTB5hU9LvvUDDVi34popsE4";



IRsend irSender;

void setup() {
     pinMode(ledPin, OUTPUT);
   pinMode(button1, INPUT); //Definiert button 1 als input
    pinMode(irPin, INPUT);  //Den IR Pin als Eingang deklarieren.
  irrecv.enableIRIn(); //Den IR Pin aktivieren
  Serial.begin(9600); //Serielle kommunikation mit 9600 Baud beginnen.
}
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
   // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
        //Ausgabe des Zeichens sowie der Zahl auf der seriellen Schnittstelle
        Serial.print("ID = ");
        Serial.print(ID);
        //Absenden des Zahlenwertes
        irSender.sendSony(ID,12);
        //eine Pause von 250ms.
        delay(250);
    
    //MQTT Ausgabe Schuss wurde abgefeuert
  } 
    
     if (irrecv.decode(&results)) { //Wenn etwas gelesen wurde dann...
    if (irrecv.getProtocolString() == "SONY") {
      unsigned long value  = results.value;
      //Ausgabe des Wertes auf die Serielle Schnittstelle.
      Serial.println(char(value));
      //MQTT Ausgabe der ID
      if(ID = 1) {
      digitalWrite(ledPin, HIGH);
      } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }
    }
    irrecv.resume(); // auf den nächsten Wert warten
  }
}
