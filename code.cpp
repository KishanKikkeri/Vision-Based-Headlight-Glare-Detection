// Pin Definitions
const int ldrPin = 34;
const int ledPin = 2;
const int buzzerPin = 4;

// Variables
int ldrValue = 0;
int smoothedValue = 0;
int ambientLight = 0;

// Settings
int sampleCount = 10;          // for averaging
int baseThreshold = 500;       // base offset above ambient
int mediumOffset = 800;
int highOffset = 1200;

// Timing
unsigned long lastAmbientUpdate = 0;
int ambientInterval = 3000;    // update ambient every 3 sec

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
}

void loop() {

  // -------- 1. Noise Filtering (Averaging) --------
  int total = 0;
  for (int i = 0; i < sampleCount; i++) {
    total += analogRead(ldrPin);
    delay(5);
  }
  smoothedValue = total / sampleCount;

  // -------- 2. Adaptive Ambient Light --------
  if (millis() - lastAmbientUpdate > ambientInterval) {
    ambientLight = smoothedValue;
    lastAmbientUpdate = millis();
  }

  // Dynamic thresholds
  int mediumThreshold = ambientLight + mediumOffset;
  int highThreshold = ambientLight + highOffset;

  // -------- 3. Glare Detection Levels --------
  String glareLevel = "NORMAL";

  if (smoothedValue > highThreshold) {
    glareLevel = "HIGH GLARE";
  }
  else if (smoothedValue > mediumThreshold) {
    glareLevel = "MEDIUM GLARE";
  }

  // -------- 4. Output Control --------
  if (glareLevel == "HIGH GLARE") {
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);   // continuous beep
  }
  else if (glareLevel == "MEDIUM GLARE") {
    digitalWrite(ledPin, HIGH);

    // slow beep
    digitalWrite(buzzerPin, HIGH);
    delay(100);
    digitalWrite(buzzerPin, LOW);
  }
  else {
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  // -------- 5. Serial Monitor Output --------
  Serial.print("Raw: ");
  Serial.print(smoothedValue);
  Serial.print(" | Ambient: ");
  Serial.print(ambientLight);
  Serial.print(" | Level: ");
  Serial.println(glareLevel);

  delay(200);
}