/* Change these values based on your calibration values */
int lowerThreshold = 350;
int upperThreshold = 400;

// Sensor pins
#define sensorPower 7
#define sensorPin A0

// Value for storing water level
int val = 0;

// Declare pins to which LEDs are connected
int redLED = 2;
int yellowLED = 11;
int greenLED = 8;

void setup() {
	Serial.begin(9600);
	pinMode(sensorPower, OUTPUT);
	digitalWrite(sensorPower, LOW);
	
	// Set LED pins as an OUTPUT
	pinMode(redLED, OUTPUT);
	pinMode(yellowLED, OUTPUT);
	pinMode(greenLED, OUTPUT);

	// Initially turn off all LEDs
	digitalWrite(redLED, LOW);
	digitalWrite(yellowLED, LOW);
	digitalWrite(greenLED, LOW);
}

void loop() {
	int level = readSensor();

	if (level == 0) {
		Serial.println("Water Level: Empty");
    Serial.print("Water level: ");
    Serial.println(readSensor());
		digitalWrite(redLED, LOW);
		digitalWrite(yellowLED, LOW);
		digitalWrite(greenLED, LOW);
	}
	else if (level > 0 && level <= lowerThreshold) {
		Serial.println("Water Level: Low");
		digitalWrite(redLED, HIGH);
    Serial.print("Water level: ");
Serial.println(readSensor());
		digitalWrite(yellowLED, LOW);
		digitalWrite(greenLED, LOW);
	}
	else if (level > lowerThreshold && level <= upperThreshold) {
		Serial.println("Water Level: Medium");
    Serial.print("Water level: ");
    Serial.println(readSensor());
		digitalWrite(redLED, LOW);
		digitalWrite(yellowLED, HIGH);
		digitalWrite(greenLED, LOW);
	}
	else if (level > upperThreshold) {
		Serial.println("Water Level: High");
    Serial.print("Water level: ");
    Serial.println(readSensor()); 
		digitalWrite(redLED, LOW);
		digitalWrite(yellowLED, LOW);
		digitalWrite(greenLED, HIGH);
	}
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
