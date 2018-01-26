#include <IRremote.h>
#include "pitches.h"
#include <stdio.h>
#include <Wire.h>  
#include <Arduino.h>
#include <U8x8lib.h>
#ifdef U8X8_HAVE_HW_SPI 
#include <SPI.h>
#endif
#define motor1pin1 4                              //定义IN1引脚
#define motor1pin2 5                              //定义IN2引脚
#define motor1pwm 9                             //定义ENA引脚
int RECV_PIN = 11;//定义红外接收器的引脚为11
IRrecv irrecv(RECV_PIN);
decode_results results;  
#include "pitches.h"
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };
unsigned long time;
unsigned long dingshi;
int s_flag=0;
int g_flag=0;
int st_flag=0;
int on_flag=0;
int led_flag=0;
int s=0;
int led = 12;
int bili =8;
unsigned long time2;
unsigned long last_time;
unsigned long t;
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 6, /* data=*/ 7, /* reset=*/ U8X8_PIN_NONE);   // OLEDs without Reset of the Display

void setup()
{
  pinMode(12,OUTPUT);
  pinMode(8,OUTPUT);
   digitalWrite(8,LOW);
  digitalWrite(12,LOW);
   Serial.begin(9600);
   irrecv.enableIRIn(); // 初始化红外接收器
  u8x8.begin();
  u8x8.setPowerSave(0); 
  u8x8.setFont(u8x8_font_amstrad_cpc_extended_r);
    u8x8.draw2x2String(3, 3, "Fisher");
    u8x8.drawString(5, 7, "make by p&z");
   for (int i = 0; i <4; i++) 
   {
    int noteDuration = 1000/noteDurations[i];
    newtone(8,melody[i],noteDuration);
    int y = noteDuration * 1.30;
    delay(y);
    newtone(8,0,0);
  }
Serial.print(123);
}
///////////////////////////////////////////////////
void newtone(byte tonePin, int frequency, int duration) {
int period = 1000000L / frequency;
int pulse = period / 2;
for (long i = 0; i < duration * 1000L; i += period) {
digitalWrite(tonePin, HIGH);
delayMicroseconds(pulse);
digitalWrite(tonePin, LOW);
delayMicroseconds(pulse);
}
}
void kaijimusic()
{
  digitalWrite(8,HIGH);
  delay(500);
  digitalWrite(8,LOW); 
  }
void bilibili()
{
   digitalWrite(8,HIGH);
   delay(500);
   digitalWrite(8,LOW);
  }
