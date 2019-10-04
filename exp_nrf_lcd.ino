#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
#include <LiquidCrystal.h>
 
int CE_pin=7, CSN_pin=8;
RF24 myRadio(CE_pin,CSN_pin);
const byte pipe [6] = "00001";
LiquidCrystal lcd( 12, 11, 5, 4, 3, 2);
void setup()
{
  analogWrite(6,90);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("LCD SETUP");
  delay(1000);
  lcd.clear();

  
 Serial.begin(9600);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MIN);
 
  myRadio.openReadingPipe(0,pipe);
  myRadio.startListening();
 // analogWrite(6,90);
 // lcd.begin(16,2);
  //lcd.setCursor(0,0);
  //lcd.print("LCD SETUP");
  //delay(1000);
  //lcd.clear();
}
  
void loop()
{
  if (myRadio.available()) {
    char text[20] = "";
    myRadio.read(&text, sizeof(text));
    Serial.println(text);
    lcd.print(text);
    delay(1000);
    lcd.clear();
  }
}
