/*
 Makers: Felipe Barbalho Rocha and Raul Silveira Silva
 
 The circuit (LCD 16x2):
 * LCD RS pin to digital pin 10
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 6
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(10, 8, 5, 6, 3, 2);

String x = "";
char y;

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void loop(){
    if(Serial.available()){
      lcd.clear();
      //Switch-Case das instrucoes e operar operandos
      //Evia pela Serial
      //Verificar necessidade de bolha
      char* g = Serial.read();
              lcd.print(g);
  }
}









