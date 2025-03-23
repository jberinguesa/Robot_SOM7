#include <Arduino.h>

//Feina per fer:
// Fer anar els dos motors
// Posar en marxa les bateries

#define DEBUG_MOTOR false
#define DEBUG_SENSOR_IR true
#define LIMIT_SENSOR_IR 300

//------------------------------------- Gestió LEDs -----------------------------------------
#define OUTPUT_LED 13
#define COLOR_ROSA 0,0,255
#define COLOR_VERMELL 0,255,255

// Funció que engega el LED
// intensitat: Valor entre 0 i 255, on 0 és màxim i 255 el mínim
void engega_LED(int intensitat){
  analogWrite(OUTPUT_LED, intensitat);
}

// Funció que apaga el LED
void apaga_LED(){
  analogWrite(OUTPUT_LED, 255);
}

// Funció que configura la sortida pel LED
void setup_LED(){
  pinMode(OUTPUT_LED, OUTPUT);
}

// Funció que engega el LED de color
// vermell: Nivell de vermell (0-255)
// verd: Nivell de verd (0-255)
// blau: Nivell de blau (0-255)
void engega_LED_color(int vermell, int blau, int verd){
  analogWrite(LED_RED, vermell);
  analogWrite(LED_GREEN, verd);
  analogWrite(LED_BLUE, blau);
}

// Funció que configura les sortides per activar el LED de color
void setup_LED_color(){
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

//------------------------------------- Gestió Motor -----------------------------------------
#define pinPWMA 2
#define pinAIN2 3
#define pinAIN1 4
#define pinSTBY 5
#define pinBIN1 6
#define pinBIN2 7
#define pinPWMB 8

// Funció que engega endavant els 2 motors
// speedE: Velocitat del motor esquerre(0-255)
// speedD: Velocitat del motor dret (0-255)
void motorEndavant(int speedE, int speedD)
{
  digitalWrite(pinSTBY, HIGH);
  digitalWrite(pinAIN1, HIGH);
  digitalWrite(pinAIN2, LOW);
  analogWrite(pinPWMA, speedE);
  digitalWrite(pinBIN1, HIGH);
  digitalWrite(pinBIN2, LOW);
  analogWrite(pinPWMB, speedD);

  #if DEBUG_MOTOR
    //Enviar per serial que el motor va endavant i la velociat de cada motor
    Serial.print("Motor endavant: ");
    Serial.print(speedE);
    Serial.print(" ");
    Serial.println(speedD);
  #endif
}

// Funció que engega enrera els 2 motors
// speedE: Velocitat del motor esquerre (0-255)
// speedD: Velocitat del motor dret (0-255)
void motorEnrera(int speedE, int speedD)
{
  digitalWrite(pinSTBY, HIGH);
  digitalWrite(pinAIN1, LOW);
  digitalWrite(pinAIN2, HIGH);
  analogWrite(pinPWMA, speedE);
  digitalWrite(pinBIN1, LOW);
  digitalWrite(pinBIN2, HIGH);
  analogWrite(pinPWMB, speedD);

  #if DEBUG_MOTOR
    //Enviar per serial que el motor va enrera i la velociat de cada motor
    Serial.print("Motor enrera: ");
    Serial.print(speedE);
    Serial.print(" ");
    Serial.println(speedD);
    #endif
}

// Funció que para els motors
void motorStop()
{
  digitalWrite(pinAIN1, LOW);
  digitalWrite(pinAIN2, LOW);
  analogWrite(pinPWMA, 0);
  digitalWrite(pinBIN1, LOW);
  digitalWrite(pinBIN2, LOW);
  analogWrite(pinPWMB, 0);

  #if DEBUG_MOTOR
    //Enviar per serial que el motor està parat
    Serial.println("Motor parat");
  #endif
}

// Funcio que arranca suaument els motor cap endavant
// speed: Velocitat dels 2 motors (0-255)
// acceleracio: Valor de l'acceleració (0-255)
void motorArrancaSuauEndavant(int speed, int acceleracio){
  //Engegar el motor endavant incrementant la velociatat segons el valor d'acceleració, utilitzant la funcio motorEndavant
  for(int i = 0; i <= speed; i+=acceleracio){
    motorEndavant(i, i);
    delay(10);
  }

  #if DEBUG_MOTOR
    //Enviar per serial que el motor arranca suau endavant i la velocitat
    Serial.print("Motors arranca suau endavant: ");
    Serial.println(speed);
  #endif
}

// Funcio que arranca suaument els motor cap enrera 
// speed: Velocitat dels 2 motors (0-255)
// acceleracio: Valor de l'acceleració (0-255)
void motorArrancaSuauEnrera(int speed, int acceleracio){
  //Engegar el motor enrera incrementant la velociatat segons el valor d'acceleració, utilitzant la funcio motorEnrera
  for(int i = 0; i <= speed; i+=acceleracio){
    motorEnrera(i, i);
    delay(10);
  }

  #if DEBUG_MOTOR
  //Enviar per serial que el motor arranca suau enrera i la velocitat
    Serial.print("Motors arranca suau enrera: ");
    Serial.println(speed);
  #endif
}

// Funció per configurar el motor
void setup_motor(){
  pinMode(pinAIN2, OUTPUT);
  pinMode(pinAIN1, OUTPUT);
  pinMode(pinPWMA, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);
  pinMode(pinPWMB, OUTPUT);
  pinMode(pinSTBY, OUTPUT);
}

//------------------------------------ Gestió Sensor IR -----------------------------------------
#define pinLED1 A0
#define pinLED3 A1
#define pinLED5 A2
#define pinLED7 A3

// Funció que configura els pins dels sensors IR
void setup_sensorIR(){
  pinMode(pinLED1, INPUT);
  pinMode(pinLED3, INPUT);
  pinMode(pinLED5, INPUT);
  pinMode(pinLED7, INPUT);
}

// Funció que llegir el valor d'una entrada del sensor IR
// pin: Pin del sensor IR
int LlegirSensorIR(int pin){
  return analogRead(pin);
}

// Funció que llegir el valor dels 4 sensors IR
void LlegirSensorsIRArray(int sensors[4]) {
  sensors[0] = LlegirSensorIR(pinLED1);
  sensors[1] = LlegirSensorIR(pinLED3);
  sensors[2] = LlegirSensorIR(pinLED5);
  sensors[3] = LlegirSensorIR(pinLED7);

  #if DEBUG_SENSOR_IR
    // Enviar per serial els valors dels 4 sensors IR
    Serial.print("Valors sensors IR: ");
    Serial.print(sensors[0]);
    Serial.print(", ");
    Serial.print(sensors[1]);
    Serial.print(", ");
    Serial.print(sensors[2]);
    Serial.print(", ");
    Serial.println(sensors[3]);
  #endif
}


void setup() {
  Serial.begin(115200);
  setup_LED();
  setup_motor();
  setup_sensorIR();
}

void loop() {
  int Sensors[4] = {0, 0, 0, 0};
  LlegirSensorsIRArray(Sensors);
  if (Sensors[0] < LIMIT_SENSOR_IR ){
    motorEndavant(125, 0);
    Serial.println("Endavant");
  }
  else if (Sensors[1] < LIMIT_SENSOR_IR){
    motorEnrera(125, 0);
  }
  else if (Sensors[2] < LIMIT_SENSOR_IR){
    motorEndavant(0, 125);
  }
  else if (Sensors[3] < LIMIT_SENSOR_IR){
    motorEnrera(0, 125);
  }
  else{
    motorStop();
  }
  delay(1000);
}

