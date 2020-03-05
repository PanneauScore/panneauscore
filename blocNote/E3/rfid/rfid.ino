#include <Wire.h> // Inclus la librairie Wire
#include <LiquidCrystal_I2C.h> // Inclus la librairie LiquidCrystal_I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // Declaration de la taille du cadrant (16x2)
#include <SoftwareSerial.h> // Inclus la librairie SoftwareSerial
SoftwareSerial rfid(8, 9); // Pin RX, TX

int compteur = 0;
String code = "";
long numeroBadge = 0;
char trame[14];

void setup() {
  Serial.begin(9600);
  Serial.println("LOG/Setup start");

  lcd.begin();
  lcd.setBacklight(HIGH);
  lcd.setCursor(2, 0);
  lcd.print("Lancement du");
  lcd.setCursor(1, 1);
  lcd.print("lecteur RFID...");

  Serial.println("LOG/LCD start...");

  rfid.begin(9600);

  Serial.println("LOG/RFID start...");
  delay(2000);

  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("TAG: ");

  Serial.println("---LCD / RFID ON---");
}


void loop() {
  char car;
  if (rfid.available()) {
    car = rfid.read();
    trame[compteur] = car;
    if ((compteur >= 3) && (compteur <= 10)) {
      code = code + car;
    }
    compteur++;
    if (compteur == 14) {
      /* verifieChecksum(); */
      numeroBadge = (long) strtol(&code[0], NULL, 16);

      Serial.print("TAG: ");
      Serial.println(numeroBadge);

      lcd.setCursor(5, 0);
      lcd.print(numeroBadge);
      compteur = 0;
      code = "";

      switch (numeroBadge) {
        case 5889129:
          lcd.setCursor(0, 0);
          lcd.clear();
          lcd.print("TAG: ");
          lcd.setCursor(5, 0);
          lcd.print(5889129);
          lcd.setCursor(0, 1);
          lcd.print("Arbitre");
          Serial.println("Arbitre");
          break;
        case 5896990:
          lcd.setCursor(0, 0);
          lcd.clear();
          lcd.print("TAG: ");
          lcd.setCursor(5, 0);
          lcd.print(5896990);
          lcd.setCursor(0, 1);
          lcd.print("Mairie");
          Serial.println("Mairie");
          break;
          
        default:
          lcd.setCursor(0, 0);
          lcd.clear();
          lcd.print("TAG: ");
          lcd.setCursor(0, 1);
          lcd.print("Badge invalide");
          Serial.println("Badge invalide");
          break;
      }
    }
  }
}


/*
  void verifieChecksum() {
  int i;
  int octet;
  Serial.println("debut chk");
  for (i = 1; i <= 10; i = i + 2) {
    octet = (trame[i] - 0x30) * 16 + (trame[i + 1] - 0x30);
    Serial.print(octet, HEX);

    lcd.setCursor(0, 1);
    lcd.print(octet, HEX);
  }
  Serial.println("fin chk");
  }
*/
