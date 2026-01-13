#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <esp_bt.h>
#include <esp_wifi.h>

#define PIN_LED 7        
#define PIN_STATUS_LED 8 
#define NUM_LEDS 35    

Adafruit_NeoPixel strip(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);

unsigned long previousMillis = 0;
const long interval = 500; 
bool ledState = LOW;

void setup() {
  WiFi.mode(WIFI_OFF);
  btStop();
  esp_wifi_stop();

  pinMode(PIN_STATUS_LED, OUTPUT);

  strip.begin();
  strip.setBrightness(40);
  strip.show();
}

// Fonction pour faire clignoter la LED de l'ESP32 sans bloquer
void checkStatusLED() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    ledState = !ledState;
    digitalWrite(PIN_STATUS_LED, ledState);
  }
}

// --- SCÉNARIO 1 : Respiration lente (Cyan) ---
void scenarioRespiration() {
  for (int b = 10; b < 100; b++) { // Variation de luminosité
    strip.setBrightness(b);
    for (int i = 0; i < NUM_LEDS; i++) {
      strip.setPixelColor(i, strip.Color(0, 160, 255));
    }
    strip.show();
    checkStatusLED();
    delay(20);
  }
  for (int b = 100; b > 10; b--) {
    strip.setBrightness(b);
    strip.show();
    checkStatusLED();
    delay(20);
  }
}

// --- SCÉNARIO 2 : Rotation ---
void scenarioRotation() {
  for (int j = 0; j < NUM_LEDS * 4; j++) { // Faire 2 tours
    strip.clear();
    for (int i = 0; i < 5; i++) { // Une chenille de 5 LEDs
      int pos = (j + i) % NUM_LEDS;
      strip.setPixelColor(pos, strip.Color(0, 255, 150)); // Vert/Cyan
    }
    strip.show();
    checkStatusLED();
    delay(50);
  }
}

// --- SCÉNARIO 3 : Flash ---
void scenarioFlash() {
  for (int f = 0; f < 5; f++) { // 5 éclairs blancs
    strip.fill(strip.Color(0, 160, 255)); // Tout Cyan
    strip.show();
    delay(30);
    strip.clear();
    strip.show();
    delay(100);
    checkStatusLED();
  }
}

void loop() {
  int choix = random(1, 4);

  if (choix == 1) {
    scenarioRespiration();
  } else if (choix == 2) {
    scenarioRotation();
  } else if (choix == 3) {
    scenarioFlash();
  }
  
  delay(1000);
}
