/*********************************************************************************************************
   Affichage des valeurs obtenues après séparation dune chaine_recue de Arduino
*********************************************************************************************************/

import controlP5.*;         // Librairie pour utiliser controlP5

String Trame_recue="";
String val_trame[];
int fin_chaine=10;
 
int Val1_vitesse=0;
float Val2_hall=0;
int Val3_oxy=0; 
char Val4_etat_kart=' ';

int R1=255;
int V1=255;
int B1=255;

ControlP5 cp5;                          // Déclaration de l'objet "cp5"
Textarea Valim_affichage;               // Déclaration de l'objet "Valim_affichage" pour affichage dans une boîte 
Textarea Valim_calcul_affichage;        // Déclaration de l'objet "Valim_calcul_affichage" pour affichage dans une boîte 
Textlabel led1;                         // Déclaration de l'objet "led1" pour afficher un label (texte) 


void setup() 
{
  size(800,500);                        // Dimension de la fenêtre d'affichage
  cp5 = new ControlP5(this);            // Initialisation de l'objet "cp5"
  
    
  Valim_affichage = cp5.addTextarea("Valim")                   // Initialisation des paramètres de la boîte de l'objet "Valim_affichage" 
                       .setPosition(190,100)
                       .setSize(110,30)
                       .setFont(createFont("arial",22))
                       .setLineHeight(14)
                       .setColor(color(255,0,0))
                       .setColorBackground(color(0,45,90))
                       ;
     
   Valim_calcul_affichage = cp5.addTextarea("Valim_modif")       // Initialisation des paramètres de la boîte de l'objet "Valim_calcul_affichage"
                       .setPosition(190,200)                       
                       .setSize(110,30)
                       .setFont(createFont("arial",22))
                       .setLineHeight(14)
                       .setColor(color(255,0,0))
                       .setColorBackground(color(0,45,90))
                       ; 
 
   led1 = cp5.addTextlabel("led1")                               // Initialisation des paramètres du label de l'objet "led1" 
           .setFont(createFont("arial",25))
           ;                      
                       
       cp5.addTextlabel("Valim_label")                            // Initialisation des paramètres du label de l'objet "Valim_label"
           .setText("Valeur de l'alimentation")
           .setPosition(170,135)
           .setColor(color(128,128,0))
           .setFont(createFont("arial",20))
           ;    
           
       cp5.addTextlabel("Valim_modif_label")                      // Initialisation des paramètres du label de l'objet "Valim_modif_label"
           .setText("Valeur modif de l'alimentation")
           .setPosition(170,235)
           .setColor(color(0,128,128))
           .setFont(createFont("arial",20))
           ;       
           
       cp5.addTextlabel("Titre")                                    // Initialisation des paramètres du label de l'objet "Titre"
           .setPosition(155,10)
           .setFont(createFont("arial",36))
           .setColor(color(255,255,255))
           .setText("Affichage d'un titre")
           ;
           
       PImage[] image = {loadImage("Arret_urgence.png"),loadImage("Arret_urgence_actif.png"),loadImage("Arret_urgence.png")};       // Initialisation des paramètres d'une image
 
       cp5.addButton("Arret_Urgence")          // Initialisation des paramètres du bouton de l'objet "Arret_Urgence"
          .setPosition(500,130)
          .setImages(image)
          .updateSize()
          ;
                   
}

void draw() 
{
   
  fill(R1,V1,B1);                              // Commande de remplissage selon la couleur R, V, B
  ellipse(250,300,50,50);                      // Réalisation d'un cercle
  
  
  Trame_recue="";          
 
              Trame_recue="31;142.54;5;M;";                   // Exemple d'une trame reçue
                 if (Trame_recue != null) 
                 {
                  println("chaine reçue: "+Trame_recue);
                   
                  val_trame = split(Trame_recue, ';');       // Découpage de la chaine reçue. Les valeurs sont séparer grâce au séparateur ";" et 
                                                             // ranger dans un tableau chaîne de caractères : val_trame[0]=31, val_trame[1]=42.54, val_trame[2]=5, ...            
                  
                  println("Valeur après 1er séparateur:"+ val_trame[0]+"   Valeur après 2ieme séparateur:"+ val_trame[1]+"    Valeur après 3ieme séparateur:"+ val_trame[2]+"    Valeur après 4ieme séparateur:"+ val_trame[3]);  // Affichage des chaines de caractères après séparation
                 
                  Val1_vitesse=int(val_trame[0]);          // Si convertion en nombre entier nécessaire pour effectuer un calcul 
                  Val2_hall=float(val_trame[1]);           // Si convertion en nombre décimal nécessaire pour effectuer un calcul  
                  Val3_oxy=int(val_trame[2]);              // Si convertion en nombre entier nécessaire pour effectuer un calcul     
                  Val4_etat_kart=val_trame[3].charAt(0);   // Si convertion en caractère nécessaire pour effectuer un calcul
                  
                     
                  Val1_vitesse=Val1_vitesse/2;                    // Calcul à réaliser sur le nombre entier
                  Val2_hall= Val2_hall+1.1;                      // Calcul à réaliser sur le nombre décimal
                  Val3_oxy=Val3_oxy*2;                           // Calcul à réaliser sur le nombre entier
                      
                  println("Vitesse instantannée:"+val_trame[0]+" m/s"+"   Vitesse de rotation:"+val_trame[1]+" tr/min"+"   Pulsation cardiaque:"+val_trame[2]+" bat");   // Affichage dans la console des valeurs chaine de caractères
                  println("Vitesse instantannée:"+Val1_vitesse+" m/s"+"   Vitesse de rotation:"+Val2_hall+" tr/min"+"   Pulsation cardiaque:"+Val3_oxy+" bat");          // Affichage dans la console des valeurs après calcul
                  println("");
     
                  Valim_affichage.setText(val_trame[0] + " V");              // Affichage  de la valeur dans la boite " Valim_affichage". La valeur doit être une chaîne de caractère
     
                  String Valim_string = str(Val2_hall);                      // Convertion en chaîne de caractère avant affichage
                  Valim_calcul_affichage.setText((Valim_string) + " V");     // Affichage  de la valeur dans la boite " Valim_calcul_affichage". La valeur doit être une chaîne de caractère
         
                 }
    
   switch(Val4_etat_kart)               // Test de la variable représentant le kart
        {
          case 'M': 
            R1 = 0;                                        // Choix de la couleur du cercle
            V1 = 255;
            B1 = 0; 
            led1.setText("Kart en fonctionnement");         // Affichage de l'état du kart avec le label led1
            led1.setColor(color(255,255,255));
            led1.setPosition(130,330);
            break;
            
          case 'A': 
            R1 = 255;                                     // Choix de la couleur du cercle
            V1 = 0;
            B1 = 0;
            led1.setText("Kart stoppé");                  // Affichage de l'état du kart avec le label led1
            led1.setColor(color(245,52,52));
            led1.setPosition(180,330);
            break;
        } 
  
}

public void Arret_Urgence()                                // Appel de la fonction "Arrêt d'urgence" lors de l'appui sur le bouton
{ 
  println("Arrêt d'urgence actionné");                     // Affichage d'un message dans la console      
  delay(2000);
}
    
