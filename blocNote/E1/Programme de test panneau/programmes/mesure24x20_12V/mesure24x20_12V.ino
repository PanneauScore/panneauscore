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
  
  matrix.setTextSize(1);
  matrix.setTextWrap(false);
  
  matrix.setCursor(0,0);
  matrix.setTextColor(matrix.Color333(0,7,7));
  matrix.fillRect(0, 0, 24, 20, matrix.Color333(7, 7, 0));
}

  //matrix.drawRect( 20, 11, 23, 11, matrix.Color333(1, 1, 1));
  //matrix.drawLine(31, 11, 31, 21, matrix.Color333(1, 1, 1));

  void loop(){
    
  }
