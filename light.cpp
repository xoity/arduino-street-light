// Pin assignments
int ldrPin = A1;             // Light sensor (simulated with potentiometer)
int trigPin = 10;            // Ultrasonic sensor - Trigger
int echoPin = 11;            // Ultrasonic sensor - Echo
int ledPins[] = {6, 2};      // LEDs
int numLEDs = 2;
int slideSwitchPin = 9;      // Day/Night switch

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(slideSwitchPin, INPUT_PULLUP);  // Use INPUT_PULLUP if wired accordingly

  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  // Read the light level
  int lightLevel = analogRead(ldrPin);
  
  // Read the mode (day/night)
  int mode = digitalRead(slideSwitchPin); // LOW = day, HIGH = night

  // Measure distance from ultrasonic sensor
  long duration;
  int distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;  // Convert to cm

  // Debug output
  Serial.print("Light: ");
  Serial.print(lightLevel);
  Serial.print(" Distance: ");
  Serial.print(distance);
  Serial.print(" Mode (Switch): ");
  Serial.println(mode);

  // Logic
  if (mode == LOW) { // Daytime mode
    if (distance < 100) {  // Adjust threshold as needed
      for (int i = 0; i < numLEDs; i++) {
        analogWrite(ledPins[i], 100);  // Dimmed light
      }
    } else {
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], LOW); // Off
      }
    }
  } else if (mode == HIGH) { // Nighttime mode
    if (lightLevel < 500 && distance < 100) {
      for (int i = 0; i < numLEDs; i++) {
        analogWrite(ledPins[i], 100);  // Dim light when someone is nearby
      }
    } else if (lightLevel < 500) {
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], HIGH);  // Full brightness (no one near)
      }
    } else {
      for (int i = 0; i < numLEDs; i++) {
        digitalWrite(ledPins[i], LOW); // Off due to ambient light
      }
    }
  }

  delay(2000); // Adjust delay as needed
}
