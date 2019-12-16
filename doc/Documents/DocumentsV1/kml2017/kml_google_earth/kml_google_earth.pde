// Affichage d'un tracé KML

//13mai


/*
public double longitude = 0.6704; //Sets the starting longitude
public double latitude = 47.9007; //Sets the starting latitude
public double altitude = 1000; //Sets the starting altitude
*/

double coord[][]={
                     {0.6704,47.9007,1000},
                     {0.6804,47.8007,2000},
                     {0.6904,47.3007,3000},
                     {0.7004,47.8007,4000},
                     {0.8004,47.9007,5000},
                     {0.9004,47.9007,6000},
                     {0.9104,47.7007,5000},
                     {0.9204,47.8007,4000},
                     {0.9304,47.9007,3000},
                     {0.9404,47.9007,2000}
                   
                 };



               
 
PrintWriter output;


void setup()
{
  size(500,90); //Sets the size of the screen
  frameRate(1); //Sets the frame rate to one per second
   
 output = createWriter("data\\google_earth.kml");

 output.print(entete_KML());

}
 
void draw(){
  background(0); //Background color
 

        
}

void dispose()
{     
  println("Fermeture du programme");
 output.print(fin_KML());
 output.flush(); // Writes the remaining data to the file
 output.close(); // Finishes the file
 
}


String entete_KML()// pour effectuer une trajectoire
{
    String kml = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
+ "<kml xmlns=\"http://www.opengis.net/kml/2.2\" xmlns:gx=\"http://www.google.com/kml/ext/2.2\" xmlns:kml=\"http://www.opengis.net/kml/2.2\" xmlns:atom=\"http://www.w3.org/2005/Atom\">"
+ "<Document>"
+ "<name>nacelle.kmz</name>"
+  "<Style id=\"sh_ylw-pushpin\">"
+    "<IconStyle>"
+      "<scale>1.3</scale>"
+      "<Icon>"
+ "<href>http://maps.google.com/mapfiles/kml/pushpin/ylw-pushpin.png</href>"
+ "      </Icon>"
+ "      <hotSpot x=\"20\" y=\"2\" xunits=\"pixels\" yunits=\"pixels\"/>"
+ "    </IconStyle>"
+ "    <LineStyle>"
+ "      <color>ff0000ff</color>"      //couleur du trait
+ "      <width>2</width>"             //epaisseur du trait
+ "    </LineStyle>"
+ "  </Style>"
+ "  <StyleMap id=\"msn_ylw-pushpin\">"
+ "    <Pair>"
+ "      <key>normal</key>"
+ "      <styleUrl>#sn_ylw-pushpin</styleUrl>"
+ "    </Pair>"
+ "    <Pair>"
+ "      <key>highlight</key>"
+ "      <styleUrl>#sh_ylw-pushpin</styleUrl>"
+ "    </Pair>"
+ "  </StyleMap>"
+ "  <Style id=\"sn_ylw-pushpin\">"
+ "    <IconStyle>"
+ "      <scale>1.1</scale>"
+ "      <Icon>"
+ "        <href>http://maps.google.com/mapfiles/kml/pushpin/ylw-pushpin.png</href>"
+ "      </Icon>"
+ "      <hotSpot x=\"20\" y=\"2\" xunits=\"pixels\" yunits=\"pixels\"/>"
+ "    </IconStyle>"
+ "    <LineStyle>"
+ "      <color>ff0000ff</color>"
+ "      <width>2</width>"
+ "    </LineStyle>"
+ "  </Style>"
+ "  <Placemark>"
+ "    <name>nacelle</name>"
+ "    <styleUrl>#msn_ylw-pushpin</styleUrl>"
+ "    <LineString>"
+ "      <tessellate>1</tessellate>"
+ "      <altitudeMode>relativeToGround</altitudeMode>"
+ "      <coordinates>";
return kml;
}


String fin_KML()//fin de trajectoire
{
  String kml = "</coordinates>"
+ "</LineString>"
+ "</Placemark>"
+ "</Document>"
+ "</kml>";
  return kml;
}




void keyPressed() {
  //If the LEFT key is pressed the latitude will increase by 1 Degree
/*
  if(key == CODED){
    if(keyCode == LEFT){
      latitude += 0.01;
      //If the RIGHT key is pressed the latitude will decrease by 1 Degree
    }
    else if(keyCode == RIGHT){
      latitude -= 0.01;
      //If the UP key is pressed the longitude will decrease by 1 Degree
    }
    else if(keyCode == UP){
      longitude -= 0.01;
      //If the DOWN key is pressed the longitude will increase by 1 Degree
    }
    else if(keyCode == DOWN){
      longitude += 0.01;
    }
  }
  println(keyCode);
 */


for(int  n =0;n<10;n++){ 
 output.print(coord[n][0]);
 output.print(",");
 output.print(coord[n][1]);
 output.print(",");
 output.print(coord[n][2]);
 output.print(" ");
}  
 println("coordonées transferées");
}


