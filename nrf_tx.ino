
#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>
int CE_pin=7, CSN_pin=8;
RF24 myRadio(CE_pin,CSN_pin);
const byte pipe [6] = "00001";
 void setup()
 {
   Serial.begin(9600);
  delay(1000);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
   
  myRadio.openWritingPipe(pipe);
  myRadio.stopListening();
  delay(1000);
 }
 void loop()
 {
  const char text[32] = "Hello World";
  myRadio.write(&text,sizeof(text));
  delay(1000);
 }

