#include "main.h"
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// DHT referenced: ladyada
// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor
#include <DHT.h>

#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define BUTTON_PIN 19 // Assign GPIO to button
#define BUZZER_PIN 23 // GPIO23 pin connected to buzzer

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Sets Button as input

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  Serial.println("Setup Complete!");

}

void loop() {
  // put your main code here, to run repeatedly:

  display.clearDisplay();
  display.setCursor(0, 0); 
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.println("dfsdsf");
  display.println(myFunction(1,2));
  display.display();
}


// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}