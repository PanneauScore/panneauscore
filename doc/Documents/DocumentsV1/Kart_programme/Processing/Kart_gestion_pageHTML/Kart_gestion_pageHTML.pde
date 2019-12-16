


String lignes_html[];
int nb_tour=0;

void setup() 
{
  size(50, 50);             // Dimension de la fenêtre d'affichage
}

void draw() 
{
  for (int nb_tour=0;nb_tour<10;nb_tour++)
  {
    String lignes_html[] = loadStrings("Page2.html");
    println("Valeur avant changement"+lignes_html[22]);
    lignes_html[22]="<td>"+nb_tour+"</td>";
    println("Valeur après changement"+lignes_html[22]);
    saveStrings("Page2.html", lignes_html);
    delay(3000);
  }
}

