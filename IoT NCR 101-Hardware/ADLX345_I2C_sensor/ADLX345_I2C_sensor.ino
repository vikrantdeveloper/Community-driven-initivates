#include <Wire.h>
#define DEVICE (0x53) //address of the module
byte value[6];   //every axis return 2 bit data
char output[512];
void setup() 
{
  Wire.begin();    //12c protocol
  Serial.begin(9600); //UART protocol

  Wire.beginTransmission(DEVICE);
  Wire.write(0x2D);
  Wire.write(0);     //clear register
  Wire.beginTransmission(DEVICE);
  Wire.write(0x2D);
  Wire.write(16);
  Wire.beginTransmission(DEVICE);
  Wire.write(0x2D);
  Wire.write(8);
  Wire.endTransmission();  
}

void loop() 
{
  int xyz=0x32;
  int x[2],y[2],z[2];
  int values[6];
  Wire.beginTransmission(DEVICE);
  Wire.write(xyz);
  Wire.endTransmission(); 
  Wire.beginTransmission(DEVICE);
  Wire.requestFrom(DEVICE,6);
  int i=0;
  while(Wire.available())
  {
    values[i]=  Wire.read();
    i++;
  }
  for(i=0;i++;i<2)
   {
    x[i]=values[i];
    Serial.println(x[i]);
   }
   delay(100);
   for(i=2;i++;i<=4)
   {
    y[i]=values[i];
    Serial.println(y[i]);
   }
   delay(100);
   for(i=4;i++;i<=6)
   {
    z[i]=values[i];
    Serial.println(z[i]);   
   }
   delay(100);

}
