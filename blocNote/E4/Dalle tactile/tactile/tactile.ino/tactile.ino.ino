/*
  Demo 1 (Display + Touch-Panel)
*/

#include <MI0283QT2.h>
#include <ADS7846.h>

#define TP_EEPROMADDR (0x00) //eeprom address for calibration data

MI0283QT2 lcd;
ADS7846 tp;

int scoreLC = 0;
int scoreVST = 0;
char tabScoreLocal[4] = "000";
char tabScoreVisiteur[4] = "000";
char tabScoreReset[4] = "000";
boolean etatTouche = true;
String trame = "";

void setup()
{

  Serial.begin(9600);
  //init display
  lcd.init(4); //spi-clk = Fcpu/4

  //init touch controller
  tp.init();

  //clear screen
  lcd.clear(COLOR_WHITE);

  //touch-panel calibration
  tp.service();

  if (tp.getPressure() > 5)
  {
    tp.doCalibration(&lcd, TP_EEPROMADDR, 0); //dont check EEPROM for calibration data
  }
  else
  {
    tp.doCalibration(&lcd, TP_EEPROMADDR, 1); //check EEPROM for calibration data
  }

  lcd.setOrientation(270); tp.setOrientation(270);
  afficheText();
}


void loop()
{
  char tmp[128];
  static uint16_t last_x = 0, last_y = 0;
  static uint8_t led = 60;
  unsigned long m;
  //static unsigned long prevMillis=0;

  //service routine for touch panel
  tp.service();

  //show tp data
  sprintf(tmp, "X:%03i|%04i Y:%03i|%04i P:%03i", tp.getX(), tp.getXraw(), tp.getY(), tp.getYraw(), tp.getPressure());
  lcd.drawText(2, 2, tmp, 1, COLOR_BLACK, COLOR_WHITE);

  detectionTouche();
  if (tp.getPressure() == 0) {
    etatTouche = true;
  }
}

void afficheText() {
  lcd.drawText(00, 20, "LOCAL", 2, COLOR_BLACK, COLOR_RED);
  lcd.drawText(25, 60, "+", 6, COLOR_BLACK, COLOR_RED);
  lcd.drawText(25, 160, "-", 6, COLOR_BLACK, COLOR_RED);

  lcd.drawText(90, 20, "VISITEURS", 2, COLOR_BLACK, COLOR_BLUE);
  lcd.drawText(130, 60, "+", 6, COLOR_BLACK, COLOR_BLUE);
  lcd.drawText(130, 160, "-", 6, COLOR_BLACK, COLOR_BLUE);

  lcd.drawText(190, 130, "R", 4, COLOR_WHITE, COLOR_BLACK);   // bouton reset
  sprintf(tabScoreLocal, "%03d", scoreLC);
  lcd.drawText(0, 250, tabScoreLocal, 4, COLOR_BLACK, COLOR_RED);  // score local
  sprintf(tabScoreVisiteur, "%03d", scoreVST);
  lcd.drawText(110, 250, tabScoreVisiteur, 4, COLOR_BLACK, COLOR_BLUE);  // score visiteurs
}

void detectionTouche() {
  if ((tp.getPressure() > 5) && (etatTouche == true)) //touch press?
  {
    etatTouche = false;
    //change backlight power
    if ((tp.getX() > 18) && (tp.getX() < 59)) {        // BOUTON + LOCAL
      if ((tp.getY() > 54) && (tp.getY() < 128))
      {
        scoreLC++;
        sprintf(tabScoreLocal, "%03d", scoreLC);
        lcd.drawText(0, 250, tabScoreLocal, 4, COLOR_BLACK, COLOR_RED);  // score local
      }
    }

    if ((tp.getX() > 21) && (tp.getX() < 57)) {     // BOUTON - LOCAL
      if ((tp.getY() > 159) && (tp.getY() < 232))
      {
        scoreLC-- ;
        if (scoreLC < 0) {
          scoreLC = 0;
        }
        sprintf(tabScoreLocal, "%03d", scoreLC);
        lcd.drawText(0, 250, tabScoreLocal, 4, COLOR_BLACK, COLOR_RED);  // score local
      }
    }
    if ((tp.getX() > 122) && (tp.getX() < 160)) {    // BOUTON + VISITEURS
      if ((tp.getY() > 62) && (tp.getY() < 136))
      {
        scoreVST++;
        sprintf(tabScoreVisiteur, "%03d", scoreVST);
        lcd.drawText(110, 250, tabScoreVisiteur, 4, COLOR_BLACK, COLOR_BLUE);  // score visiteurs
      }
    }
    if ((tp.getX() > 119) && (tp.getX() < 160)) {     // BOUTON - VISITEURS
      if ((tp.getY() > 167) && (tp.getY() < 240))
      {
        scoreVST-- ;
        if (scoreVST < 0) {
          scoreVST = 0;
        }
        sprintf(tabScoreVisiteur, "%03d", scoreVST);
        lcd.drawText(110, 250, tabScoreVisiteur, 4, COLOR_BLACK, COLOR_BLUE);  // score visiteurs
      }
    }
    if ((tp.getX() > 175) && (tp.getX() < 200)) {  //RESET
      if ((tp.getY() > 145) && (tp.getY() < 190))
      {
        scoreVST = 0;
        scoreLC = 0;
        lcd.drawText(0, 250, scoreLC, 4, COLOR_BLACK, COLOR_RED);
        lcd.drawText(110, 250, scoreVST, 4, COLOR_BLACK, COLOR_BLUE);

        sprintf(tabScoreReset, "%03d", scoreVST, scoreLC);
        lcd.drawText(110, 250, tabScoreReset, 4, COLOR_BLACK, COLOR_BLUE);
        lcd.drawText(0, 250, tabScoreReset, 4, COLOR_BLACK, COLOR_RED);
      }
    }
    envoieTrame();
  }
}

void envoieTrame() {
  trame = "S" + (String)tabScoreLocal + ":" + (String)tabScoreVisiteur;
  Serial.println(trame);
}



