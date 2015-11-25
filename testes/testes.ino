#include <EEPROM.h> // incluir a biblioteca
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



LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

void setup(){
  Serial.begin(9600);
  
  lcd.begin(16, 2); 
  lcd.setCursor(0,0); 
}

void loop(){
  /*Endereço da EEPROM*/
  //int address = 0;
  /*lEITURA*/
  //byte value = EEPROM.read(address);
  /*ESCRITA*/
  //EEPROM.write(address,value);
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
    char  param1 = (char)Serial.read();
    char  param2 = (char)Serial.read();
    char  param3 = (char)Serial.read();
    /*(.........)*/
    
  }else{
    Serial.println("Instruction ADD ERROR");
  }
  
}

void executeSUB(){
  if(Serial.available()==3){
    char  param1 = (char)Serial.read();
    char  param2 = (char)Serial.read();
    char  param3 = (char)Serial.read();
    
    /*(.........)*/
    
  }else{
    Serial.println("Instruction SUB ERROR");
  }
}

void executeADDI(){
  if(Serial.available()==3){
    char  param1 = (char)Serial.read();
    char  param2 = (char)Serial.read();
    char  param3 = (char)Serial.read();
    /*(.........)*/
    
  }else{
    Serial.println("Instruction ADDI ERROR");
  }
  
}

void executeLW(){
  if(Serial.available()==3){
    char  param1 = (char)Serial.read();
    char  param2 = (char)Serial.read();
    char  param3 = (char)Serial.read();
    
    /*(.........)*/
    
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
