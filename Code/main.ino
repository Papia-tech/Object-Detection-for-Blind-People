#define TRIG_LEFT   2
#define ECHO_LEFT   3

#define TRIG_RIGHT  4
#define ECHO_RIGHT  5

#define TOUCH_PIN   6
#define BUZZER_PIN  8

bool systemOn = false;
bool lastTouchState = LOW;

unsigned long lastTouchTime = 0;
const unsigned long debounceTime = 300;


// --------------------
// Get distance
// --------------------
long getDistance(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return -1;
  }

  long distance = duration * 0.0343 / 2;

  return distance;
}


// --------------------
// Setup
// --------------------
void setup() {

  Serial.begin(9600);

  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT);

  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);

  pinMode(TOUCH_PIN, INPUT);

  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(BUZZER_PIN, LOW);

  Serial.println("Smart Glass Started");
  Serial.println("Touch sensor to turn ON/OFF");
}


// --------------------
// Main loop
// --------------------
void loop() {

  // --------------------
  // Touch ON/OFF
  // --------------------

  bool touchState = digitalRead(TOUCH_PIN);

  if (touchState == HIGH && lastTouchState == LOW) {

    if (millis() - lastTouchTime > debounceTime) {

      systemOn = !systemOn;

      lastTouchTime = millis();

      if (systemOn) {
        Serial.println("SYSTEM: ON");
      }
      else {
        Serial.println("SYSTEM: OFF");

        noTone(BUZZER_PIN);
        digitalWrite(BUZZER_PIN, LOW);
      }
    }
  }

  lastTouchState = touchState;


  // --------------------
  // If system is OFF
  // --------------------

  if (!systemOn) {

    noTone(BUZZER_PIN);

    delay(50);
    return;
  }


  // --------------------
  // Read LEFT sensor
  // --------------------

  long leftDistance = getDistance(TRIG_LEFT, ECHO_LEFT);

  // Give ultrasonic waves time to die down
  delay(50);


  // --------------------
  // Read RIGHT sensor
  // --------------------

  long rightDistance = getDistance(TRIG_RIGHT, ECHO_RIGHT);


  // --------------------
  // Print distances
  // --------------------

  Serial.print("LEFT: ");

  if (leftDistance == -1) {
    Serial.print("No reading");
  }
  else {
    Serial.print(leftDistance);
    Serial.print(" cm");
  }

  Serial.print("    RIGHT: ");

  if (rightDistance == -1) {
    Serial.println("No reading");
  }
  else {
    Serial.print(rightDistance);
    Serial.println(" cm");
  }


  // --------------------
  // Obstacle detection
  // Maximum warning distance = 35 cm
  // --------------------

  bool leftObstacle =
    leftDistance > 0 && leftDistance <= 35;

  bool rightObstacle =
    rightDistance > 0 && rightDistance <= 35;


  // --------------------
  // NO OBSTACLE
  // More than 35 cm
  // --------------------

  if (!leftObstacle && !rightObstacle) {

    noTone(BUZZER_PIN);
  }


  // --------------------
  // BOTH SIDES
  // --------------------

  else if (leftObstacle && rightObstacle) {

    // Very close: 0–15 cm
    if (leftDistance <= 15 || rightDistance <= 15) {

      tone(BUZZER_PIN, 3000);
      delay(100);

      noTone(BUZZER_PIN);
      delay(50);
    }

    // Medium: 16–25 cm
    else if (leftDistance <= 25 || rightDistance <= 25) {

      tone(BUZZER_PIN, 2500);
      delay(120);

      noTone(BUZZER_PIN);
      delay(180);
    }

    // Far warning: 26–35 cm
    else {

      tone(BUZZER_PIN, 2000);
      delay(100);

      noTone(BUZZER_PIN);
      delay(500);
    }
  }


  // --------------------
  // LEFT ONLY
  // --------------------

  else if (leftObstacle) {

    // Very close: 0–15 cm
    if (leftDistance <= 15) {

      tone(BUZZER_PIN, 3000);
      delay(100);

      noTone(BUZZER_PIN);
      delay(50);
    }

    // Medium: 16–25 cm
    else if (leftDistance <= 25) {

      tone(BUZZER_PIN, 2500);
      delay(120);

      noTone(BUZZER_PIN);
      delay(180);
    }

    // Far warning: 26–35 cm
    else {

      tone(BUZZER_PIN, 2000);
      delay(100);

      noTone(BUZZER_PIN);
      delay(500);
    }
  }


  // --------------------
  // RIGHT ONLY
  // --------------------

  else if (rightObstacle) {

    // Very close: 0–15 cm
    if (rightDistance <= 15) {

      tone(BUZZER_PIN, 3000);
      delay(100);

      noTone(BUZZER_PIN);
      delay(50);
    }

    // Medium: 16–25 cm
    else if (rightDistance <= 25) {

      tone(BUZZER_PIN, 2500);
      delay(120);

      noTone(BUZZER_PIN);
      delay(180);
    }

    // Far warning: 26–35 cm
    else {

      tone(BUZZER_PIN, 2000);
      delay(100);

      noTone(BUZZER_PIN);
      delay(500);
    }
  }


  // --------------------
  // Small delay before next reading
  // --------------------

  delay(50);
}