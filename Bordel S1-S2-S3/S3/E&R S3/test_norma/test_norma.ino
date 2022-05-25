void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(normalisation("1"));
delay(10000);
}

String normalisation(String date) {
String years="2020";
String month="01";
String days="01";
String dateconver(years + "-" + month + "-" + days +"%2000:00:00");
return (dateconver);
}
