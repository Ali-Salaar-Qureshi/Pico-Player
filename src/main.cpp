#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

// Hardware I2C Constructor for 128x64 SSD1306
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

const int BUTTON_PIN = 2; // Wired directly to Pin 2 and GND
bool selectVolume = false; // false = Music (Top), true = Volume (Bottom)

void setup() {
  u8g2.begin();
  
  // CRITICAL CHANGE: Activates the internal pull-up resistor. 
  // This holds Pin 2 at 3.3V (HIGH) until the button is physically pressed.
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // 1. Check for button press. Because of INPUT_PULLUP, a press reads as LOW.
  if (digitalRead(BUTTON_PIN) == LOW) {
    selectVolume = !selectVolume; // Toggle selection
    
    // Simple debounce delay so a single quick tap doesn't register 
    // as 50 rapid-fire presses.
    delay(250); 
  }

  // 2. Start drawing the UI
  u8g2.clearBuffer();
  
  u8g2.setFont(u8g2_font_9x15_tf); 

  // Draw Option 1: Music (Top Row)
  u8g2.drawStr(25, 26, "Music");
  
  // Draw Option 2: Volume (Bottom Row)
  u8g2.drawStr(25, 52, "Volume");

  // 3. Draw the Square Selector Frame around the active option
  if (!selectVolume) {
    // Square around "Music"
    u8g2.drawFrame(15, 12, 98, 20); 
  } else {
    // Square around "Volume"
    u8g2.drawFrame(15, 38, 98, 20); 
  }

  u8g2.sendBuffer();
}