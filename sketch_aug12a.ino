#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

#define USE_SERIAL Serial

#define LED_PIN 2

WiFiMulti wifiMulti;

void setup() {
  USE_SERIAL.begin(115200);

  
  pinMode(LED_PIN, OUTPUT);

  wifiMulti.addAP("iPhone", "Rayan901");
}

void loop() {
  
  if ((wifiMulti.run() == WL_CONNECTED)) {

    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    
    
    http.begin("http://rayan09.freehosting.dev/status.txt"); 

    USE_SERIAL.print("[HTTP] GET...\n");
    int httpCode = http.GET();

    if (httpCode > 0) {
      USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        
        payload.trim(); 
        
        USE_SERIAL.println("Payload: " + payload);

        
        if (payload == "1") {
          digitalWrite(LED_PIN, HIGH);
          USE_SERIAL.println("LED Status: ON");
        } else {
          digitalWrite(LED_PIN, LOW);
          USE_SERIAL.println("LED Status: OFF");
        }
      }
    } else {
      USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(2000); 
}