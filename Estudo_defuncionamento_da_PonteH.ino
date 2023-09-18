int motor1a = 5;//portasGpio //A_1A
int motor1b = 4;//portasGpio // A_1B
int motor2a = 14; //portasGpio// B_1A
int motor2b = 12; //portasGpio// B_1B

int velocidade = 200; // velocidade inicial dos motores

void setup() {

  pinMode(motor1a, OUTPUT);
  pinMode(motor1b, OUTPUT);
  pinMode(motor2a, OUTPUT);
  pinMode(motor2b, OUTPUT);
}

void loop() {

  // Movimento para frente
  analogWrite(motor1a, velocidade);
  digitalWrite(motor1b, LOW);
  analogWrite(motor2a, velocidade);
  digitalWrite(motor2b, LOW);
  delay(2000);

  // Movimento para trás
  digitalWrite(motor1a, LOW);
  analogWrite(motor1b, velocidade);
  digitalWrite(motor2a, LOW);
  analogWrite(motor2b, velocidade);
  delay(2000);

  // Movimento para esquerda
  analogWrite(motor1a, velocidade);
  digitalWrite(motor1b, HIGH);
  analogWrite(motor2a, velocidade);
  digitalWrite(motor2b, LOW);
  delay(2000);

  // Movimento para direita
  analogWrite(motor1a, velocidade);
  digitalWrite(motor1b, LOW);
  analogWrite(motor2a, velocidade);
  digitalWrite(motor2b, HIGH);
  delay(2000);
  
  // Teste decremento velocidade 
  //if (velocidade > 0) {
  //  velocidade--;
  //}
}
