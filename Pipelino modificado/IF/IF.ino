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
#define CLOCK 3000

// Definicao dos pinos do LCD para exibicao das informacoes
LiquidCrystal lcd(9, 8, 5, 6, 3, 2);

// Array com as operacoes que podem ser usadas. Cada indice representa o OP code
const String operators[] = {"ADD","SUB","ADDI","LW","SW","SLL","SRL","BEQ","BNE"};
// Array com os registradores que podem ser usados. Cada indice representa a referencia do registrador na EEPROM
const String registers[] = {"$0","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7"};

void setup(){
  // Inicia o LCD 16x2
  lcd.begin(16, 2);
  // Inicia a Serial com um baudrate de 9600bps
  Serial.begin(9600);
  
  // Mensagem inicial no LCD
  lcd.setCursor(2, 0);
  lcd.print("Initializing");
  lcd.setCursor(3, 1);
  lcd.print("SD card...");
  
  // Verificacao do cartao
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
  
  // Abrir arquivo com codigo Assembly
  File assemblyFile = SD.open("code.txt");
  
  // Verificacao do arquivo com codigo
  if (assemblyFile){
    String opCode = "";
    String param1 = "";
    String param2 = "";
    String param3 = "";
    
    // Le do arquivo byte-a-byte ate que nao tenha mais nada a ser lido
    while (assemblyFile.available()) {
      // Verifica se houve salto e pula a quantidade de linhas que foram informadas
      if(Serial.available()==1){
        byte brench = (byte)Serial.read();
        for(brench -= 1; brench > 0; brench--){
          while(assemblyFile.read() != '\n'){
          }
        }
      }

      // Se o OP code nao tiver sido lido, significa que o primeiro byte e do OP code
      if(opCode == ""){
        opCode = readParam(assemblyFile);
        for(byte i = 0; i<9; i++){
          if(operators[i] == opCode){
            Serial.print(i);
          }
        }
      }
      
      // Apos a leitura do OP code e verificado quais dados devem ser lidos, baseados no OP code
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
      
      // Limpa o LCD e escreve a operacao seguida dos operandos
      lcd.clear();
      lcd.setCursor(6,0);
      lcd.print(opCode);
      lcd.setCursor(2,1);
      lcd.print(param1 + " " + param2 + " " + param3);

      // Aguarda um tempo para a proxima interaca do pipeline
      delay(CLOCK);
      
      // Limpa as variaveis de leitura
      opCode = "";
      param1 = "";
      param2 = "";
      param3 = "";

    }

    // Fecha o arquivo apos a leitura de todo o programa
    assemblyFile.close();
    
    // Limpa o LCD e informa que o programa foi concluido
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("End of program");
    
  // Caso o arquivo com codigo em Assembly nao seja encotrado, informa que nao ha codigo no cartao
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

/*
 * Le um parametro da instrucao
 * @param assemblyFile Arquivo aberto.
 * @return String com o parametro lido.
 */
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

/*
 * Le uma constante da instrucao
 * @param assemblyFile Arquivo aberto.
 * @return String com a constante lida.
 */
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
