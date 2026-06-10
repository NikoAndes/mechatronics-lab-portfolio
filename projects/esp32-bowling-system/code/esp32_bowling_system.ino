/*
 * ESP32 Bowling System
 * Author: Nicolas Isaza Sierra (NikoAndes)
 * Description: Detects fallen bowling pins using LDR sensors and tracks score
 * Platform: ESP32 / Arduino
 */

// --- Configuration ---
const int NUM_PINS = 10;
const int LDR_THRESHOLD = 500;  // Adjust based on ambient light
const int FRAME_DELAY = 2000;   // ms between frames

// LDR sensor pins (analog inputs on ESP32)
const int ldrPins[NUM_PINS] = {34, 35, 32, 33, 25, 26, 27, 14, 12, 13};

// Game state
bool pinStanding[NUM_PINS];
int totalScore = 0;
int currentFrame = 1;
int rollsInFrame = 0;
int pinsKnockedThisFrame = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("==========================");
  Serial.println(" ESP32 Bowling System v1.0");
  Serial.println("==========================");
  resetPins();
  Serial.println("Pins reset. Ready to bowl!");
  printPinStatus();
}

void loop() {
  if (currentFrame > 10) {
    Serial.println("--- Game Over ---");
    Serial.print("Final Score: ");
    Serial.println(totalScore);
    delay(5000);
    restartGame();
    return;
  }

  Serial.print("\nFrame ");
  Serial.print(currentFrame);
  Serial.print(" | Roll ");
  Serial.println(rollsInFrame + 1);

  delay(1000);  // Wait for roll
  int knocked = detectKnockedPins();

  Serial.print("Pins knocked down this roll: ");
  Serial.println(knocked);

  pinsKnockedThisFrame += knocked;
  totalScore += knocked;
  rollsInFrame++;

  // Check strike
  if (rollsInFrame == 1 && knocked == 10) {
    Serial.println("STRIKE!");
    totalScore += 10;  // Bonus simplified
    nextFrame();
    return;
  }

  // Check spare
  if (rollsInFrame == 2 && pinsKnockedThisFrame == 10) {
    Serial.println("SPARE!");
    totalScore += 5;  // Bonus simplified
    nextFrame();
    return;
  }

  // Second roll done
  if (rollsInFrame >= 2) {
    nextFrame();
  }

  printPinStatus();
  delay(FRAME_DELAY);
}

// --- Read all LDR sensors and detect fallen pins ---
int detectKnockedPins() {
  int knocked = 0;
  for (int i = 0; i < NUM_PINS; i++) {
    if (pinStanding[i]) {
      int val = analogRead(ldrPins[i]);
      if (val < LDR_THRESHOLD) {  // Low light = pin blocked = knocked down
        pinStanding[i] = false;
        knocked++;
        Serial.print("  Pin ");
        Serial.print(i + 1);
        Serial.println(" knocked!");
      }
    }
  }
  return knocked;
}

void resetPins() {
  for (int i = 0; i < NUM_PINS; i++) {
    pinStanding[i] = true;
  }
}

void printPinStatus() {
  Serial.print("Pin status: ");
  for (int i = 0; i < NUM_PINS; i++) {
    Serial.print(pinStanding[i] ? "O" : "X");
    Serial.print(" ");
  }
  Serial.println();
  Serial.print("Current Score: ");
  Serial.println(totalScore);
}

void nextFrame() {
  currentFrame++;
  rollsInFrame = 0;
  pinsKnockedThisFrame = 0;
  resetPins();
}

void restartGame() {
  totalScore = 0;
  currentFrame = 1;
  rollsInFrame = 0;
  pinsKnockedThisFrame = 0;
  resetPins();
  Serial.println("New game started!");
}
