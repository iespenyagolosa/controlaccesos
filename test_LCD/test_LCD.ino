//#include <SPI.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);



void setup() {
 
  Serial.begin(9600);
  //SPI.begin();
  
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
 
  //Muestra el UID de la  tarjeta en el monitor serie
  Serial.println();
  Serial.print("Etiqueta UID :");
 
  delay(2000);
}
