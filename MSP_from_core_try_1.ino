#include "rashikMSP.h"
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>

//## WIFI RELATED STUFFS ##############################
const char* ssid     = "moto";
const char* password = "12345679";

char host[] = "192.168.43.70";
int port = 12345;

WiFiClient drone1;  // Use WiFiClient class to create TCP connections

//## MSP RELATED STUFFS ##############################

SoftwareSerial naze_serial(D2, D3); // RX TX

rc_struct rc;
orientation ori;

MSP naze;

int z = 0;

void setup()
{
  Serial.begin(19200);

  connect_to_server();

  rc.roll = 1500;
  rc.pitch = 1500;
  rc.yaw = 1500;
  rc.throttle = 1050;
  rc.aux1 = 1500;
  rc.aux2 = 1500;
  rc.aux3 = 1500;
  rc.aux4 = 1111;

  naze_serial.begin(19200);
  naze.begin(naze_serial);


}

void loop()
{
  naze.set_raw_rc(rc);
  delay(50);
  //  ori = naze.get_orientation();
  //  delay(50);
  //
  //  drone1.print(String(ori.yaw) + "," + String(ori.pitch) + "," + String(ori.roll) + "|" );
  //  delay(50);

  //  drone1.print("Yaw:  " + String(ori.yaw) + "\t" );
  //  drone1.print("Pitch:  " + String(ori.pitch) + "\t");
  //  drone1.println("Roll:  " + String(ori.roll));

  while ( drone1.available() )
  {
    char cmd = drone1.read();

    

    if ( cmd == 'q')
    {
      rc.throttle = 1050;
      rc.aux1 = 1000;
    }
    if ( cmd == 's') 
    {
      rc.throttle = 1050;
      rc.aux1 = 2000;
    }

    if ( cmd == 'o')  if (rc.throttle <= 2000)   rc.throttle += 100;
    if ( cmd == 'l')  if (rc.throttle >= 1000)  rc.throttle -= 100;

    Serial.print(cmd);
    Serial.print(rc.aux1);
  }


  delay(100);
}

void connect_to_server()
{
  // First Connect to a WiFi network (Access Point)

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Connect to the websocket server

  Serial.print("Connecting to server (");
  Serial.print(host);
  Serial.print(":");
  Serial.print(String(port));
  Serial.println(")  ");

  for (int t = 0; t < 50; t++)
  {
    Serial.print("#");
    delay(100);
  }
  Serial.println();

  if (drone1.connect(host, port))
  {
    Serial.println("Connected");
  }
  else
  {
    Serial.println("Connection failed please restart the device and Server.");
    while (1)
    {
      // Hang on failure
      Serial.print(":-(  ");
      delay(1000);
    }
  }
}
