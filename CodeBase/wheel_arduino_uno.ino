//This code is designed to calibrate your setup. It spins the wheel slowly and stops it exactly when it counts the number of pulses you specified for one turn.
/*
 * JY01 Driver - ARDUINO UNO ONE ROTATION CALIBRATION
 * * BEHAVIOR:
 * 1. Spins at a slow, steady speed.
 * 2. Counts pulses.
 * 3. HARD BRAKES exactly when 1 rotation (pulse limit) is reached.
 */

// ================= USER CONFIGURATION =================
// CHANGE THIS to calibrate! (How many pulses = 360 degrees?)
const int PULSES_PER_REV = 30;     

// Speed Settings
// Low speed (e.g. 70-90) is best for calibration so it stops instantly without coasting.
const int TEST_SPEED_PWM = 80;    
// ======================================================

// Pin Definitions
const int PIN_SIGNAL = 2; // MUST be Pin 2 for Interrupts on Uno
const int PIN_ZF = 7;     // Direction
const int PIN_EL = 8;     // Enable/Brake
const int PIN_VR = 9;     // Speed (PWM)

// Interrupt Variables
volatile long pulseCount = 0;
volatile unsigned long lastPulseTime = 0;

// State variable
bool isRunning = true;

void setup() {
  Serial.begin(115200);
  
  pinMode(PIN_VR, OUTPUT);
  pinMode(PIN_EL, OUTPUT);
  pinMode(PIN_ZF, OUTPUT);
  pinMode(PIN_SIGNAL, INPUT_PULLUP);

  // Attach Interrupt to Pin 2
  attachInterrupt(digitalPinToInterrupt(PIN_SIGNAL), countPulse, FALLING);

  // --- START SEQUENCE ---
  Serial.println(">>> STARTING 1 ROTATION TEST <<<");
  
  // 1. Reset Pulse Count to 0
  pulseCount = 0;
  
  // 2. Enable & Set Direction
  digitalWrite(PIN_ZF, HIGH); // Forward
  digitalWrite(PIN_EL, HIGH); // Enable
  
  // 3. Start Motor
  analogWrite(PIN_VR, TEST_SPEED_PWM);
}

void loop() {
  // If we have already finished, do nothing
  if (!isRunning) return;

  // 1. Read Pulse Count Safely
  noInterrupts();
  long currentPulses = pulseCount;
  interrupts();

  // 2. Print Status (to help you see if it's counting)
  Serial.print("Pulses: ");
  Serial.print(currentPulses);
  Serial.print(" / ");
  Serial.println(PULSES_PER_REV);

  // 3. Check for Finish Line
  if (currentPulses >= PULSES_PER_REV) {
    // STOP!
    analogWrite(PIN_VR, 0);     // Kill power
    digitalWrite(PIN_EL, LOW);  // Hard Brake
    isRunning = false;          // Stop the loop logic
    
    Serial.println(">>> ROTATION COMPLETE <<<");
    Serial.print("Final Count: ");
    Serial.println(currentPulses);
  }
  
  delay(50); // Small delay to keep Serial readable
}

// --- INTERRUPT ROUTINE ---
void countPulse() {
  unsigned long now = micros();
  // Debounce (ignore pulses closer than 500 microseconds)
  if (now - lastPulseTime > 500) {
    lastPulseTime = now;
    pulseCount++;
  }
}
