#include <Arduino.h>

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <max6675.h>
#include "config.h"

WiFiClientSecure client;
HTTPClient https;

int thermoDO = 19;
int thermoCS = 5;
int thermoCLK = 18;

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void setClock() {
  configTime(0, 0, "pool.ntp.org");

  Serial.print(F("Waiting for NTP time sync: "));
  time_t nowSecs = time(nullptr);
  while (nowSecs < 8 * 3600 * 2) {
    delay(500);
    Serial.print(F("."));
    yield();
    nowSecs = time(nullptr);
  }

  Serial.println();
  struct tm timeinfo;
  gmtime_r(&nowSecs, &timeinfo);
  Serial.printf("Current time: %s", asctime(&timeinfo));
}

void setup() {
  Serial.begin(115200);

  Serial.printf("Attempting to connect to wifi with SSID: %s\n", ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.printf("Connected to %s\n", ssid);

  setClock();

  client.setCACert(ca_cert);
  client.setCertificate(client_cert);
  client.setPrivateKey(client_key);
}

void loop() {
  time_t now = time(nullptr);
  struct tm timeinfo;
  gmtime_r(&now, &timeinfo);

  Serial.printf("Heartbeat: %ld - %s", millis(), asctime(&timeinfo));
  delay(3000);

  float temp = thermocouple.readFahrenheit();
  Serial.printf("temp: %.2f\n", temp);
  char buffer[256];
  snprintf(buffer, sizeof(buffer), "# TYPE stove_temp gauge\nstove_temp %.2f\n", temp);
  
  Serial.print("[HTTPS] begin...\n");
  if (https.begin(client, prompush_url)) {
    int httpCode = https.POST((uint8_t*)buffer, strlen(buffer));
    Serial.printf("[HTTPS] POST... code: %d\n", httpCode);
    https.end();
  }
}                                                                                                                                                                                                                                   
