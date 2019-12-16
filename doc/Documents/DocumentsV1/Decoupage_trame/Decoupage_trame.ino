/********************************************************************
Ce programme permet de séparer les valeurs d'une chaine de caractère
séparées par le séparateur ','              le 05/05/2016
*********************************************************************/

String Trame_recue = "1,123,4.56,45,52,6.8,Mjk,";         //Exemple de la trame à séparer contenant 7 chaines de caractères séparées par le caractère ','
int nb_separateur=0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
   nb_separateur=0;
  for (int i = 0; i < Trame_recue.length(); i++)        
   {
     if (Trame_recue.charAt(i) == ',')                      //Compte le nombre de séparateur ',' contenu dans la chaine
      {                                                     
        nb_separateur++;                                    
      }
   }
   Serial.print("Nombre de separateur ',': ");
   Serial.println(nb_separateur);                           //Affiche le nombre de séparateur de la trame
   int Position_separateur[nb_separateur];                  //Déclaration d'un tableau contenant la position des séparateurs
   String Valeur_chaine[nb_separateur];                     //Déclaration d'un tableau "Chaine de caractères" contenant les chaines de la trame
   Position_separateur[0]=Trame_recue.indexOf(',');         //Détermine la position du premier séparateur dans la trame et la range dans le tableau "position séparateur"
  // Serial.print("Position 0 du separateur: ");
  // Serial.println(Position_separateur[0]);
   Valeur_chaine[0]=Trame_recue.substring(0,Position_separateur[0]);              //Détermine la 1ère chaine dans la trame et la range dans le tableau "Valeur chaine"
   Serial.print("Valeur 0 de la chaine: ");
   Serial.println(Valeur_chaine[0]);                                              //Affichage après découpage de la 1ère chaine contenue dans le tableau "Valeur chaine"
   for(int i=1; i<nb_separateur; i++)                                            
   {     
      Position_separateur[i]=Trame_recue.indexOf(',', Position_separateur[i-1] + 1 );       //Détermine la position des autres séparateurs dans la trame et les range dans le tableau "position séparateur"
     // Serial.print("Position "); 
     // Serial.print(i);
     // Serial.print(" du separateur: ");
    //  Serial.println(Position_separateur[i]);    
      Valeur_chaine[i]=Trame_recue.substring(Position_separateur[i-1]+1,Position_separateur[i]);   //Détermine les autres chaines dans la trame et les range dans le tableau "Valeur chaine"
      Serial.print("Valeur ");
      Serial.print(i);
      Serial.print(" de la chaine: ");  
      Serial.println(Valeur_chaine[i]);                                                           //Affichage après découpage des chaines contenues dans le tableau "Valeur chaine"
   }   
      delay(200); 
      Serial.println();
}

