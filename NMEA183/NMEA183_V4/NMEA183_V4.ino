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
int sum, sum5, sum52;
String trame, trame5,trame52, cheksum, cheksum5, cheksum52;

unsigned long previousMillis = 0;
const long interval = 1000;
unsigned long previousMillis2 = 0;
const long interval2 = 2000;

void setup() {
  trameAis.IdentifierMessage = 1;
  trameAis.RepeatIndicator = 2;
  trameAis.MMSInumber = 228306800;
  trameAis.NavigationalStatus = 2;
  trameAis.RateOfTurn = 5;
  trameAis.SpeedOverGround = 1021;
  trameAis.PositionAccuracy = 0;
  trameAis.Longitude = 3563067;
  trameAis.Latitude = 25861317;
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

  trametype5.nom.nam[0] = 18; //RISING PHOENIX
  trametype5.nom.nam[1] = 9; //001101 001001 010011 001001 001110 000111 100000 010000 001000 000101 001111 001110 001100 011000 100000 100000 100000 100000 100000 100000
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
  trametype5.nom.nam[12] = 9;
  trametype5.nom.nam[13] = 24;
  trametype5.nom.nam[14] = 32;
  trametype5.nom.nam[15] = 32;
  trametype5.nom.nam[16] = 32;
  trametype5.nom.nam[17] = 32;
  trametype5.nom.nam[18] = 32;
  trametype5.nom.nam[19] = 32;

  trametype5.TypeOfShip = 30;
  trametype5.Dimension = 1050627900; // 111110100 111110100 111100 111100 longeur:1000metres largeur:120m
  trametype5.ElectronicType = 1;

  trametype5.ETA = 612811; //10011001100111001011 : le 09/11 a 7h11
  trametype5.MaximumPresent = 255;

  //ON VA CHEZ PAPA NOEL
  trametype5.dest.des[0] = 15; //001111 001110 100000 010110 000001 100000 000011 001000 000101 011010 100000 010000 000001 010000 000001 100000 001110 001111 000101 001100
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
  tab5[20] = ((trametype5.nom.nam[1] << 2) | (trametype5.nom.nam[2] >> 4)) & 0x3F;//01 0011
  tab5[21] = ((trametype5.nom.nam[2] << 2) | (trametype5.nom.nam[3] >> 4)) & 0x3F;//00 1001
  tab5[22] = ((trametype5.nom.nam[3] << 2) | (trametype5.nom.nam[4] >> 4)) & 0x3F;//00 1110
  tab5[23] = ((trametype5.nom.nam[4] << 2) | (trametype5.nom.nam[5] >> 4)) & 0x3F;//00 0111
  tab5[24] = ((trametype5.nom.nam[5] << 2) | (trametype5.nom.nam[6] >> 4)) & 0x3F;//10 0000
  tab5[25] = ((trametype5.nom.nam[6] << 2) | (trametype5.nom.nam[7] >> 4)) & 0x3F;//01 0000
  tab5[26] = ((trametype5.nom.nam[7] << 2) | (trametype5.nom.nam[8] >> 4)) & 0x3F;//00 1000
  tab5[27] = ((trametype5.nom.nam[8] << 2) | (trametype5.nom.nam[9] >> 4)) & 0x3F;//00 0101
  tab5[28] = ((trametype5.nom.nam[9] << 2) | (trametype5.nom.nam[10] >> 4)) & 0x3F;//00 1111
  tab5[29] = ((trametype5.nom.nam[10] << 2) | (trametype5.nom.nam[11] >> 4)) & 0x3F;//00 1110
  tab5[30] = ((trametype5.nom.nam[11] << 2) | (trametype5.nom.nam[12] >> 4)) & 0x3F;//00 1100
  tab5[31] = ((trametype5.nom.nam[12] << 2) | (trametype5.nom.nam[13] >> 4)) & 0x3F;//01 1000
  tab5[32] = ((trametype5.nom.nam[13] << 2) | (trametype5.nom.nam[14] >> 4)) & 0x3F;//10 0000
  tab5[33] = ((trametype5.nom.nam[14] << 2) | (trametype5.nom.nam[15] >> 4)) & 0x3F;//10 0000
  tab5[34] = ((trametype5.nom.nam[15] << 2) | (trametype5.nom.nam[16] >> 4)) & 0x3F;//10 0000
  tab5[35] = ((trametype5.nom.nam[16] << 2) | (trametype5.nom.nam[17] >> 4)) & 0x3F;//10 0000
  tab5[36] = ((trametype5.nom.nam[17] << 2) | (trametype5.nom.nam[18] >> 4)) & 0x3F;//10 0000
  tab5[37] = ((trametype5.nom.nam[18] << 2) | (trametype5.nom.nam[19] >> 4)) & 0x3F;//10 0000
  tab5[38] = ((trametype5.nom.nam[19] << 2) | (trametype5.TypeOfShip >> 6)) & 0x3F;//00
  tab5[39] = (trametype5.TypeOfShip)  & 0x3F;//111011
  tab5[40] = (trametype5.Dimension >> 24) & 0x3F; //111110
  tab5[41] = (trametype5.Dimension >> 18) & 0x3F; //100111
  tab5[42] = (trametype5.Dimension >> 12) & 0x3F; //110100
  tab5[43] = (trametype5.Dimension >> 6) & 0x3F; //111100
  tab5[44] = (trametype5.Dimension) & 0x3F; //111100
  tab5[45] = ((trametype5.ElectronicType << 2) | (trametype5.ETA >> 18)) & 0x3F;//0001 //10
  tab5[46] = (trametype5.ETA >> 12) & 0x3F;//010101
  tab5[47] = (trametype5.ETA >> 6) & 0x3F;//100111
  tab5[48] = (trametype5.ETA) & 0x3F;//001011
  tab5[49] = (trametype5.MaximumPresent >> 2) & 0x3F; //111111 11
  tab5[50] = ((trametype5.MaximumPresent << 4) | (trametype5.dest.des[0] >> 2)) & 0x3F; //11 0011 //11
  tab5[51] = ((trametype5.dest.des[0] << 4) | (trametype5.dest.des[1] >> 2)) & 0x3F; //0011 10
  tab5[52] = ((trametype5.dest.des[1] << 4) | (trametype5.dest.des[2] >> 2)) & 0x3F; //1000 00
  tab5[53] = ((trametype5.dest.des[2] << 4) | (trametype5.dest.des[3] >> 2)) & 0x3F; //0101 10
  tab5[54] = ((trametype5.dest.des[3] << 4) | (trametype5.dest.des[4] >> 2)) & 0x3F; //0000 01
  tab5[55] = ((trametype5.dest.des[4] << 4) | (trametype5.dest.des[5] >> 2)) & 0x3F; //1000 00
  tab5[56] = ((trametype5.dest.des[5] << 4) | (trametype5.dest.des[6] >> 2)) & 0x3F; //0000 11
  tab5[57] = ((trametype5.dest.des[6] << 4) | (trametype5.dest.des[7] >> 2)) & 0x3F; //0010 00
  tab5[58] = ((trametype5.dest.des[7] << 4) | (trametype5.dest.des[8] >> 2)) & 0x3F; //0001 01
  tab5[59] = ((trametype5.dest.des[8] << 4) | (trametype5.dest.des[9] >> 2)) & 0x3F; //0110 10
  tab5[60] = ((trametype5.dest.des[9] << 4) | (trametype5.dest.des[10] >> 2)) & 0x3F; //1000 00
  tab5[61] = ((trametype5.dest.des[10] << 4) | (trametype5.dest.des[11] >> 2)) & 0x3F; //0100 00
  tab5[62] = ((trametype5.dest.des[11] << 4) | (trametype5.dest.des[12] >> 2)) & 0x3F; //0000 01
  tab5[63] = ((trametype5.dest.des[12] << 4) | (trametype5.dest.des[13] >> 2)) & 0x3F; //0100 00
  tab5[64] = ((trametype5.dest.des[13] << 4) | (trametype5.dest.des[14] >> 2)) & 0x3F; //0000 01
  tab5[65] = ((trametype5.dest.des[14] << 4) | (trametype5.dest.des[15] >> 2)) & 0x3F; //1000 00
  tab5[66] = ((trametype5.dest.des[15] << 4) | (trametype5.dest.des[16] >> 2)) & 0x3F; //0011 10
  tab5[67] = ((trametype5.dest.des[16] << 4) | (trametype5.dest.des[17] >> 2)) & 0x3F; //0011 11
  tab5[68] = ((trametype5.dest.des[17] << 4) | (trametype5.dest.des[18] >> 2)) & 0x3F; //0001 01
  tab5[69] = ((trametype5.dest.des[18] << 4) | (trametype5.dest.des[19] >> 2)) & 0x3F; //0011 00
  tab5[70] = ((trametype5.dest.des[19] << 4) | (trametype5.DTE << 3) | (trametype5.Spare5 << 2) | 0b01) & 0x3F;//00 //01

  Serial.begin(115200);
  Serial2.begin(4800);
}

