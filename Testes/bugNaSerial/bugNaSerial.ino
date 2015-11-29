/*
 Makers: Felipe Barbalho Rocha and Raul Silveira Silva
 
 The circuit (LCD 16x2):
 * LCD RS pin to digital pin 9
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

#include <EEPROM.h> 
#include <SoftwareSerial.h>
#include <LiquidCrystal.h> 

/*--------Código de OP-------*/
#define ADD    0
#define SUB    1
#define ADDI   2

#define LW     3
#define SW     4

#define SLL    5
#define SRL    6
#define BEQ    7
#define BNE    8

String operators[] = {"ADD","SUB","ADDI","LW","SW","SLL","SRL","BEQ","BNE"};

const String registers[] = {"$0","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7"};

#define CLOCK 3000

LiquidCrystal lcd(9, 8, 5, 6, 3, 2);

void setup(){
    lcd.begin(16, 2); 
    Serial.begin(9600);
}

String opCode = "";
String param1 = "";
String param2 = "";
String param3 = "";

byte opCodeByte = 0;
char param1Byte = 0;
char param2Byte = 0;
char param3Byte = 0;

void loop(){
  if(Serial.available()){
    char aux = Serial.read();
    if(aux != '\n'){
      opCodeByte = aux - 48;
    Serial.println(operators[opCodeByte]);
    }
  }
  delay(500);
}
