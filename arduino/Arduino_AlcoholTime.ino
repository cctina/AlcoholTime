#include <SoftwareSerial.h>
#include <Wire.h>  //引用二個函式庫SoftwareSerial及Wire

SoftwareSerial I2CBT(10,11);  //定義PIN10及PIN11分別為RX及TX腳位

byte cmmd[20];
int insize, a;

void setup() {
  Serial.begin(9600);     //Arduino起始鮑率：9600
  I2CBT.begin(9600);     //藍牙鮑率：9600 (for HC-05) 注意！鮑率每個藍牙晶片不一定相同，請務必確認
  pinMode(13, OUTPUT);   //請注意您使用的 Arduino 該腳位是否支援 PWM (會有~符號），否則會看不到效果
}

void loop() {
  byte cmmd[20];
  int insize;	
  while(1){  
    //讀取藍牙訊息
    if ((insize=(I2CBT.available()))>0){
      //    Serial.print("input size = ");
      //   Serial.println(insize);
      for (int i=0; i<insize; i++){
        cmmd[i]=char(I2CBT.read());
      }
//      Serial.print("input=");
//      Serial.print(cmmd[0]);
//      Serial.print(";  ");
      a = cmmd[0]-48;  // 由 ASCII code 轉換成對應的數值 (input=0~6)
    }

    Serial.print(a);   
    Serial.print("  ");  
    switch (a) { 
    case 0: // 0 //(x)97為"a"的ASCII CODE
      Serial.print("Turn off");
      Serial.print("  ");
      digitalWrite(13, LOW);  //熄滅LED
      delay(1000);            //熄滅 1 秒
      break;
    default: //(x)98為"b"的ASCII CODE
      if (a>0 && a<10) {
        Serial.print("Turn on");
        Serial.print("  ");
        digitalWrite(13, HIGH); // 點亮 LED & 推動幫浦馬達
        delay(a*5000);          // 點亮 a*5 秒
//        delay(a*1000);        // 點亮 a 秒 (a ms)
      }
      else{
        Serial.print("(Do nothing)");
        Serial.print("  ");
        digitalWrite(13, LOW);   // 熄滅 LED & 停止幫浦馬達
        delay(1000);             // 熄滅 1 秒 (1000 ms)
      }
      break;
    } //Switch
    Serial.println("  ");
  } //while
}

