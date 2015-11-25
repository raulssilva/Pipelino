#include <EEPROM.h> // incluir a biblioteca
#include <LiquidCrystal.h> 

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
  /*isso na verdade é p op*/
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
       case 'A':
         instructionAContext();
         break;
       case 'B':
         instructionBContext();
         break;
       default:
         Serial.println("Instruction ERROR");
         break;
    }
}


void instructionAContext(){
  if(Serial.available()==3){
    char  param1 = (char)Serial.read();
    char  param2 = (char)Serial.read();
    
    /*(.........)*/
    
  }else{
    Serial.println("Instruction A ERROR");
  }
  
}

void instructionBContext(){
  if(Serial.available()==3){
    char  param1 = (char)Serial.read();
    char  param2 = (char)Serial.read();
    char  param3 = (char)Serial.read();
    
    /*(.........)*/
    
  }else{
    Serial.println("Instruction B ERROR");
  }
}
