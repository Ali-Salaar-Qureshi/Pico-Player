#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

//Screen initialization:
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Button Variables:
int button2State;
int button1State;
int lastButton2State = HIGH;

//Volume Variables:
int volumePercent;

//Selection Variables:
int selection;
int currentScreen = 0;

//Potentiometer Variables:
int potPin = A1; 
int potVal = 0;


void setup() {
  // put your setup code here, to run once:
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  display.clearDisplay();
  Serial.begin(9600); 
}


void loop() {

  button1State = digitalRead(3);
  if (button1State == LOW) {
    currentScreen = 0;
  }
  button2State = digitalRead(4);


//Main Loop for controls:
switch (currentScreen) {
  case 0:
   potVal = analogRead(potPin);
   display.clearDisplay();
  

  if(potVal > 510){
    selection = 1;
  } else{
    selection = 0;
  };
  
  button1State = digitalRead(3);

if (button2State == LOW && lastButton2State == HIGH && selection == 1) {
  currentScreen = 2;
}

if(button2State == LOW && lastButton2State == HIGH && selection == 0){
  currentScreen = 1;
}

  switch (selection)
  {
  case 0:
    //Music selected:
    display.setCursor(50,16);
    display.fillRoundRect(22, 10, 84, 20, 4,SSD1306_WHITE);
    display.setTextColor(SSD1306_BLACK);
    display.println(F("Music"));
    

    display.setTextColor(SSD1306_WHITE);
    display.setCursor(48,48);  
    display.println(F("Volume"));
    display.drawRoundRect(22, 42, 84, 20, 4, SSD1306_WHITE);
    display.display();
    break;

    case 1:
    //Volume selected:
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(50,16);
    display.drawRoundRect(22, 10, 84, 20, 4, SSD1306_WHITE);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("Music"));
    

    display.setCursor(48,48);  
    display.fillRoundRect(22, 42, 84, 20, 4, SSD1306_WHITE);
    display.setTextColor(SSD1306_BLACK);
    display.println(F("Volume"));
    
    display.display();
    break;
  }
  break;

  case 1:
  display.clearDisplay();
    display.setCursor(0,0);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("Music Menu"));
    display.display();
    break;

  case 2:
  //Volume Menu:
  potVal = analogRead(potPin); 
    volumePercent = map(potVal, 0, 1023, 0, 100);
    Serial.println(volumePercent);
  //page title:
  display.clearDisplay();
    display.setCursor(0,0);
    display.setTextColor(SSD1306_WHITE);
    display.println(F("Set Volume:"));
  //Volume percentage:
    display.setCursor(0,16);
    display.print(volumePercent);
    display.print(F("%"));
  //volume bar
    display.drawRect(14, 40, 102, 16, SSD1306_WHITE);
    display.fillRect(15, 41, volumePercent, 14, SSD1306_WHITE);
    display.display();

    break;
}

//debugging:
Serial.println(currentScreen);
Serial.println(volumePercent);

  display.display();
  lastButton2State = button2State;
  delay(50);
}