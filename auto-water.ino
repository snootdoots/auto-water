#include "HX711.h"
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Arduino.h>


// VALUES TO BE CHANGED
#define WEIGHT_THRESHOLD 5
#define MOISTURE_THRESHOLD 500
#define TIME_PER_READING 20 //86400
#define SERVO_DOWN_TIME 5


// dont change the following values
// moisture
int val = 0; //value for storing moisture value
int soilPin = A0;//Declare a variable for the soil moisture sensor
int soilPower = 7;//Variable for Soil moisture Power
// weight
#define calibration_factor -220
#define DOUT 3
#define CLK 2
HX711 scale;
// servo
Servo servo; // servo object representing the MG 996R servo
// bluetooth
SoftwareSerial HM10(4,6); //rx, tx


// IMPORTANT: MAKE SURE TANK ISN'T ON SCALE WHEN PROGRAM IS STARTED
void setup() {
 Serial.begin(9600);   // open serial over USB
 // moisture
 pinMode(soilPower, OUTPUT);//Set D7 as an OUTPUT
 digitalWrite(soilPower, LOW);//Set to LOW so no power is flowing through the sensor
 // weight
 scale.begin(DOUT, CLK);
 scale.set_scale(calibration_factor);
 scale.tare();
 scale.power_down(); // initialize scale to be turned off by default
 // servo
 servo.attach(5); // servo is wired to Arduino on digital pin 5
 servo.write(180);
 // bluetooth
 HM10.begin(9600);
}


void loop() {
 checkAndWater();
 servo.write(180);
 readWeight();
 delay(TIME_PER_READING);
}


// reads soil moisture content
int readSoil() {
 digitalWrite(soilPower, HIGH); // turn D7 "On"
 delay(1000); // wait 1 second
 val = analogRead(soilPin); // Read the SIG value form sensor
 digitalWrite(soilPower, LOW); // turn D7 "Off"
 return val; // send current moisture value
}


// reads the weight of the scale
void readWeight() {
 // turn power on, since it is powered off by default
 scale.power_up();
 int weight = scale.get_units(50);
 if(weight < WEIGHT_THRESHOLD) {
   sendBluetooth();
 }
 scale.power_down();
}


// moves servo to the "down" position for param number of seconds
void moveServo(int time) {
 servo.write(125);
 delay(time * 1000);
}


// if the moisture is below a certain number, then move the plant
void checkAndWater() {
 if(readSoil() < MOISTURE_THRESHOLD) {
   moveServo(SERVO_DOWN_TIME);
 }
}


// sends message through bluetooth
void sendBluetooth() {
 HM10.write("Fill up the water");
}

