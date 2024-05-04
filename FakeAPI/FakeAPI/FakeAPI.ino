#include <WiFi.h>
#include <HTTPClient.h>
// #include <DebouncedLDR.h>

// const char* ssid = "HACKUPC2024B";
// const char* password = "Biene2024!";
const char* ssid = "pau";
const char* password = "pau12345";
const int LDR_PIN = 34;
// DebouncedLDR ldr(1023, 9, 100);

int init1;

void setup() {
  Serial.begin(115200);
  pinMode(LDR_PIN, INPUT);

  Serial.println("Conectando a Wi-Fi");
  WiFi.begin(ssid, password);
  // init1 = 1;

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }

}

void loop() {
  // if (init1){

  //   init1 = 0;
  // }
  

  Serial.println("Conexión establecida");
  int sensorValue = analogRead(LDR_PIN);
  Serial.println(sensorValue);
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String serverAddress = "http://192.168.72.18:5000/data/create";
    http.begin(serverAddress);
    
    // Leer el valor del sensor
    // unsigned int sensorValue = analogRead(LDR_PIN);
    // int sensorValue = 33;
    // Serial.println(sensorValue);
    // Convertir el valor del sensor a una cadena
    // String sensorValueStr = String(sensorValue);

    // Construir el JSON con el valor del sensor
    String jsonPayload = "{";
    jsonPayload += "\"value\": ";
    jsonPayload += sensorValue;
    jsonPayload += "}";

    // Configurar la cabecera de la solicitud POST
    http.addHeader("Content-Type", "application/json");

    // Realizar la solicitud POST con el JSON
    int httpResponseCode = http.POST(jsonPayload);
    
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Solicitud exitosa");
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.println("Error en la solicitud:");
      Serial.println(httpResponseCode);
    }

    // Cierra la conexión
    http.end();
  } else {
    Serial.println("Error en la conexión a Wi-Fi");
  }

  delay(5000); // Espera 5 segundos antes de realizar la siguiente solicitud
}
