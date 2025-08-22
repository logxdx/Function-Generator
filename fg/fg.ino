#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "AD9833.h"
#include <WiFi.h>
#include <WebServer.h>
#include <math.h>
#include <ESP32Encoder.h>
#include <string>
#include "index_html.h"

// Encoder pins
#define CLK 14  // CLK
#define DT 12   // DT
#define FREQ_IN_BUTTON_PIN 13 // SW
ESP32Encoder encoder;

WebServer server(80);

#ifndef ESP32
#error ESP32 only example, please select appropriate board
#endif

// AD9833 pins
#define VSPI_SS   19
#define VSPI_SCK  18
#define VSPI_MOSI 5
#define VSPI_MISO -1
SPIClass *myspi = new SPIClass(VSPI);
// SDATA=19, SCK=18, CS=5
AD9833 AD(VSPI_SS, myspi);

// 16X2 LCD Display Pins
#define SDA 26
#define SCL 27

// Display constants
#define LCD_COLS 16
#define LCD_ROWS 2
#define LCD_ADDRESS 0x27

// Buttons
#define LED_PIN 25
#define BUTTON_WAVE 35
#define WIFI_BUTTON 33
#define START_STOP 32

#define MAX_WAVE_TYPES 4

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLS, LCD_ROWS);

String FG_NAME = "    FG-1.5M";

bool iswifi = false;
int currentWaveType = 0;
float frequency = 1000;
float Amplitude = 3.0;
float Offset = 0.0;
const float maxFrequency = 1200000.0;
const float minFrequency = 0.1;
const float maxAmplitude = 12;
const float minAmplitude = 0;
const float maxoffset = 12;
const float minoffset = -12;
bool isRunning = true;
unsigned long lastButtonPressTime = 0;
const int debounceDelay = 200;
const char *waveTypes[] = { "Sin", "Sq1", "Sq2", "Tri" };
String freqstr = "0000000.0";

void update_freqstr(float freq) {
  int f = freq * 10;
  int deci = f % 10;
  f = f / 10;
  char buf[10];  // 9+null
  sprintf(buf, "%07d.%1d", f, deci);
  freqstr = String(buf);
  Serial.print("of ");
  Serial.print(freq);
  Serial.print(" sf ");
  Serial.println(freqstr);
}
void update_AD() {
  if (isRunning) {
    AD.setFrequency(frequency, 0);
    switch (currentWaveType) {
      case 0: AD.setWave(AD9833_SINE); break;
      case 1: AD.setWave(AD9833_SQUARE1); break;
      case 2: AD.setWave(AD9833_SQUARE2); break;
      case 3: AD.setWave(AD9833_TRIANGLE); break;
    }
  } else AD.setWave(AD9833_OFF);
  update_freqstr(frequency);
  updateDisplays();
}

void updateDisplays() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(waveTypes[currentWaveType]);
  lcd.print(" ");
  lcd.print(isRunning ? "ON" : "OFF");
  lcd.print(" ");
  if (iswifi) lcd.print("Wifi");
  lcd.setCursor(0, 1);
  lcd.print(freqstr);
  lcd.print("Hz");
  digitalWrite(LED_PIN, isRunning);
}

void wifiMode() {
  iswifi = !iswifi;
  if (iswifi) {
    lcd.clear();
    lcd.print("Wifi On");
    delay(1000);
    lcd.clear();
    // lcd.setCursor(1, 0);
    lcd.print("IP: ");
    lcd.print(WiFi.softAPIP());
    // delay(2000);
    // String password = String(random(10000000, 99999999));
    String password = "12345678";
    // lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Pass: ");
    lcd.print(password);
  } else {
    lcd.clear();
    lcd.print("Wifi OFF");
  }
  delay(5000);
  updateDisplays();
}

void handleRoot() {
  server.send(200, "text/html", index_html);
}

void handleStart() {
  isRunning = true;
  server.send(200, "text/plain", "Waveform STARTED");
  Serial.println("Waveform generation started");
  update_AD();
}

void handleStop() {
  isRunning = false;
  server.send(200, "text/plain", "Waveform STOPPED");
  Serial.println("Waveform generation stopped");
  update_AD();
}

void handleSetFreq() {
  if (server.hasArg("val")) {
    frequency = server.arg("val").toFloat();
    if (frequency < minFrequency) frequency = minFrequency;
    if (frequency > maxFrequency) frequency = maxFrequency;
    server.send(200, "text/plain", "Frequency updated");
    Serial.print("Frequency updated to: ");
    Serial.println(frequency);
  } else {
    server.send(400, "text/plain", "Missing 'val' parameter");
    Serial.println("Error: Missing 'val' parameter in frequency update_AD");
  }
  update_AD();
}

