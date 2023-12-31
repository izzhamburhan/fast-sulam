// #include <Wire.h>
// #include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "CTBot.h"

CTBot myBot;
 // TBMessage message;
const char* ssid = "nama wifi";
const char* pass = "nama pass";
const char* token = "6440264298:AAFN8H4Rib74bLDjeVE1xdHMwCIvWNGdr_c";
const int id = 687007684; //tele izzham

int val = 0;

void setup() {
  Serial.begin(9600);
  pinMode(D5, HIGH);  // Blue led Pin Connected To D5 Pin
  pinMode(D6, HIGH);  // Red Led Pin Connected To D7 Pin
  pinMode(D7, HIGH);  // Green Led Connected To D6 Pin

  // lcd.init();
  // lcd.backlight();
  delay(1000);  // Allow time for Serial Monitor to open

  // Connect to WiFi
  connectToWiFi();

  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);
  if (myBot.testConnection())
    Serial.println("Connection to Telegram successful");
  else
    Serial.println("Connection to Telegram failed");


  Serial.println("Setup complete.");
}

void loop() {
  // Check if WiFi is connected before proceeding
  
  if (WiFi.status() == WL_CONNECTED) {
    int s1 = analogRead(A0);
    Serial.println("Water Level Reading: " + String(s1));

  
        if (s1 > 600 && s1 < 700) {
          digitalWrite(D6, HIGH);
          sendMessageToTelegram("Flood Alert! Please get ready.");
          // myBot.sendMessage(id, "Flood Alert! Please get reaadyy.");
          
        } else {
          digitalWrite(D6, LOW);
        }

        if (s1 < 600) {
          digitalWrite(D5, HIGH);
          
        } else {
          digitalWrite(D5, LOW);
        }

        if (s1 > 700) {
          digitalWrite(D7, HIGH);
          sendMessageToTelegram("Flood Alert! Water level is high.");
          // myBot.sendMessage(id, "Flood Alert! Water level is high.");
          delay(10000);  // Delay for 5 seconds to avoid continuous alerts (for testing)
        } else {
          digitalWrite(D7, LOW);
        }

    // function paling spoil - looping wifi ntah kenapa
      checkTelegramMessage();
        

  } else {
    // If WiFi is not connected, attempt to reconnect
    Serial.println("WiFi not connected. Reconnecting...");
    connectToWiFi();
  }
}

void sendMessageToTelegram(const char* message) {
  // Check if WiFi is connected before attempting to send a Telegram alert
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Sending message to Telegram...");
    if (myBot.sendMessage(id, message)) {
      Serial.println("Message sent successfully");
    } else {
      Serial.println("Failed to send message. Check your Telegram setup.");
    }
  } else {
    Serial.println("WiFi not connected. Unable to send Telegram alert.");
  }
}

void connectToWiFi() {
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, pass);

  int attempt = 0;
  while (WiFi.status() != WL_CONNECTED && attempt < 40) {
    delay(1000);
    Serial.print("Attempt " + String(attempt) + ": ");
    Serial.println("WiFi status: " + String(WiFi.status()));
    attempt++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("WiFi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Failed to connect to WiFi. Please check your credentials.");
  }
}

void checkTelegramMessage() {
  //Check for new message from Telegram
  TBMessage message;
  while (myBot.getNewMessage(message)){
    if (message.text == "/waterlevel"){
      int waterlevel = analogRead(A0);
      myBot.sendMessage(id, "Current water level is : " + String(waterlevel));
    }
  }
}
