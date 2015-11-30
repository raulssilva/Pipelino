/*
 Makers: Felipe Barbalho Rocha and Raul Silveira Silva
 
 The circuit (micro SD card reader):
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4
 
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

#include <SPI.h>
#include <SD.h>
#include <LiquidCrystal.h>

#define CHIP_SELECT 4
LiquidCrystal lcd(9, 8, 5, 6, 3, 2);

const String operators[] = {"ADD","SUB","ADDI","LW","SW","SLL","SRL","BEQ","BNE"};

const String registers[] = {"$0","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7"};

#define CLOCK 3000

void setup(){
  lcd.begin(16, 2);
  Serial.begin(9600);
  
  lcd.setCursor(2, 0);
  lcd.print("Initializing");
  lcd.setCursor(3, 1);
  lcd.print("SD card...");
  
  if (!SD.begin(CHIP_SELECT)){
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("[ERROR]");
    lcd.setCursor(0, 1);
    lcd.print("Card not present!");
    return;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Card initialized.");
}

String opCode = "";
String param1 = "";
String param2 = "";
String param3 = "";

byte opCodeByte = 0;
byte param1Byte = 0;
byte param2Byte = 0;
byte param3Byte = 0;

String memContent = "";

void loop(){
  if(Serial.available()){
    if(opCode == ""){
      opCodeByte = (byte)(Serial.read()-48);
      opCode = operators[opCodeByte];
      if(opCodeByte == 3){
        param1Byte = (byte)(Serial.read()-48);
        param1 = registers[param1Byte];
        param2Byte = (byte)Serial.read();
        param3Byte = (byte)Serial.read();
        
        File memory = SD.open("mem.txt");
        
        if(memory){
          byte lineCounter = 0;
          while(memory.available()){
            if(lineCounter == param3Byte){
              byte colunCounter = 0;
              while(memory.available()){
                char aux = memory.read();
                if(aux == '\n'){
                  break;
                }
                
                if(colunCounter >= param2Byte && colunCounter < (param2Byte+4)){
                  memContent += aux;
                }
                colunCounter++;
              }
            }else{
              while(memory.available()){
                char aux = memory.read();
                if(aux == '\n'){
                  break;
                }
              }
              lineCounter++;
            }
          }
        }
        
        Serial.println(memContent);
        
      }else if(opCodeByte == 4){
        
      }
    }
  }
}
