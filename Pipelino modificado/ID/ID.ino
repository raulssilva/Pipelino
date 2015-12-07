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
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

#define CLOCK 3000

// Definicao dos pinos do LCD para exibicao das informacoes
LiquidCrystal lcd(9, 8, 5, 6, 3, 2);
// Definicao de uma segunda porta de comunicacao Serial para o Write Back
SoftwareSerial controllerSerial(10, 11); // RX, TX

// Array com as operacoes que podem ser usadas. Cada indice representa o OP code
const String operators[] = {"ADD","SUB","ADDI","LW","SW","SLL","SRL","BEQ","BNE"};
// Array com os registradores que podem ser usados. Cada indice representa a referencia do registrador na EEPROM
const String registers[] = {"$0","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7"};

void setup(){
  // Inicia o LCD 16x2
  lcd.begin(16, 2);
  // Inicia a Serial com um baudrate de 9600bps
  Serial.begin(9600);
  // Inicia a Serial do Write Back com um baudrate de 9600bps
  controllerSerial.begin(9600);
  // Pino de notificacao de salto
  pinMode(12, INPUT);
}

// Variaveis de exibicao no LCD
String opCode = "";
String param1 = "";
String param2 = "";
String param3 = "";

// Variaveis de indentificadores de OP code, registradores e constantes
byte opCodeByte = 0;
byte param1Byte = 0;
byte param2Byte = 0;
byte param3Byte = 0;

// Flag para tratamento de salto
bool brenchFlag = false;

