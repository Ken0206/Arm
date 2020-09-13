//  6 頻道接收器
//  PWM 輸出於 pins D2, D3, D4, D5, D6, D7

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

int AngleIncrement = 1;
int DelayTime = 1;

int ch_width_1 = 0;
int ch_width_2 = 0;
int ch_width_3 = 0;
int ch_width_4 = 0;
int ch_width_5 = 0;
int ch_width_6 = 0;

int ch_width_1_ = 2068;
int ch_width_2_ = 774;
int ch_width_3_ = 656;
int ch_width_4_ = 2225;
int ch_width_5_ = 900;
int ch_width_6_ = 1990;

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
data.Signal_A0 = 242;
data.Signal_A1 = 7;
data.Signal_A2 = 204;
data.Signal_A3 = 183;
data.Signal_A4 = 110;
data.Signal_A5 = 248;
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

//動作範圍
ch_width_1 = map(data.Signal_A0, 119, 242, 1200, 2068);     // pin D2 (PWM 訊號) 2068
ch_width_2 = map(data.Signal_A1, 7, 136, 774, 1650);     // pin D3 (PWM 訊號) 774
ch_width_3 = map(data.Signal_A2, 205, 255, 656, 1360);     // pin D4 (PWM 訊號) 656
ch_width_4 = map(data.Signal_A3, 4, 194, 1300, 2225);     // pin D5 (PWM 訊號) 2225
ch_width_5 = map(data.Signal_A4, 137, 255, 900, 1500);     // pin D6 (PWM 訊號) 900
ch_width_6 = map(data.Signal_A5, 61, 241, 1400, 1990);     // pin D7 (PWM 訊號) 1990

//零點  242  7  205  194  137  241
//外點  119  136  255  4  255  61

//漸變
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


//原點極限值
if (ch_width_1_ > 2068){
  ch_width_1_ = 2068;
  }
if (ch_width_2_ > 1650){
  ch_width_2_ = 1650;
  }
if (ch_width_3_ > 1360){
  ch_width_3_ = 1360;
  }
if (ch_width_4_ > 2255){
  ch_width_4_ = 2255;
  }
if (ch_width_5_ < 900){
  ch_width_5_ = 900;
  }
if (ch_width_6_ > 1990){
  ch_width_6_ = 1990;
  }

//外點極限值
if (ch_width_1_ < 1200){
  ch_width_1_ = 1200;
  }
if (ch_width_2_ < 774){
  ch_width_2_ = 774;
  }
if (ch_width_3_ < 656){
  ch_width_3_ = 656;
  }
if (ch_width_4_ < 1300){
  ch_width_4_ = 1300;
  }
if (ch_width_5_ > 1500){
  ch_width_5_ = 1500;
  }
if (ch_width_6_ < 1400){
  ch_width_6_ = 1400;
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

delay(DelayTime);
}
