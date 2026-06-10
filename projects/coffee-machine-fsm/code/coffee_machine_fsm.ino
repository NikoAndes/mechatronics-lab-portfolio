/*
 * Coffee Machine FSM (Finite State Machine)
 * Author: Nicolas Isaza Sierra (NikoAndes)
 * Description: Simulates a coffee maker using a state machine on ESP32
 * Inputs: simulated via Serial commands
 * Platform: ESP32 / Arduino
 */

// --- State definitions ---
enum State {
  IDLE,
  SELECTING,
  CHECK_SUPPLIES,
  SERVING_COFFEE,
  SERVING_WATER,
  FINISHED,
  ERROR_STATE
};

State currentState = IDLE;

// Simulated supplies
int waterLevel = 100;    // percentage
int coffeeLevel = 100;   // percentage
int cupPresent = 1;      // 1 = cup present

// LED pins (optional hardware output)
const int LED_IDLE = 2;
const int LED_SERVING = 4;
const int LED_ERROR = 5;

void setup() {
  Serial.begin(115200);
  pinMode(LED_IDLE, OUTPUT);
  pinMode(LED_SERVING, OUTPUT);
  pinMode(LED_ERROR, OUTPUT);
  printMenu();
  setState(IDLE);
}

void loop() {
  if (Serial.available()) {
    char input = Serial.read();
    handleInput(input);
  }
  updateLEDs();
}

void handleInput(char cmd) {
  Serial.print("Command received: ");
  Serial.println(cmd);

  switch (currentState) {
    case IDLE:
      if (cmd == 's') setState(SELECTING);
      break;

    case SELECTING:
      if (cmd == '1') {
        Serial.println("Coffee selected.");
        setState(CHECK_SUPPLIES);
        checkAndServe(true);
      } else if (cmd == '2') {
        Serial.println("Water selected.");
        setState(CHECK_SUPPLIES);
        checkAndServe(false);
      } else if (cmd == 'x') {
        Serial.println("Selection cancelled.");
        setState(IDLE);
      }
      break;

    case FINISHED:
      if (cmd == 'r') {
        Serial.println("Ready for next cup.");
        setState(IDLE);
        printMenu();
      }
      break;

    case ERROR_STATE:
      if (cmd == 'r') {
        Serial.println("Attempting recovery...");
        waterLevel = 100;
        coffeeLevel = 100;
        cupPresent = 1;
        setState(IDLE);
        printMenu();
      }
      break;

    default:
      break;
  }
}

void checkAndServe(bool isCoffee) {
  if (!cupPresent) {
    Serial.println("ERROR: No cup detected!");
    setState(ERROR_STATE);
    return;
  }
  if (waterLevel < 20) {
    Serial.println("ERROR: Water level too low!");
    setState(ERROR_STATE);
    return;
  }
  if (isCoffee && coffeeLevel < 10) {
    Serial.println("ERROR: No coffee left!");
    setState(ERROR_STATE);
    return;
  }

  if (isCoffee) {
    setState(SERVING_COFFEE);
    Serial.println("Serving coffee...");
    delay(2000);  // Simulate brewing time
    coffeeLevel -= 10;
    waterLevel -= 20;
  } else {
    setState(SERVING_WATER);
    Serial.println("Serving hot water...");
    delay(1000);
    waterLevel -= 15;
  }

  printSupplies();
  setState(FINISHED);
  Serial.println("Done! Press 'r' to reset.");
}

void setState(State newState) {
  currentState = newState;
  Serial.print("[STATE] -> ");
  Serial.println(stateToString(newState));
}

String stateToString(State s) {
  switch (s) {
    case IDLE:          return "IDLE";
    case SELECTING:     return "SELECTING";
    case CHECK_SUPPLIES: return "CHECK_SUPPLIES";
    case SERVING_COFFEE: return "SERVING_COFFEE";
    case SERVING_WATER: return "SERVING_WATER";
    case FINISHED:      return "FINISHED";
    case ERROR_STATE:   return "ERROR";
    default:            return "UNKNOWN";
  }
}

void updateLEDs() {
  digitalWrite(LED_IDLE, currentState == IDLE ? HIGH : LOW);
  digitalWrite(LED_SERVING, (currentState == SERVING_COFFEE || currentState == SERVING_WATER) ? HIGH : LOW);
  digitalWrite(LED_ERROR, currentState == ERROR_STATE ? HIGH : LOW);
}

void printMenu() {
  Serial.println("\n=== Coffee Machine FSM ===");
  Serial.println("'s' - Start selection");
  Serial.println("'1' - Coffee  |  '2' - Water");
  Serial.println("'x' - Cancel  |  'r' - Reset");
}

void printSupplies() {
  Serial.print("Water: "); Serial.print(waterLevel); Serial.println("%");
  Serial.print("Coffee: "); Serial.print(coffeeLevel); Serial.println("%");
}
