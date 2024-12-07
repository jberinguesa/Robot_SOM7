#include <Arduino.h>

//Feina per fer:
// Hem d'acabar de pujar el codi a Github. Falta que s'autentifiquin.
// Estudiar el driver del motor
// Soldar-lo
// Fer les funcions per inicialitzar i fer anar el motor
// Fer les funcions de motor endavant i enrere
// Modificar que el motor arranqui suau, aprendre fer un for
// Arrancar més ràpid o més lent

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
  digitalWrite(OUTPUT_LED, HIGH);
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
#define pinPWMA 18
#define pinAIN2 19
#define pinAIN1 20
#define pinBIN1 22
#define pinBIN2 23
#define pinPWMB 24

// Funció que engega el motor
// speed: Velocitat del motor (0-255)
void motorForwardL(int speed)
{
  digitalWrite(pinAIN1, HIGH);
  digitalWrite(pinAIN2, LOW);
  analogWrite(pinPWMA, speed);
}

// Funció que para el motor
void motorStopL()
{
  digitalWrite(pinAIN1, LOW);
  digitalWrite(pinAIN2, LOW);
  analogWrite(pinPWMA, 0);
  //digitalWrite(pinBIN1, LOW);
  //digitalWrite(pinBIN2, LOW);
  //analogWrite(pinPWMB, 0);
}

// Funció per configurar el motor
void setup_motor(){
  pinMode(pinAIN2, OUTPUT);
  pinMode(pinAIN1, OUTPUT);
  pinMode(pinPWMA, OUTPUT);
  pinMode(pinBIN1, OUTPUT);
  pinMode(pinBIN2, OUTPUT);
  pinMode(pinPWMB, OUTPUT);
}

void setup() {
  Serial.begin(115200);
  setup_LED();
  setup_motor();
}

void loop() {
  Serial.println("Hello World");
  engega_LED_color(COLOR_VERMELL);
  engega_LED(250);
  motorForwardL(50);
  delay(1000);
  engega_LED_color(COLOR_ROSA);
  apaga_LED();
  motorStopL();
  delay(1000);
  
}

