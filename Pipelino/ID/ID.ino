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
#include <SoftwareSerial.h>

SoftwareSerial writeBackSerial(10, 11); // RX, TX
LiquidCrystal lcd(10, 8, 5, 6, 3, 2);

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  writeBackSerial.begin(9600);
}

void loop(){
  if(writeBackSerial.available()){
    //Grava na EEPROM
  }else{
    if(Serial.available()){
      //Switch-Case das instrucoes e ler da EEPROM
      //Evia pela Serial
      //Verificar necessidade de bolha
    }
  }
}









