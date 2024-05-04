
#include "config.h" // Incluye el archivo config.h que acabamos de crear
#include <WiFi.h>

<<<<<<< Updated upstream
=======
const char* ssid = "HACKUPC2024B";
const char* password = "Biene2024!";

#define ServerPort 1999
#define ServerIP "192.168.72.52"

>>>>>>> Stashed changes
WiFiClient TcpClient;

void setup() {
  Serial.begin(115200);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("WiFi connected!");
  Serial.println(WiFi.localIP());

  Serial.println("TcpClient is connecting to server");

  while (!TcpClient.connect(ServerIP, ServerPort)) {
    Serial.println("Connection to server failed");
    delay(2000);
  }

  Serial.println("Connected to server successful!");
}

void loop() {
  if (TcpClient.connected()) {
    if (Serial.available() > 0) {
      String msg = Serial.readStringUntil('\n');
      msg.trim(); // Remove leading/trailing whitespace

      if (msg == "close") {
        TcpClient.stop();
        Serial.println("Client disconnected");
        while (true) {
        } // Infinite loop to stop further execution
      }

      msg += "$"; // Add terminator character
      TcpClient.print(msg);
      Serial.println("Message sent");
    }
  } else {
    Serial.println("Connection lost. Reconnecting...");
    TcpClient.connect(ServerIP, ServerPort);
  }

  delay(1000);
}
