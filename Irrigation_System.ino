#include "arduino_secrets.h"
#include "thingProperties.h"

const int rpin_1 = 3;
const int rpin_2 = 4;
const int rpin_3 = 5;

const int threshold = 80;

Schedule schedValues = plant_schedule_1.getValue();

void setup() {

  Serial.begin(9600);

  //declare relay pins
  pinMode(rpin_1, OUTPUT);
  pinMode(rpin_2, OUTPUT);
  pinMode(rpin_3, OUTPUT);

  delay(1500);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  sensor_1 = sensorReading(A1);
  sensor_2 = sensorReading(A2);
  sensor_3 = sensorReading(A3);
  
  onPlantSchedule1Change();
  onPlantSchedule2Change();
  onPlantSchedule3Change();

}

int sensorReading(int pin){
  int result;
  int reading = analogRead(pin);
  result = map(reading, 0, 1023, 100, 0);
  return result;
}

void onPlantSchedule1Change() {
  if (automatic_mode) {
    if (sensor_1 < threshold && plant_schedule_1.isActive()) {
      digitalWrite(rpin_1, HIGH);
    } else {
      digitalWrite(rpin_1, LOW);
    }
  }
}

void onPlantSchedule2Change() {
  if (automatic_mode) {
    if (sensor_2 < threshold && plant_schedule_1.isActive()) {
      digitalWrite(rpin_2, HIGH);
    } else {
      digitalWrite(rpin_2, LOW);
    }
  }
}

void onPlantSchedule3Change() {
  if (automatic_mode) {
    if (sensor_3 < threshold && plant_schedule_1.isActive()) {
      digitalWrite(rpin_3, HIGH);
    } else {
      digitalWrite(rpin_3, LOW);
    }
  }
}

void onRelay1Change() {
  if (relay_1) {
    digitalWrite(rpin_1, HIGH);
  } else {
    digitalWrite(rpin_1, LOW);
  }
}

void onRelay2Change() {
  if (relay_2) {
    digitalWrite(rpin_2, HIGH);
  } else {
    digitalWrite(rpin_2, LOW);
  }
}

void onRelay3Change() {
  if (relay_3) {
    digitalWrite(rpin_3, HIGH);
  } else {
    digitalWrite(rpin_3, LOW);
  }
}

void onAutomaticModeChange() {
}
