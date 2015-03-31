/*  
about:  This is code written for the arduino uno and the sharp dust sensor 
"GP2Y1010AU0F" sold by sparkfun in combination with a flipdot as an output device.
author: œMuenchMan
license:  The MIT License (MIT)
comments:  created during a course on the University of Applied Science Potsdam
many thanks to @fabiantheblind for sharing his knowledge! 
Data sheet for the Dust sensor:  https://www.sparkfun.com/datasheets/Sensors/gp2y1010au_e.pdf).
*/

/* this code uses a custom loop to ignore spikes in the sensor readings
so stray particles won't flip the dot but only a proper decrease in air-quality.
*/

int dustPin=0;
int dustVal=0;
int dustLimit=400; // change for adjusting the air-quality treshold
int dustBuildup=0;
int loopCounter=0; 
int loopLength=4+1; // change first number for more loop passes (increases input delay!)
int loopLimit=dustLimit*loopLength;
int loopDelay=1000; // change for faster or slower readings

int flip=10;
int flop=11;

int ledPower=2;
int delayTime=280;
int delayTime2=40;
float offTime=9680;

void setup(){
Serial.begin(9600);
pinMode(ledPower,OUTPUT);
pinMode(4, OUTPUT);

pinMode(flip, OUTPUT);
pinMode(flop, OUTPUT);
digitalWrite(flip, HIGH);
digitalWrite(flop, LOW);
}

void loop(){
// ledPower is any digital pin on the arduino connected to Pin 3 on the sensor
digitalWrite(ledPower,LOW); // power on the LED
delayMicroseconds(delayTime);
dustVal=analogRead(dustPin); // read the dust value via pin 5 on the sensor
delayMicroseconds(delayTime2);
digitalWrite(ledPower,HIGH); // turn the LED off
delayMicroseconds(offTime);

loopCounter=loopCounter+1; 
dustBuildup=dustBuildup+dustVal;

 Serial.println("Counter");
 Serial.println(loopCounter); 
 
 if ((dustVal>dustLimit))  { // prints dustVal if dustLimit is exceeded
   Serial.println("val");
   Serial.println(dustVal);
 }
 else  {
 }
 

   if ((dustBuildup>loopLimit) && (loopCounter==loopLength))  {
    digitalWrite(flop,LOW); // flips the dot
    digitalWrite(flip,HIGH);
    Serial.println("flip");
    delay(10);
    digitalWrite(flip,LOW);
    
    Serial.println("Buildup");
    Serial.println(dustBuildup);
    
    loopCounter=0; // resets counter and buildup value 
    dustBuildup=0; 
  }
  else if ((dustBuildup<loopLimit) && (loopCounter==loopLength)){
    digitalWrite(flip,LOW); // flops the dot
    digitalWrite(flop,HIGH);
    Serial.println("flop");
    delay(10);
    digitalWrite(flop,LOW);
    
    Serial.println("Buildup");
    Serial.println(dustBuildup);
    
    loopCounter=0; // resets counter and buildup value
    dustBuildup=0;
  }
Serial.println("-----");
delay(loopDelay);
}
