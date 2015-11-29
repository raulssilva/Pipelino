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

/*Taxa de transmissão*/
#define BAUDS_RATE 9600

/*Tempo de delay para leitura dos dados da serial*/
#define TIME_WAIT_SERIAL 10

/*---------PINOS LCD---------*/
#define LCD_RS 9
#define LCD_Enable 8
#define LCD_D4 5
#define LCD_D5 6
#define LCD_D6 3
#define LCD_D7 2

/*--------Código de OP-------*/
#define ADD    0b00000000
#define SUB    0b00000001
#define ADDI   0b00000010

#define LW     0b00000011
#define SW     0b00000100

#define SLL    0b00000101
#define SRL    0b00000110
#define BEQ    0b00000111
#define BNE    0b00001000

/*Clock de ciclo do PipeLine*/
#define clock 2000

/*---RX e TX  do WriteBack--*/
#define WRITE_BACK_RX 10
#define WRITE_BACK_TX 11

/*---Oprações para exibição na tela--*/
const String operators[] = {"ADD","SUB","ADDI","LW","SW","SLL","SRL","BEQ","BNE"};

/*---Registradores para exibição na tela--*/
const String registers[] = {"$0","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7"};

/*Inicializa sosftSerial para writeBack*/
SoftwareSerial writeBackSerial(WRITE_BACK_RX, WRITE_BACK_TX);

