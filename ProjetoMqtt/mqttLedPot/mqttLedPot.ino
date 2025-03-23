#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Redmi 9";
const char* password = "fernanda";
const char* mqtt_server = "broker.hivemq.com";

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE 50
char msg[MSG_BUFFER_SIZE];  // Corrigido: mudado para array de char

const int LED = 12;
const int Potenciometro = 35;
int potValue = 0;  // Corrigido o nome da variável
int ledState = 0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  // Corrigido: mudado de Wifi.localIP() para WiFi.localIP()
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if ((char)payload[0] == 'L') {
      digitalWrite(LED, HIGH);
      snprintf(msg, MSG_BUFFER_SIZE, "O LED está aceso");
      Serial.print("Publica mensagem: ");
      Serial.println(msg);
      client.publish("mariaMicro/led", msg);
    }
    if((char)payload[0] == 'D') {
      digitalWrite(LED, LOW);
      snprintf(msg, MSG_BUFFER_SIZE, "O LED está apagado");  // Corrigido: faltava ponto e vírgula
      Serial.print("Publica mensagem: ");
      Serial.println(msg);
      client.publish("mariaMicro/led", msg);
    }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP32Client-";  // Corrigido: inicializando corretamente clientId
    clientId += String(random(0xffff), HEX);

    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado");
      client.subscribe("mariaMicro");
    } else {
      Serial.print("failed, rc=");
      Serial.println(client.state());  // Corrigido: imprimir o estado do cliente
      Serial.println("try again in 5 seconds");
      delay(5000);  // Corrigido: alterado para 5000ms
    }
  }
}

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);  // Corrigido: mudado de serial.begin para Serial.begin
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

    potValue = (analogRead(Potenciometro))/16;
 
    char buffer[50];
    snprintf(msg, MSG_BUFFER_SIZE, "%d", potValue);
    Serial.println(msg);
    client.publish("mariaMicro/potenciometro", msg);

  delay(100);
}