void loop(){
  // Verifica se houve salto e ativa a flag
  if(digitalRead(12)==1){
    controllerSerial.read();
    brenchFlag = true;
  // Verifica se houve Write Back e escreva na EEPROM
  }else if(controllerSerial.available()){
    byte address = controllerSerial.read();
    byte value = controllerSerial.read();
    writeRegister(address, value);
  }
  // Verifica se uma nova instrucao chegou pela Serial
  if(Serial.available()){
    // Se o OP code nao tiver sido lido, significa que o primeiro byte e do OP code
    if(opCode == ""){
      opCodeByte = (byte)(Serial.read()-48);
      opCode = operators[opCodeByte];
      // Se a Flag nao estiver ativada, a proxima instrucao deve ser executada
      if(!brenchFlag){
        Serial.print(opCodeByte);
      }
    }
    
    // Apos a leitura do OP code e verificado quais dados devem ser lidos, baseados no OP code
    switch(opCodeByte){
      case 0:
        // ADD
        param1Byte = (byte)(Serial.read()-48);
        param1 = registers[param1Byte];
        param2Byte = (byte)(Serial.read()-48);
        param2 = (String)readRegister(param2Byte);
        param3Byte = (byte)(Serial.read()-48);
        param3 = (String)readRegister(param3Byte);
        // Se a Flag nao estiver ativada, a proxima instrucao deve ser executada
        if(!brenchFlag){
          Serial.print(param1Byte);
          Serial.print((char)(param2.toInt())); // Necessario, pois se for 0 sera NULL e nao e enviado
          Serial.print((char)(param3.toInt())); // Necessario, pois se for 0 sera NULL e nao e enviado
        }
        break;
      case 1:
        // SUB
        param1Byte = (byte)(Serial.read()-48);
        param1 = registers[param1Byte];
        param2Byte = (byte)(Serial.read()-48);
        param2 = (String)readRegister(param2Byte);
        param3Byte = (byte)(Serial.read()-48);
        param3 = (String)readRegister(param3Byte);
        // Se a Flag nao estiver ativada, a proxima instrucao deve ser executada
        if(!brenchFlag){
          Serial.print(param1Byte);
          Serial.print((char)(param2.toInt())); // Necessario, pois se for 0 sera NULL e nao e enviado
          Serial.print((char)(param3.toInt())); // Necessario, pois se for 0 sera NULL e nao e enviado
        }
        break;
      case 2:
        param1Byte = (byte)(Serial.read()-48);
        param1 = registers[param1Byte];
        param2Byte = (byte)(Serial.read()-48);
        param2 = (String)readRegister(param2Byte);
//        param2 = registers[param2Byte];
        param3Byte = (byte)(Serial.read()-48);
        param3 = (String)param3Byte;
        if(!brenchFlag){
          Serial.print(param1Byte);
          Serial.print((char)(param2.toInt())); // Necessario, pois se for 0 sera NULL e nao e enviado
          Serial.print((char)param3Byte);
        }
        break;
      case 3:
        param1Byte = (byte)(Serial.read()-48);
        param1 = registers[param1Byte];
        param2Byte = (byte)Serial.read();
        param2 = (String)param2Byte;
        param3Byte = (byte)(Serial.read()-48);
        param3 = (String)readRegister(param3Byte);
//        param3 = registers[param3Byte];
        if(!brenchFlag){
          Serial.print(param1Byte);
          Serial.print((char)param2Byte);
          Serial.print((char)(param3.toInt())); // Necessario, pois se for 0 sera NULL e nao e enviado
        }
        break;
      case 4:
        param1Byte = (byte)(Serial.read()-48);
        param1 = (String)readRegister(param1Byte);
//        param1 = registers[param1Byte];
        param2Byte = (byte)Serial.read();
        param2 = (String)param2Byte;
        param3Byte = (byte)(Serial.read()-48);
        param3 = (String)readRegister(param3Byte);
//        param3 = registers[param3Byte];
        if(!brenchFlag){
          Serial.print((char)(param1.toInt())); // Necessario, pois se for 0 sera NULL e nao e enviado
          Serial.print((char)param2Byte);
          Serial.print((char)(param3.toInt())); // Necessario, pois se for 0 sera NULL e nao e enviado
        }
        break;
      case 5:
        param1Byte = (byte)(Serial.read()-48);
        param1 = registers[param1Byte];
        param2Byte = (byte)(Serial.read()-48);
        param2 = (String)readRegister(param2Byte);
//        param2 = registers[param2Byte];
        param3Byte = (byte)(Serial.read()-48);
        param3 = (String)param3Byte;
        if(!brenchFlag){
          Serial.print(param1Byte);
          Serial.print((char)(param2.toInt())); // Necessario, pois se for 0 sera NULL e nao e enviado
          Serial.print((char)param3Byte);
        }
        break;
      case 6:
        param1Byte = (byte)(Serial.read()-48);
        param1 = registers[param1Byte];
        param2Byte = (byte)(Serial.read()-48);
        param2 = (String)readRegister(param2Byte);
//        param2 = registers[param2Byte];
        param3Byte = (byte)(Serial.read()-48);
        param3 = (String)param3Byte;
        if(!brenchFlag){
          Serial.print(param1Byte);
          Serial.print((char)(param2.toInt())); // Necessario, pois se for 0 sera NULL e nao e enviado
          Serial.print((char)param3Byte);
        }
        break;
      case 7:
        param1Byte = (byte)(Serial.read()-48);
        param1 = (String)readRegister(param1Byte);
//        param1 = registers[param1Byte];
        param2Byte = (byte)(Serial.read()-48);
        param2 = (String)readRegister(param2Byte);
//        param2 = registers[param2Byte];
        param3Byte = (byte)(Serial.read()-48);
        param3 = (String)param3Byte;
        if(!brenchFlag){
          Serial.print((char)(param1.toInt())); // Necessario, pois se for 0 sera NULL e nao e enviado
          Serial.print((char)(param2.toInt())); // Necessario, pois se for 0 sera NULL e nao e enviado
          Serial.print((char)param3Byte);
        }
        break;
      default:
        param1Byte = (byte)(Serial.read()-48);
        param1 = (String)readRegister(param1Byte);
//        param1 = registers[param1Byte];
        param2Byte = (byte)(Serial.read()-48);
        param2 = (String)readRegister(param2Byte);
//        param2 = registers[param2Byte];
        param3Byte = (byte)(Serial.read()-48);
        param3 = (String)param3Byte;
        if(!brenchFlag){
          Serial.print((char)(param1.toInt())); // Necessario, pois se for 0 sera NULL e nao e enviado
          Serial.print((char)(param2.toInt())); // Necessario, pois se for 0 sera NULL e nao e enviado
          Serial.print((char)param3Byte);
        }
    }
    if(!brenchFlag){
      lcd.clear();
      lcd.setCursor(6,0);
      lcd.print(opCode);
      lcd.setCursor(2,1);
      lcd.print(param1 + " " + param2 + " " + param3);
    }
    brenchFlag = false;
  }
  
  opCode = "";
  param1 = "";
  param2 = "";
  param3 = "";
  
  delay(CLOCK);
  lcd.clear();
}

void writeRegister(byte address, byte value){
  EEPROM.write(address, value);
}

byte readRegister(byte address){
    byte value = EEPROM.read(address);
    return value;
}
