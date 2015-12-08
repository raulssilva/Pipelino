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

#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

/**/
SoftwareSerial controllerSerial(10, 11); // RX, TX
LiquidCrystal lcd(9, 8, 5, 6, 3, 2);

/*Operadores para exibição no Display LCD apartir do código recebido pela serial*/
const String operators[] = {"ADD","SUB","ADDI","LW","SW","SLL","SRL","BEQ","BNE"};

/*Registradores para exibição no Dsiplay LCD apartir do código recebido pela serial*/
const String registers[] = {"$0","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7"};

#define CLOCK 3000

void setup(){
  // Inicia o LCD 16x2
  lcd.begin(16, 2);
  // Inicia a Serial com um baudrate de 9600bps
  Serial.begin(9600);
  // Inicia a Serial do Write Back com um baudrate de 9600bps
  controllerSerial.begin(9600);
}

/*String que serão exibidas no LCD*/
String opCode = "";
String param1 = "";
String param2 = "";
String param3 = "";

/*intruções recebidas pela serial*/
byte opCodeByte = 0;
byte param1Byte = 0;
byte param2Byte = 0;
byte param3Byte = 0;

/*Irar auxiliar durante as operações*/
byte aux;


void loop(){
  
  if(Serial.available()){
    if(opCode == ""){
      /*Lêr o opcode*/	
      opCodeByte = (byte)(Serial.read()-48);

      /*Armazena a String do opcode para exibição no LCD*/	
      opCode = operators[opCodeByte];
    }
    
    switch(opCodeByte){
      case 0:
        /*Lêr da serial o valor dos parâmetros*/
        param1Byte = (byte)(Serial.read()-48);
        param2Byte = (byte)Serial.read();
        param3Byte = (byte)Serial.read();

 	      /*soma e armazena em param2Byte (por economia)*/
        param2Byte += param3Byte;
	
        /*Armazena nas String para exibição no LCD*/
        param1 = registers[param1Byte];
        param2 = (String)param2Byte;
	
        /*Envia os parâmetros para o estágio da Memória*/
        Serial.write(opCodeByte);
        Serial.write(param1Byte);
        Serial.write(param2Byte);

        break;
      case 1:
        /*Lêr da serial o valor dos parâmetros*/
        param1Byte = (byte)(Serial.read()-48);
        param2Byte = (byte)Serial.read();
        param3Byte = (byte)Serial.read();
	
        /*subtrai e armazena em param2Byte (por economia)*/
        param2Byte -= param3Byte;

        /*Armazena nas String para exibição no LCD*/
        param1 = registers[param1Byte];
        param2 = (String)param2Byte;

        /*Envia os parâmetros para o estágio da Memória*/
        Serial.write(opCodeByte);
        Serial.write(param1Byte);
        Serial.write(param2Byte); /*Não tratamos valores negativos*/

        break;
      case 2:
        /*Lêr da serial o valor dos parâmetros*/
        param1Byte = (byte)(Serial.read()-48);
        param2Byte = (byte)Serial.read();
        param3Byte = (byte)Serial.read();
	
        /*soma e armazena em param2Byte (por economia)*/
        param2Byte += param3Byte;

        /*Armazena nas String para exibição no LCD*/
        param1 = registers[param1Byte];
        param2 = (String)param2Byte;

        /*Envia os parâmetros para o estágio da Memória*/
        Serial.write(opCodeByte);
        Serial.write(param1Byte);
        Serial.write(param2Byte);

        break;
      case 3:
        /*Lêr da serial o valor dos parâmetros*/
        param1Byte = (byte)(Serial.read()-48);
        param2Byte = (byte)Serial.read();
        param3Byte = (byte)Serial.read();

        /*Armazena nas String para exibição no LCD*/
        param1 = registers[param1Byte];
        param2 = (String)param2Byte;
        param3 = (String)param3Byte;
        
        /*Envia os parâmetros para o estágio da Memória*/
        Serial.write(opCodeByte);
        Serial.write(param1Byte);
        Serial.write(param2Byte);
        Serial.write(param3Byte);

        break;
      case 4:
        /*Lêr da serial o valor dos parâmetros*/
        param1Byte = (byte)Serial.read();
        param2Byte = (byte)Serial.read();
        param3Byte = (byte)Serial.read();

        /*Armazena nas String para exibição no LCD*/
        param1 = (String)param1Byte;
        param2 = (String)param2Byte;
        param3 = (String)param3Byte;

        /*Envia os parâmetros para o estágio da Memória*/
        Serial.write(opCodeByte);
        Serial.write(param1Byte);
        Serial.write(param2Byte);
        Serial.write(param3Byte);

        break;
      case 5:
        /*Lêr da serial o valor dos parâmetros*/
        param1Byte = (byte)(Serial.read()-48);
        param2Byte = (byte)Serial.read();
        param3Byte = (byte)Serial.read();

        /*Variavel para alocar o valor com o shift*/
        aux = (param2Byte << param3Byte);

        /*Armazena nas String para exibição no LCD*/
        param1 = registers[param1Byte];
        param2 = (String)aux;

        /*Envia os parâmetros para o estágio da Memória*/
        Serial.write(opCodeByte);
        Serial.write(param1Byte);
        Serial.write(aux);

        break;
      case 6:
        /*Lêr da serial o valor dos parâmetros*/
        param1Byte = (byte)(Serial.read()-48);
        param2Byte = (byte)Serial.read();
        param3Byte = (byte)Serial.read();

        /*Variavel para alocar o valor com o shift*/
        aux = (param2Byte >> param3Byte);

        /*Armazena nas String para exibição no LCD*/
        param1 = registers[param1Byte];
        param2 = (String)aux;

        /*Envia os parâmetros para o estágio da Memória*/
        Serial.write(opCodeByte);
        Serial.write(param1Byte);
        Serial.write(aux);

        break;

      case 7:
        /*Lêr da serial o valor dos parâmetros*/
        param1Byte = (byte)Serial.read();
        param2Byte = (byte)Serial.read();

        /*Verificacao booleana do brench*/
        param1 = "False";
        if(param1Byte == param2Byte){
          aux = 1;
          param1 = "True";
          param2Byte = (byte)Serial.read();
          param2 = (String)param2Byte;
          controllerSerial.print(param2Byte);
        }

        break;

      default:
        /*Lêr da serial o valor dos parâmetros*/
        param1Byte = (byte)Serial.read();
        param2Byte = (byte)Serial.read();
	
        /*Verificacao booleana do brench*/
        param1 = "False";
        if(param1Byte != param2Byte){
          aux = 1;
          param1 = "True";
          param2Byte = (byte)Serial.read();
          param2 = (String)param2Byte;
          controllerSerial.print(param2Byte);
        }
    }
    /*Exibe no LCD a operacao e os valores operados*/
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print(opCode);
    lcd.setCursor(2,1);
    lcd.print(param1 + " " + param2 + " " + param3);
  }
  /*Limpa as variaveis de entrada*/
  opCode = "";
  param1 = "";
  param2 = "";
  param3 = "";
 
  delay(CLOCK);
  lcd.clear();
}









