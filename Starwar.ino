// Musical Notes
const int c = 261, d = 294, e = 329, f = 349, g = 391, gS = 415, a = 440, aS = 455, b = 466, cH = 523, cSH = 554, dH = 587, dSH = 622, eH = 659, fH = 698, fSH = 740, gH = 784, gSH = 830, aH = 880;

const int buzzerPin = 27; // Set to GPIO 27
const int buttonPin = 21; // Set to GPIO 21

// Speed Control Variables
volatile float speedMultiplier = 1.0;
volatile int speedStage = 3; 
volatile unsigned long lastButtonPress = 0;

void IRAM_ATTR handleButton() {
  unsigned long now = millis();
  // 250ms Debounce
  if (now - lastButtonPress > 250) {
    speedStage++;
    if (speedStage > 5) speedStage = 1;

    if (speedStage == 1)      speedMultiplier = 1.50; // Slowest
    else if (speedStage == 2) speedMultiplier = 1.25; 
    else if (speedStage == 3) speedMultiplier = 1.00; // Normal
    else if (speedStage == 4) speedMultiplier = 0.75; 
    else if (speedStage == 5) speedMultiplier = 0.50; // Fastest
    
    lastButtonPress = now;
  }
}

void setup() {
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); 

  // Attach Interrupt: Note the IRAM_ATTR for ESP32 stability
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButton, FALLING);
}

void loop() {
  firstSection();
  secondSection();
  
  // Variant 1
  beep(f, 250); beep(gS, 500); beep(f, 350); beep(a, 125);
  beep(cH, 500); beep(a, 375); beep(cH, 125); beep(eH, 650);
  smartDelay(500);

  secondSection();

  // Variant 2
  beep(f, 250); beep(gS, 500); beep(f, 375); beep(cH, 125);
  beep(a, 500); beep(f, 375); beep(cH, 125); beep(a, 650);
  smartDelay(650);
}

void smartDelay(int ms) {
  delay(ms * speedMultiplier);
}

void beep(int note, int duration) {
  int adjDuration = duration * speedMultiplier;
  
  tone(buzzerPin, note, adjDuration);
  delay(adjDuration); 
  
  noTone(buzzerPin);
  delay(50 * speedMultiplier); 
}

void firstSection() {
  beep(a, 500); beep(a, 500); beep(a, 500); beep(f, 350); beep(cH, 150);
  beep(a, 500); beep(f, 350); beep(cH, 150); beep(a, 650);
  smartDelay(500);

  beep(eH, 500); beep(eH, 500); beep(eH, 500); beep(fH, 350); beep(cH, 150);
  beep(gS, 500); beep(f, 350); beep(cH, 150); beep(a, 650);
  smartDelay(500);
}

void secondSection() {
  beep(aH, 500); beep(a, 300); beep(a, 150); beep(aH, 500); beep(gSH, 325);
  beep(gH, 175); beep(fSH, 125); beep(fH, 125); beep(fSH, 250);
  smartDelay(325);

  beep(aS, 250); beep(dSH, 500); beep(dH, 325); beep(cSH, 175);
  beep(cH, 125); beep(b, 125); beep(cH, 250);
  smartDelay(350);
}
