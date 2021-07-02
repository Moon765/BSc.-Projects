int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

int c,f;

#include <EasyTransfer.h>

//create object
EasyTransfer ET; 

struct SEND_DATA_STRUCTURE{
  int16_t blinks;
  int16_t pause;
};

SEND_DATA_STRUCTURE mydata;

void setup() {
Serial.begin(9600);
ET.begin(details(mydata), &Serial);
}

void loop() {

  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  Tc = T - 273.15;
  Tf = (Tc * 9.0)/ 5.0 + 32.0; 

  Serial.print("Temperature: "); 
  Serial.print(Tf);
  Serial.print(" F; ");
  Serial.print(Tc);
  Serial.println(" C"); 

  c = (Tc*10);
  f = (Tf*10);
  mydata.blinks = c;
  mydata.pause = f;
  //send the data
  ET.sendData(); 
  delay(500);
}   
