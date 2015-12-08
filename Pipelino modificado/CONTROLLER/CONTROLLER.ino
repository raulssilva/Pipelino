// Makers: Felipe Barbalho Rocha and Raul Silveira Silva

#define CLOCK 3000

void setup() {
  // Inicia a Serial com a baudrate de 9600bps
  Serial.begin(9600);
  // Define o pino 2 como saida para informar o ID se houve salto ou nao
  pinMode(2, OUTPUT);
}

// Contagem de linhas a serem puladas
byte pcLine = 0;

void loop() {
  // Verificando se houve salto
  while(Serial.available()){
    pcLine = (byte)(Serial.read()-48);
  }

  if(pcLine != 0){
    // Envia para o IF a quantidade de linhas a serem saltadas
    Serial.print((char)pcLine);
    // Avisa ao ID que houve salto
    digitalWrite(2, HIGH);
    delay(CLOCK);
    digitalWrite(2, LOW);
    pcLine = 0;
  }
}
