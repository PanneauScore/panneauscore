/* prog final avec eeprom
 le 8/4 /2015
 inclus la gestion de l'écriture et de la lecture à l'aide de structures

cavalier présent : mode lecture
cavalier absent : mode vol
bouton poussoir  : init le ptr interne a la mise sous tension
led : clignote : acquisition (mode vol)
led : fixe  mémoire pleine (mode vol)
*/

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <Wire.h>

#define tempo 1000    //A calculer 4 heures de vol mini garanti

typedef struct  {
 int pression1;
 int pression2;
 int temp_int;
 int temp_ext;
 int humidite;
 int ir;
  }CapteursStruct;
  CapteursStruct Capteurs;    //declare la structure capteurs  6*16 bits = 96 bits = 12 octets


int mux1 = 8;
int mux2 = 2; //Le numéro dépendra de la carte finale
int mux3 = 7; //idem
int bp_pin = 9;  //actif NL0
int led_pin = 13;
int cavalier_pin = 10;  //actif NL0
int bp_state;
int cavalier_state;

double Rctn;
double Nint, Next;
float Nhumidite, Npression, Npression2, Ninfra;
double T;
int Vsupply = 5;
float Humidite;
float tension;
float pression;
long lux;
char car=0;

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

unsigned long pointeur_Capteurs;
unsigned long ptr_Lecture=0;


