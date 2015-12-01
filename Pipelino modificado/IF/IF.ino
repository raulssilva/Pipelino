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
  
  File assemblyFile = SD.open("code.txt");
  
  if (assemblyFile){
    String opCode = "";
    String param1 = "";
    String param2 = "";
    String param3 = "";
    
    // Read byte-by-byte from the file until there's nothing else in it
    while (assemblyFile.available()) {
      if(Serial.available()){
        byte brench = (byte)Serial.read();
        for(brench -= 1; brench > 0; brench--){
          while(assemblyFile.read() != '\n'){
          }
        }
      }

      if(opCode == ""){
        opCode = readParam(assemblyFile);
        for(byte i = 0; i<9; i++){
          if(operators[i] == opCode){
            Serial.print(i);
          }
        }
      }
      
      switch(opCode.length()){
        case 2:
          //Load ou Store
          param1 = readParam(assemblyFile);
          param2 = readParamConst(assemblyFile);
          param3 = readParam(assemblyFile);
          param3 = param3.substring(0,param3.length()-1);
          
          for(byte i = 0; i<9; i++){
            if(registers[i] == param1){
              Serial.print(i);
              Serial.print((char)param2.toInt());
            }
          }
          
          for(byte i = 0; i<9; i++){
            if(registers[i] == param3){
              Serial.print(i);
            }
          }
          param3 = "(" + param3 + ")";
          break;
        case 3:
          //ADD, SUB, BEQ, BNE, SLL e SRL
          param1 = readParam(assemblyFile);
          param2 = readParam(assemblyFile);
          param3 = readParam(assemblyFile);
          
          for(byte i = 0; i<9; i++){
            if(registers[i] == param1){
              Serial.print(i);
            }
          }
          
          for(byte i = 0; i<9; i++){
            if(registers[i] == param2){
              Serial.print(i);
            }
          }
          
          if(opCode == "ADD" || opCode == "SUB"){
            for(byte i = 0; i<9; i++){
              if(registers[i] == param3){
                Serial.print(i);
              }
            }
          }else{
            Serial.print(param3.toInt());
          }
          break;
        default:
          //ADDI
          param1 = readParam(assemblyFile);
          param2 = readParam(assemblyFile);
          param3 = readParam(assemblyFile);
          
          for(byte i = 0; i<9; i++){
            if(registers[i] == param1){
              Serial.print(i);
            }
          }
          
          for(byte i = 0; i<9; i++){
            if(registers[i] == param2){
              Serial.print(i);
              Serial.print(param3.toInt());
            }
          }
      }
      
      lcd.clear();
      lcd.setCursor(6,0);
      lcd.print(opCode);
      lcd.setCursor(2,1);
      lcd.print(param1 + " " + param2 + " " + param3);

      delay(CLOCK);
      
      opCode = "";
      param1 = "";
      param2 = "";
      param3 = "";

    }
    assemblyFile.close();
    
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("End of program");
    
  }else{
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("[ERROR]");
    lcd.setCursor(0, 1);
    lcd.print("No code on card!");
  }
}

void loop(){
  
}

String readParam(File assemblyFile){
  char aux;
  String param = "";
  while (assemblyFile.available()) {
    aux = assemblyFile.read();
    if(aux == ' ' || aux == '\n' || aux == '\t'){
      return param;
    }else{
      param += aux;
    }
  }
}

String readParamConst(File assemblyFile){
  char aux;
  String param = "";
  while (assemblyFile.available()) {
    aux = assemblyFile.read();
    if(aux == '('){
      return param;
    }else{
      param += aux;
    }
  }
}
