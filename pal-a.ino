#include <Key.h>
#include <Keypad.h>
#include "Freenove_WS2812_Lib_for_ESP32.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

//Nanopixel
#define LEDS_COUNT  1   // The number of led
#define LEDS_PIN	  16  // define the pin connected to the led strip
#define CHANNEL		  0   // RMT module channel
Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);
int m_color[5][3] = { {255, 0, 255}, {255, 0, 255}, {255, 0, 0}, {255, 255, 255} };
int delayval = 500;

//LCD
#define SDA 13                    //Define SDA pins
#define SCL 14                    //Define SCL pins
LiquidCrystal_I2C lcd(0x27,16,2); 

//Keypad
#define ROW_NUM 4
#define COLUMN_NUM 4
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROW_NUM] = {19, 18, 5, 17};
byte colPins[COLUMN_NUM] = {16, 4, 0, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROW_NUM, COLUMN_NUM);


void setup() {
  Serial.begin(9600);
  Wire.begin(SDA, SCL);           // attach the IIC pin
  if (!i2CAddrTest(0x27)) {
    lcd = LiquidCrystal_I2C(0x3F, 16, 2);
  }
  lcd.init();                     // LCD driver initialization
  lcd.backlight();                // Open the backlight
  lcd.setCursor(0,0);             // Move the cursor to row 0, column 0
  lcd.print("hello, world!");     // The print content is displayed on the LCD
	strip.begin();
	strip.setBrightness(10);	
}
void loop() {
  char key = keypad.getKey();
  if (key) {
    Serial.println(key);
  }
  lcd.setCursor(0,1);             // Move the cursor to row 1, column 0
  lcd.print("Counter:");          // The count is displayed every second
  lcd.print(millis() / 1000);
  delay(1000);
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < LEDS_COUNT; i++) {
			strip.setLedColorData(i, m_color[j][0], m_color[j][1], m_color[j][2]);// Set color data.
			strip.show();   // Send color data to LED, and display.
			delay(delayval);// Interval time of each LED.
		}
		delay(200);       // Interval time of each group of colors.
	}
}

bool i2CAddrTest(uint8_t addr) {
  Wire.begin();
  Wire.beginTransmission(addr);
  if (Wire.endTransmission() == 0) {
    return true;
  }
  return false;
}
