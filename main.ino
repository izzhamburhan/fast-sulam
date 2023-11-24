#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <TelegramBot.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
const char* botToken = "YourTelegramBotToken";

const int waterLevelPin = D2;
const int ledPin = D3;

int waterLevelThreshold = 500; // Adjust this value based on your sensor and requirements
int currentWaterLevel;
bool alertSent = false;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);
  lcd.print("Water Level:");

  pinMode(ledPin, OUTPUT);
  pinMode(waterLevelPin, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Initialize Telegram bot
  TelegramBot.begin(botToken);
}

void loop() {
  currentWaterLevel = analogRead(waterLevelPin);

  lcd.setCursor(0, 1);
  lcd.print("   "); // Clear previous water level
  lcd.setCursor(0, 1);
  lcd.print(currentWaterLevel);

  if (currentWaterLevel > waterLevelThreshold && !alertSent) {
    sendAlert();
    alertSent = true;
    digitalWrite(ledPin, HIGH); // Turn on the LED as an alert
  } else if (currentWaterLevel <= waterLevelThreshold) {
    alertSent = false;
    digitalWrite(ledPin, LOW); // Turn off the LED
  }

  delay(1000); // Adjust the delay based on your project requirements
}

void sendAlert() {
  String chatId = "YourTelegramChatID"; // Replace with your chat ID
  String message = "Flood alert! Water level exceeded the threshold.";

  TelegramBot.sendMessage(chatId, message);
}