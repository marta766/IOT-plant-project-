// Moisture Sensor Arduino Code
//By Circuitdigest 
#define ledPin 6
#define sensorPin A0


#include <Wire.h>
#include "rgb_lcd.h"


  char devid[] = "vD9DC65577B80F4D";
  
  //////////////
 //   End    //
//////////////

char serverName[] = "api.pushingbox.com";
boolean DEBUG = true;
#include <Bridge.h>
#include <HttpClient.h>

rgb_lcd lcd;
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  lcd.begin(16, 2);
    // Print a message to the LCD.
    pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  Bridge.begin();
  digitalWrite(13, HIGH);

  Serial.begin(9600);
  while (!Serial); // wait for a serial connection
    
}
void loop() {
  Serial.print("Analog output: ");
  // Serial.println(readSensor());
  // if readSensor() >= 
  delay(500);
  // Turn off the display:
    lcd.noDisplay();
    delay(500);
    // Turn on the display:
    lcd.display();
    delay(500);

    HttpClient client;

  //Setup sensorValue to read a value from Analog Port A0
  int sensorValue = analogRead(A0);
  if (sensorValue >= 100) {
    lcd.println("Water plant");
  }

  else{
    lcd.println("Plant is watered");
  }
  
  //Testing value - when sensor is not connected - comment out when sketch is shown to be working - and take value from A0 instead
  //sensorValue=1500;

  // Make a HTTP request:  
  String APIRequest;
  APIRequest = String(serverName) + "/pushingbox?devid=" + String(devid)+ "&IDtag=100&TimeStamp="+sensorValue+"&TempC=";
  client.get (APIRequest);
  
  // if there are incoming bytes available
  // from the server, read them and print them:
  while (client.available()) {
    char c = client.read();

  }
  Serial.flush();
  String UploadMessage;
  Serial.print("\n Uploaded temp value: ");
  Serial.print(sensorValue);
  delay(5000);
}
//  This function returns the analog data to calling function
// int readSensor() {
//   int sensorValue = analogRead(sensorPin);  // Read the analog value from sensor
//   // int outputValue = map(sensorValue, 0, 1023, 255, 0); // map the 10-bit data to 8-bit data
  
//   analogWrite(ledPin, sensorValue); // generate PWM signal
//   int outputValue = sensorValue;
//   return outputValue;             // Return analog moisture value

  
// }