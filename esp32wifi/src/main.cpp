#include <Arduino.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <WiFiManager.h>

const char *ssidFile = "/ssid.txt";
const char *passwordFile = "/password.txt";

void writeFile(fs::FS &fs, const char *path, const char *message);
String readFile(fs::FS &fs, const char *path);
void wifiYonetici();

void setup()
{
  Serial.begin(115200);

  int denemeSayisi = 0;
  bool baglandi = false;

  while (denemeSayisi < 10 && !baglandi)
  {
    if (LittleFS.begin())
    {
      File ssidDosya = LittleFS.open("/ssid.txt", "r");
      File passwordDosya = LittleFS.open("/password.txt", "r");

      if (ssidDosya && passwordDosya)
      {
        String ssid = ssidDosya.readStringUntil('\n');
        String password = passwordDosya.readStringUntil('\n');

        ssidDosya.close();
        passwordDosya.close();

        WiFi.begin(ssid.c_str(), password.c_str());
        if (WiFi.waitForConnectResult() == WL_CONNECTED)
        {
          baglandi = true;
          Serial.println("LittleFS ile bağlandı");
        }
      }

      LittleFS.end();
    }

    if (!baglandi)
    {
      denemeSayisi++;
      delay(1000);
    }
  }

  if (!baglandi)
  {
    if (LittleFS.begin())
    {
      wifiYonetici();
      LittleFS.end();
    }
  }

  // Diğer setup işlemleri buraya eklenebilir
}

void loop() {}

void writeFile(fs::FS &fs, const char *path, const char *message)
{
  File file = fs.open(path, FILE_WRITE);
  if (!file)
  {
    Serial.println("Dosya oluşturulamadı");
  }
  else
  {
    file.print(message);
    Serial.println("yazıldı");
  }
}

String readFile(fs::FS &fs, const char *path)
{
  File file = fs.open(path);
  if (!file || file.isDirectory())
  {
    Serial.println("Dosya okunamadı");
  }
  String fileContent;
  while (file.available())
  {
    fileContent = file.readStringUntil('\n');
    Serial.println("okundu");
  }
  return fileContent;
}

void wifiYonetici()
{
  WiFiManager wm;
  wm.resetSettings();

  bool res;
  res = wm.autoConnect("AutoConnectAP", "password");

  if (!res)
  {
    Serial.println("Failed to connect");
    ESP.restart();
  }
  else
  {
    Serial.println("Wifi Manager ile bağlandı");

    writeFile(LittleFS, ssidFile, WiFi.SSID().c_str());
    writeFile(LittleFS, passwordFile, WiFi.psk().c_str());
  }
}
