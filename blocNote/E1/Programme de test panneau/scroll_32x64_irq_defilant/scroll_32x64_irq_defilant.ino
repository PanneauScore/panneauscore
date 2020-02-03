// testshapes demo for RGBmatrixPanel library.
// Demonstrates the drawing abilities of the RGBmatrixPanel library.
// For 32x64 RGB LED matrix.

// NOTE THIS CAN ONLY BE USED ON A MEGA! NOT ENOUGH RAM ON UNO!


#include <TimerThree.h>
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

#define OE   9
#define LAT 10
#define CLK 11
#define A   A0
#define B   A1
#define C   A2
#define D   A3

#define sync   2


RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, true, 64);   //true : preparation avant affichage

char car = ' ';
char str[100] = " ";
char tab_car[100] = " ";
int indice = 0;
int textX = matrix.width();
int textMin;
byte flag = 0;
byte etat_premier_caractere = 0;

void setup() {
  Serial.begin(57600);
  matrix.begin();
  matrix.setTextWrap(false); // Allow text to run off right edge
  matrix.setTextSize(1);
  pinMode(sync, OUTPUT);
  Timer3.initialize(55000); // set a timer of length 40ms
  Timer3.attachInterrupt(timerIsr);
}

void loop() {

  if (Serial.available() > 0) {
    reception_caractere();
  }

  if (flag == 1) {
    matrix.fillScreen(0);
    matrix.setTextColor(matrix.Color333(7, 7, 7));
    matrix.setCursor(textX, 3);
    matrix.print(str);
    matrix.swapBuffers(true);
    flag = 0;
  }
}

void reception_caractere()
{

//A completer

  
}

void timerIsr()
{
  // Toggle sync
  digitalWrite(sync, digitalRead(sync) ^ 1);
  if ((--textX) < textMin) textX = matrix.width();
  flag = 1;
}

