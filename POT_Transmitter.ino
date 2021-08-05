#include <Wire.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LiquidCrystal_I2C.h>
#define POT_MIN 0
#define POT_MAX 4095
#define DUTY_MIN 1200
#define DUTY_MAX 2000

const char* ssid = "Hasenhoeft";
const char* pwd = "21162010819665839679";
const int POT = 34;
int pot_val, duty;
LiquidCrystal_I2C lcd(39, 16, 2);
AsyncWebServer server(80);

String readPOT() {
  pot_val = analogRead(POT);
  //duty = map(pot_val, POT_MIN, POT_MAX, DUTY_MIN, DUTY_MAX);
  return(String(pot_val));
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  lcd.print("Initializing...");
  lcd.setCursor(0, 1);
  lcd.print("Display Ready!");
  delay(2000);
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("WiFi");
  lcd.setCursor(0,1);
  lcd.print("Connecting...");
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Done!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/pot", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readPOT().c_str());
  });

  server.begin();
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,0);
  lcd.print("Transmitting... ");
  lcd.setCursor(0,1);
  lcd.print("    ");
  lcd.setCursor(0,1);
  lcd.print(readPOT());
}
