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
 * LCD RS pin to digital pin 10
 * LCD Enable pin to digital pin 9
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
LiquidCrystal lcd(10, 9, 5, 6, 3, 2);

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
  
  File assemblyFile = SD.open("Assembly_Code.txt");

  if (assemblyFile){
    // Read byte-by-byte from the file until there's nothing else in it
    while (assemblyFile.available()) {
      Serial.write(assemblyFile.read());
    }
    assemblyFile.close();
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









