#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // Tx, Rx (HC-05)

#define enA 10  // Left motor speed
#define in1 9   // Left motor IN1
#define in2 8   // Left motor IN2
#define in3 7   // Right motor IN3
#define in4 6   // Right motor IN4
#define enB 5   // Right motor speed

int Speed = 220;
char command;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  Serial.println("Bluetooth RC Car Ready");

  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
}

void loop() {
  if (mySerial.available()) {
    command = mySerial.read();
    Serial.print("Received: "); Serial.println(command);

    // Speed control: '0' to '9' and 'q'
    if (command >= '0' && command <= '9') {
      Speed = map(command - '0', 0, 9, 0, 255); // '0' = 0, '9' = 255
    } else if (command == 'q') {
      Speed = 255; // Speed 100
    }

    // Apply PWM speeds
    analogWrite(enA, Speed);
    analogWrite(enB, Speed);

    // Movement commands
    if (command == 'F') {
      Serial.println("Forward");
      digitalWrite(in1, LOW);  digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);  digitalWrite(in4, HIGH);
    }
    else if (command == 'B') {
      Serial.println("Backward");
      digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
    }
    else if (command == 'L') {
      Serial.println("Left");
      digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);  digitalWrite(in4, HIGH);
    }
    else if (command == 'R') {
      Serial.println("Right");
      digitalWrite(in1, LOW);  digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
    }
    else if (command == 'S') {
      Serial.println("Stop");
      digitalWrite(in1, LOW);  digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);  digitalWrite(in4, LOW);
      analogWrite(enA, 0);
      analogWrite(enB, 0);
    }
  }

  delay(10);
}

//---------------------------------------------------------

//Includes Diagonal Movement Support

// #include <SoftwareSerial.h>

// SoftwareSerial mySerial(2, 3); // Tx, Rx (HC-05)

// // Left motor (ENA, IN1, IN2)
// #define enA 10
// #define in1 9
// #define in2 8

// // Right motor (ENB, IN3, IN4)
// #define enB 5
// #define in3 7
// #define in4 6

// // Global speed state
// int baseSpeed = 220;        // global base speed (0–255)
// int leftSpeed = 0;          // applied PWM for left ENA
// int rightSpeed = 0;         // applied PWM for right ENB
// char command = 'S';

// // Coefficients for diagonals (reduce one side)
// const float diagCoeff = 0.5; // 50% speed on the “slow” side

// void applyDirectionForward() {
//   // Left forward
//   digitalWrite(in1, LOW);  digitalWrite(in2, HIGH);
//   // Right forward
//   digitalWrite(in3, LOW);  digitalWrite(in4, HIGH);
// }

// void applyDirectionBackward() {
//   // Left backward
//   digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
//   // Right backward
//   digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
// }

// void applyStop() {
//   digitalWrite(in1, LOW);  digitalWrite(in2, LOW);
//   digitalWrite(in3, LOW);  digitalWrite(in4, LOW);
// }

// void setup() {
//   Serial.begin(9600);
//   mySerial.begin(9600);
//   Serial.println("Bluetooth RC Car Ready");

//   pinMode(enA, OUTPUT);
//   pinMode(in1, OUTPUT);
//   pinMode(in2, OUTPUT);
//   pinMode(enB, OUTPUT);
//   pinMode(in3, OUTPUT);
//   pinMode(in4, OUTPUT);

//   // Start stopped
//   applyStop();
//   leftSpeed = 0;
//   rightSpeed = 0;
// }

// void loop() {
//   // Read Bluetooth commands
//   if (mySerial.available()) {
//     command = mySerial.read();
//     Serial.print("Received: "); Serial.println(command);

//     // Speed control from app:
//     // '0'..'9' map linearly to 0..255, 'q' = 255
//     if (command >= '0' && command <= '9') {
//       // If you require custom mapping (e.g., 10 -> 110), replace map() with your rule.
//       baseSpeed = map(command - '0', 0, 9, 0, 255);
//       Serial.print("Base speed set to: "); Serial.println(baseSpeed);
//     } else if (command == 'q') {
//       baseSpeed = 255;
//       Serial.println("Base speed set to: 255 (Speed 100)");
//     }

//     // Set directions and per-side speeds
//     if (command == 'F') {
//       Serial.println("Forward");
//       applyDirectionForward();
//       leftSpeed = baseSpeed;
//       rightSpeed = baseSpeed;
//     }
//     else if (command == 'B') {
//       Serial.println("Backward");
//       applyDirectionBackward();
//       leftSpeed = baseSpeed;
//       rightSpeed = baseSpeed;
//     }
//     else if (command == 'L') {
//       Serial.println("Left (pivot)");
//       // Left backward, right forward
//       digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
//       digitalWrite(in3, LOW);  digitalWrite(in4, HIGH);
//       leftSpeed = baseSpeed;
//       rightSpeed = baseSpeed;
//     }
//     else if (command == 'R') {
//       Serial.println("Right (pivot)");
//       // Left forward, right backward
//       digitalWrite(in1, LOW);  digitalWrite(in2, HIGH);
//       digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
//       leftSpeed = baseSpeed;
//       rightSpeed = baseSpeed;
//     }
//     else if (command == 'G') {
//       Serial.println("Forward Left (diagonal)");
//       applyDirectionForward();
//       leftSpeed  = (int)(baseSpeed * diagCoeff); // slow left
//       rightSpeed = baseSpeed;
//     }
//     else if (command == 'I') {
//       Serial.println("Forward Right (diagonal)");
//       applyDirectionForward();
//       leftSpeed  = baseSpeed;
//       rightSpeed = (int)(baseSpeed * diagCoeff); // slow right
//     }
//     else if (command == 'H') {
//       Serial.println("Back Left (diagonal)");
//       applyDirectionBackward();
//       leftSpeed  = (int)(baseSpeed * diagCoeff); // slow left
//       rightSpeed = baseSpeed;
//     }
//     else if (command == 'J') {
//       Serial.println("Back Right (diagonal)");
//       applyDirectionBackward();
//       leftSpeed  = baseSpeed;
//       rightSpeed = (int)(baseSpeed * diagCoeff); // slow right
//     }
//     else if (command == 'S') {
//       Serial.println("Stop");
//       applyStop();
//       leftSpeed = 0;
//       rightSpeed = 0;
//     }
//   }

//   // Always apply PWM every loop (persistent control)
//   analogWrite(enA, leftSpeed);
//   analogWrite(enB, rightSpeed);

//   delay(5);
// }

//---------------------------------------------------------