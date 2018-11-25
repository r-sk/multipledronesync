#include <ESP8266WiFi.h>

const char* ssid     = "TMkibash_wlink";
const char* password = "1234market";

char host[] = "192.168.1.75";
int port = 12345;


WiFiClient drone1;  // Use WiFiClient class to create TCP connections

void setup()
{
  Serial.begin(115200);
  delay(10);

  connect_to_server();

}


void loop()
{

  drone1.println("Hello I am Client");

  while ( drone1.available() )
  {
     char str=drone1.read();
     Serial.print(str);
  }

   delay(1000);

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
  
  for(int t=0;t<50;t++)
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
    Serial.println("Connection failed please restart the device.");
    while(1)
    {
      // Hang on failure
      Serial.print(":-(  ");
      delay(1000);
    }
  }
}
