/* Programme permettant de calculer l'humidité dans l'air en
pourcentage. La tension varie en fonction de l'humidité.
*/
int Vsupply = 5; //tension d'alimentation
float N;
float test;

void setup(){
  Serial.begin(9600);
}

void loop(){
N = analogRead(A0); //lire la valeur analogique de la tension sur A0
float Humidite = ((N*5)/(1023.0*0.03))-(1.2716/0.03); //Calcul de l'humidité relative
Serial.println(Humidite); 
delay(250);
}
