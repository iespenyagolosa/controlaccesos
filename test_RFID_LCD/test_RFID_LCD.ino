#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define RST_PIN D0
#define SS_PIN D4


MFRC522 mfrc522(SS_PIN, RST_PIN);


void setup() {
 
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.begin(16,2);     
  lcd.init();          
  lcd.backlight();     
  lcd.setCursor(0, 0); 
  lcd.print("CONTROL ACCESOS");  // Print HELLO to the screen, starting at 0,0.
  lcd.setCursor(0, 1);    // Move the cursor to the next line and print
  lcd.print(" BIBLIOTECA IES ");     // WORLD.  
  delay(2000);
 
}

void loop() {
  lcd.clear();
  lcd.home ();
  lcd.print(">Pase la tarjeta");
   
   delay (1000);
   // Busca una tarjeta
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Seleciona una de las tarjetas
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Muestra el UID de la  tarjeta en el monitor serie
  Serial.println();
  Serial.print("Etiqueta UID :");
  String tarjeta= "";
 
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     tarjeta.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     tarjeta.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tarjeta.toUpperCase();
  Serial.println();
  if (tarjeta.substring(1) == "9A FB 24 C9", "F1 E1 D1 0E") //cambia el UID de la tarjeta a la cual qieras conceder acceso
  {
    Serial.println(" Acceso Concedido ");  
    lcd.clear();
    lcd.home ();
    lcd.print("Acceso concedido");
    delay(3000);
  }
  
  else   {
    Serial.println(" Acceso Denegado ");  
    lcd.clear();
    lcd.home ();
    lcd.print("Acceso Denegado");  
    delay(3000);
  }
  delay(2000);
}