void setup() {
  lcd.begin(16, 2);
  Wire.begin();
  Serial.begin(57600);
  pinMode(mux1, OUTPUT);  
  pinMode(mux2, OUTPUT);
  pinMode(mux3, OUTPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(bp_pin, INPUT);
  pinMode(cavalier_pin, INPUT); 
 
 digitalWrite(led_pin, LOW);
 
 cavalier_state=digitalRead(cavalier_pin);
 bp_state=digitalRead(bp_pin);
 
  if (bp_state==0)  //bp appuyé à la mise sous tension init pointeur
                        {    
                        pointeur_Capteurs=0;
                        ecriture_ptr(0,pointeur_Capteurs);
                        Serial.println("clear ptr"); 
                        lcd.print("clear ptr");
                        delay(1000);
                        lcd.clear();
                        }


  pointeur_Capteurs=lecture_ptr(0);             // pointeur_Capteurs=130944;  //essai pour tester la memoire pleine

  
  if (cavalier_state==0)  //cavalier présent mode lecture affichage des données dans le terminal série
                        {
                         Serial.println("barre d'espace pour lire l'eeprom");  
                         lcd.print("space to read");                        
                         while(car!=' ') car=Serial.read();
                         lcd.setCursor(0, 1);
                         lcd.print("reading");   
                          Serial.print("mxp5100 *10");
                          Serial.write(9);
                          Serial.print("mxp2100 *10");
                          Serial.write(9);
                          Serial.print("Temp int *10 ");
                          Serial.write(9);
                          Serial.print("Temp ext *10");
                          Serial.write(9);
                          Serial.print("Humidite");
                          Serial.write(9);
                          Serial.println("ir /10");
                        while (ptr_Lecture<pointeur_Capteurs)
                          {
                          lecture_eeprom_vers_structures(ptr_Lecture);                                              
                          Serial.print(Capteurs.pression1);
                          Serial.write(9);
                          Serial.print(Capteurs.pression2);
                          Serial.write(9);
                          Serial.print(Capteurs.temp_int);
                          Serial.write(9);
                          Serial.print(Capteurs.temp_ext);
                          Serial.write(9);
                          Serial.print(Capteurs.humidite);
                          Serial.write(9);
                          Serial.println(Capteurs.ir);
                          ptr_Lecture=ptr_Lecture+12;
                          digitalWrite(led_pin, digitalRead(led_pin)^1);
                          }
                        lcd.setCursor(0, 1);
                         lcd.print("done   ");   
                         Serial.println("termine");                          
                         while(1) {}  //arret
                        }
                        
}

void loop() {

   if ( pointeur_Capteurs>131000) while(1) {digitalWrite(led_pin, HIGH);}  //arret en cas de mémoire pleine
  
  //TEMPERATURE EXTERIEUR
  digitalWrite(mux1,LOW);  
  digitalWrite(mux2,LOW); // 000 --> 0
  digitalWrite(mux3,LOW);
  Nint = (double) analogRead(A1);
  Rctn= ((1023-Nint)/Nint)*36000; //36000 = valuer resistance R1
  T=log(Rctn/10000); //10000 = R0
  T=(T*298)+4000; // valeur du dessus fois T0 +273(25°C +273) kelvin + Beta
  T=1192000/T; //T0 fois Beta
  T=T-273;
  Capteurs.temp_ext=(int) (T*10);
  lcd.setCursor(0, 0);
  lcd.print("T ext");
  lcd.setCursor(0, 1);
  lcd.print(T);
  delay(tempo);  
  lcd.clear();
  digitalWrite(led_pin, digitalRead(led_pin)^1);
  
  //TEMPERATURE INTERIEUR
  digitalWrite(mux1,HIGH);  
  digitalWrite(mux2,LOW); // 001 --> 1
  digitalWrite(mux3,LOW);
  Next = (double) analogRead(A1);
  Rctn= ((1023-Next)/Next)*36000; //36000 = valuer resistance R1
  T=log(Rctn/10000); //10000 = R0
  T=(T*298)+4000; // valeur du dessus fois T0 +273(25°C +273) kelvin + Beta
  T=1192000/T; //T0 fois Beta
  T=T-273;
  Capteurs.temp_int=(int) (T*10);
  lcd.setCursor(0, 0);
  lcd.print("T int");
  lcd.setCursor(0, 1);
  lcd.print(T);  
  delay(tempo);
  lcd.clear();
  digitalWrite(led_pin, digitalRead(led_pin)^1);
  
  //HUMIDITE
  Nhumidite = analogRead(A3); //lire la valeur analogique de la tension sur A1
  Humidite = ((Nhumidite*5)/(1023.0*0.03))-(1.2716/0.03); //Calcul de l'humidité relative
  lcd.setCursor(0, 0);
  lcd.print("Humidite");
  lcd.setCursor(0, 1);
  lcd.print(Humidite); 
  Capteurs.humidite =(int) Humidite;
  delay(tempo);
  lcd.clear();
  digitalWrite(led_pin, digitalRead(led_pin)^1); 
  
  //PRESSION
  Npression = analogRead(A0);
  tension = (Npression/1023)*5.0;
  pression = (tension+0.526)/0.0045;
  Capteurs.pression1=(int) (pression*10);
  lcd.setCursor(0, 0);
  lcd.print("Pression");
  lcd.setCursor(0, 1);
  lcd.print(pression);  
  delay(tempo);
  lcd.clear();
  digitalWrite(led_pin, digitalRead(led_pin)^1); 
  
  //PRESSION 2
  digitalWrite(mux1,LOW);  
  digitalWrite(mux2,HIGH); // 010 --> 2
  digitalWrite(mux3,LOW);
  Npression = analogRead(A1);
  tension = (Npression/1023)*5.0;
  pression = (285.7143*tension)-142.8571;
  Capteurs.pression2=(int) (pression*10);
  lcd.setCursor(0, 0);
  lcd.print("Pression 2");
  lcd.setCursor(0, 1);
  lcd.print(pression);  
  delay(tempo);
  lcd.clear();
  digitalWrite(led_pin, digitalRead(led_pin)^1); 
  
  //INFRAROUGE
  int Ninfra = analogRead(A2); //N4 = nombre en binaire de 0 a 5v */
  lux = ((2683.27*(long)Ninfra)-2072); //coeff Dir.
  lux = lux*9; // 9 car rapport de 9 entre la valeur de test et la valeur soleil.
  Capteurs.ir= (int) (lux/10);
  lcd.setCursor(0, 0);
  lcd.print("Infrarouge");
  lcd.setCursor(0, 1);
  lcd.print(lux);  
  delay(tempo);
  lcd.clear();
  digitalWrite(led_pin, digitalRead(led_pin)^1);  

  ecriture_structures_vers_eeprom(pointeur_Capteurs);  //ecriture des données en eeprom i2c
  
  pointeur_Capteurs=pointeur_Capteurs+12;  //incrémentation du pointeur de 2*6 octets

  ecriture_ptr(0,pointeur_Capteurs);  //ecriture du pointeur eeprom arduino

  
  
}




//********************************************** Traitement eeprom dans l'atmel
// memorisation du pointeur

void ecriture_ptr(int adresse,unsigned long ptr)
{
byte page=ptr/0x10000;
byte adresse_temp_high=(unsigned int) ptr / 256;
byte adresse_temp_low=(unsigned int) ptr & 0xFF;

EEPROM.write(0+adresse, page);
delay(10);  
EEPROM.write(1+adresse, adresse_temp_low);
delay(10);  
EEPROM.write(2+adresse, adresse_temp_high);
delay(10);  
/*Serial.println (page);
Serial.println (adresse_temp_high);
Serial.println (adresse_temp_low); */
Serial.print("Adresse ecrite: ");
Serial.println (ptr);
}

// lecture du pointeur
unsigned long lecture_ptr(int adresse)
{
unsigned long ptr;
ptr=0;
long page=EEPROM.read(0+adresse);
long adresse_temp_low=EEPROM.read(1+adresse);
long adresse_temp_high=EEPROM.read(2+adresse);

Serial.println (page);
Serial.println (adresse_temp_high);
Serial.println (adresse_temp_low);

ptr=page*0x10000+adresse_temp_high*256 + adresse_temp_low;
Serial.print("*****************adresse lue: ");
Serial.println (ptr);
return ptr;
}


//************************************************** Traitement eeprom 24fc1025

 // Ecriture d'un octet dans l'eeprom 
  void i2c_eeprom_write(unsigned long eeaddress, byte valeur)
  {
    if ((eeaddress & 0x10000)==0x10000) Wire.beginTransmission(0x54); else Wire.beginTransmission(0x50);
    eeaddress&=0xffff;
    Wire.write((byte)(eeaddress >> 8)); 
    Wire.write((byte)(eeaddress)); 
    Wire.write(valeur);
    Wire.endTransmission();
    delay(5);
  }
  
// Lecture d'un octet dans l'eeprom en mémoire haute
byte i2c_eeprom_read(unsigned long eeaddress)
{
    byte valeur;
    byte page;
    if ((eeaddress & 0x10000)==0x10000) page=1; else page=0;
    if (page==1) Wire.beginTransmission(0x54); else Wire.beginTransmission(0x50);
    eeaddress&=0xffff;
    Wire.write((byte)(eeaddress >> 8)); 
    Wire.write((byte)(eeaddress)); 
    Wire.endTransmission();
    if (page==1) Wire.requestFrom(0x54,1); else  Wire.requestFrom(0x50,1);
    if (Wire.available()) {
                           valeur = Wire.read();
                           }
    return valeur;
  }
  


void lecture_eeprom_vers_structures(unsigned long adresse_capteurs)
{
int i;

  for(i = 0; i < 12; i++){
   *((char*)&Capteurs + i) = i2c_eeprom_read(i+adresse_capteurs);
  }
}


void ecriture_structures_vers_eeprom(unsigned long adresse_capteurs)
{
 int i; 
 for(i = 0; i < 12; i++){
   i2c_eeprom_write(i+adresse_capteurs, *((char*)&Capteurs + i));
 }
}




