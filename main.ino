#include <Wire.h>
#include <LiquidCrystal_I2C.h>
/* Change these values based on your calibration values */
int lowerThreshold = 380;
int upperThreshold = 430;

// Sensor pins
#define sensorPower 7
#define sensorPin A0

// Value for storing water level
int val = 0;

// Declare pins to which LEDs are connected
int redLED = 2;
int yellowLED = 11;
int greenLED = 8;

LiquidCrystal_I2C lcd(0x27, 20, 4);
// LiquidCrystal_I2C lcd(0x3F, 20, 4);
// LiquidCrystal_I2C lcd(0x20, 20, 4);


void setup() {
	Serial.begin(9600);
	pinMode(sensorPower, OUTPUT);
	digitalWrite(sensorPower, LOW);
	
	// Set LED pins as an OUTPUT
	pinMode(redLED, OUTPUT);
	pinMode(yellowLED, OUTPUT);
	pinMode(greenLED, OUTPUT);

  lcd.init();
  lcd.backlight();

	// Initially turn off all LEDs
	digitalWrite(redLED, LOW);
	digitalWrite(yellowLED, LOW);
	digitalWrite(greenLED, LOW);
}

void loop() {
	int level = readSensor();

   lcd.clear();
  lcd.setCursor(0, 0);

	if (level == 0) {
		Serial.print("Water Level: Empty ~");
    Serial.println(readSensor());

    lcd.print("Water Level: Empty");

		digitalWrite(redLED, LOW);
		digitalWrite(yellowLED, LOW);
		digitalWrite(greenLED, LOW);
	}
	else if (level > 0 && level <= lowerThreshold) {
		Serial.print("Water Level: Low ~");
    Serial.println(readSensor());

    lcd.print("Water Level: Low");

		digitalWrite(redLED, HIGH);
		digitalWrite(yellowLED, LOW);
		digitalWrite(greenLED, LOW);
	}
	else if (level > lowerThreshold && level <= upperThreshold) {
		Serial.print("Water Level: Medium ~");
    Serial.println(readSensor());

    lcd.print("Water Level: Medium");

		digitalWrite(redLED, LOW);
		digitalWrite(yellowLED, HIGH);
		digitalWrite(greenLED, LOW);
	}
	else if (level > upperThreshold) {
		Serial.print("Water Level: High ~");
    Serial.println(readSensor()); 

    lcd.print("Water Level: High");

		digitalWrite(redLED, LOW);
		digitalWrite(yellowLED, LOW);
		digitalWrite(greenLED, HIGH);
	}

  lcd.setCursor(0, 1);
  lcd.print("Level: ");
  lcd.print(level);

	delay(1000);
}

//This is a function used to get the reading
int readSensor() {
	digitalWrite(sensorPower, HIGH);
	delay(10);
	val = analogRead(sensorPin);
	digitalWrite(sensorPower, LOW);
	return val;
}
