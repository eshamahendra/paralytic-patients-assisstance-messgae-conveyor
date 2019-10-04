#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include<Wire.h>
#include<SPI.h>
#include<nRF24L01.h>

int CE_pin=7, CSN_pin=8;
RF24 myRadio(CE_pin,CSN_pin);
const byte pipe [6] = "00001";

const int MPU_addr=0x68; int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265; int maxVal=402;

double x; double y; double z;

void setup(){ 
  Wire.begin(); 
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x6B); Wire.write(0); 
  Wire.endTransmission(true); 
  Serial.begin(9600);
  myRadio.begin();  
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MIN);
   
  myRadio.openWritingPipe(pipe);
  myRadio.stopListening();
  delay(1000);
  } 
void loop(){ 
  
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x3B); 
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_addr,14,true); 
  AcX=Wire.read()<<8|Wire.read(); 
  AcY=Wire.read()<<8|Wire.read(); 
  AcZ=Wire.read()<<8|Wire.read(); 
  int xAng = map(AcX,minVal,maxVal,-90,90); 
  int yAng = map(AcY,minVal,maxVal,-90,90); 
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);

  //Serial.print("AngleX= "); Serial.println(x);

 // Serial.print("AngleY= "); Serial.println(y);

  //Serial.print("AngleZ= "); Serial.println(z);
  delay(1000); 
  
 
  if (x >= 80 && x <=100 )
  {
   const char text[20] = "NEED FOOD";
   myRadio.write(&text,sizeof(text));
   Serial.println(text);
  }
  
    
   if (x>=250 && x<=280)
  { const char text[20]="NEED WATER";
   myRadio.write(&text,sizeof(text));
   Serial.println(text);
   delay(1000);
  }
}
  
 
