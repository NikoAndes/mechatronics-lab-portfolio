/*
 * L298N DC Motor Control with ESP32
 * Author: Nicolas Isaza Sierra (NikoAndes)
 * Description: Controls a DC motor using ESP32 and L298N H-Bridge driver.
 *              Supports forward, backward, stop, and PWM speed control.
 * Platform: ESP32 / Arduino
 */

// --- L298N Pin Connections ---
const int IN1 = 26;   // Direction pin 1
const int IN2 = 27;   // Direction pin 2
const int ENA = 14;   // Enable pin (PWM speed control)

// --- PWM Configuration ---
const int PWM_CHANNEL = 0;
const int PWM_FREQ = 1000;   // 1 kHz
const int PWM_RESOLUTION = 8; // 8-bit: 0-255

// --- Speed settings ---
int currentSpeed = 200;  // Default speed (0-255)

void setup() {
  Serial.begin(115200);

  // Setup direction pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Setup PWM for speed control
  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(ENA, PWM_CHANNEL);

  motorStop();
  printMenu();
}

void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    handleCommand(cmd);
  }
}

void handleCommand(char cmd) {
  switch (cmd) {
    case 'f':
      Serial.println("Motor: FORWARD");
      motorForward(currentSpeed);
      break;
    case 'b':
      Serial.println("Motor: BACKWARD");
      motorBackward(currentSpeed);
      break;
    case 's':
      Serial.println("Motor: STOP");
      motorStop();
      break;
    case '+':
      currentSpeed = min(255, currentSpeed + 20);
      Serial.print("Speed increased: ");
      Serial.println(currentSpeed);
      break;
    case '-':
      currentSpeed = max(0, currentSpeed - 20);
      Serial.print("Speed decreased: ");
      Serial.println(currentSpeed);
      break;
    case 't':
      runTestSequence();
      break;
    default:
      break;
  }
}

// --- Motor control functions ---

void motorForward(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  ledcWrite(PWM_CHANNEL, speed);
}

void motorBackward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(PWM_CHANNEL, speed);
}

void motorStop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  ledcWrite(PWM_CHANNEL, 0);
}

void motorBrake() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  ledcWrite(PWM_CHANNEL, 255);
}

// --- Test sequence ---
void runTestSequence() {
  Serial.println("--- Running test sequence ---");

  Serial.println("Forward at 50%");
  motorForward(128);
  delay(2000);

  Serial.println("Brake");
  motorBrake();
  delay(500);

  Serial.println("Backward at 75%");
  motorBackward(192);
  delay(2000);

  Serial.println("Gradual stop");
  for (int s = 192; s >= 0; s -= 10) {
    ledcWrite(PWM_CHANNEL, s);
    delay(100);
  }
  motorStop();

  Serial.println("--- Test complete ---");
  printMenu();
}

void printMenu() {
  Serial.println("\n=== L298N Motor Control ===");
  Serial.println("'f' - Forward");
  Serial.println("'b' - Backward");
  Serial.println("'s' - Stop");
  Serial.println("'+' - Speed up");
  Serial.println("'-' - Speed down");
  Serial.println("'t' - Run test sequence");
  Serial.print("Current speed: ");
  Serial.println(currentSpeed);
}