void loop() {
  //Serial.println(tab5[70], BIN);
  //Serial.println("-----");
  //delay(1000);
  trame = "!AIVDM,1,1,,A,";
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

  //----------------------------------------------
  trame5 = "!AIVDM,2,1,5,B,";//54VE:802<@fL?HHsJ21<TiHE:1<P4@uN2222220t7B0;>C7<e?E25DTi0FH2 //53IfgL000000?HHsJ20lU<TpN10PDtpiR222220svWltt6EW;wkk'5PH0j1F
  for (int i = 0; i < 60; i++) {//71
    trame5 = trame5 + (String)bintostring(tab5[i]);
  }

  trame5 = trame5 + ",0*";
  sum5 = Chksum(trame5);
  if (sum5 < 10) {
    trame5 = trame5 + "0";
  }
  cheksum5 = String(sum5, HEX);
  trame5 = trame5 + cheksum5;


  //-----------------------------------------------

  trame52 = "!AIVDM,2,2,5,B,";//54VE:802<@fL?HHsJ21<TiHE:1<P4@uN2222220t7B0;>C7<e?E25DTi0FH2 //53IfgL000000?HHsJ20lU<TpN10PDtpiR222220svWltt6EW;wkk'5PH0j1F
  for (int i = 60; i < 71; i++) {//71
    trame52 = trame52 + (String)bintostring(tab5[i]);
  }

  trame52 = trame52 + ",0*";
  sum52 = Chksum(trame52);
  if (sum52 < 10) {
    trame52 = trame52 + "0";
  }
  cheksum52 = String(sum52, HEX);
  trame52= trame52 + cheksum52;

  //-----------------------------------------------------------
  Serial.println(trame);
  Serial2.println(trame);
  Serial.println(trame5);
  Serial2.println(trame5);
  Serial.println(trame52);
  Serial2.println(trame52);
  delay(1000);
  trame = "";
  trame5 = "";
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
