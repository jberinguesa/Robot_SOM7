#include <Arduino.h>

// Definició de 
const int pinPWMA = 18;
const int pinAIN2 = 19;
const int pinAIN1 = 20;
const int pinBIN1 = 22;
const int pinBIN2 = 23;
const int pinPWMB = 24;

void motorForward(int speed)
{
  digitalWrite(pinAIN1, HIGH);
  digitalWrite(pinAIN2, LOW);
  analogWrite(pinPWMA, speed);
  digitalWrite(pinBIN1, HIGH);
  digitalWrite(pinBIN2, LOW);
  analogWrite(pinPWMB, speed);
}

void motorStop()
{
  digitalWrite(pinAIN1, LOW);
  digitalWrite(pinAIN2, LOW);
  analogWrite(pinPWMA, 0);
  digitalWrite(pinBIN1, LOW);
  digitalWrite(pinBIN2, LOW);
  analogWrite(pinPWMB, 0);
}

void setup()
{
  // initialize RGB LED pins as outputs
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  Serial.begin(115200);
  pinMode(pinAIN2, OUTPUT);
  pinMode(pinAIN1, OUTPUT);
  pinMode(pinPWMA, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);
  pinMode(pinPWMB, OUTPUT);
}

void loop()
{
  // turn the RGB LED on (HIGH is the voltage level)
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  // wait for a second
  delay(500);
  // turn the RGB LED off by making the voltage LOW
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, HIGH);
  // wait for a second
  delay(1000);
  Serial.println("Engego motor");
  motorForward(100);
  delay(3000);
  Serial.println("Aturo motor");
  motorStop();
}

