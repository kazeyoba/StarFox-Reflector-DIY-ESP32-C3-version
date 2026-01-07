#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <esp_bt.h>
#include <esp_wifi.h>

#define PIN_LED 7       // GPIO 7 sur ESP32-C3
#define NUM_LEDS 12    

Adafruit_NeoPixel strip(NUM_LEDS, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  // Désactivation des ondes pour économiser la batterie
  WiFi.mode(WIFI_OFF);
  btStop();
  esp_wifi_stop();

  strip.begin();
  strip.setBrightness(120); // Ajuster selon l'épaisseur du diffuseur
  strip.show();
}

void loop() {
  // Fond Bleu Cyan
  for(int i=0; i<NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(0, 160, 255)); 
  }
  strip.show();
  delay(50);
  
  // Effet de scintillement
  int spark = random(NUM_LEDS);
  strip.setPixelColor(spark, strip.Color(255, 255, 255));
  strip.show();
  delay(20);
}
