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

const String operators[] = {"ADD","SUB","ADDI","LW","SW","SLL","SRL","BEQ","BNE"};

byte memoryLogic[512] = {0};

#define CLOCK 3000

#define MEMORIA "MEM.txt"

void setup(){
  
  Serial.begin(9600);
  
  /*Procedimento de leitura do LCD*/
  lcd.begin(16, 2);
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
}

void loop(){
     
}

/*Interrupção da Serial*/
void serialEvent(){
    /*Tempo para chegar todos os bytes*/
    delay(10);
	
    /*Lêr a operação*/
    byte op = Serial.read();
    
    /*Mensagem que será exibida no LCD*/
    String saidaLCD = "";

    if(Serial.available()>=2){
	
       /*Load Word*/
       if( op == LW){
          byte reg = Serial.read();
          byte cons = Serial.read();
          byte address = Serial.read();
          int addressReal = cons + address;
          byte data = readMemory(addressReal);

          outLCD(operators[op-48], "Loading $"+String(addressReal));
        
          putNext(reg, data);
      
      /*Store Word*/
      }else if( op == SW){
          byte data = Serial.read();
          byte cons = Serial.read();
          byte address = Serial.read();
          int addressReal = cons + address;
          writeMemory(addressReal, data);

          outLCD(operators[op-48], "Store $"+String(addressReal));

      /*Direto para o Write Back*/
      }else if(op == ADD || op == SUB || op == ADDI || op == SLL || op == SRL){
          byte reg = Serial.read();
          byte value = Serial.read();
          putNext(reg, value);

          outLCD(operators[op-48], " WriteBack");
        
      }else if(op == BEQ || op == BNE){
          /*Não faz nada*/
        
      }else{
          /*ERRO*/
      }
    }
}

/*Exibe a intrução no Display LCD*/
void outLCD(String title, String description){
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print(title);
  lcd.setCursor(2,1);
  lcd.print(description);
  delay(CLOCK);
  lcd.clear();
}

/*Envia os dados para write back*/
void putNext(byte reg, byte value){
    Serial.write(reg);
    Serial.write(value);
}

/*Lêr um byte apartir de um endereço da memória e retorna o byte lido*/
byte readMemory(int address){
  byte data =  memoryLogic[address];
  return data;
}

/*Escreve um byte na memória papartir do endereço informado*/
void writeMemory(int address, byte data){
  //Salva na memória lógica
  memoryLogic[address] = data;

  SD.remove(MEMORIA);
  //Abre o arquivo
  File memory = SD.open(MEMORIA, FILE_WRITE);

  //Salva a memória lógica no arquivo
  for (int i = 0; i < 512; i++) {
     int n = memoryLogic[i];
     memory.println(n);
  }

  //Fecha o arquivo
  memory.close();
}

