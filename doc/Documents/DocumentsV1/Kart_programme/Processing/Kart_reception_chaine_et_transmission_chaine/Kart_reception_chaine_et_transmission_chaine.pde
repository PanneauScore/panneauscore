
/*****************************************************************************************
   Reception d'une chaine_recue de Arduino et envoie d'une chaine_envoyee vers Arduino;
*****************************************************************************************/

import processing.serial.*;  // Librairie pour transmission série

Serial myPort;               // Déclaration du port série "myPort"

String Trame_recue="";
String Trame_envoyee="";
int fin_chaine=10;           // Code décimal du caractère Fin de ligne (LF:Line Feed)
 

void setup() 
{
  myPort = new Serial(this,"COM22", 9600);         // Configuration du port série connecté à l'Arduino
}

void draw() 
{ 
  Trame_recue="";                                  // Initialisation de la trame reçue
  
       if (myPort.available() > 0)                 // Si réception sur le port série
        {
           char Premier_caractere = myPort.readChar();              // Lecture d'un caractère et 
              if ( Premier_caractere == '$')                        // vérification si c'est le début de la trame
               {
                 Trame_recue= myPort.readStringUntil(fin_chaine);   // Lecture de la chaine de caractère reçue
                    if (Trame_recue != null) 
                    {
                       println("chaine reçue: "+Trame_recue);                          
                    }
               }
         }
  Trame_envoyee="$M\n";                       // Création de la chaine de caractère à envoyer à l'Arduino
  myPort.write(Trame_envoyee);                // Envoie de la trame vers l'Arduino à partir du port série
}

    
