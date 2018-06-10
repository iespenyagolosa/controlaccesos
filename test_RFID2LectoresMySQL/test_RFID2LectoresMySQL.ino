
#include <ESP8266WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <SPI.h>
#include <MFRC522.h>

// ------- configuración lectores RFID  --------------------
#define RST_PIN D0
#define SS_1_PIN D4 //sda1 PIN lector Entrada
#define SS_2_PIN D3 //sda1 PIN lector Salida
MFRC522 lectorEntrada(SS_1_PIN, RST_PIN);
MFRC522 lectorSalida(SS_2_PIN, RST_PIN);

// ------- configuración acceso a la Base de Datos  --------------------
WiFiClient client;
MySQL_Connection conexionBD((Client *)&client);
MySQL_Cursor* cursor;

IPAddress direccion_servidorBD(192, 168, 50, 10);          // dirección IP del servidor de Bases de Datos
char usuario[] = "controlAccesos";           // usuario MySQL 
char contrasenya[] = "control#2018"; // contraseña MySQL 

// Consulta de ejemplo
char INSERTA_DATOS[] = "INSERT INTO controlAccesos.Registro (Usuario, EntradaSalida) VALUES ('%s',%d)";
char CONSULTA_DATOS[] ="SELECT Grupos.Permiso FROM controlAccesos.Usuarios AS Usuarios, controlAccesos.Grupos AS Grupos WHERE Usuarios.Grupo = Grupos.IdGrupo AND Usuarios.TagRFID = '9AFB24C9'";
//char CONSULTA_DATOS[] ="SELECT "Grupos"."Permiso" FROM "controlAccesos"."Usuarios" AS "Usuarios", "controlAccesos"."Grupos" AS "Grupos" WHERE "Usuarios"."Grupo" = "Grupos"."IdGrupo" AND "Usuarios"."TagRFID" = '9AFB24C9'";
char consulta[128];
char RFID[9];

void setup() {
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
   // crea un objeto MySQL cursor 
  cursor = new MySQL_Cursor(&conexionBD); 
  //--------------------------------------------------------------------

  // Inicializa lectores RFID --------------------------------------------
  SPI.begin();
  lectorEntrada.PCD_Init(SS_1_PIN,RST_PIN);
  Serial.print("Lector Entrada: ");
  lectorEntrada.PCD_DumpVersionToSerial();
  
  lectorSalida.PCD_Init(SS_2_PIN,RST_PIN);
  Serial.print("Lector Salida: ");
  lectorSalida.PCD_DumpVersionToSerial();
  delay(2000);
  Serial.println(" Lectores preparados "); 
}

void loop() {

   leeEntrada();
   delay(1000);
   //leeSalida();
 
   delay (1000);
}


void leeEntrada(){
 // Busca una tarjeta en le lector de entrada
  if (lectorEntrada.PICC_IsNewCardPresent() && lectorEntrada.PICC_ReadCardSerial()) 
  {
    //Muestra el UID de la  tarjeta en el monitor serie
    Serial.println("::::Lector Entrada::::");
    Serial.print("Etiqueta UID :");
    String tarjeta= "";
    String cadenaPrueba="";
    
    for (byte i = 0; i < lectorEntrada.uid.size; i++) 
     {
       Serial.print(lectorEntrada.uid.uidByte[i] < 0x10 ? "0" : "");
       Serial.print(lectorEntrada.uid.uidByte[i], HEX);
       tarjeta.concat(String(lectorEntrada.uid.uidByte[i] < 0x10 ? "0" : ""));
       tarjeta.concat(String(lectorEntrada.uid.uidByte[i], HEX));
      }
     tarjeta.toUpperCase();
     tarjeta.toCharArray(RFID,9);
     Serial.println();
     // Consulta si tiene permiso ···


     
     sprintf(consulta, INSERTA_DATOS, RFID, 1);
     
     Serial.println(consulta);
     //Inserta una entrada...
     if (conexionBD.connected()){
        cursor->execute(consulta);
         Serial.println("Datos grabados.");
     }
   }

}

void leeSalida(){
 // Busca una tarjeta en le lector de entrada
  if (lectorSalida.PICC_IsNewCardPresent() && lectorSalida.PICC_ReadCardSerial()) 
  {
    //Muestra el UID de la  tarjeta en el monitor serie
    Serial.println("::::Lector Salida::::");
    Serial.print("Etiqueta UID :");
    String tarjeta= "";
 
    for (byte i = 0; i < lectorSalida.uid.size; i++) 
     {
       Serial.print(lectorSalida.uid.uidByte[i] < 0x10 ? "0" : "");
       Serial.print(lectorSalida.uid.uidByte[i], HEX);
       tarjeta.concat(String(lectorSalida.uid.uidByte[i] < 0x10 ? "0" : ""));
       tarjeta.concat(String(lectorSalida.uid.uidByte[i], HEX));
      }
     tarjeta.toUpperCase();
     tarjeta.toCharArray(RFID,9);
     Serial.println();
     sprintf(consulta, INSERTA_DATOS, RFID, 0);
     //Inserta una entrada...
     if (conexionBD.connected()){
        cursor->execute(consulta);
         Serial.println("Datos grabados.");
     }
   }

}