void handleSetWave() {
  if (server.hasArg("type")) {
    currentWaveType = server.arg("type").toInt();
    server.send(200, "text/plain", "Wave type updated");
    Serial.print("Wave type updated to: ");
    Serial.println(waveTypes[currentWaveType]);
  } else {
    server.send(400, "text/plain", "Missing 'type' parameter");
    // Serial.println("Error: Missing 'type' parameter in wave type update_AD");
  }
  update_AD();
}

// void handleValues() {
//   String json = "{\"amplitude\": ";
//   json += String(Amplitude, 2);
//   json += ", \"offset\": ";
//   json += String(Offset, 2);
//   json += "}";
//   server.send(200, "application/json", json);
// }

int place = 0;
int DECIMAL_PLACE = 7;
int FREQ_STR_LEN = 9;
int lastEncoderCount = 0;
int handle_place() {
  place++;
  if (place == DECIMAL_PLACE) place++;
  lastEncoderCount = 0;
  encoder.setCount(0);
  place = place % FREQ_STR_LEN;
  Serial.print("place ");
  Serial.println(place);
  return place;
}

String freq_change() {
  place = place % FREQ_STR_LEN;
  if (place == DECIMAL_PLACE) return freqstr;
  int currentCount = encoder.getCount() / 2;
  if (currentCount != lastEncoderCount) {
    int digit = freqstr.charAt(place) - '0';
    digit += (currentCount - lastEncoderCount);
    digit = (digit + 10) % 10;  // Keep 0-9
    if (place == 0) digit = digit % 3;
    freqstr[place] = '0' + digit;
    lastEncoderCount = currentCount;
  }
  return freqstr;
}

void updateFrequencyFromPot() {
  if (encoder.getCount() / 2 != lastEncoderCount) {
    freqstr = freq_change();
    frequency = freqstr.toFloat();
    update_AD();
  }
}

// void updateAmplitudeFromPot() {
//   Amplitude = ((float)analogRead(AMP_IN_POT_PIN) / 4096.0) * (maxAmplitude - minAmplitude) + minAmplitude;
// }

// void updateOffsetFromPot() {
//   Offset = ((float)analogRead(OFFSET_IN_POT_PIN) / 4096.0) * (maxoffset - minoffset) + minoffset;
// }

// void wifi_or_pot() {
//   if (iswifi) {
//     server.handleClient();
//   } else {
//     updateFrequencyFromPot();
//     // updateAmplitudeFromPot();
//     // updateOffsetFromPot();
//   }
// }

void handleButtons() {
  unsigned long currentTime = millis();
  if (currentTime - lastButtonPressTime <= debounceDelay) return;
  if (digitalRead(START_STOP) == LOW) isRunning = !isRunning;
  else if (digitalRead(BUTTON_WAVE) == LOW) currentWaveType = (currentWaveType + 1) % MAX_WAVE_TYPES;
  else if (digitalRead(WIFI_BUTTON) == LOW) wifiMode();
  else if (digitalRead(FREQ_IN_BUTTON_PIN) == LOW) handle_place();
  else return;
  lastButtonPressTime = currentTime;
  update_AD();
}

void setup_pinMode_Buttons() {
  pinMode(BUTTON_WAVE, INPUT_PULLUP);
  pinMode(FREQ_IN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(WIFI_BUTTON, INPUT_PULLUP);
  pinMode(START_STOP, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  // pinMode(OFFSET_IN_POT_PIN, INPUT);
  // pinMode(FREQ_IN_POT_PIN, INPUT);
  // pinMode(AMP_IN_POT_PIN, INPUT);
}

void server_setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP("ESP32WaveAP", "12345678");  // AP SSID and password
  IPAddress apIP = WiFi.softAPIP();
  Serial.print("Wi-Fi IP Address: ");
  Serial.println(apIP);
  server.on("/", handleRoot);
  server.on("/start", handleStart);
  server.on("/stop", handleStop);
  server.on("/set_freq", handleSetFreq);
  server.on("/set_wave", handleSetWave);
  // server.on("/values", HTTP_GET, handleValues);
  server.begin();
}

void lcd_setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print(FG_NAME);
  lcd.setCursor(0, 1);
  lcd.print(" Tungnath Inc.");
  delay(5000);
}

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA, SCL);
  myspi->begin(VSPI_SCK, VSPI_MISO, VSPI_MOSI, VSPI_SS);
  AD.begin();
  lcd_setup();
  setup_pinMode_Buttons();
  AD.setFrequency(1000, 0);
  AD.setWave(AD9833_SINE);
  server_setup();
  encoder.attachHalfQuad(DT, CLK);
  encoder.setCount(0);

  // lcd.clear();
  // lcd.setCursor(0, 0);
  // lcd.print("wifi pass:");
  // lcd.setCursor(0, 1);
  // lcd.print(" 12345678");
  // delay(2000);
  lcd.clear();
  update_AD();
  // update_freqstr(frequency);
}

void loop() {
  handleButtons();
  updateFrequencyFromPot();
  // iswifi=true;
  if (iswifi) server.handleClient();
}