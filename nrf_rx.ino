
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
  myRadio.setPALevel(RF24_PA_MIN);
 
  myRadio.openReadingPipe(0,pipe);
  myRadio.startListening();
  
  delay(1000);
}
void loop()
{
//  Serial.println("out ");
  if (myRadio.available())
  {
    
    int res=0;
    myRadio.read(&res,sizeof(res));
    //Serial.println("printing ");
    Serial.println(res);
  
}
}
