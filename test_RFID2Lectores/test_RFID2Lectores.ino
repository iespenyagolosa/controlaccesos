#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN D0
#define SS_1_PIN D4 //sda1 PIN lector Entrada
#define SS_2_PIN D3 //sda1 PIN lector Salida


MFRC522 lectorEntrada(SS_1_PIN, RST_PIN);
MFRC522 lectorSalida(SS_2_PIN, RST_PIN);

void setup() {
 
  Serial.begin(9600);
  delay(3000);
  SPI.begin();
  lectorEntrada.PCD_Init(SS_1_PIN,RST_PIN);
  Serial.print("Lector Entrada: ");
  lectorEntrada.PCD_DumpVersionToSerial();
  
  lectorSalida.PCD_Init(SS_2_PIN,RST_PIN);
  Serial.print("Lector Salida: ");
  lectorSalida.PCD_DumpVersionToSerial();
  delay(2000);
  Serial.println(" Control de accesos preparado "); 
}

void loop() {

   leeEntrada();
   delay(1000);
   leeSalida();
  /*
  if (tarjeta.substring(1) == "9A FB 24 C9", "F1 E1 D1 0E") //cambia el UID de la tarjeta a la cual qieras conceder acceso
  {
    Serial.println(" Acceso Concedido ");  
  
    delay(3000);
  }
  
  else   {
    Serial.println(" Acceso Denegado ");  
  
    delay(3000);
  }
  delay(2000);
  */
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
 
    for (byte i = 0; i < lectorEntrada.uid.size; i++) 
     {
       Serial.print(lectorEntrada.uid.uidByte[i] < 0x10 ? "0" : "");
       Serial.print(lectorEntrada.uid.uidByte[i], HEX);
       tarjeta.concat(String(lectorEntrada.uid.uidByte[i] < 0x10 ? "0" : ""));
       tarjeta.concat(String(lectorEntrada.uid.uidByte[i], HEX));
      }
     tarjeta.toUpperCase();
     Serial.println();
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
     Serial.println();
   }

}

