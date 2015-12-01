void setup() {
  Serial.begin(9600);
}
byte pcLine = 0;
void loop() {
  while(Serial.available()){
    pcLine = (byte)(Serial.read()-48);
  }
  if(pcLine != 0){
    Serial.print((char)pcLine);
    pcLine = 0;
  }
}
