#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "AndroidAP";
const char* password = "gsw@1234";
const char* serverUrl = "http://192.168.43.244:5000/endpoint";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    // Create JSON payload
    DynamicJsonDocument json(1024);
    json["sensor"] = "ESP32";
    json["value"] = random(100);

    // Convert JSON to string
    String payload;
    serializeJson(json, payload);

    // Send HTTP POST request
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");
    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("HTTP Error code: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }

  delay(5000); // Send data every 5 seconds
}
