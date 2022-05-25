// A la fin du doc de cours
//https://sebastienguillon.com/test/javascript/convertisseur.html
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

typedef struct CallSign {
  unsigned char Csign[7];
};

typedef struct VesselName {
  unsigned char nam[20];
};

typedef struct Destination {
  unsigned char des[20];
};

typedef struct type5 {
  unsigned char MessageID;
  unsigned char RepeatMessage;
  unsigned long UserID;
  unsigned char AisVersion;
  unsigned long IMO;
  CallSign sign;
  VesselName nom;
  unsigned short TypeOfShip;
  unsigned long Dimension;
  unsigned char ElectronicType;
  unsigned long ETA;
  unsigned short MaximumPresent;
  Destination dest;
  unsigned char DTE;
  unsigned char Spare5;
};

Ais trameAis;
type5 trametype5;

unsigned char tab[28] = {0};
unsigned char tab5[71] = {0};
int sum;
String trame, cheksum;

unsigned long previousMillis = 0;
const long interval = 1000;
unsigned long previousMillis2 = 0;
const long interval2 = 2000;

void setup() {
  trameAis.IdentifierMessage = 1;
  trameAis.RepeatIndicator = 2;
  trameAis.MMSInumber = 228306800;
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

  trametype5.MessageID = 5;
  trametype5.RepeatMessage = 0;
  trametype5.UserID = trameAis.MMSInumber;
  trametype5.AisVersion = 0;
  trametype5.IMO = 0;

  trametype5.sign.Csign[0] = 3; //  000011 110110 000110 001110 110110 100000 100000
  trametype5.sign.Csign[1] = 54;
  trametype5.sign.Csign[2] = 6;
  trametype5.sign.Csign[3] = 14;
  trametype5.sign.Csign[4] = 54;
  trametype5.sign.Csign[5] = 32;
  trametype5.sign.Csign[6] = 32;

  trametype5.nom.nam[0] = 13; //RISING PHOENIX
  trametype5.nom.nam[1] = 9;
  trametype5.nom.nam[2] = 19;
  trametype5.nom.nam[3] = 9;
  trametype5.nom.nam[4] = 14;
  trametype5.nom.nam[5] = 7;
  trametype5.nom.nam[6] = 32;
  trametype5.nom.nam[7] = 16;
  trametype5.nom.nam[8] = 8;
  trametype5.nom.nam[9] = 5;
  trametype5.nom.nam[10] = 15;
  trametype5.nom.nam[11] = 14;
  trametype5.nom.nam[12] = 12;
  trametype5.nom.nam[13] = 24;
  trametype5.nom.nam[14] = 32;
  trametype5.nom.nam[15] = 32;
  trametype5.nom.nam[16] = 32;
  trametype5.nom.nam[17] = 32;
  trametype5.nom.nam[18] = 32;
  trametype5.nom.nam[19] = 32;

  trametype5.TypeOfShip = 59;
  trametype5.Dimension = 1050627900; // 111110100 111110100 111100 111100 longeur:1000metres largeur:120m
  trametype5.ElectronicType = 1;

  trametype5.ETA = 612811; //1001 01011 00111 001011 : le 09/11 a 7h11
  trametype5.MaximumPresent = 255;

  //ON VA CHEZ PAPA NOEL
  trametype5.dest.des[0] = 15;
  trametype5.dest.des[1] = 14;
  trametype5.dest.des[2] = 32;
  trametype5.dest.des[3] = 22;
  trametype5.dest.des[4] = 1;
  trametype5.dest.des[5] = 32;
  trametype5.dest.des[6] = 3;
  trametype5.dest.des[7] = 8;
  trametype5.dest.des[8] = 5;
  trametype5.dest.des[9] = 26;
  trametype5.dest.des[10] = 32;
  trametype5.dest.des[11] = 16;
  trametype5.dest.des[12] = 1;
  trametype5.dest.des[13] = 16;
  trametype5.dest.des[14] = 1;
  trametype5.dest.des[15] = 32;
  trametype5.dest.des[16] = 14;
  trametype5.dest.des[17] = 15;
  trametype5.dest.des[18] = 5;
  trametype5.dest.des[19] = 12;

  trametype5.DTE = 0;
  trametype5.Spare5 = 0;


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



  tab5[0] = trametype5.MessageID & 0x3F;
  tab5[1] = ((trametype5.RepeatMessage << 4) | (trametype5.UserID >> 26)) & 0x3F;;
  tab5[2] = (trametype5.UserID >> 20) & 0x3F;
  tab5[3] = (trametype5.UserID >> 14) & 0x3F;
  tab5[4] = (trametype5.UserID >> 8) & 0x3F;
  tab5[5] = (trametype5.UserID >> 2) & 0x3F;
  tab5[6] = ((trametype5.UserID << 4) | (trametype5.AisVersion << 2) | (trametype5.IMO >> 28)) & 0x3F;
  tab5[7] = (trametype5.IMO >> 22) & 0x3F;
  tab5[8] = (trametype5.IMO >> 16) & 0x3F;
  tab5[9] = (trametype5.IMO >> 10) & 0x3F;
  tab5[10] = (trametype5.IMO >> 4) & 0x3F;
  tab5[11] = ((trametype5.IMO << 2) | (trametype5.sign.Csign[0]) >> 4) & 0x3F; //00 0011
  tab5[12] = ((trametype5.sign.Csign[0] << 2) | (trametype5.sign.Csign[1] >> 4)) & 0x3F; //11 0110
  tab5[13] = ((trametype5.sign.Csign[1] << 2) | (trametype5.sign.Csign[2] >> 4)) & 0x3F; //00 0110
  tab5[14] = ((trametype5.sign.Csign[2] << 2) | (trametype5.sign.Csign[3] >> 4)) & 0x3F; //00 1110
  tab5[15] = ((trametype5.sign.Csign[3] << 2) | (trametype5.sign.Csign[4] >> 4)) & 0x3F; //11 0110
  tab5[16] = ((trametype5.sign.Csign[4] << 2) | (trametype5.sign.Csign[5] >> 4)) & 0x3F; //10 0000
  tab5[17] = ((trametype5.sign.Csign[5] << 2) | (trametype5.sign.Csign[6] >> 4)) & 0x3F; //10 0000
  tab5[18] = ((trametype5.sign.Csign[6] << 2) | (trametype5.nom.nam[0] >> 4)) & 0x3F;// 00 1101
  tab5[19] = ((trametype5.nom.nam[0] << 2) | (trametype5.nom.nam[1] >> 4)) & 0x3F;//00 1001
  tab5[20] = 0;//4 d'avant, 2 mtn
  tab5[21] = 0;
  tab5[22] = 0;
  tab5[23] = 0;
  tab5[24] = 0;
  tab5[25] = 0;
  tab5[26] = 0;
  tab5[27] = 0;
  tab5[28] = 0;
  tab5[29] = 0;
  tab5[30] = 0;
  tab5[31] = 0;
  tab5[32] = 0;
  tab5[33] = 0;
  tab5[34] = 0;
  tab5[35] = 0;
  tab5[36] = 0;
  tab5[37] = 0;
  tab5[38] = 0;
  tab5[39] = 0;
  tab5[40] = 0;
  tab5[41] = 0;
  tab5[42] = 0;
  tab5[43] = 0;
  tab5[44] = 0;
  tab5[45] = 0;
  tab5[46] = 0;
  tab5[47] = 0;
  tab5[48] = 0;
  tab5[49] = 0;
  tab5[50] = 0;
  tab5[51] = 0;
  tab5[52] = 0;
  tab5[53] = 0;
  tab5[54] = 0;
  tab5[55] = 0;
  tab5[56] = 0;
  tab5[57] = 0;
  tab5[58] = 0;
  tab5[59] = 0;
  tab5[60] = 0;
  tab5[61] = 0;
  tab5[62] = 0;
  tab5[63] = 0;
  tab5[64] = 0;
  tab5[65] = 0;
  tab5[66] = 0;
  tab5[67] = 0;
  tab5[68] = 0;
  tab5[69] = 0;
  tab5[70] = 0;

  Serial.begin(115200);
  Serial2.begin(4800);
}

void loop() {
  Serial.println(tab5[19], BIN);
  Serial.println("-----");
  delay(1000);
  //  trame = "!AIVDM,1,1,,1,";
  //  for (int i = 0; i < 28; i++) {
  //    trame = trame + (String)bintostring(tab[i]);
  //  }
  //
  //  trame = trame + ",0*";
  //  sum = Chksum(trame);
  //  if (sum < 10) {
  //    trame = trame + "0";
  //  }
  //  cheksum = String(sum, HEX);
  //  trame = trame + cheksum;
  //
  //  Serial.println(trame);
  //  Serial2.println(trame);
  //  delay(1000);
  //  trame = "";
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
