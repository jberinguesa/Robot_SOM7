#include <Arduino.h>

//Feina per fer:
// Ari i Jana: Crear les funcions engega_LED i apaga_LED
// Crear la funció setup_LED()
// Ficar comentari Gestió LEDs
// CMD+SHIFT+P: Publish to Github
//

//------------------------------------- Gestió LEDs -----------------------------------------
#define OUTPUT_LED 13
#define COLOR_VERD 0,0,255
#define COLOR_GROC 0,255,255

//Funció que engega el LED
//intensitat: Valor entre 0 i 255, on 0 és màxim i 255 el mínim
void engega_LED(int intensitat){
  analogWrite(OUTPUT_LED, intensitat);
}

//Funció que apaga el LED
void apaga_LED(){
  digitalWrite(OUTPUT_LED, HIGH);
}

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

void setup() {
  Serial.begin(115200);
  setup_LED();

}

void loop() {
  Serial.println("Hello World");
  engega_LED_color(COLOR_VERD);
  engega_LED(250);
  delay(1000);
  engega_LED_color(COLOR_GROC);
  
  
}

