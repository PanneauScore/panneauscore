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

int scoreLC;
int scoreVST;

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);
 
void setup() {

  scoreLC = 0;
  scoreVST = 0;

  matrix.begin();

  matrix.fillScreen(matrix.Color333(0, 0, 0));
  uint8_t w = 0;
  char *str = "";
  for (w = 0; w < 7; w++) {
    matrix.fillScreen(str[w]);
  }

  matrix.setTextSize(1);
  matrix.setTextWrap(false);

  matrix.setCursor(15, 12);
  matrix.setTextColor(matrix.Color333(6, 6, 6));
  matrix.println("Pansco");
  delay(2000);

  matrix.fillScreen(matrix.Color333(0, 0, 0));
  delay(750);


  matrix.drawRect( 0, 0, 32, 11, matrix.Color333(2, 0, 0)); //dipsosition initiale du panneau
  matrix.drawRect(5, 10, 27, 13, matrix.Color333(2, 0, 0));
  matrix.drawLine(0, 11, 5, 22, matrix.Color333(2, 0, 0));

  matrix.drawRect( 32, 0, 32, 11, matrix.Color333(0, 0, 2));
  matrix.drawRect(32, 10, 27, 13, matrix.Color333(0, 0, 2));
  matrix.drawLine(63, 11, 58, 22, matrix.Color333(0, 0, 2));
  
  matrix.println();
  matrix.setTextColor(matrix.Color333(6, 0, 0));
  matrix.setCursor(10, 2);
  matrix.print("lc");
  matrix.setTextColor(matrix.Color333(0, 0, 6));
  matrix.setCursor(39, 2);
  matrix.print("vst");

 matrix.setTextColor(matrix.Color333(6, 6, 6));
  matrix.setCursor(0, 23);
  matrix.println("-----------");

}

void loop() {
  
 matrix.setCursor(10, 13);
  matrix.setTextColor(matrix.Color333(6, 6, 6));
  matrix.println(scoreLC);
  matrix.setCursor(37, 13);
  matrix.println(scoreVST);




}
//+1 score

 
 

// Input a value 0 to 24 to get a color value.
// The colours are a transition r - g - b - back to r.
uint16_t Wheel(byte WheelPos) {
  if (WheelPos < 8) {
    return matrix.Color333(7 - WheelPos, WheelPos, 0);
  } else if (WheelPos < 16) {
    WheelPos -= 8;
    return matrix.Color333(0, 7 - WheelPos, WheelPos);
  } else {
    WheelPos -= 16;
    return matrix.Color333(0, WheelPos, 7 - WheelPos);
  }
}
