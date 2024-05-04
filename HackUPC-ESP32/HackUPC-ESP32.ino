
#include "config.h" // Incluye el archivo config.h que acabamos de crear
#include <HTTPClient.h>
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  pinMode(LDR_PIN, INPUT);

  Serial.println("Conectando a Wi-Fi");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }
}

void loop() {
  Serial.println("Conexión establecida");
  int sensorValue = analogRead(LDR_PIN);
  Serial.println(sensorValue);
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverAddress);

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
