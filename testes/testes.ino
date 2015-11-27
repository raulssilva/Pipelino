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

#include <EEPROM.h> 
#include <SoftwareSerial.h>
#include <LiquidCrystal.h> 

#define ADD    0b00000001  //''
#define SUB    0b00000010  //''
#define ADDI   0b00000011  //''

#define LW     0b00000100  //''
#define SW     0b00000101  //''

#define SLL    0b00000110  //''
#define SRL    0b00000111  //''
#define BEQ    0b00001000  //''
#define BNE    0b00001001  //''

#define J      0b00001010  //''
#define JR     0b00001011  //''
#define JAL    0b00001100  //''

SoftwareSerial writeBackSerial(10, 11); // RX, TX
LiquidCrystal lcd(10, 8, 5, 6, 3, 2);

void setup(){
  Serial.begin(9600);
  writeBackSerial.begin(9600);
  lcd.begin(16, 2); 
  lcd.setCursor(0,0); 
}

void loop(){
  writeBackSerialEvent();
  //Verificar necessidade de bolha
}

byte raeadRegister(byte address){
  byte value = EEPROM.read(address);
  return value;
}

void writeRegister(byte address, byte data){
  EEPROM.write(address, data);
}

void writeBackSerialEvent(){
  if(writeBackSerial.available()){
      char address = writeBackSerial.read();
      byte data = writeBackSerial.read();
      writeRegister(address, data);
  }
}

void serialEvent(){
  instructionReading();
}

void instructionReading(){
  char instruction = (char)Serial.read();
  executeInstruction(instruction);
  /*Captura a instrução*/
  //String str =  Serial.readString();
  /*Imprime na serial (teste)*/
  //Serial.println(str);
  /*Imprime no LCD*/
  //lcd.clear();
  //lcd.println(str);  
}

void executeInstruction(char instruction){
    switch(instruction){
       case ADD:
         executeADD();
         break;
       case SUB:
         executeSUB();
         break;
       case ADDI:
         executeADDI();
         break;
       case LW:
         executeLW();
         break;
       case SW:
         executeSW();
         break;
       case SLL:
         executeSLL();
         break;
       case SRL:
         executeSRL();
         break;
       case BEQ:
         executeBEQ();
         break;
       case BNE:
         executeBNE();
         break;
       case J:
         executeJ();
         break;
       case JR:
         executeJR();
         break;
       case JAL:
         executeJAL();
         break;
       default:
         Serial.println("Instruction ERROR");
         break;
    }
}


void executeADD(){
  if(Serial.available()==3){
    /*Lêr o primeiro endereço do registrador*/
    char  param1Reg = (char)Serial.read();
    /*Lêr o segundo endereço do registrador*/
    byte  param2Reg = (byte)Serial.read();
    /*Lêr o terceiro endereço do registrador*/
    byte  param3Reg = (byte)Serial.read();

    /*Lêr o valor armazenado no endereço do resgistradores*/
    byte value1 = raeadRegister(param2Reg);
    byte value2 = raeadRegister(param3Reg);

    /*Manda os dados para o próximo estágio = (ADD [ENDEREÇO DE ESCRITA] [VALOR] [VALOR])*/
    Serial.print(ADD);
    Serial.print(param1Reg);
    Serial.print(value1);
    Serial.print(value2);
    
  }else{
    Serial.println("Instruction ADD ERROR");
  }
  
}

void executeSUB(){
  if(Serial.available()==3){
    char  param1Reg = (char)Serial.read();
    byte  param2Reg = (byte)Serial.read();
    byte  param3Reg = (byte)Serial.read();

    byte value1 = raeadRegister(param2Reg);
    byte value2 = raeadRegister(param3Reg);

    Serial.print(SUB);
    Serial.print(param1Reg);
    Serial.print(value1);
    Serial.print(value2);
    
  }else{
    Serial.println("Instruction SUB ERROR");
  }
}

void executeADDI(){
  if(Serial.available()==3){
    char  param1Reg = (char)Serial.read();
    byte  param2Reg = (byte)Serial.read();
    byte  param2Value2 = (byte)Serial.read();

    byte value1 = raeadRegister(param2Reg);

    Serial.print(ADDI);
    Serial.print(param1Reg);
    Serial.print(value1);
    Serial.print(param2Value2);
    
  }else{
    Serial.println("Instruction ADDI ERROR");
  }
  
}

void executeLW(){
  if(Serial.available()==3){
    char  param1Reg = (char)Serial.read();
    byte  param2Const = (byte)Serial.read();
    byte  param3Reg = (byte)Serial.read();

    byte valueAddress = raeadRegister(param3Reg);

    Serial.print(LW);
    Serial.print(param1Reg);
    Serial.print(param2Const );
    Serial.print(valueAddress);
    
  }else{
    Serial.println("Instruction LW ERROR");
  }
}


void executeSW(){
  if(Serial.available()==3){
    char  param1 = (char)Serial.read();
    char  param2 = (char)Serial.read();
    char  param3 = (char)Serial.read();
    
    /*(.........)*/
    
  }else{
    Serial.println("Instruction LW ERROR");
  }
}

void executeSLL(){
  if(Serial.available()==3){
    char  param1 = (char)Serial.read();
    char  param2 = (char)Serial.read();
    char  param3 = (char)Serial.read();
    
    /*(.........)*/
    
  }else{
    Serial.println("Instruction SLL ERROR");
  }
}

void executeSRL(){
  if(Serial.available()==3){
    char  param1 = (char)Serial.read();
    char  param2 = (char)Serial.read();
    char  param3 = (char)Serial.read();
    
    /*(.........)*/
    
  }else{
    Serial.println("Instruction SRL ERROR");
  }
}

void executeBEQ(){
  if(Serial.available()==3){
    char  param1 = (char)Serial.read();
    char  param2 = (char)Serial.read();
    char  param3 = (char)Serial.read();
    
    /*(.........)*/
    
  }else{
    Serial.println("Instruction BEQ ERROR");
  }
}

void executeBNE(){
  if(Serial.available()==3){
    char  param1 = (char)Serial.read();
    char  param2 = (char)Serial.read();
    char  param3 = (char)Serial.read();
    
    /*(.........)*/
    
  }else{
    Serial.println("Instruction BNE ERROR");
  }
}

void executeJ(){
  if(Serial.available()==3){
    char  param1 = (char)Serial.read();
    char  param2 = (char)Serial.read();
    char  param3 = (char)Serial.read();
    
    /*(.........)*/
    
  }else{
    Serial.println("Instruction J ERROR");
  }
}

void executeJR(){
  if(Serial.available()==3){
    char  param1 = (char)Serial.read();
    char  param2 = (char)Serial.read();
    char  param3 = (char)Serial.read();
    
    /*(.........)*/
    
  }else{
    Serial.println("Instruction JR ERROR");
  }
}

void executeJAL(){
  if(Serial.available()==3){
    char  param1 = (char)Serial.read();
    char  param2 = (char)Serial.read();
    char  param3 = (char)Serial.read();
    
    /*(.........)*/
    
  }else{
    Serial.println("Instruction JAL ERROR");
  }
}
