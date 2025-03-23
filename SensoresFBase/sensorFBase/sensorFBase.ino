#include <WiFi.h>                          //importa biblioteca para conectar esp32 com wifi
#include <IOXhop_FirebaseESP32.h>          //importa biblioteca para esp32 se comunicar com firebase
#include <ArduinoJson.h>                   //importa biblioteca para colocar informação no formato json, utilizado no firebase (intalar versão 5)
#include <OneWire.h>
#include <DallasTemperature.h>
# define DOOR_SENSOR_PIN 18   // pino GPIO19 do ESP32 conectado ao pino do sensor da porta

#define WIFI_SSID "Redmi 9"                  
#define WIFI_PASSWORD "fernanda"             
#define FIREBASE_HOST "https://sensorfirebase-dd9ec-default-rtdb.firebaseio.com/"    
#define FIREBASE_AUTH "AIzaSyBz6ipvQz3jOxOcaOWjyeRV327xvX7JgN4"   

int doorState;

const int oneWireBus = 15;     

OneWire oneWire(oneWireBus);


DallasTemperature sensors(&oneWire);
void setup() {

  Serial.begin(115200);

  sensors.begin();

  pinMode(DOOR_SENSOR_PIN, INPUT_PULLUP);

  //Ligação à Rede Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);     //inicia comunicação com wifi com rede definica anteriormente
  
  Serial.print("Conectando ao wifi");       //imprime "Conectando ao wifi"
  while (WiFi.status() != WL_CONNECTED)     //enquanto se conecta ao wifi fica colocando pontos
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();                         //imprime pulo de linha

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   //inicia comunicação com firebase definido anteriormente
}

void loop() {
  sensors.requestTemperatures(); 
  float temperatureC = sensors.getTempCByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Firebase.setFloat("/Dados/Temperatura", temperatureC);
  delay(5000);

  doorState = digitalRead(DOOR_SENSOR_PIN); // read state

  if (doorState == HIGH) {
    Serial.println("A porta esta Aberta!");
    Firebase.setString("/Dados/EstadoPorta", "A porta esta Aberta!");
  } else {
    Serial.println("A porta está fechada!");
    Firebase.setString("/Dados/EstadoPorta", "A porta esta Fechada!");
  }
}
