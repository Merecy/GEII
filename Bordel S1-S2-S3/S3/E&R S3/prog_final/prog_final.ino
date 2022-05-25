#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>

#define SCK     5    // GPIO5  -- SX1278's SCK
#define MISO    19   // GPIO19 -- SX1278's MISnO
#define MOSI    27   // GPIO27 -- SX1278's MOSI
#define SS      18   // GPIO18 -- SX1278's CS
#define RST     14   // GPIO14 -- SX1278's RESET
#define DI0     26   // GPIO26 -- SX1278's IRQ(Interrupt Request)
#define BAND  868E6

int counter = 0;

String rssi = "RSSI --";
String packSize = "--";
String packet ;

const int Output_Pin = 25;

volatile int  Pulse_Count;
unsigned int  Liter_per_hour;
unsigned long Current_Time, Loop_Time;


void setup() {
  Serial.begin(115200);
  pinMode(Output_Pin, INPUT);
  attachInterrupt(Output_Pin, Detect_Rising_Edge, RISING);

  Current_Time = millis();
  Loop_Time = Current_Time;


  while (!Serial);
  Serial.println();
  Serial.println("LoRa Sender Test");


  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DI0);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);

  }

  Serial.println("init ok");

  delay(1500);
}


void loop() {
  
  Current_Time = millis();


  if (Current_Time >= (Loop_Time + 1000))
  {
    Loop_Time = Current_Time;
    Liter_per_hour = (Pulse_Count * 60 / 7.5);
    Pulse_Count = 0;
    Serial.print(Liter_per_hour, DEC);
    Serial.println(" Liter/hour");
    
    LoRa.beginPacket();
    LoRa.print(Liter_per_hour, DEC);
    LoRa.endPacket();
  }
}


void Detect_Rising_Edge ()
{
  Pulse_Count++;
}
