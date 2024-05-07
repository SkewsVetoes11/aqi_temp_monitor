#include "main.h"


#define DHTPIN 4     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define BUTTON_PIN 19 // Assign GPIO to button
#define BUZZER_PIN 23 // GPIO23 pin connected to buzzer

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_SSD1306 * display_ptr = &display;

int buttonState = 1;  // variable for reading the pushbutton status
int buttonPrevState = 1;

// For time tracking
unsigned long lastScreenChanged = millis();
unsigned long delayTime = 3000;
unsigned long curTime = 0;


// For tracking screen switching
int curScreen = 0; // 0 = Temperature, 1 = Humidity, 2 = PM2.5, 3 = PM 10, 4 = AQI


// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT_PULLUP);  // Sets Button as input

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  delay(2000);
  
  dht.begin();


  Serial.println("Setup Complete!");

}

void loop() {
  //================ Handles button events ================
  // read the pushbutton input pin:
  buttonState = digitalRead(BUTTON_PIN);
  // compare the buttonState to its previous state
  if (buttonState != buttonPrevState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
      // if the current state is HIGH then the button
      // wend from off to on:

  delay(100);
    } else {
      // if the current state is LOW then the button
      // wend from on to off:
      tone(BUZZER_PIN, 1567, 50); // Plays sound when pressed

  delay(100);
    }
    // Delay a little bit to avoid bouncing
    //delay(50);
  }
  // save the current state as the last state,
  //for next time through the loop
  buttonPrevState = buttonState;
// =======================================================

//================ Handles Screen Content ================
  curTime = millis();
  if(curTime - lastScreenChanged > delayTime)
  {
    char(content)[8];
    curScreen += 1;
    if(curScreen >= 5) { curScreen = 0; }
    lastScreenChanged = millis();
    switch(curScreen)
    {
      case 0:
      {
        // Read temperature as Fahrenheit
        float t = dht.readTemperature(true);
        char(title)[12] = "Temp";
        sprintf(content, "%.2f F", t);
        TwolineDisplay(display_ptr, &title, &content);
        break;
      }

      case 1:
      {
        float h = dht.readHumidity();
        char(title)[12] = "Hum";
        sprintf(content, "%.2f %%", h);
        TwolineDisplay(display_ptr, &title, &content);
        break;
      }

      case 2:
      {
        float pm2_5 = 50;
        char(title)[12] = "PM2.5 ug/L";
        sprintf(content, "%.1f", pm2_5);
        TwolineDisplay(display_ptr, &title, &content);
        break;
      }

      case 3:
      {
        float pm10 = 50;
        char(title)[12] = "PM10";
        sprintf(content, "%.0f", pm10);
        TwolineDisplay(display_ptr, &title, &content);
        break;
      }

      case 4:
      {
        float aqi = 30;
        char(title)[12] = "AQI";
        sprintf(content, "%.0f", aqi);
        TwolineDisplay(display_ptr, &title, &content);
        break;
      }
    }
  }
}


// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

/*
Displays 2 lines of content on SSD 1306 128x64 OLED Display
display: an instance of Adafruit_SSD1306 to be used
title: the first line on the display, yellow
content: the second line on the display, blue
*/
void TwolineDisplay(Adafruit_SSD1306 * d, char(*title)[12], char(*content)[8])
{
  
  d->clearDisplay();
  d->setCursor(0, 0); 
  d->setTextColor(WHITE);
  d->setTextSize(2);
  d->println(*title);

  d->setTextSize(1);
  d->println();


  d->setTextSize(3);
  d->println(*content);
  d->display();


  // display.setTextSize(1);
  // display.println();
  // display.display();


  // display.setTextSize(3);
  // display.print(content);
  // display.display();

}