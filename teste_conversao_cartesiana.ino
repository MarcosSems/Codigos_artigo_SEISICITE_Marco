#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>
#include <math.h>

// Cria uma instância do sensor MPU6050
Adafruit_MPU6050 mpu;

// Variáveis para controlar o tempo e o deslocamento
unsigned long tempoAnterior = 0;
double posicaoX = 0.0;
double posicaoY = 0.0;
double posicaoZ = 0.0;
double correcaoG = 9.964; // Valor de correção para a aceleração da gravidade
double ang_anteriorY = 0.0;
double ang_anteriorZ = 0.0;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }

  Wire.begin();

  // Inicializa o sensor MPU6050
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  // Configuração do sensor MPU6050
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setAccelerometerRange(MPU6050_RANGE_2_G);
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  double aceleracaoX = a.acceleration.x;
  double aceleracaoY = a.acceleration.y;
  double aceleracaoZ = a.acceleration.z;

  double rotacaoY = g.gyro.y;
  double rotacaoZ = g.gyro.z;

  //---------Conversão a partir da aceleração estática-------------------------

  // Obtém o tempo atual em milissegundos
  unsigned long tempoAtual = millis();

  // Calcula o tempo decorrido em segundos desde a última medição
  double tempoDecorrido = (tempoAtual - tempoAnterior) / 1000.0;

  // Conversão da aceleração no eixo X (aceleração estática)
  double aceleracaoXAjustada = aceleracaoX - correcaoG;
  double deslocamentoX = 0.5 * (aceleracaoXAjustada) * tempoDecorrido * tempoDecorrido;
  posicaoX += deslocamentoX;

  //---------Conversão partindo de aceleração dinâmica------------------------------

  // Converte rotações para ângulos em radianos
  double anguloY = rotacaoY * tempoDecorrido;
  double anguloZ = rotacaoZ * tempoDecorrido;

  double cosTheta = cos(anguloZ);
  double cosPhi = cos(anguloY);

  // Conversão da aceleração no eixo Y considerando componente da gravidade
  double aceleracaoYAjustada = aceleracaoY - (9.8 * cosPhi);
  double deslocamentoY = 0.5 * (aceleracaoYAjustada) * tempoDecorrido * tempoDecorrido;

  // Conversão da aceleração no eixo Z considerando componente da gravidade
  double aceleracaoZAjustada = aceleracaoZ - (9.8 * cosTheta);
  double deslocamentoZ = 0.5 * (aceleracaoZAjustada) * tempoDecorrido * tempoDecorrido;

  // Atualiza as variáveis de ângulo anterior, tempo anterior e posições
  ang_anteriorY += anguloY;
  ang_anteriorZ += anguloZ;
  tempoAnterior = tempoAtual;
  posicaoY += deslocamentoY;
  posicaoZ += deslocamentoZ;

  // Imprime os valores de deslocamento X, Y e Z
  Serial.print("Deslocamento X (m): ");
  Serial.println(posicaoX);

  Serial.print("Deslocamento X (de Z para X) (m): ");
  Serial.println(posicaoZ);

  Serial.print("Deslocamento X (de Y para X) (m): ");
  Serial.println(posicaoY);

  Serial.print("Deslocamento X (de Z para X) (m): ");
  Serial.println(posicaoZ);

  delay(500); // Aguarda 500 milissegundos antes da próxima iteração
}
