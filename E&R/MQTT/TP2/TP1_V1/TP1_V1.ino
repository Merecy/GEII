struct gpsData {
  String type ; // sans le $
  String time ; // format HH:MM:SS
  float timeMs ; // millisecondes supplémentaires de time
  double lat ;// >0 N <0 S en degrés décimaux
  String NS ;
  double lon ; // >0 E <0 W en degrés décimaux
  String EO;
  bool posGps ; // vrai si positionnement GPS faux sinon
  int satNum ; // nombre de satellites utilisés?
  float hdop ; // précision horizontale en mètres
  float altitude ; // en mètre
  int checksum ; // en binaire
  bool checksumOk ; // vrai si cheksum correcte
};

//String trame2 = "$GPGLL,5300.97914,N,00259.98174,E,125926,A*28";
String trame1 = "$GPGGA,064036.289,4836.5375,N,00740.9373,E,1,04,3.2,200.2,M,,,,,,0000,*22";

struct gpsData data1 ;

void fillData( String trame, struct gpsData& data ) ;
void printData( struct gpsData data);
bool verifyChksum(String trame, int allezsamarche);


void setup() {
  Serial.begin(9600);
  Serial.print("\n\n\n\n");
  fillData(trame1, data1);
  Serial.println("Trame reçue : " + trame1 ) ;
  printData(trame1, data1);
}

void fillData(String trame, struct gpsData& data) {
  int sepa1 = trame.indexOf(",", 0);
  data.type = trame.substring(1, sepa1);
  //Serial.println(data.type);

  data.time = trame.substring(sepa1 + 1, sepa1 + 3) + ":" + trame.substring(sepa1 + 3, sepa1 + 5) + ":" + trame.substring(sepa1 + 5, sepa1 + 7);
  //Serial.println(data.time);

  int sepa2 = trame.indexOf(".", sepa1 + 1);
  sepa1 = trame.indexOf(",", sepa2 + 1);
  data.timeMs = ("0" + trame.substring(sepa2, sepa1)).toFloat();
  //Serial.println(data.timeMs);

  sepa2 = trame.indexOf(",", sepa1 + 1);
  data.lat = ((trame.substring(sepa1 + 1, sepa1 + 3) + String((trame.substring(sepa1 + 3, sepa2).toFloat()) / (float)6, 5)).toDouble()) / (double)10;
  //Serial.println(data.lat,6);

  sepa1 = trame.indexOf(",", sepa2 + 1);
  if (trame.substring(sepa2 + 1, sepa1) == "N")
    data.NS = "NORD";
  else
    data.NS = "SUD";
  //Serial.println(data.NS);

  sepa2 = trame.indexOf(",", sepa1 + 1);
  data.lon = ((trame.substring(sepa1 + 1, sepa1 + 3) + String((trame.substring(sepa1 + 3, sepa2).toFloat()) / (float)6, 5)).toDouble()) / (double)10;
  //Serial.println(data.lat,6);

  sepa1 = trame.indexOf(",", sepa2 + 1);
  if (trame.substring(sepa2 + 1, sepa1) == "E")
    data.EO = "EST";
  else
    data.EO = "OUEST";
  //Serial.println(data.EO);

  sepa2 = trame.indexOf(",", sepa1 + 1);
  if (trame.substring(sepa1 + 1, sepa2) == "1") {
    data.posGps = 1;
  }
  else {
    data.posGps = 0;
  }
  //Serial.println(data.posGps);

  sepa1 = trame.indexOf(",", sepa2 + 1);
  data.satNum = trame.substring(sepa2 + 1, sepa1).toInt();

  sepa2 = trame.indexOf(",", sepa1 + 1);
  data.hdop = trame.substring(sepa1 + 1, sepa2).toFloat();

  sepa1 = trame.indexOf(",", sepa2 + 1);
  data.altitude = trame.substring(sepa2 + 1, sepa1).toFloat();

  sepa2 = trame.indexOf("*", sepa1 + 1);
  data.checksum = HexToInt(trame.substring(sepa2 + 1, sepa2 + 2)) * 16 + HexToInt(trame.substring(sepa2 + 2, sepa2 + 3));

}
int HexToInt(String truc) {
  int resultat;
  if (truc.toInt() >= 0 & truc.toInt() <= 9) {
    resultat = truc.toInt();
    return resultat;
  }
  if (truc == "A") {
    resultat = 10;
    return resultat;
  }
  if (truc == "B") {
    resultat = 11;
    return resultat;
  }
  if (truc == "C") {
    resultat = 12;
    return resultat;
  }
  if (truc == "D") {
    resultat = 13;
    return resultat;
  }
  if (truc == "E") {
    resultat = 14;
    return resultat;
  }
  if (truc == "F") {
    resultat = 15;
    return resultat;
  }
}

void printData(String trame, struct gpsData data) {
  Serial.println("type : " + data.type);
  Serial.println("time : " + data.time);
  Serial.println("timeMs : " + String(data.timeMs, 3));
  Serial.print("lat : " + String(data.lat, 6));
  Serial.println("° " + data.NS);
  Serial.print("lon : " + String(data.lon, 6));
  Serial.println("° " + data.EO);
  Serial.println("gps mode : " + String(data.posGps));
  Serial.println("sat number : " + String(data.satNum));
  Serial.println("horiz. dilution : " + String(data.hdop));
  Serial.println("Altitude : " + String(data.altitude, 1) + " a partir de la mer");
  Serial.println("checksum : " + String(data.checksum));
  Serial.print("checksum ok : ");
  Serial.println(verifyChksum(trame, data.checksum));
}

bool verifyChksum(String trame, int check) {
  int sepa1 = trame.indexOf("$", 0);
  int sepa2 = trame.indexOf("*", sepa1 + 1);
  int somme = 0;

  for (int i = 1; i < trame.substring(sepa1 + 1, sepa2).length() + 1; i++) {
    somme = somme ^ trame[i];
    //Serial.print(trame[i]);
  }
  Serial.print(check);
  Serial.print(" = ");
  Serial.print(somme);
  Serial.print(" ? -->");

  if (somme == check)
    return 1;
  else
    return 0;
}

void loop() {
}
