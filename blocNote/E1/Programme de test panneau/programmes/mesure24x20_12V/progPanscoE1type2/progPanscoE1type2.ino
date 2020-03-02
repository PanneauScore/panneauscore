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

#define LF 10

char carDeb;

String chaineScore;
String scoreLc;
String scoreVst;

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false, 64);

void setup() {

  Serial.begin(9600);

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
  matrix.drawRect(0, 10, 27, 13, matrix.Color333(2, 0, 0));
  //matrix.drawLine(0, 11, 5, 22, matrix.Color333(2, 0, 0));

  matrix.drawRect( 32, 0, 32, 11, matrix.Color333(0, 0, 2));
  matrix.drawRect(37, 10, 27, 13, matrix.Color333(0, 0, 2));
  //matrix.drawLine(63, 11, 58, 22, matrix.Color333(0, 0, 2));

  matrix.println();
  matrix.setTextColor(matrix.Color333(6, 0, 0));
  matrix.setCursor(1, 2);
  matrix.print("local");
  matrix.setTextColor(matrix.Color333(0, 0, 6));
  matrix.setCursor(34, 2);
  matrix.print("visit");

  matrix.setTextColor(matrix.Color333(6, 6, 6));
  matrix.setCursor(0, 23);
  matrix.println("-----------");

}

void loop() {

  if (Serial.available() > 0) {
    carDeb = Serial.read();


    if (carDeb == '$') {
      chaineScore = Serial.readStringUntil(LF);
      scoreLc = chaineScore.substring(0, 3);
      scoreVst = chaineScore.substring(4, 7);

      Serial.print("scoreLc = ");
      Serial.println(scoreLc);

      Serial.print("scoreVst = ");
      Serial.println(scoreVst);

      matrix.setCursor(5, 13);   //score
      matrix.setTextColor(matrix.Color333(6, 6, 6));
      matrix.println(scoreLc);
      matrix.setCursor(42, 13);
      matrix.println(scoreVst);



    }
  }
}

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
