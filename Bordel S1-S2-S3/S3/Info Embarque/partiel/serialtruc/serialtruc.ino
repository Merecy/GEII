int i = 0;

#define LedR 5
#define LedG 6
#define LedB 10
#define Led1 A3

String EntreString = "";
bool stringPlein = false;

void couleurRGB(int, int, int);
int StringHextoInt(String);
int HextoInt(String);

void setup() {
  Serial.begin(9600);
  pinMode(LedR, OUTPUT);
  pinMode(LedG, OUTPUT);
  pinMode(LedB, OUTPUT);
  pinMode(Led1, OUTPUT);
  Serial.println("+  pour allumer la lumiere");
  Serial.println("-  pour eteindre la lumiere");
  Serial.println("RGB=rrr,ggg,bbb  pour mettre une valeur specifique sur la led RGB");
  Serial.println("RGBH=rr,gg,bb  pour mettre une valeur specifique sur la led RGB en hex");
  Serial.println("-----------------------------");
  EntreString.reserve(200);
}

void loop() {
  if (stringPlein == true) {
    Serial.println(EntreString);

    if (EntreString == "+") {
      digitalWrite(Led1, HIGH);

      for (i = 0; i < 256; i++) {
        couleurRGB(i, 0, 255 - i);
        delay(50);
        i = i + 5;
      }
    }

    if (EntreString == "-") {
      digitalWrite(Led1, LOW);
      couleurRGB(0, 0, 0);
      delay(20);
    }

    if (EntreString.substring(0, 4) == "RGB=") {
      //Pour eviter que rien ne marche si tu te plante dans les chiffres
      if ((EntreString.substring(7, 8) == ",") and (EntreString.substring(11, 12) == ",")) {
        //RGB=119,200,0
        //Recuperation des morceaux de string
        String Rs = EntreString.substring(4, 7);
        //Serial.println(Rs);
        String Vs = EntreString.substring(8, 11);
        //Serial.println(Vs);
        String Bs = EntreString.substring(12, 15);
        //Serial.println(Bs);

        //changement des morceaux en int pour la fonction
        int Ri = Rs.toInt();
        int Vi = Vs.toInt();
        int Bi = Bs.toInt();
        couleurRGB(Ri, Vi, Bi);
      }

      else {
        Serial.println("Erreur d'ecriture pour le RGB");
      }
    }

    if (EntreString.substring(0, 5) == "RGBH=") {
      //Pour eviter que rien ne marche si tu te plante dans les chiffres
      if ((EntreString.substring(7, 8) == ",") and (EntreString.substring(10, 11) == ",")) {
        //RGBH=FF,05,A2
        //Recuperation des morceaux de string
        String Rs = EntreString.substring(5, 7);
        String Vs = EntreString.substring(8, 10);
        String Bs = EntreString.substring(11, 13);

        //changement des morceaux en int pour la fonction
        int Ri = StringHextoInt(Rs);
        int Vi = StringHextoInt(Vs);
        int Bi = StringHextoInt(Bs);
        couleurRGB(Ri, Vi, Bi);
      }

      else {
        Serial.println("Erreur d'ecriture pour le RGB Hex");
      }
    }

    EntreString = "";
    stringPlein = false;
  }
}


void couleurRGB(int rouge, int vert, int bleu)
{
  analogWrite(LedR, rouge);
  analogWrite(LedG, vert);
  analogWrite(LedB, bleu);
}


void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();

    if (inChar == '\n') {
      stringPlein = true;
    }
    else {
      EntreString += inChar;
    }
  }
}


int StringHextoInt(String val) {
  String V16s = val.substring(0, 1);
  String V1s = val.substring(1, 2);
  V16s = HextoInt(V16s);
  Serial.println(V16s);
  V1s = HextoInt(V1s);

  int nb = 16 * (V16s.toInt()) + (V1s.toInt());
  return nb;
}

int HextoInt(String valseul)
{
  if (valseul.toInt() < 10)
  {
    return valseul.toInt();
  }
  else if (valseul == "A")
  {
    return 10;
  }
  else if (valseul == "B")
  {
    return 11;
  }
  else if (valseul == "C")
  {
    return 12;
  }
  else if (valseul == "D")
  {
    return 13;
  }
  else if (valseul == "E")
  {
    return 14;
  }
  else if (valseul == "F")
  {
    return 15;
  }
  else
  {
    Serial.print("valeur non hexadecimale");
    return 0;
  }

}
