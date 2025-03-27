// Pin assignments
int ldrPin = A0;        // Light sensor (simulated with potentiometer)
int pirPin = 2;         // PIR motion sensor
int ledPins[] = {3, 5, 6, 9, 10};  // 5 LEDs
int numLEDs = 5;        // Number of LEDs
int batteryPin = A1;    // Battery level pin
int dimThreshold = 200; // Battery level for dimming
int minBatteryLevel = 500;  // Critical battery level (below which we turn off LEDs)

void setup() {
  pinMode(pirPin, INPUT);  
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  int lightLevel = analogRead(ldrPin);   // Read light level
  int motionDetected = digitalRead(pirPin); // Read motion status
  int batteryLevel = analogRead(batteryPin);  // Read battery level

  // Print debug info
  Serial.print("Light Level: ");
  Serial.print(lightLevel);
  Serial.print("\tMotion Detected: ");
  Serial.print(motionDetected);
  Serial.print("\tBattery Level: ");
  Serial.println(batteryLevel);

  if (lightLevel < 500 && motionDetected == HIGH) {  // Only act if it's dark and motion detected
    if (batteryLevel < dimThreshold) {
      // Dim the LEDs if battery is critically low
      for (int i = 0; i < numLEDs; i++) {
        analogWrite(ledPins[i], 100);  // Dim brightness (0-255)
      }
    } else if (batteryLevel >= dimThreshold && batteryLevel < minBatteryLevel) {
      // Normal brightness when battery is sufficient but not fully charged
      for (int i = 0; i < numLEDs; i++) {
        analogWrite(ledPins[i], 255);  // Full brightness
      }
    } else {
      // If battery is fully charged, turn on at full brightness
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], HIGH);
      }
    }
  } else {
    // If it's bright or no motion, keep LEDs OFF
    for (int i = 0; i < numLEDs; i++) {
      digitalWrite(ledPins[i], LOW);
    }
  }

  delay(2000);  // Delay for stability
}

