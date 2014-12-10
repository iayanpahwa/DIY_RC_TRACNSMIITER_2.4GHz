/* By Ayan Pahwa 
competely open source, feel free to edit and improve. 
No responsibilty in any case is taken by the dev of this code. Use it wisely at your won risk */

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

#define Throttle A0
#define Rudder A1
#define Elevator A2

#define LeftAileron 2
#define RightAileron 3 //Ailerons will be activated when these pins recieve active low

const uint64_t pipe = 0xE8E8F0F0E1LL; //Unique address for communication
RF24 radio(9,10); //SPI bus+9,10 pins 
int t,x,y;
int joystick[5]; //variable array to store joystick readings


void setup()
{
  //Serial.begin(9600); //Enable serial for debugging
  digitalWrite(LeftAileron, HIGH); //Activating pull-ups
  digitalWrite(RightAileron, HIGH);
  
  
  radio.begin();
  radio.setPALevel(RF24_PA_MAX); //For Maximum range
  radio.setPayloadSize(10);
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(15,15);
  
  radio.openWritingPipe(pipe);
}

void loop()
{
  
  t=analogRead(Throttle);
  x=analogRead(Rudder);
  y=analogRead(Elevator);

int l=digitalRead(LeftAileron); 
int r=digitalRead(RightAileron);

 
 joystick[0]=map(t,0,1023,1000,2000); //map values according to desired throws 
 joystick[1]=map(x,0,1023,30,160);
 joystick[2]=map(y,0,1023,45,150);
 joystick[3]=l;
 joystick[4]=r;
 
 
 radio.write(joystick, sizeof(joystick));
 

}
  


