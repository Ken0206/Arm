//  4 Channel Receiver
//  PWM output on pins D2, D3, D4, D5

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

int ch_width_1 = 0;
int ch_width_2 = 0;
int ch_width_3 = 0;
int ch_width_4 = 0;
int ch_width_5 = 0;
int ch_width_6 = 0;
int ch_width_7 = 0;
int ch_width_8 = 0;
int ch_width_9 = 0;
int ch_width_10 = 0;
int ch_width_11 = 0;
int ch_width_12 = 0;

int ch_width_1_ = 1323;
int ch_width_2_ = 1707;
int ch_width_3_ = 1323;
int ch_width_4_ = 1323;
int ch_width_5_ = 1323;
int ch_width_6_ = 1323;
int ch_width_7_ = 1323;
int ch_width_8_ = 1323;
int ch_width_9_ = 1323;
int ch_width_10_ = 1323;
int ch_width_11_ = 1323;
int ch_width_12_ = 1323;

Servo ch1;
Servo ch2;
Servo ch3;
Servo ch4;
Servo ch5;
Servo ch6;
Servo ch7;
Servo ch8;
Servo ch9;
Servo ch10;
Servo ch11;
Servo ch12;

struct Signal {
byte throttle;      
byte pitch;
byte roll;
byte yaw;
};

Signal data;

const uint64_t pipeIn = 0xE9E8F0F0E1LL;
RF24 radio(9, 10); 

void ResetData()
{
// Define the inicial value of each data input
// The middle position for Potenciometers. (254/2=127)
data.throttle = 127; // Motor Stop
data.pitch = 127;  // Center
data.roll = 127;   // Center
data.yaw = 127;   // Center
}

void setup()
{
  //Set the pins for each PWM signal
  ch1.attach(2);
  ch2.attach(3);
  ch3.attach(4);
  ch4.attach(5);
  ch5.attach(6);
  ch6.attach(7);
  ch7.attach(14);
  ch8.attach(15);
  ch9.attach(16);
  ch10.attach(17);
  ch11.attach(18);
  ch12.attach(19);

  //Configure the NRF24 module
  ResetData();
  radio.begin();
  radio.openReadingPipe(1,pipeIn);
  radio.startListening(); //start the radio comunication for receiver
  //Serial.begin(9600);
}

unsigned long lastRecvTime = 0;

void recvData()
{
while ( radio.available() ) {
radio.read(&data, sizeof(Signal));
lastRecvTime = millis();   // receive the data
}
}

void loop()
{
recvData();
unsigned long now = millis();
if ( now - lastRecvTime > 1000 ) {
ResetData(); // Signal lost.. Reset data
}

ch_width_1 = map(data.throttle, 0, 255, 500, 2500);     // pin D2 (PWM signal)
ch_width_2 = map(data.pitch,    0, 255, 500, 2500);     // pin D3 (PWM signal)
ch_width_3 = map(data.roll,     0, 255, 500, 2500);     // pin D4 (PWM signal)
ch_width_4 = map(data.yaw,      0, 255, 500, 2500);     // pin D5 (PWM signal)


if (ch_width_1 > ch_width_1_){
  ch_width_1_ = ch_width_1_ + 1;
  }
if (ch_width_1 < ch_width_1_){
  ch_width_1_ = ch_width_1_ - 1;
  }
if (ch_width_2 > ch_width_2_){
  ch_width_2_ = ch_width_2_ + 1;
  }
if (ch_width_2 < ch_width_2_){
  ch_width_2_ = ch_width_2_ - 1;
  }
if (ch_width_3 > ch_width_3_){
  ch_width_3_ = ch_width_3_ + 1;
  }
if (ch_width_3 < ch_width_3_){
  ch_width_3_ = ch_width_3_ - 1;
  }
if (ch_width_4 > ch_width_4_){
  ch_width_4_ = ch_width_4_ + 1;
  }
if (ch_width_4 < ch_width_4_){
  ch_width_4_ = ch_width_4_ - 1;
  }

ch_width_5_ = ch_width_1_;
ch_width_6_ = ch_width_1_;
ch_width_7_ = ch_width_2_;
ch_width_8_ = ch_width_2_;
ch_width_9_ = ch_width_3_;
ch_width_10_ = ch_width_3_;
ch_width_11_ = ch_width_4_;
ch_width_12_ = ch_width_4_;

//Serial.print(ch_width_1_);
//Serial.print("  ");
//Serial.print(ch_width_2_);
//Serial.print("  ");
//Serial.print(ch_width_3_);
//Serial.print("  ");
//Serial.println(ch_width_4_);
delay(2);

//Serial.println(ch_width_4);
// Write the PWM signal
ch1.writeMicroseconds(ch_width_1_);
ch2.writeMicroseconds(ch_width_2_);
ch3.writeMicroseconds(ch_width_3_);
ch4.writeMicroseconds(ch_width_4_);
ch5.writeMicroseconds(ch_width_5_);
ch6.writeMicroseconds(ch_width_6_);
ch7.writeMicroseconds(ch_width_7_);
ch8.writeMicroseconds(ch_width_8_);
ch9.writeMicroseconds(ch_width_9_);
ch10.writeMicroseconds(ch_width_10_);
ch11.writeMicroseconds(ch_width_11_);
ch12.writeMicroseconds(ch_width_12_);
}
