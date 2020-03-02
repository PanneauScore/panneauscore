#define LF 10

char carDeb;

String chaineScore;
String scoreLc;
String scoreVst;


void setup() {

  Serial.begin(9600);

}

void loop() {

  if (Serial.available() > 0) {
    carDeb = Serial.read();

    if (carDeb == '$') {
      chaineScore = Serial.readStringUntil(LF);
      scoreLc = chaineScore.substring(0, 3);
      scoreVst = chaineScore.substring(4, 7);

      Serial.print("scoreLc = ");
      Serial.println(scoreLc);

      Serial.print("scoreVst = ");
      Serial.println(scoreVst);
    }
  }
}
