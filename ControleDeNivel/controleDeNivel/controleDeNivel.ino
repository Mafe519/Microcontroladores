#include <Arduino.h>
#include <PID_v1.h>  // Inclui a biblioteca de controle PID

#define SOUND_SPEED 0.034  // Define a velocidade do som em cm/us (constante)

const int triggerPin = 12;  // Pino Trigger do sensor ultrassônico (responsável por enviar o pulso)
const int echoPin = 13;     // Pino Echo do sensor ultrassônico (recebe o pulso refletido)
const int pwmPin = 4;       // Pino de saída PWM para controlar a bomba

// Variáveis para medir o tempo de pulso e calcular a altura da água
long tempoDePulso;
float altura;  // Armazena a altura da água em cm

// Configuração do PID
double setpoint = 10.0;    // Nível de água desejado, inicialmente 10 cm
double input, output;      // Variáveis para armazenar o valor atual do sistema e a saída do PID
double Kp = 2.5, Ki = 6.0, Kd = 1.2; // Parâmetros do controlador PID (ajustados)

const double maxLevel = 18.0; // Altura máxima da caixa d'água em cm
const double minLevel = 0;    // Altura mínima da caixa d'água

// Inicializa o objeto PID com os ponteiros para input, output, e setpoint, e os valores Kp, Ki, e Kd
PID myPID(&input, &output, &setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(115200);  // Inicializa a comunicação serial a 115200 bps

  // Configuração dos pinos do sensor e da bomba
  pinMode(triggerPin, OUTPUT);  // Pino do Trigger como saída
  pinMode(echoPin, INPUT);      // Pino do Echo como entrada
  pinMode(pwmPin, OUTPUT);      // Pino do PWM como saída para a bomba

  // Ativando o PID no modo automático
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(20, 255); // Define os limites da saída do PID (20 a 255)

  // Inicia o PWM da bomba com valor zero
  analogWrite(pwmPin, 0);

  // Exibe uma mensagem solicitando o nível desejado
  Serial.println("Insira o nivel desejado (em cm) entre 3 e 16 cm:");
}

void loop() {
  // Verifica se há dados disponíveis na serial
  if (Serial.available() > 0) {
    // Lê o valor de nível desejado inserido pelo usuário
    double userInput = Serial.parseFloat();
    
    // Verifica se o valor inserido está entre os limites permitidos
    if (userInput >= minLevel && userInput <= maxLevel) {
      setpoint = userInput;  // Atualiza o setpoint para o valor inserido
      Serial.print("Nivel desejado atualizado para: ");
      Serial.print(setpoint);
      Serial.println(" cm");
    } else {
      // Mensagem de erro se o valor estiver fora dos limites
      Serial.println("Erro: Nivel fora dos limites permitidos. Insira um valor entre 3 e 16 cm.");
    }
  }

  // Limpa o buffer serial
  while(Serial.available() > 0){
    Serial.read();
  }

  // Medição do nível de água usando o sensor ultrassônico
  digitalWrite(triggerPin, LOW);  // Garante que o Trigger comece em LOW
  delayMicroseconds(2);           // Pequena pausa antes de enviar o pulso
  digitalWrite(triggerPin, HIGH); // Envia um pulso de 10 µs
  delayMicroseconds(10);          
  digitalWrite(triggerPin, LOW);  // Termina o pulso

  // Medindo o tempo de retorno do pulso pelo Echo
  tempoDePulso = pulseIn(echoPin, HIGH);  // Mede o tempo até o pulso voltar

  // Calcula a altura da água (20 cm é a altura máxima)
  altura = 20 - (tempoDePulso * SOUND_SPEED / 2);  // Calcula a distância baseada no tempo de retorno do som

  // Exibe o nível atual da água no monitor serial
  Serial.print("Nivel Atual: ");
  Serial.print(altura);
  Serial.println(" cm");

  // Atualiza a entrada do PID com o nível atual e calcula a nova saída
  input = altura;
  myPID.Compute();  // Calcula o novo valor de saída baseado na diferença entre setpoint e input

  // Ajuste fino para quando a altura está próxima do setpoint ou o setpoint é menor que a altura
  if ((abs(setpoint - altura) <= 0.1) || setpoint < altura) {  
      while(output > 80){  // Se a saída for maior que 80, diminui gradativamente
        output -=5;
        delay(5);
      }
  }  

  // Define o valor de PWM para a bomba baseado na saída do PID, garantindo que nunca seja menor que 20
  int pwmOutput = max(20.0, output);  
  analogWrite(pwmPin, pwmOutput);  // Aplica o PWM calculado à bomba

  // Exibe o valor do PWM no monitor serial
  Serial.print("PWM Output: ");
  Serial.println(pwmOutput);

  // Aguarda 500 ms antes de repetir o loop
  delay(500);
}
