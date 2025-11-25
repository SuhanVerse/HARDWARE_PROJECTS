#define IN1 5
#define IN2 6
#define IN3 10
#define IN4 11

#define ENA 9   // Enable pin for Motor A (connect to Arduino PWM pin)
#define ENB 3   // Enable pin for Motor B (connect to Arduino PWM pin)

int speedVal = 200; // Speed range: 0–255

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Set initial speed
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);
}

// Forward
void forward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Backward
void backward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

// Stop
void stopMotors() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  // Optionally disable outputs completely
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void loop() {
  // Forward at set speed
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);
  forward();
  delay(2000);

  stopMotors();
  delay(1000);

  // Backward at set speed
  analogWrite(ENA, speedVal);
  analogWrite(ENB, speedVal);
  backward();
  delay(2000);

  stopMotors();
  delay(1000);
}
