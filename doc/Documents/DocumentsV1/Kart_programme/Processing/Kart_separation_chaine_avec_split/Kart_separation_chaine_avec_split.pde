/*********************************************************************************************************
   Séparation des valeurs d'une chaine_recue de Arduino et envoie d'une chaine_envoyee vers Arduino;
*********************************************************************************************************/

String Trame_recue="";
String val_trame[];
int fin_chaine=10;
 
int Val1_vitesse=0;
float Val2_hall=0;
int Val3_oxy=0; 
char Val4_etat_kart=' ';
 
 
void setup() 
{
 
}

void draw() 
{
      Trame_recue="31;42.54;5;M;";                     // Exemple d'une chaine reçue pour traitement
      
                 if (Trame_recue != null) 
                 {
                  println("chaine reçue: "+Trame_recue);
                   
                  val_trame = split(Trame_recue, ';');       // Découpage de la chaine reçue. Les valeurs sont séparer grâce au séparateur ";" et 
                                                             // ranger dans un tableau chaîne de caractères : val_trame[0]=31, val_trame[1]=42, val_trame[2]=5, val_trame[3]=M, ...            
                  
                  println("Valeur après 1er séparateur:"+ val_trame[0]+"   Valeur après 2ieme séparateur:"+ val_trame[1]+"    Valeur après 3ieme séparateur:"+ val_trame[2]+"    Valeur après 4ieme séparateur:"+ val_trame[3]);  // Affichage des chaines de caractères après séparation
                 
                  Val1_vitesse=int(val_trame[0]);          // Si convertion en nombre entier nécessaire pour effectuer un calcul 
                  Val2_hall=float(val_trame[1]);           // Si convertion en nombre décimal nécessaire pour effectuer un calcul  
                  Val3_oxy=int(val_trame[2]);              // Si convertion en nombre entier nécessaire pour effectuer un calcul     
                  Val4_etat_kart=val_trame[3].charAt(0);   // Si convertion en caractère nécessaire pour effectuer un calcul        
                 
                  Val1_vitesse=Val1_vitesse/2;      // Calcul à réaliser sur le nombre entier
                  Val2_hall= Val2_hall+1.1;         // Calcul à réaliser sur le nombre décimal
                  Val3_oxy=Val3_oxy*2;              // Calcul à réaliser sur le nombre entier
                      
                  println("Vitesse instantannée:"+val_trame[0]+" m/s"+"   Vitesse de rotation:"+val_trame[1]+" tr/min"+"   Pulsation cardiaque:"+val_trame[2]+" bat");   // Affichage dans la console des valeurs chaine de caractères
                  println("Vitesse instantannée:"+Val1_vitesse+" m/s"+"   Vitesse de rotation:"+Val2_hall+" tr/min"+"   Pulsation cardiaque:"+Val3_oxy+" bat");          // Affichage dans la console des valeurs après calcul
                  println("");
      
                 }
}
    
