//  6 頻道接收器
//  PWM 輸出於 pins D2, D3, D4, D5, D6, D7

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

int AngleIncrement = 1;
int DelayTime = 10;

//機械原點 PWM 值
int init_1 = 1984;
int init_2 = 845;
int init_3 = 705;
int init_4 = 2021;
int init_5 = 924;
int init_6 = 1918;

//機械極限點 PWM 值
int limit_1 = 1446;
int limit_2 = 1568;
int limit_3 = 1360;
int limit_4 = 1300;
int limit_5 = 1800;
int limit_6 = 1150;

int ch_width_1_ = init_1;
int ch_width_2_ = init_2;
int ch_width_3_ = init_3;
int ch_width_4_ = init_4;
int ch_width_5_ = init_5;
int ch_width_6_ = init_6;

int ch_width_1 = 0;
int ch_width_2 = 0;
int ch_width_3 = 0;
int ch_width_4 = 0;
int ch_width_5 = 0;
int ch_width_6 = 0;

Servo ch1;
Servo ch2;
Servo ch3;
Servo ch4;
Servo ch5;
Servo ch6;

struct Signal {
byte Signal_A0;      
byte Signal_A1;
byte Signal_A2;
byte Signal_A3;
byte Signal_A4;
byte Signal_A5;
};

Signal data;

const uint64_t pipeIn = 0xABCDEFABCDEF;  //必與發射器設定相同
RF24 radio(9, 10); 

void ResetData()
{
// 定義每個數據輸入的初始值
// 可變電阻中間位置 (254/2=127)
data.Signal_A0 = 244;
data.Signal_A1 = 8;
data.Signal_A2 = 0;
data.Signal_A3 = 255;
data.Signal_A4 = 10;
data.Signal_A5 = 123;
}

void setup()
{
  //PWM 訊號腳位
  ch1.attach(2);
  ch2.attach(3);
  ch3.attach(4);
  ch4.attach(5);
  ch5.attach(6);
  ch6.attach(7);
  
  //啟動 NRF24 模組
  ResetData();
  radio.begin();
  radio.openReadingPipe(1,pipeIn);
  radio.startListening(); ////啟動無線連接，只接收訊號
  //Serial.begin(115200);
}

unsigned long lastRecvTime = 0;

void recvData()
{
while ( radio.available() ) {
radio.read(&data, sizeof(Signal));
lastRecvTime = millis();   // 接收資料
}
}

void loop()
{
delay(DelayTime);
//delayMicroseconds(DelayTime);
recvData();
unsigned long now = millis();
if ( now - lastRecvTime > 1000 ) {
ResetData(); // 失去訊號，重設資料
}

/*
Serial.print(data.Signal_A0);
Serial.print("  ");
Serial.print(data.Signal_A1);
Serial.print("  ");
Serial.print(data.Signal_A2);
Serial.print("  ");
Serial.print(data.Signal_A3);
Serial.print("  ");
Serial.print(data.Signal_A4);
Serial.print("  ");
Serial.println(data.Signal_A5);
*/

//動作範圍對應
ch_width_1 = map(data.Signal_A0, 123, 246, limit_1, init_1);     // pin D2 (PWM 訊號)
ch_width_2 = map(data.Signal_A1, 12, 124, init_2, limit_2);     // pin D3 (PWM 訊號)
ch_width_3 = map(data.Signal_A2, 0, 58, init_3, limit_3);     // pin D4 (PWM 訊號)
ch_width_4 = map(data.Signal_A3, 200, 254, limit_4, init_4);     // pin D5 (PWM 訊號)
ch_width_5 = map(data.Signal_A4, 142, 242, init_5, limit_5);     // pin D6 (PWM 訊號)
ch_width_6 = map(data.Signal_A5, 133, 244, limit_6, init_6);     // pin D7 (PWM 訊號)

// PWM 訊號漸變
if (ch_width_1 > ch_width_1_){
  ch_width_1_ = ch_width_1_ + AngleIncrement;
  }
if (ch_width_1 < ch_width_1_){
  ch_width_1_ = ch_width_1_ - AngleIncrement;
  }
if (ch_width_2 > ch_width_2_){
  ch_width_2_ = ch_width_2_ + AngleIncrement;
  }
if (ch_width_2 < ch_width_2_){
  ch_width_2_ = ch_width_2_ - AngleIncrement;
  }
if (ch_width_3 > ch_width_3_){
  ch_width_3_ = ch_width_3_ + AngleIncrement;
  }
if (ch_width_3 < ch_width_3_){
  ch_width_3_ = ch_width_3_ - AngleIncrement;
  }
if (ch_width_4 > ch_width_4_){
  ch_width_4_ = ch_width_4_ + AngleIncrement;
  }
if (ch_width_4 < ch_width_4_){
  ch_width_4_ = ch_width_4_ - AngleIncrement;
  }
if (ch_width_5 > ch_width_5_){
  ch_width_5_ = ch_width_5_ + AngleIncrement;
  }
if (ch_width_5 < ch_width_5_){
  ch_width_5_ = ch_width_5_ - AngleIncrement;
  }
if (ch_width_6 > ch_width_6_){
  ch_width_6_ = ch_width_6_ + AngleIncrement;
  }
if (ch_width_6 < ch_width_6_){
  ch_width_6_ = ch_width_6_ - AngleIncrement;
  }

//機械原點限制 PWM 值
if (ch_width_1_ > init_1){
  ch_width_1_ = init_1;
  }
if (ch_width_2_ < init_2){
  ch_width_2_ = init_2;
  }
if (ch_width_3_ < init_3){
  ch_width_3_ = init_3;
  }
if (ch_width_4_ > init_4){
  ch_width_4_ = init_4;
  }
if (ch_width_5_ < init_5){
  ch_width_5_ = init_5;
  }
if (ch_width_6_ > init_6){
  ch_width_6_ = init_6;
  }

//機械極限點限制 PWM 值
if (ch_width_1_ < limit_1){
  ch_width_1_ = limit_1;
  }
if (ch_width_2_ > limit_2){
  ch_width_2_ = limit_2;
  }
if (ch_width_3_ > limit_3){
  ch_width_3_ = limit_3;
  }
if (ch_width_4_ < limit_4){
  ch_width_4_ = limit_4;
  }
if (ch_width_5_ > limit_5){
  ch_width_5_ = limit_5;
  }
if (ch_width_6_ < limit_6){
  ch_width_6_ = limit_6;
  }

/*
Serial.print(ch_width_1_);
Serial.print("  ");
Serial.print(ch_width_2_);
Serial.print("  ");
Serial.print(ch_width_3_);
Serial.print("  ");
Serial.print(ch_width_4_);
Serial.print("  ");
Serial.print(ch_width_5_);
Serial.print("  ");
Serial.println(ch_width_6_);
*/

// 執行 PWM 訊號
ch1.writeMicroseconds(ch_width_1_);
ch2.writeMicroseconds(ch_width_2_);
ch3.writeMicroseconds(ch_width_3_);
ch4.writeMicroseconds(ch_width_4_);
ch5.writeMicroseconds(ch_width_5_);
ch6.writeMicroseconds(ch_width_6_);

}
