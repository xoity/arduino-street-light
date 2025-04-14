// Pin assignments
int ldrPin = 3;        // Light sensor (simulated with potentiometer)
int pirPin = A0;         // PIR motion sensor
int ledPins[] = {6, 2};  // 5 LEDs
int numLEDs = 2;        // Number of LEDs
int slideSwitchPin = 9; // Slide switch pin
int dimThreshold = 250; // Battery level for dimming

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
  int mode = digitalRead(slideSwitchPin); // 1 = night, 0 = day

  Serial.print("Light: ");
  Serial.print(lightLevel);
  Serial.print(" Motion: ");
  Serial.print(motionDetected);
  Serial.print(" Mode (Switch): ");
  Serial.println(mode);

  if (mode == LOW) { // Daytime mode
    if (motionDetected == HIGH) {
      for (int i = 0; i < numLEDs; i++) {
        analogWrite(ledPins[i], 100);  // Dimmed light
      }
    } else {
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], LOW); // Off
      }
    }
  } else if (mode == HIGH) { // Nighttime mode
    if (lightLevel < 500 && motionDetected == HIGH) {
      for (int i = 0; i < numLEDs; i++) {
        analogWrite(ledPins[i], 100);  // Dim
      }
    } else if (lightLevel < 500) {
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], HIGH);  // Max brightness
      }
    } else {
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], LOW); // Off
      }
    }
  }

  delay(2000); // Delay to slow down output
}
