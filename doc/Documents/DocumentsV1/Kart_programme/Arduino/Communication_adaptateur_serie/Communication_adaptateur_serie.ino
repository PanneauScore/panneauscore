/***********************************************************************************************
   Reception d'une chaine_recue de Processing et envoie d'une chaine_envoyee vers Processing;
************************************************************************************************/

#include <SoftwareSerial.h>             // Librairie nécessaire si création d'un port série logiciel (port série supplémentaire)

SoftwareSerial mySerial(2,3);           // Déclaration des broches du port série logiciel si nécessaire (broche2:RX, broche3:TX) 

int val1=0;
float val2=0;
int val3=0;
char val4=' ';

String Trame_envoyee="";
String Trame_recue="";
const int fin_chaine=10;                  // Code décimal du caractère Fin de ligne (LF:Line Feed)

int Led=13;

void setup()  
{
   Serial.begin(9600);         // Initialisation du port série matérielle (Port série existant) à la vitesse 9600 bits/s
   mySerial.begin(9600);       // Si nécessaire, initialisation du port série logiciel à la vitesse 9600 bits/s
   pinMode(Led,OUTPUT);
   digitalWrite(Led,LOW);
}

void loop() // run over and over
{
  Trame_envoyee="";
     //if (mySerial.available()>0)                       // Si nécessaire, vérification d'une réception sur le port série logiciel
     if (Serial.available()>0)                           // Vérification d'une réception sur le port série matériel
      {
        char premier_caractere = Serial.read();         // Lecture d'un caractère et 
        if (premier_caractere=='$')                     // vérification si c'est le début de la trame
         {
            Trame_recue=Serial.readStringUntil(fin_chaine);     // Lecture de la chaine de caractère reçue
            if (Trame_recue =="M")
              {
                digitalWrite(Led,HIGH);
              }
             else 
               {
                 digitalWrite(Led,LOW); 
               }
         }
      }
  val1=10;
  val2=val1+13.52;
  val3=val2+2;
  val4='M';
  
  Trame_envoyee="$"+(String)val1+";"+(String)val2+";"+(String)val3+";"+(String)val4+";\n";       // Création de la chaine de caractère à envoyer à Processing
  
  Serial.print("Trame_envoyee:");
  Serial.println(Trame_envoyee);                                                                  // Envoie de la trame vers l'Arduino à partir du port série matériel
  // mySerial.println(Trame_envoyee);                                                             // Si nécessaire, envoie de la trame vers l'Arduino à partir du port série matériel
  delay(1000);
  
}
