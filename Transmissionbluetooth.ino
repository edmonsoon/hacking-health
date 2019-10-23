#include "BluetoothSerial.h"


BluetoothSerial SerialBT;
long int message = 0;
int bpm=60, hum=70, temp=25, chute=0, compteur=0;
bool bewl=false;
bool ChuteOK=false;

void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32");
  pinMode(2, INPUT);
}
 
void loop() {
  chute=digitalRead(2);
  chute=1;
  message=message+bpm;
  message=message+(hum*256);
  message=message+(temp*256*256);
 
  if (chute==1)
  {
    bewl=true;
  }
     
   if (bewl==true)
  {
     compteur++;
  }
    if (compteur==25 && ChuteOK==false)
   {
     message=message+(128*256*256); 
     Serial.println("Chute");
     ChuteOK==true;
  }

    SerialBT.print(message);
    Serial.println(message);

    message=0;
    delay(200);
}