void saomiao()
{
  //////////////////
 if (irrecv.decode(&results)) 
  {
    Serial.println(results.value);
    irrecv.resume(); // 接收下一个值 
     switch(results.value)
   {
     case 16753245://开机按钮
    {
      bilibili();
      if (on_flag==0){
        u8x8.clear();
    u8x8.draw2x2String(6, 5, "ON");
    u8x8.draw2x2String(3, 2, "Fisher");
    last_time=0;
    motor(motor1pin1,motor1pin2,motor1pwm,100);
    on_flag=1;
     }
     else
     {
      on_flag=0;
       u8x8.clear();
       u8x8.draw2x2String(3, 2, "Fisher");
       u8x8.draw2x2String(5, 5, "OFF");
      motor(motor1pin1,motor1pin2,motor1pwm,0);
      }
    }
    break;
    case 16769565:
    {
      bilibili();
    u8x8.clear();
      u8x8.draw2x2String(2, 3, "Setting");
      motor(motor1pin1,motor1pin2,motor1pwm,0);
       st_flag=1;
       s=0; 
        }
        break;
     case 16736925:         //上led
     {
      bilibili();
if (led_flag==0){
        u8x8.clear();
    u8x8.draw2x2String(2, 5, "LED_ON");
    u8x8.draw2x2String(3, 2, "Fisher");
    digitalWrite(12,HIGH);
    led_flag=1;
     }
     else
     {
      led_flag=0;
       u8x8.clear();
       u8x8.draw2x2String(3, 2, "Fisher");
       u8x8.draw2x2String(2, 5, "LED_OFF");
       digitalWrite(12,LOW);
      }


      
      }
      break;
     case 16738455:   //1
     {
      bilibili();

     if(st_flag==1)
     {
       u8x8.clear();
      u8x8.draw2x2String(5, 5, "1");
      if(s>=10)
      {
      s=s+1;
      g_flag=1;
      }
      else
      {
      s=10*1;
      s_flag=1;
      }
      }
      else
      { 
   u8x8.clear();
      u8x8.draw2x2String(2, 2, "Please");
      u8x8.draw2x2String(4, 5, "set!");
        }
      }   
      break;  
      ////////////////////////////
           case 16750695:   //2
     {
      bilibili();
     if(st_flag==1)
     {
          u8x8.clear();
      u8x8.draw2x2String(5, 5, "2");
      if(s>=10)
      {
      s=s+2;
      g_flag=1;
      }
      else
      {
      s=10*2;
      s_flag=1;
      }
      }
      else
      {
   u8x8.clear();
      u8x8.draw2x2String(2, 2, "Please");
      u8x8.draw2x2String(4, 5, "set!");
        }
      }      
      break;
      case 16756815:   //3
     {
bilibili();
     if(st_flag==1)
     {
       u8x8.clear();
      u8x8.draw2x2String(5, 5, "3");
      if(s>=10)
      {
      s=s+3;
      g_flag=1;
      }
      else
      {
      s=10*3;
      s_flag=1;
      }
      }
      else
      { 
   u8x8.clear();
      u8x8.draw2x2String(2, 2, "Please");
      u8x8.draw2x2String(4, 5, "set!");
        }
      }   
      break; 
      case 16724175:   //4
     {
bilibili();
     if(st_flag==1)
     {
       u8x8.clear();
      u8x8.draw2x2String(5, 5, "4");
      if(s>=10)
      {
      s=s+4;
      g_flag=1;
      }
      else
      {
      s=10*4;
      s_flag=1;
      }
      }
      else
      { 
   u8x8.clear();
      u8x8.draw2x2String(2, 2, "Please");
      u8x8.draw2x2String(4, 5, "set!");
        }
      }   
      break; 
      case 16718055:   //5
     {
bilibili();
     if(st_flag==1)
     {
       u8x8.clear();
      u8x8.draw2x2String(5, 5, "5");
      if(s>=10)
      {
      s=s+5;
      g_flag=1;
      }
      else
      {
      s=10*5;
      s_flag=1;
      }
      }
      else
      { 
   u8x8.clear();
      u8x8.draw2x2String(2, 2, "Please");
      u8x8.draw2x2String(4, 5, "set!");
        }
      }   
      break; 
      case 16743045:   //6
     {
bilibili();
     if(st_flag==1)
     {
       u8x8.clear();
      u8x8.draw2x2String(5, 5, "6");
      if(s>=10)
      {
      s=s+6;
      g_flag=1;
      }
      else
      {
      s=10*6;
      s_flag=1;
      }
      }
      else
      { 
   u8x8.clear();
      u8x8.draw2x2String(2, 2, "Please");
      u8x8.draw2x2String(4, 5, "set!");
        }
      }   
      break; 
      case 16716015:   //7
     {
bilibili();
     if(st_flag==1)
     {
       u8x8.clear();
      u8x8.draw2x2String(5, 5, "7");
      if(s>=10)
      {
      s=s+7;
      g_flag=1;
      }
      else
      {
      s=10*7;
      s_flag=1;
      }
      }
      else
      { 
   u8x8.clear();
      u8x8.draw2x2String(2, 2, "Please");
      u8x8.draw2x2String(4, 5, "set!");
        }
      }   
      break; 
      case 16726215:   //8
     {
bilibili();
     if(st_flag==1)
     {
       u8x8.clear();
      u8x8.draw2x2String(5, 5, "8");
      if(s>=10)
      {
      s=s+8;
      g_flag=1;
      }
      else
      {
      s=10*8;
      s_flag=1;
      }
      }
      else
      { 
    u8x8.clear();
      u8x8.draw2x2String(2, 2, "Please");
      u8x8.draw2x2String(4, 5, "set!");
        }
      }   
      break; 
      case 16734885:   //9
     {
bilibili();
     if(st_flag==1)
     {
       u8x8.clear();
      u8x8.draw2x2String(5, 5, "9");
      if(s>=10)
      {
      s=s+9;
      g_flag=1;
      }
      else
      {
      s=10*9;
      s_flag=1;
      }
      }
      else
      { 
    u8x8.clear();
      u8x8.draw2x2String(2, 2, "Please");
      u8x8.draw2x2String(4, 5, "set!");
        }
      }   
      break; 
      case 16728765:   //0
     {
bilibili();
     if(st_flag==1)
     {
       u8x8.clear();
      u8x8.draw2x2String(5, 5, "0");
      if(s>=10)
      {
      s=s+0;
      g_flag=1;
      }
      else
      {
      s=10*0;
      s_flag=1;
      }
      }
      else
      { 
    u8x8.clear();
      u8x8.draw2x2String(2, 5, "please.set!");
        }
      }   
      break; 
      ///////////////////
      case   16732845://fasong
{
  bilibili();
  if(s_flag==1 && g_flag==1)
  {
 u8x8.setCursor(0,2);
 u8x8.print("Input time:");
 u8x8.setCursor(12,2);
 u8x8.print(s);
  u8x8.setCursor(15,2);
 u8x8.print("m");
 s_flag=0;
 g_flag=0;
 st_flag=0;
  }
  else
  {
 s=s/10;
 u8x8.setCursor(0,2);
 u8x8.print("Input time:");
 u8x8.setCursor(12,2);
 u8x8.print(s);
  u8x8.setCursor(15,2);
 u8x8.print("m");
 s_flag=0;
 g_flag=0;
 st_flag=0; 
    }
   t=s*60000;
   time = millis();
   last_time=time+t;
  }
      break;

   }   
      }
//////////////////////
  }   
  void motor(int motorpin1,int motorpin2,int motorpwm,int val)  //定义一个电机转动函数
{
pinMode(motorpin1,OUTPUT);                              //输出第一个引脚
pinMode(motorpin2,OUTPUT);                             //输出第二个引脚
digitalWrite(motorpin2,0);                                    //将第二个引脚置低
digitalWrite(motorpin1,1);                                     //将第一个引脚抬高
analogWrite(motorpwm,val);                                //给EN引脚设定模拟值，设定转速
}
  void yunxing()
  {
  time2=millis();
  Serial.print(time2);
  Serial.print("enen");
  Serial.println(last_time);
   if(time2>last_time && last_time!=0)
   {
    Serial.println("dawo66666666666666666666666666666");
    motor(motor1pin1,motor1pin2,motor1pwm,100);      
    delay(2000);
    motor(motor1pin1,motor1pin2,motor1pwm,0);  
   time = millis();
   last_time=time+t;
    }
    else
    {
      //Serial.println("wait");    
      } 
    }
void loop() {
saomiao();
yunxing();
}


