// Pin assignments
int ldrPin = A0;        // Light sensor (simulated with potentiometer)
int pirPin = 2;         // PIR motion sensor
int ledPins[] = {3, 5, 6, 9, 10};  // 5 LEDs
int numLEDs = 5;        // Number of LEDs
int batteryPin = A1;    // Battery level pin
int slideSwitchPin = 7; // Slide switch pin
int dimThreshold = 250; // Battery level for dimming
int minBatteryLevel = 500;  // Critical battery level

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(slideSwitchPin, INPUT);  // If needed: use INPUT_PULLUP for simplicity
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int lightLevel = analogRead(ldrPin);
  int motionDetected = digitalRead(pirPin);
  int batteryLevel = analogRead(batteryPin);
  int mode = digitalRead(slideSwitchPin); // 1 = night, 0 = day

  Serial.print("Light: ");
  Serial.print(lightLevel);
  Serial.print(" Motion: ");
  Serial.print(motionDetected);
  Serial.print(" Battery: ");
  Serial.print(batteryLevel);
  Serial.print(" Mode (Switch): ");
  Serial.println(mode);

  // Simulate behavior based on mode
  if (mode == LOW) { // Daytime mode
    if (motionDetected == HIGH) {
      for (int i = 0; i < numLEDs; i++) {
        analogWrite(ledPins[i], 100);  // Dimmed light if needed during day
      }
    } else {
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], LOW); // Off if no motion
      }
    }
  } else if (mode == HIGH) { // Nighttime mode
    if (lightLevel < 500 && motionDetected == HIGH) {
      if (batteryLevel < dimThreshold) {
        for (int i = 0; i < numLEDs; i++) {
          analogWrite(ledPins[i], 100);  // Dim
        }
      } else if (batteryLevel >= dimThreshold && batteryLevel < minBatteryLevel) {
        for (int i = 0; i < numLEDs; i++) {
          analogWrite(ledPins[i], 255);  // Bright
        }
      } else {
        for (int i = 0; i < numLEDs; i++) {
          digitalWrite(ledPins[i], HIGH);  // Max brightness
        }
      }
    } else {
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], LOW);
      }
    }
  }

  delay(2000);
}
