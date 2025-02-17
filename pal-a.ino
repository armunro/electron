/**********************************************************************
  Filename    : NeoPixel
  Description : Basic usage of LEDPixel, 
                Make the strip light up in different colors gradually.
  Auther      : www.freenove.com
  Modification: 2023/06/15
**********************************************************************/
#include "Freenove_WS2812_Lib_for_ESP32.h"

#define LEDS_COUNT  1   // The number of led
#define LEDS_PIN	  16  // define the pin connected to the led strip
#define CHANNEL		  0   // RMT module channel

Freenove_ESP32_WS2812 strip = Freenove_ESP32_WS2812(LEDS_COUNT, LEDS_PIN, CHANNEL, TYPE_GRB);

int m_color[5][3] = { {255, 0, 255}, {255, 0, 255}, {255, 0, 0}, {255, 255, 255} };
int delayval = 500;

void setup() {
	strip.begin();
	strip.setBrightness(10);	
}
void loop() {
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < LEDS_COUNT; i++) {
			strip.setLedColorData(i, m_color[j][0], m_color[j][1], m_color[j][2]);// Set color data.
			strip.show();   // Send color data to LED, and display.
			delay(delayval);// Interval time of each LED.
		}
		delay(200);       // Interval time of each group of colors.
	}
}
