#include <LiquidCrystal.h> 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 
int incomingByte, x, y; 

void setup() { 
  Serial.begin(9600); 
  
} 
void loop() { 
}

void serialEvent() {
  
  /*Ler uma String toda*/
   String inString = Serial.readString();
   Serial.println(inString);
   lcd.clear();
   lcd.println(inString);
   /*Ler char a char*/
  //char inChar = (char)Serial.read();
  //Serial.println(inChar);
}


