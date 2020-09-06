// 6 頻道發射器

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

const uint64_t pipeOut = 0xABCDEFABCDEF;   //必與接收器設定相同
RF24 radio(9, 10); // 設定 CE,CSN pin

struct Signal {
byte Signal_A0;
byte Signal_A1;
byte Signal_A2;
byte Signal_A3;
byte Signal_A4;
byte Signal_A5;
};

Signal data;

void ResetData() 
{
// 可變電阻中間位置(254/2=127)(預設失去訊號的位置)
data.Signal_A0 = 255;
data.Signal_A1 = 0;
data.Signal_A2 = 0;
data.Signal_A3 = 255;
data.Signal_A4 = 0;
data.Signal_A5 = 255;
}

void setup()
{
//啟動 NRF24 模組
radio.begin();
radio.openWritingPipe(pipeOut);
radio.stopListening(); //啟動無線連接，只發射訊號
ResetData();
}

// 搖桿中心及其邊界
int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
val = constrain(val, lower, upper);
if ( val < middle )
val = map(val, lower, middle, 0, 128);
else
val = map(val, middle, upper, 128, 255);
return ( reverse ? 255 - val : val );
}

void loop()
{
//可變電阻校準
//伺服方向為 "true" 或 "false"
data.Signal_A0 = mapJoystickValues( analogRead(A0), 12, 524, 1020, false );
data.Signal_A1 = mapJoystickValues( analogRead(A1), 12, 524, 1020, false );
data.Signal_A2 = mapJoystickValues( analogRead(A2), 12, 524, 1020, false );
data.Signal_A3 = mapJoystickValues( analogRead(A3), 12, 524, 1020, false );
data.Signal_A4 = mapJoystickValues( analogRead(A4), 12, 524, 1020, true );
data.Signal_A5 = mapJoystickValues( analogRead(A5), 12, 524, 1020, true );

radio.write(&data, sizeof(Signal));
}
