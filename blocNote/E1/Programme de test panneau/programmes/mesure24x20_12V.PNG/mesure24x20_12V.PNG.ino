// testshapes demo for RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x64 RGB LED matrix.

// NOTE THIS CAN ONLY BE USED ON A MEGA! NOT ENOUGH RAM ON UNO!

#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define OE   9
#define LAT 10
#define CLK 11
#define A   A0
#define B   A1
#define C   A2
#define D   A3

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

void setup() {

  matrix.begin();

  matrix.fillScreen(matrix.Color333(0, 0, 0));
  uint8_t w = 0;
  char *str = "";
  for (w=0; w<8; w++) {
  matrix.fillScreen(str[w]);
  }
  
  matrix.setTextSize(1);
  matrix.setTextWrap(false);
  
  matrix.setCursor(15, 12);
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.println("Pansco");
  delay(2000);

  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(750);

  //matrix.drawRect( 20, 11, 23, 11, matrix.Color333(1, 1, 1));
  //matrix.drawLine(31, 11, 31, 21, matrix.Color333(1, 1, 1));

  matrix.setCursor(17, 1);
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.println("00:00");

  matrix.println();
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.setCursor(7, 8);
  matrix.print("lc");
  matrix.setTextColor(matrix.Color333(0,0,7));
  matrix.setCursor(45, 8);
  matrix.print("vst");

  matrix.setCursor(9, 16);
  matrix.setTextColor(matrix.Color333(7,7,7));
  matrix.println("000");
  matrix.setCursor(37, 16);
  matrix.println("000");

  matrix.setCursor(0, 24);
  matrix.println("AAAAAAAAAAA");
  
}




 

 void loop(){
 
 }

// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.
uint16_t Wheel(byte WheelPos) {
  if(WheelPos < 8) {
   return matrix.Color333(7 - WheelPos, WheelPos, 0);
  } else if(WheelPos < 16) {
   WheelPos -= 8;
   return matrix.Color333(0, 7-WheelPos, WheelPos);
  } else {
   WheelPos -= 16;
   return matrix.Color333(0, WheelPos, 7 - WheelPos);
  }
}
