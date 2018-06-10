
#include <ESP8266WiFi.h>

WiFiClient client;


void setup()
{
  Serial.begin(9600);

  WiFi.disconnect();
  Serial.println("Conectando a Internet . . .");
  delay(3000);
   WiFi.begin("testIOT","testIOT#2018");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);

  }
  Serial.println("¡¡¡Ya estoy conectado!!!");

}


void loop()
{

 

}
