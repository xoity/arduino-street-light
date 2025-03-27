int ldrPin = A0;        // Potentiometer (simulating LDR) connected to Analog Pin A0
int pirPin = 2;         // PIR motion sensor connected to Digital Pin 2
int ledPins[] = {9, 10, 11, 12, 13};  // 5 LEDs connected to Digital Pins 9, 10, 11, 12, 13
int numLEDs = 5;        // Number of LEDs
int batteryPin = A1;    // Battery voltage reading pin (simulate battery voltage)
int minBatteryLevel = 500;  // Minimum battery level before dimming lights

void setup() {
  pinMode(pirPin, INPUT);  // PIR sensor pin as input
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);  // LED pins as output
  }
  Serial.begin(9600);
}

void loop() {
  int lightLevel = analogRead(ldrPin);   // Read light level (from potentiometer)
  int motionDetected = digitalRead(pirPin); // Read motion detection status
  int batteryLevel = analogRead(batteryPin);  // Read battery level (simulate solar power)

  // Print debug info
  Serial.print("Light Level: ");
  Serial.print(lightLevel);
  Serial.print("\tMotion Detected: ");
  Serial.print(motionDetected);
  Serial.print("\tBattery Level: ");
  Serial.println(batteryLevel);

  // Simulate solar power by adjusting the LED brightness
  if (batteryLevel < minBatteryLevel) {
    // If battery is low, reduce brightness or turn off lights
    for (int i = 0; i < numLEDs; i++) {
      digitalWrite(ledPins[i], LOW);  // Turn off lights to save energy
    }
  } else {
    // Normal operation: turn on lights based on light level and motion
    if (lightLevel < 500 && motionDetected == HIGH) {  // If it's dark and motion is detected
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], HIGH);  // Turn on all LEDs (streetlights)
      }
    } else {
      // Keep LEDs OFF if no motion or it's bright
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], LOW);
      }
    }
  }
  delay(500);  // Delay to stabilize readings
}
