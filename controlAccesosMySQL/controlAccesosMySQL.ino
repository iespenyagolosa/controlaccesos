
#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

WiFiClient client;
MySQL_Connection conexionBD((Client *)&client);
MySQL_Cursor* cursor;

IPAddress direccion_servidorBD(192, 168, 50, 10);          // dirección IP del servidor de Bases de Datos
char usuario[] = "controlAccesos";           // usuario MySQL 
char contrasenya[] = "control#2018"; // contraseña MySQL 

// Consulta de ejemplo
char INSERTA_SQL[] = "INSERT INTO controlAccesos.Registro (Usuario, EntradaSalida) VALUES ('AABBCCDD',1)";

void setup()
{
  Serial.begin(9600);

  // Conexión a Internet ----------------------------------------------
  WiFi.disconnect();
  Serial.println("Conectando a Internet . . .");
  delay(3000);
   WiFi.begin("testIOT","testIOT#2018");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);

  }
  Serial.println("¡¡¡Ya estoy conectado!!!");
  //--------------------------------------------------------------------
  // Conexión a la Base de Datos ---------------------------------------
  Serial.println("Conectando a la base de datos");

  while (conexionBD.connect(direccion_servidorBD, 3306, usuario, contrasenya) != true) {
    delay(200);
    Serial.print ( "." );
  }

  Serial.println("");
  Serial.println("¡Conectado al servidor de Bases de Datos!");  
  //--------------------------------------------------------------------

  // crea un objeto MySQL cursor 
  cursor = new MySQL_Cursor(&conexionBD);
  //Prueba a insertar una fila...
   if (conexionBD.connected())
    cursor->execute(INSERTA_SQL);
}


void loop()
{
 
 

}
