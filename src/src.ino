//12
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
bool isUpdating = false;
int otaProgress = 0;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("🔌 Iniciando ESP32...");

  if (!SPIFFS.begin(true)) {
    Serial.println("❌ Error iniciando SPIFFS");
    return;
  }

  loadCredentials();
  startAPMode();
  setupServer();
}

void loop() {
  server.handleClient();
}

void loadCredentials() {
  File file = SPIFFS.open(CONFIG_FILE);
  if (!file) return;

  StaticJsonDocument<256> doc;
  if (deserializeJson(doc, file) == DeserializationError::Ok) {
    ssid = doc["ssid"].as<String>();
    password = doc["password"].as<String>();
  }
  file.close();
}

void saveCredentials(const String& ssid, const String& password) {
  StaticJsonDocument<256> doc;
  doc["ssid"] = ssid;
  doc["password"] = password;
  File file = SPIFFS.open(CONFIG_FILE, "w");
  serializeJson(doc, file);
  file.close();
}

void startAPMode() {
  WiFi.softAP(AP_SSID, AP_PASS);
  Serial.println("📡 Modo AP iniciado");
  Serial.print("IP AP: ");
  Serial.println(WiFi.softAPIP());
}

void setupServer() {
  server.on("/", HTTP_GET, []() {
    String html = "<html><body style='font-size:18px;'>";
    html += "<h2>ESP32 OTA Configuración</h2>";
    html += "<form method='POST' action='/save'>";
    html += "SSID: <input name='ssid' style='font-size:18px'><br>";
    html += "Password: <input type='password' name='pass' style='font-size:18px'><br><br>";
    html += "<button type='submit' style='font-size:18px'>Guardar WiFi</button></form><br><br>";
    html += "<form action='/update'><button style='font-size:18px'>Actualizar Firmware OTA</button></form>";
    if (isUpdating) {
      html += "<p>📦 Progreso: " + String(otaProgress) + "%</p>";
    }
    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  server.on("/save", HTTP_POST, []() {
    ssid = server.arg("ssid");
    password = server.arg("pass");
    saveCredentials(ssid, password);
    server.send(200, "text/html", "<p>✅ Credenciales guardadas. Ahora puedes presionar Actualizar Firmware OTA.</p><a href='/'>Volver</a>");
  });

  server.on("/update", HTTP_GET, []() {
    server.send(200, "text/html", "<p>🔄 Iniciando actualización OTA... Verifica el monitor serial para ver el progreso.</p><a href='/'>Volver</a>");
    performOTAUpdate();
  });

  server.begin();
}

void performOTAUpdate() {
  isUpdating = true;
  otaProgress = 0;

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
            otaProgress = percent;
            Serial.printf("📦 Progreso: %d%%\n", percent);
            lastPercent = percent;
          }
        }
      }

      if (Update.end(true)) {
        Serial.println("✅ OTA completada. Reiniciando...");
        delay(2000);
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
  isUpdating = false;
}
