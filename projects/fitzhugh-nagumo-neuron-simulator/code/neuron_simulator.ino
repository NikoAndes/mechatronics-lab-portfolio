/*
 * FitzHugh-Nagumo Neuron Simulator
 * Author: Nicolas Isaza Sierra (NikoAndes)
 * Description: Simplified neuron firing simulation inspired by
 *              FitzHugh-Nagumo model. Uses button input and LED output.
 * Platform: ESP32 / Arduino
 *
 * Concept:
 *   The FitzHugh-Nagumo model describes how neurons fire (action potentials).
 *   When input stimulus exceeds a threshold, the neuron 'fires' a pulse.
 *   After firing, it enters a refractory period before it can fire again.
 */

// --- Pin definitions ---
const int BUTTON_PIN = 15;   // Stimulus input button
const int LED_FIRE = 2;      // LED that fires when neuron activates
const int LED_REFRACT = 4;   // LED showing refractory period
const int ANALOG_OUT = 25;   // DAC output to simulate voltage (optional)

// --- FN Model Parameters (simplified) ---
float v = -1.0;      // membrane voltage variable
float w = 0.0;       // recovery variable
float I_ext = 0.0;   // external current (stimulus)

const float dt = 0.1;   // time step
const float a = 0.7;
const float b = 0.8;
const float tau = 12.5;
const float FIRE_THRESHOLD = 0.5;

// State flags
bool isFiring = false;
bool isRefractory = false;
unsigned long fireTime = 0;
const int REFRACTORY_MS = 300;
const int FIRE_DURATION_MS = 100;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_FIRE, OUTPUT);
  pinMode(LED_REFRACT, OUTPUT);
  Serial.println("=== FitzHugh-Nagumo Neuron Simulator ===");
  Serial.println("Press button to apply stimulus.");
  Serial.println("Monitoring: v (voltage), w (recovery), state");
}

void loop() {
  // Read stimulus from button
  I_ext = (digitalRead(BUTTON_PIN) == LOW) ? 1.5 : 0.0;

  // Update FN model
  updateModel();

  // Check for firing condition
  if (v > FIRE_THRESHOLD && !isRefractory) {
    triggerFire();
  }

  // Handle refractory period
  handleRefractory();

  // Output to Serial plotter (open Tools > Serial Plotter)
  Serial.print("v:"); Serial.print(v, 3);
  Serial.print(",w:"); Serial.print(w, 3);
  Serial.print(",I:"); Serial.println(I_ext);

  delay((int)(dt * 100));
}

void updateModel() {
  // FitzHugh-Nagumo equations (Euler integration)
  float dv = v - (v * v * v / 3.0) - w + I_ext;
  float dw = (v + a - b * w) / tau;
  v += dv * dt;
  w += dw * dt;

  // Optional: output v as analog voltage on DAC pin (0-3.3V mapped to 0-255)
  int dacVal = constrain((int)((v + 2.0) / 4.0 * 255), 0, 255);
  dacWrite(ANALOG_OUT, dacVal);
}

void triggerFire() {
  if (!isFiring) {
    isFiring = true;
    isRefractory = false;
    fireTime = millis();
    digitalWrite(LED_FIRE, HIGH);
    Serial.println(" >>> NEURON FIRED! <<<");
  }
}

void handleRefractory() {
  if (isFiring && millis() - fireTime > FIRE_DURATION_MS) {
    isFiring = false;
    isRefractory = true;
    digitalWrite(LED_FIRE, LOW);
    digitalWrite(LED_REFRACT, HIGH);
    Serial.println(" [refractory period]");
  }
  if (isRefractory && millis() - fireTime > (FIRE_DURATION_MS + REFRACTORY_MS)) {
    isRefractory = false;
    digitalWrite(LED_REFRACT, LOW);
    Serial.println(" [neuron ready]");
  }
}
