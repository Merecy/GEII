// A la fin du doc de cours
char bintostring(unsigned char s);
int Chksum(String trame);

typedef struct Ais {
  unsigned char IdentifierMessage;
  unsigned char RepeatIndicator;
  unsigned long MMSInumber;
  unsigned char NavigationalStatus;
  unsigned short RateOfTurn;
  unsigned short SpeedOverGround;
  unsigned char PositionAccuracy;
  unsigned long Longitude;
  unsigned long Latitude;
  unsigned short CourseOverGround;
  unsigned short TrueHeading;
  unsigned char UTCreport;
  unsigned char RegionalApplication;
  unsigned char Spare;
  unsigned char RAIMflag;
  unsigned long CommunicationState;
};

Ais trameAis;

unsigned char tab[28] = {0};
int sum;
String trame, cheksum;
void setup() {
  trameAis.IdentifierMessage = 1;
  trameAis.RepeatIndicator = 2;
  trameAis.MMSInumber = 127;
  trameAis.NavigationalStatus = 0;
  trameAis.RateOfTurn = 5;
  trameAis.SpeedOverGround = 612;
  trameAis.PositionAccuracy = 0;
  trameAis.Longitude = 25861317;
  trameAis.Latitude = 3563067;
  trameAis.CourseOverGround = 959;
  trameAis.TrueHeading = 351;
  trameAis.UTCreport = 53;
  trameAis.RegionalApplication = 0;
  trameAis.Spare = 0;
  trameAis.RAIMflag = 0;
  trameAis.CommunicationState = 24132;

  tab[0] = trameAis.IdentifierMessage & 0x3F;
  tab[1] = ((trameAis.RepeatIndicator << 4) | (trameAis.MMSInumber >> 26)) & 0x3F;
  tab[2] = (trameAis.MMSInumber >> 20) & 0x3F;
  tab[3] = (trameAis.MMSInumber >> 14) & 0x3F;
  tab[4] = (trameAis.MMSInumber >> 8) & 0x3F;
  tab[5] = (trameAis.MMSInumber >> 2) & 0x3F;
  tab[6] = ((trameAis.MMSInumber << 4) | (trameAis.NavigationalStatus)) & 0x3F;
  tab[7] = (trameAis.RateOfTurn >> 2) & 0x3F;
  tab[8] = ((trameAis.RateOfTurn << 4) | trameAis.SpeedOverGround >> 6) & 0x3F;
  tab[9] = (trameAis.SpeedOverGround) & 0x3F;
  tab[10] = ((trameAis.PositionAccuracy) | (trameAis.Longitude >> 23)) & 0x3F;
  tab[11] = (trameAis.Longitude >> 17) & 0x3F;
  tab[12] = (trameAis.Longitude >> 11) & 0x3F;
  tab[13] = (trameAis.Longitude >> 5) & 0x3F;
  tab[14] = ((trameAis.Longitude << 1) | (trameAis.Latitude >> 26)) & 0x3F;
  tab[15] = (trameAis.Latitude >> 20) & 0x3F;
  tab[16] = (trameAis.Latitude >> 14) & 0x3F;
  tab[17] = (trameAis.Latitude >> 8) & 0x3F;
  tab[18] = (trameAis.Latitude >> 2) & 0x3F;
  tab[19] = ((trameAis.Latitude << 4) | (trameAis.CourseOverGround >> 8)) & 0x3F;
  tab[20] = (trameAis.CourseOverGround >> 2) & 0x3F;
  tab[21] = ((trameAis.CourseOverGround << 4) | (trameAis.TrueHeading >> 5)) & 0x3F;
  tab[22] = ((trameAis.TrueHeading << 1) | (trameAis.UTCreport >> 5)) & 0x3F;
  tab[23] = ((trameAis.UTCreport << 1) | (trameAis.RegionalApplication >> 3)) & 0x3F;
  tab[24] = ((trameAis.RegionalApplication << 3) | ((trameAis.Spare & 1) << 2) | ((trameAis.RAIMflag & 1) << 1) | ((trameAis.CommunicationState >> 18) & 1)) & 0x3F; //Ya moyen que sa deconne mdr
  tab[25] = (trameAis.CommunicationState >> 12) & 0x3F;
  tab[26] = (trameAis.CommunicationState >> 6) & 0x3F;
  tab[27] = trameAis.CommunicationState  & 0x3F;

  Serial.begin(115200);
  Serial2.begin(4800);
}

void loop() {
  trame = "!AIVDM,1,1,,1,";
  for (int i = 0; i < 28; i++) {
    trame = trame + (String)bintostring(tab[i]);
  }

  trame = trame + ",0*";
  sum = Chksum(trame);
  if (sum < 10) {
    trame = trame + "0";
  }
  cheksum = String(sum, HEX);
  trame = trame + cheksum;

  Serial.println(trame);
  Serial2.println(trame);
  delay(1000);
  trame = "";
}

char bintostring(unsigned char s) {
  char tableau[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?', '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', '\'', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w'};
  return tableau[(long)s];
}

int Chksum(String trame) {
  int sepa1 = trame.indexOf("!", 0);
  int sepa2 = trame.indexOf("*", sepa1 + 1);
  int somme = 0;

  for (int i = 1; i < trame.substring(sepa1 + 1, sepa2).length() + 1; i++) {
    somme = somme ^ trame[i];
    //Serial.print(trame[i]);
  }
  return somme;
}
