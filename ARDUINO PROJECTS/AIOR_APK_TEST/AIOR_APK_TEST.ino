#include <SoftwareSerial.h>

// -------------------- Pins --------------------
SoftwareSerial BT_Serial(2, 3); // Tx, Rx (HC-05)

#define enA 10  // Left motor speed
#define in1 9   // Left motor IN1
#define in2 8   // Left motor IN2
#define in3 7   // Right motor IN3
#define in4 6   // Right motor IN4
#define enB 5   // Right motor speed

// -------------------- Globals --------------------
int Speed = 130;          // PWM speed (0–255), adjustable via app slider
int bt_cmd = 5;           // Last command (default Stop)
unsigned long lastCmdPrint = 0;

// -------------------- Setup --------------------
void setup() {
  Serial.begin(9600);
  BT_Serial.begin(9600);

  // Motor pins
  pinMode(enA, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

// -------------------- Main Loop --------------------
void loop() {
  readBluetooth();

  // Apply normal speed
  analogWrite(enA, Speed);
  analogWrite(enB, Speed);

  // Manual control
  if      (bt_cmd == 1) { forward(); }
  else if (bt_cmd == 2) { backward(); }
  else if (bt_cmd == 3) { turnLeft(); }
  else if (bt_cmd == 4) { turnRight(); }
  else if (bt_cmd == 5 || bt_cmd == 0) { Stop(); }

  // Voice control (momentary, with boosted speed)
  else if (bt_cmd == 6) {
    Serial.println("Voice Left Turn");
    analogWrite(enA, 255); // boost left motor
    analogWrite(enB, 255); // boost right motor
    turnLeft();
    delay(500);            // longer turn duration
    Stop();
    bt_cmd = 5;            // reset to Stop
  }
  else if (bt_cmd == 7) {
    Serial.println("Voice Right Turn");
    analogWrite(enA, 255); // boost left motor
    analogWrite(enB, 255); // boost right motor
    turnRight();
    delay(500);            // longer turn duration
    Stop();
    bt_cmd = 5;            // reset to Stop
  }

  // Debug print
  if (millis() - lastCmdPrint > 500) {
    Serial.print("Speed: "); Serial.print(Speed);
    Serial.print("  Cmd: "); Serial.println(bt_cmd);
    lastCmdPrint = millis();
  }

  delay(10);
}

// -------------------- Bluetooth Input --------------------
void readBluetooth() {
  if (BT_Serial.available() > 0) {
    int data = BT_Serial.read();
    Serial.print("BT: "); Serial.println(data);

    if (data >= 21 && data <= 255) {
      Speed = data; // Slider value
    } else {
      bt_cmd = data; // Button/voice command
    }
  }
}

// -------------------- Motor Control --------------------
void forward() {
  // Left motor forward
  digitalWrite(in1, LOW);  digitalWrite(in2, HIGH);
  // Right motor forward
  digitalWrite(in3, LOW);  digitalWrite(in4, HIGH);
}

void backward() {
  // Left motor backward
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  // Right motor backward
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void turnRight() {
  // Left motor forward, right motor backward
  digitalWrite(in1, LOW);  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
}

void turnLeft() {
  // Left motor backward, right motor forward
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  digitalWrite(in4, HIGH);
}

void Stop() {
  digitalWrite(in1, LOW);  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  digitalWrite(in4, LOW);
}
