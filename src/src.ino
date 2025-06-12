
#include <WiFi.h>
#include <WebServer.h>
#include <SPIFFS.h>
#include <HTTPClient.h>
#include <Update.h>
#include <ArduinoJson.h>

#define FIRMWARE_URL "https://github.com/Rodrigo5036/colabi/releases/download/v-latest/firmware.bin"
#define AP_SSID "ESP32_SETUP"
#define AP_PASS ""
#define CONFIG_FILE "/config.json"

WebServer server(80);

String ssid = "";
String password = "";

void setup() {
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  delay(500);
  Serial.println("🔌 Iniciando ESP32...");

  if (!SPIFFS.begin(true)) {
    Serial.println("❌ Error iniciando SPIFFS");
    return;
  }

  loadCredentials();

  if (ssid == "") {
    startAPMode();
  } else {
    connectToWiFi();
  }

  setupServer();
}

void loop() {
  server.handleClient();

  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(500);
}


void loadCredentials() {
  File file = SPIFFS.open(CONFIG_FILE);
  if (!file) {
    Serial.println("⚠️ No se encontró configuración WiFi");
    return;
  }

  StaticJsonDocument<256> doc;
  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.println("❌ Error leyendo JSON");
    return;
  }

  ssid = doc["ssid"].as<String>();
  password = doc["password"].as<String>();
}

void connectToWiFi() {
  Serial.printf("🔗 Conectando a %s...
", ssid.c_str());
  WiFi.begin(ssid.c_str(), password.c_str());

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 15000) {
    delay(500);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Conectado a WiFi!");
    Serial.print("IP local: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n⚠️ Fallo al conectar, iniciando modo AP");
    startAPMode();
  }
}

void startAPMode() {
  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.println("📡 Modo AP iniciado");
  Serial.print("IP AP: ");
  Serial.println(WiFi.softAPIP());
}

void setupServer() {
  server.on("/", HTTP_GET, []() {
    String html = "<h2>Configuración WiFi</h2><form method='POST' action='/save'>";
    html += "SSID: <input name='ssid'><br>Password: <input name='pass' type='password'><br>";
    html += "<button type='submit'>Guardar</button></form><br><form action='/update'><button>Actualizar Firmware OTA</button></form>";
    server.send(200, "text/html", html);
  });

  server.on("/save", HTTP_POST, []() {
    ssid = server.arg("ssid");
    password = server.arg("pass");

    StaticJsonDocument<256> doc;
    doc["ssid"] = ssid;
    doc["password"] = password;

    File file = SPIFFS.open(CONFIG_FILE, "w");
    serializeJson(doc, file);
    file.close();

    server.send(200, "text/html", "<p>Guardado. Reinicia manualmente el dispositivo.</p>");
  });

  server.on("/update", HTTP_GET, []() {
    server.send(200, "text/plain", "Iniciando OTA...");
    performOTAUpdate();
  });

  server.begin();
}

void performOTAUpdate() {
  HTTPClient http;
  http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
  http.begin(FIRMWARE_URL);
  int httpCode = http.GET();

  if (httpCode == HTTP_CODE_OK) {
    int contentLength = http.getSize();
    WiFiClient& stream = http.getStream();

    if (Update.begin(contentLength)) {
      uint8_t buff[1024];
      int totalRead = 0;
      int lastPercent = -1;

      while (http.connected() && totalRead < contentLength) {
        int bytesRead = stream.readBytes(buff, sizeof(buff));
        if (bytesRead > 0) {
          totalRead += bytesRead;
          Update.write(buff, bytesRead);

          int percent = (totalRead * 100) / contentLength;
          if (percent != lastPercent) {
            Serial.printf("📦 Progreso: %d%%\n", percent);
            lastPercent = percent;
          }
        }
      }

      if (Update.end(true)) {
        Serial.println("✅ OTA completada. Reiniciando...");
        ESP.restart();
      } else {
        Serial.println("❌ Error al finalizar la actualización.");
      }
    } else {
      Serial.println("❌ No hay suficiente espacio para OTA.");
    }
  } else {
    Serial.printf("❌ Error HTTP: %d\n", httpCode);
  }

  http.end();
}
