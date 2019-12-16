#include <LiquidCrystal.h>

LiquidCrystal lcd (12, 11, 6, 5, 4, 3);  // initialize the library with the numbers of the interface pins

/************Sous-programme d'initialisation*******************/
void setup()
{ 
   Serial.begin(4800);   // initialize serial communication at 4800 for the GPS
   lcd.begin(16, 2);     // Initialise le nombre de lignes et de colonnes 
   lcd.clear();          // Efface l'afficheur et positionne le curseur en (0,0)
} 

/*************/
void loop() 
{ 
  String trameGPS_recue;
  const int lf=10;
  int virgule[12];
  char sync;
  
    if (Serial.available()>0)          // Vérifie qu'une communication série est présente
      {
        sync=Serial.read();            // Place chaque caractère reçu un à un dans la variable sync
        if (sync=='$')                 // Vérifie que la variable sync correspond au caractère $: synchronisation au début d'une trame
        {
           trameGPS_recue = Serial.readStringUntil(lf);      // lit la trame complète et la stocke dans la chaîne trameGPS_recue
       //  trameGPS_recue = "$GPGGA,152241.000,4759.7067,N,00012.2782,E,0,4,5.2,100.0,M,12.3,M,,*6A" ;  // Test avec une trame contenant FIX=0               
           if (trameGPS_recue.substring(0,5) == "GPGGA")     // Vérifie si la trame complète commence par GPGGA : Synchronisation de la trame $GPGGA
             { 
     








             }
        }
      }
   }


 




