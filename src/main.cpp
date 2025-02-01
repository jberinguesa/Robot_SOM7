#include <Arduino.h>

//Feina per fer:
// Modificar que el motor arranqui suau, aprendre fer un for
// Fer anar els dos motors

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
#define pinPWMA 18
#define pinAIN2 19
#define pinAIN1 20
#define pinSTBY 21
#define pinBIN1 22
#define pinBIN2 23
#define pinPWMB 24

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

  //Enviar per serial que el motor va endavant i la velociat de cada motor
  Serial.print("Motor endavant: ");
  Serial.print(speedE);
  Serial.print(" ");
  Serial.println(speedD);
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

  //Enviar per serial que el motor va enrera i la velociat de cada motor
  Serial.print("Motor enrera: ");
  Serial.print(speedE);
  Serial.print(" ");
  Serial.println(speedD);
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

  //Enviar per serial que el motor està parat
  Serial.println("Motor parat");
}

// Funcio que arranca suaument els motor cap endavant
// speed: Velocitat dels 2 motors (0-255)
void motorArrancaSuauEndavant(int speed){
  for(int i = 0; i < speed; i += 3){
    motorEndavant(i, i);
    delay(10);
  }

  //Enviar per serial que el motor arranca suau endavant i la velocitat
  Serial.print("Motors arranca suau endavant: ");
  Serial.println(speed);
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

void setup() {
  Serial.begin(115200);
  setup_LED();
  setup_motor();
}

void loop() {
  Serial.println("Hello World");
  //Fes un bucle que enviï pel canal serie un missatge que digui "El número X" on X és un número de 1 a 10 que incrementa en cada iteració
  for(int i = 0; i < 10; i++){
    Serial.print("El número ");
    Serial.println(i);
    delay(1000);
  }
  //Prova la funció /explain del copilot
  //Fes un bucle que enviï pel canal serie un missatge que digui "El número X" on X és un número de 1 a 10 que decrementa en cada iteració
  for(int i = 10; i > 0; i--){
    Serial.print("El número ");
    Serial.println(i);
    delay(1000);
  }
  //Fes un bucle que enviï pel canal serie un missatge que digui "El número X" on X és un número de 1 a 10 que incrementa en cada iteració, però saltant els números de 2 en 2
  for(int i = 0; i < 10; i += 2){
    Serial.print("El número ");
    Serial.println(i);
    delay(1000);
  }
  //Fes un bucle que enviï pel canal serie les taules de multiplicar, enviant "X per Y igual a Z" on X i Y són els números de 1 a 10 i Z és el resultat de multiplicar-los
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      Serial.print(i);
      Serial.print(" per ");
      Serial.print(j);
      Serial.print(" igual a ");
      Serial.println(i*j);
    }
  }

}

