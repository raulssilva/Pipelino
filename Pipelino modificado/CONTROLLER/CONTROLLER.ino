// Makers: Felipe Barbalho Rocha and Raul Silveira Silva


#define CLOCK 3000

void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
}
byte pcLine = 0;
void loop() {
  while(Serial.available()){
    pcLine = (byte)(Serial.read()-48);
  }
  if(pcLine != 0){
    Serial.print((char)pcLine);
    digitalWrite(2, HIGH);
    delay(CLOCK);
    digitalWrite(2, LOW);
    pcLine = 0;
  }
}
