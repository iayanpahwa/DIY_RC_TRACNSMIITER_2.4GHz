/* By Ayan Pahwa 
competely open source, feel free to edit and improve. 
No responsibilty in any case is taken by the dev of this code. Use it wisely at your won risk */




#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include<Servo.h>

Servo Throttle,Rudder,Elevator,LeftAileron,RightAileron ;

const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(9,10);
int joystick[5];

void setup()
{
  /*Serial.begin(9600);
  delay(1000);
  Serial.println("Starting Rx");*/ //Enable serial for debugging
  
  attachMotors();
  
  calibrateMotors();
  
  radio.begin();
  
  detachMotors();
  
  radio.setPALevel(RF24_PA_MAX);
  radio.setPayloadSize(10);
  radio.setDataRate(RF24_250KBPS);
  radio.setRetries(15,15);
  
  radio.openReadingPipe(1,pipe);
  radio.startListening();;
}

void loop()
{
  detachMotors();
  
  if(radio.available())
  {
   
    bool done=false;
    while(!done)
    {
      done=radio.read(joystick,sizeof(joystick));
    }
    
  attachMotors();
  
  int a=joystick[0];
  int b= joystick[1]; //stores values from tx
  int c=joystick[2];
  int d=joystick[3];
  int e=joystick[4];
  
  
  
  //Serial.println(a);
  //Serial.println(b);
  //Serial.println(c);
  //Serial.println(d);
  //Serial.println(e);
 // Serial.println(f);
  
  delay(20);
  Throttle.writeMicroseconds(a);   //write values to motor
  Rudder.write(b);
  Elevator.write(180-c);
  
  if(d== LOW)
  {
  LeftAileron.write(180); ////to activate right aileron
  RightAileron.write(180);
  delay(15);
  }
  
  else if(e == LOW)
  { 
    LeftAileron.write(0);  //to activate left aileron
    RightAileron.write(0);
    delay(15);
  }
  
  
  else
  {
    LeftAileron.write(100);
    RightAileron.write(110); //Ailerons at neutral pos
    delay(15);
  }
    }
      
   
  
  else
  {
    calibrateMotors();
    delay(15);
    
  }
  }
     
void attachMotors()
{
  Throttle.attach(3);
  Rudder.attach(4);
  Elevator.attach(5);
  LeftAileron.attach(6);
  RightAileron.attach(7); 
}

void calibrateMotors()
{
  Rudder.write(90);
  Elevator.write(90);
  LeftAileron.write(100);
  RightAileron.write(110); //centering servo shafts
}

void detachMotors()
{
  Throttle.detach();
  Rudder.detach();
  Elevator.detach();
  LeftAileron.detach();
  RightAileron.detach();
}
  

