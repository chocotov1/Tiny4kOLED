/*
 * Tiny4kOLED - Drivers for SSD1306 controlled dot matrix OLED/PLED 128x32 displays
 *
 * Based on ssd1306xled, re-written and extended by Stephen Denne
 * from 2017-04-25 at https://github.com/datacute/Tiny4kOLED
 *
 */

/*
 * Display power consumption test:
 * 
 * - change contrast in steps of 51 from 0 to 255
 * - display counter counting from 7 to 34
 * - turn off screen in between tests
 * 
 * Tested on a ATtiny85 at 1 MHz with built in Wire.h of https://github.com/SpenceKonde/ATTinyCore
 * 
 * chocotov1
 * 
 */

#include <Tiny4kOLED_Wire.h>

uint16_t TEST_DELAY = 1000;

void setup() {
  oled.begin();
  // big numbers
  oled.setFont(FONT16X32DIGITS);
  // toggle DisplayFrame to not be the RenderFrame, otherwise updates are visible 
  oled.switchDisplayFrame();
  clear_screen();
  // Turn on the display.
  oled.on();
}

void print_number(int16_t n){
  oled.setCursor(0, 0);
  oled.print(n);
  // Swap which half of RAM is being written to, and which half is being displayed.
  // This is equivalent to calling both switchRenderFrame and switchDisplayFrame.
  oled.switchFrame();
}

void clear_screen(){
    oled.clear();
    oled.switchFrame();
    oled.clear();
    oled.switchFrame();
}

void loop(){

  for (int16_t c = 0; c <= 255; c += 51){
    oled.setContrast(c);
    print_number(c);
    delay(TEST_DELAY);
    clear_screen();
    
    for (uint16_t i = 7; i < 35; i++){ 
       print_number(i);
       delay(200);
    }
    delay(TEST_DELAY);
    
    clear_screen();
    oled.off();
    delay(TEST_DELAY * 2);
    oled.on();
  }
}