/*Inicializa LCD*/
LiquidCrystal lcd(LCD_RS, LCD_Enable, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

/*--Flag para quando precisar de WriteBack--*/
bool writeBackWait = false;

void setup(){
    Serial.begin(BAUDS_RATE);
    writeBackSerial.begin(BAUDS_RATE);
    lcd.begin(16, 2); 
    lcd.setCursor(0,0); 
}

void loop(){
    /*Verifica as duas seriais*/
    writeBackSerialEvent();

    /*Verifica se a flag do WriteBack está ativa*/
    if(!writeBackWait){
        inSerialEvent();
    }
    
    /*IMPLEMENTAR Verificação de necessidade de bolha*/
}

/*Lêr do banco de registradores*/
byte readRegister(byte address){
    byte value = EEPROM.read(address);
    return value;
}

/*Grava no banco de registradores*/
void writeRegister(byte address, byte data){
    EEPROM.write(address, data);
}

/*Ação do WriteBack*/
void writeBackSerialEvent(){
    if(writeBackSerial.available()){
      delay(TIME_WAIT_SERIAL);
      showLCD("[writeBack]");
        /*char address = writeBackSerial.read();
        byte data = writeBackSerial.read();
        writeRegister(address, data);
        writeBackWait = false;*/
    }
}

/*Ação da Serial principal*/
void inSerialEvent(){
   if(Serial.available()){
        delay(TIME_WAIT_SERIAL);
        instructionReading();
   }
}

/*Lêr apenas o OP*/
void instructionReading(){
    byte op = Serial.read();
    decodeInstruction(op);
}

void decodeInstruction(byte op){
    switch(op){
       case ADD:
           decodeADD();
           break;
       case SUB:
           decodeSUB();
           break;
       case ADDI:
           decodeADDI();
           break;
       case LW:
           decodeLW();
           break;
       case SW:
           decodeSW();
           break;
       case SLL:
           decodeSLL();
           break;
       case SRL:
           decodeSRL();
           break;
       case BEQ:
           decodeBEQ();
           break;
       case BNE:
         decodeBNE();
         break;
       default:
           showLCD(operators[op]+" ERROR");
           break;
    }
}

/*Exibe a instrução no LCD*/
void showLCD(String text){
    lcd.clear();
    Serial.println("TESTANDO: "+text);
    lcd.println(text);
    delay(clock);
}

void decodeADD(){
  if(Serial.available()==3){
    /*Lêr o primeiro endereço do registrador*/
    byte param1Reg = Serial.read();
    /*Lêr o segundo endereço do registrador*/
    byte  param2Reg = Serial.read();
    /*Lêr o terceiro endereço do registrador*/
    byte  param3Reg = Serial.read();

    /*Lêr o valor armazenado no endereço do resgistradores*/
    byte value1 = readRegister(param2Reg);
    byte value2 = readRegister(param3Reg);
    
    showLCD(operators[ADD]+" "+registers[param1Reg]+" "+registers[param2Reg]+" "+registers[param3Reg]);
    
    /*Manda os dados para o próximo estágio = (ADD [ENDEREÇO DE ESCRITA] [VALOR] [VALOR])*/
    Serial.print(ADD);
    Serial.print(param1Reg);
    Serial.print(value1);
    Serial.print(value2);
    
  }else{
    Serial.println("Instruction ADD ERROR");
  }
  
}

void decodeSUB(){
  if(Serial.available()==3){
    byte  param1Reg = Serial.read();
    byte  param2Reg = Serial.read();
    byte  param3Reg = Serial.read();

    byte value1 = readRegister(param2Reg);
    byte value2 = readRegister(param3Reg);

    showLCD(operators[SUB]+" "+registers[param1Reg]+" "+registers[param2Reg]+" "+registers[param3Reg]);

    Serial.print(SUB);
    Serial.print(param1Reg);
    Serial.print(value1);
    Serial.print(value2);
    
  }else{
    Serial.println("Instruction SUB ERROR");
  }
}

void decodeADDI(){
  if(Serial.available()==3){
    byte  param1Reg = Serial.read();
    byte  param2Reg = Serial.read();
    byte  param2Value2 = Serial.read();

    byte value1 = readRegister(param2Reg);

    showLCD(operators[ADDI]+" "+registers[param1Reg]+" "+registers[param2Reg]+" "+param2Value2);

    Serial.print(ADDI);
    Serial.print(param1Reg);
    Serial.print(value1);
    Serial.print(param2Value2);
    
  }else{
    Serial.println("Instruction ADDI ERROR");
  }
  
}

void decodeLW(){
  if(Serial.available()==3){
    byte  param1Reg = Serial.read();
    byte  param2Const = Serial.read();
    byte  param3Reg = Serial.read();

    byte valueAddress = readRegister(param3Reg);
    
    showLCD(operators[LW]+" "+registers[param1Reg]+" "+param2Const+"("+registers[param3Reg]+")");

    Serial.print(LW);
    Serial.print(param1Reg);
    Serial.print(param2Const );
    Serial.print(valueAddress);
    
    writeBackWait = true;

  }else{
    Serial.println("Instruction LW ERROR");
  }
}


void decodeSW(){
  if(Serial.available()==3){
    byte  param1Reg = Serial.read();
    byte  param2Const = Serial.read();
    byte  param3Reg = Serial.read();

    byte valueStore = readRegister(param1Reg);
    byte valueAddress = readRegister(param3Reg);

    showLCD(operators[SW]+" "+registers[param1Reg]+" "+param2Const+"("+registers[param3Reg]+")");

    Serial.print(SW);
    Serial.print(valueStore);
    Serial.print(param2Const);
    Serial.print(valueAddress);
    
  }else{
    Serial.println("Instruction LW ERROR");
  }
}

/*Não implementei o restante*/
void decodeSLL(){
  if(Serial.available()==3){
    byte  param1Reg = Serial.read();
    byte  param2Reg = Serial.read();
    byte  param3Const = Serial.read();
  
    byte value = readRegister(param2Reg);

    showLCD(operators[SLL]+" "+registers[param1Reg]+" "+value+" "+param3Const);

    Serial.print(SLL);
    Serial.print(param1Reg);
    Serial.print(value);
    Serial.print(param3Const);
    
  }else{
    Serial.println("Instruction SLL ERROR");
  }
}

void decodeSRL(){
  if(Serial.available()==3){
    byte  param1Reg = Serial.read();
    byte  param2Reg = Serial.read();
    byte  param3Const = Serial.read();
    
    byte value = readRegister(param2Reg);

    showLCD(operators[SRL]+" "+registers[param1Reg]+" "+value+" "+param3Const);

    Serial.print(SRL);
    Serial.print(param1Reg);
    Serial.print(value);
    Serial.print(param3Const);
    
  }else{
    Serial.println("Instruction SRL ERROR");
  }
}

void decodeBEQ(){
  if(Serial.available()==3){
    byte param1Reg = Serial.read();
    byte param2Reg = Serial.read();
    byte param3Const = Serial.read();
    
    byte value1 = readRegister(param1Reg);
    byte value2 = readRegister(param2Reg);

    showLCD(operators[SRL]+" "+registers[param1Reg]+" "+registers[param2Reg]+" "+param3Const);

    Serial.print(SRL);
    Serial.print(value1);
    Serial.print(value2);
    Serial.print(param3Const);
    
  }else{
    Serial.println("Instruction BEQ ERROR");
  }
}

void decodeBNE(){
  if(Serial.available()==3){
    byte param1Reg = Serial.read();
    byte param2Reg = Serial.read();
    byte param3Const = Serial.read();
    
    byte value1 = readRegister(param1Reg);
    byte value2 = readRegister(param2Reg);

    showLCD(operators[SRL]+" "+registers[param1Reg]+" "+registers[param2Reg]+" "+param3Const);

    Serial.print(SRL);
    Serial.print(value1);
    Serial.print(value2);
    Serial.print(param3Const);
    
  }else{
    Serial.println("Instruction BNE ERROR");
  }
}




