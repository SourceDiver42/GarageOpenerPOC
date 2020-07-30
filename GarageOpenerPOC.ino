#include <TinyGPS.h>
#include <Adafruit_GPS.h>
#include <Adafruit_PMTK.h>
//#include <NMEA_data.h>


#include <mcp_can.h>
#include <mcp_can_dfs.h>

#include <SPI.h>

#include "config.h"

//Variables
const int SPI_CS_PIN = 9;


//Instances
SoftwareSerial gpsSerial(3,4);
TinyGPS gps;
MCP_CAN CAN(SPI_CS_PIN);  


//Opposing corner coordinates of the area your garage door is in
float lat1 = AREA_LAT1;
float long1 = AREA_LONG1;
float lat2 = AREA_LAT2;
float long2 = AREA_LONG2;

float long = 0.0f;
float lat = 0.0f;

bool PositionInArea(){
  gps.f_get_position(&lat, &long);

  if (lat < lat1 && lat > lat2){
    if (long > long1 && lat < long2) {
      return true;
    }
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
  gpsSerial.begin(9600);


  while (CAN_OK != CAN.begin(CAN_500KBPS))        
    {
        Serial.println("CAN BUS Shield init failed, retrying...");
        delay(100);
    }

  Serial.println("Ready, listening for messages");
  
  
}

void loop() {

   unsigned char len = 0;
   unsigned char buf[16];
   
if(PositionInArea(){
    if(CAN_MSGAVAIL == CAN.checkReceive())            
    {
      CAN.readMsgBuf(&len, buf);
      unsigned char ID = CAN.getCanId();

      /*for(int i = 0; i<len; i++)    
        {
            Serial.print(buf[i]);
            
        }*/

      //TODO: Check if incoming message equals CANMESSAGE or maybe use a CAN filter/mask

      Serial.print("trigger");
    }
  }
}
