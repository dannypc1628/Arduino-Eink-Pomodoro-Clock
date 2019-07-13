/**
 *  @filename   :   epd2in9-demo.ino
 *  @brief      :   2.9inch e-paper display demo
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     September 9 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "DS3231.h"
#include <Wire.h>
#include <SPI.h>
#include "epd2in9.h"
#include "epdpaint.h"


#define COLORED     0
#define UNCOLORED   1

DS3231 Clock;
/**
  * Due to RAM not enough in Arduino UNO, a frame buffer is not allowed.
  * In this case, a smaller image buffer is allocated and you have to 
  * update a partial display several times.
  * 1 byte = 8 pixels, therefore you have to set 8*N pixels at a time.
  */
unsigned char image[1024];
Paint paint(image, 0, 0);    // width should be the multiple of 8 
Epd epd;
unsigned long time_start_ms;
unsigned long time_now_s;
int x=0;
int times=0;
int lastMinute=0;

bool h12=true;
bool PM;
bool Century=false;
const int t25pin=5;
const int t10pin=6;

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  if (epd.Init(lut_full_update) != 0) {
      Serial.print("e-Paper init failed");
      return;
  }

pinMode(t25pin,INPUT);
pinMode(t10pin,INPUT);
  /** 
   *  there are 2 memory areas embedded in the e-paper display
   *  and once the display is refreshed, the memory area will be auto-toggled,
   *  i.e. the next action of SetFrameMemory will set the other memory area
   *  therefore you have to clear the frame memory twice.
   */
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();

  paint.SetRotate(ROTATE_90);
  paint.SetWidth(30);
  paint.SetHeight(90);

  /* For simplicity, the arguments are explicit numerical coordinates */
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, "Hello world!", &TaipeiSans18, COLORED);
  epd.SetFrameMemory(paint.GetImage(), 30, 10, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  delay(3000);
//  
//  
//  paint.Clear(UNCOLORED);
//  paint.DrawStringAt(0, 4, "e-Paper Demo", &Font16, COLORED);
//  epd.SetFrameMemory(paint.GetImage(), 0, 30, paint.GetWidth(), paint.GetHeight());
//  epd.DisplayFrame();
//  delay(1500);
//
//  paint.SetWidth(64);
//  paint.SetHeight(64);
//  
//  paint.Clear(UNCOLORED);
//  paint.DrawRectangle(0, 0, 40, 50, COLORED);
//  paint.DrawLine(0, 0, 40, 50, COLORED);
//  paint.DrawLine(40, 0, 0, 50, COLORED);
//  epd.SetFrameMemory(paint.GetImage(), 16, 60, paint.GetWidth(), paint.GetHeight());
//  delay(1500);
//
//  paint.Clear(UNCOLORED);
//  paint.DrawCircle(32, 32, 30, COLORED);
//  epd.SetFrameMemory(paint.GetImage(), 72, 60, paint.GetWidth(), paint.GetHeight());
//  delay(1500);
//
//  paint.Clear(UNCOLORED);
//  paint.DrawFilledRectangle(0, 0, 40, 50, COLORED);
//  epd.SetFrameMemory(paint.GetImage(), 16, 130, paint.GetWidth(), paint.GetHeight());
//  delay(1500);
//  
//  paint.SetWidth(64);
//  paint.SetHeight(64);
//  paint.Clear(UNCOLORED);
//  paint.DrawFilledCircle(32, 32, 30, COLORED);
//  epd.SetFrameMemory(paint.GetImage(), 72, 130, paint.GetWidth(), paint.GetHeight());
//  epd.DisplayFrame();
//
//  delay(2000);

  if (epd.Init(lut_partial_update) != 0) {
      Serial.print("e-Paper init failed");
      return;
  }

  /** 
   *  there are 2 memory areas embedded in the e-paper display
   *  and once the display is refreshed, the memory area will be auto-toggled,
   *  i.e. the next action of SetFrameMemory will set the other memory area
   *  therefore you have to set the frame memory and refresh the display twice.
   */
//  epd.SetFrameMemory(IMAGE_DATA);
//  epd.DisplayFrame();
//  epd.SetFrameMemory(IMAGE_DATA2);
//  epd.DisplayFrame();
//
//epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
//epd.DisplayFrame();
//epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
//epd.DisplayFrame();
//
epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
epd.DisplayFrame();
delay(500);

epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
epd.DisplayFrame();
delay(500);

}

void loop() {
//int second,minute,hour,date,month,year,temperature; 
//  second=Clock.getSecond();
//  minute=Clock.getMinute();
//  h12=true;
//  hour=Clock.getHour(h12, PM);
//
//  date=Clock.getDate();
//  month=Clock.getMonth(Century);
//  year=Clock.getYear();
//  
//  //temperature=Clock.getTemperature();
//  
//  Serial.print("20");
//  Serial.print(year,DEC);
//  Serial.print('-');
//  Serial.print(month,DEC);
//  Serial.print('-');
//  Serial.print(date,DEC);
//  Serial.print(' ');
//
//  Serial.print(' ');
//  Serial.print(hour,DEC);  
//  Serial.print(' ');
//    if (h12) {
//    if (PM) {
//      Serial.print(" PM ");
//    } else {
//      Serial.print(" AM ");
//    }
//  } else {
//    Serial.print(" 24h ");
//  }
//  Serial.print(minute,DEC);
//  Serial.print(':');
//  Serial.print(second,DEC);
//  Serial.print('\n');
//  //Serial.print("Temperature=");
//  //Serial.print(temperature); 
//  Serial.print('\n');
//  
//  Serial.print("pTimer");
//  Serial.print('\n');

  Serial.print("wait to getSecond()");
  Serial.print("\n");
  int sec =Clock.getSecond();
  Serial.print("Second  is ");
  Serial.print( sec,DEC);
  Serial.print("\n");

  int val25 = digitalRead(t25pin);
  int val10 = digitalRead(t10pin);
  if(val25 ==HIGH){
    pTimer(25);
  }
  if(val10==HIGH){
    pTimer(10);
  }
  else{
    pTimer(sec);
    }
  
  delay(500);

//pFont1();
//delay(3000);
//pFont2();

  Serial.print("pClock");
  Serial.print('\n');
  pClock();  
  //delay(1000);
  
  Serial.print("pToDay");
  Serial.print('\n');
  pToDay();
//  
  //delay(1000);
}

 

void pTimer(int setMinute){
  char time_string[] = {'0', '0', ':', '0', '0', '\0'};
 
  int minute_units_digit , minute_tens_digit; 

  if(setMinute>9){
    minute_tens_digit = setMinute/10; 
    minute_units_digit = setMinute%10;
  }
  else{
    minute_tens_digit = 0; 
    minute_units_digit = setMinute%10;
  }
 
  time_string[0] = minute_tens_digit + '0';
  time_string[1] = minute_units_digit + '0';
  time_string[3] =  '0';
  time_string[4] =  '0';
  Serial.print("inside "+ String(time_string));
  for(int i =0 ;i<5;i++){
    time_string[i]= getFont18Char(time_string[i]);
  }
  
  paint.SetWidth(30);
  paint.SetHeight(125);
  paint.SetRotate(ROTATE_90);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, time_string, &TaipeiSans18 ,COLORED);
  Serial.print("SetFrameMemory");
  epd.SetFrameMemory(paint.GetImage(), 0, 180, paint.GetWidth(), paint.GetHeight());
  Serial.print("DisplayFrame");
  epd.DisplayFrame();
  Serial.print("Finish");
}
//void pFont1(){
//  char st[]={' ','!','"','#','$','%','&','\'','(','\0'};
//  paint.SetWidth(30);
//  paint.SetHeight(290);
//  paint.SetRotate(ROTATE_90);
//
//  paint.Clear(UNCOLORED);
//  paint.DrawStringAt(0, 4, st, &TaipeiSans18 ,COLORED);
//  epd.SetFrameMemory(paint.GetImage(), 60, 0, paint.GetWidth(), paint.GetHeight());
//  epd.DisplayFrame();
//}
//void pFont2(){
//  char st[]={'年','月','日','時','分','秒','上','\0'};
//  for(int i =0 ;i<3;i++){
//    st[i]= getFont18Char(st[i]);
//  }
//  
//  paint.SetWidth(60);
//  paint.SetHeight(200);
//  paint.SetRotate(ROTATE_90);
//
//  paint.Clear(UNCOLORED);
//  paint.DrawStringAt(0, 4, st, &TaipeiSans18 ,COLORED);
//  epd.SetFrameMemory(paint.GetImage(), 80, 0, paint.GetWidth(), paint.GetHeight());
//  epd.DisplayFrame();
//}
void pClock(){
  char time_string[] = {'0', '0', ':', '0', '0', '\0'};
  int minute , hour;
  int hour_units_digit , hour_tens_digit; 
  int minute_units_digit , minute_tens_digit; 
  
  
  hour=Clock.getHour(h12, PM);
  minute=Clock.getMinute();


  
  if(hour>9){
    hour_tens_digit = hour/10; 
    hour_units_digit = hour%10;
  }
  else{
    hour_tens_digit = 0; 
    hour_units_digit = hour%10;
  }
  if(minute>9){
    minute_tens_digit = minute/10; 
    minute_units_digit = minute%10;
  }
  else{
    minute_tens_digit = 0; 
    minute_units_digit = minute%10;
  }
  time_string[0] = hour_tens_digit + '0';
  time_string[1] = hour_units_digit + '0';
  time_string[3] = minute_tens_digit + '0';
  time_string[4] = minute_units_digit + '0';
  Serial.print("clock is  "+ String(time_string));
//  for(int i =0 ;i<5;i++){
//    time_string[i]= getFont48Char(time_string[i]);
//  }
  
  paint.SetWidth(40);
  paint.SetHeight(150);
  paint.SetRotate(ROTATE_90);
   Serial.print("pclock  ROTATE_90");
  Serial.print('\n');
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, time_string, &Font24 ,COLORED);
  
if(minute!=lastMinute){
    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();
    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();

    epd.SetFrameMemory(paint.GetImage(), 80, 0, paint.GetWidth(), paint.GetHeight());
   
    epd.DisplayFrame();
        epd.SetFrameMemory(paint.GetImage(), 80, 0, paint.GetWidth(), paint.GetHeight());
   
    epd.DisplayFrame();
    lastMinute=minute;
}
  
 // epd.DisplayFrame();
}
void pToDay(){
  String year_string="";
  String month_string="";
  String date_string="";
  String concat_string="";
  int year , month , date;

    Serial.print("pToDay  1");
  Serial.print('\n');
  
  year=Clock.getYear();
  year_string ="20"+String(year)+" ";//年
  Serial.print("pToDay 2  get year is ");
  Serial.print(year_string);
  Serial.print("\n");
  month=Clock.getMonth(Century);
  month_string = String(month)+"!";//月
   
  date=Clock.getDate();
  date_string = String(date)+"\"";//日
  Serial.print("pToDay  3");
  Serial.print('\n');
  concat_string = year_string + month_string + date_string;
  
  int len=concat_string.length()+1;
  char char_string[len];
    Serial.print("pToDay  4");
  Serial.print('\n');
  concat_string.toCharArray(char_string,len);
  
//  Serial.print("\n");
//  Serial.print(concat_string);
  for(int i=0;i<len-1;i++){
    if(char_string[i]>='0'){
      char_string[i]=getFont18Char(char_string[i]);
    }
  }
//  Serial.print("字元轉換 \n");
//  Serial.print(char_string);
//  Serial.print("\n");
    Serial.print("pToDay  5");
  Serial.print('\n');
  paint.SetWidth(30);
  paint.SetHeight(250);
  paint.SetRotate(ROTATE_90);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, char_string, &TaipeiSans18 ,COLORED);
  epd.SetFrameMemory(paint.GetImage(), 30, 0, paint.GetWidth(), paint.GetHeight());
  //epd.DisplayFrame();
}
void pAMPM(){
  }
  
char getFont48Char(char input){
  char output=' ';

  switch(input){

    case '/':
      output=' ';
      break;
    case '0':
      output='!';
      break;
    case '1':
      output='"';
      break;
    case '2':
      output='#';
      break;
    case '3':
      output='$';
      break;
    case '4':
      output='%';
      break;
    case '5':
      output='&';
      break;
    case '6':
      output='\'';
      break;
    case '7':
      output='(';
      break;
    case '8':
      output=')';
      break;
    case '9':
      output='*';
      break;
    case ':':
      output='+';
      break;

  }

  return output;
}

  
char getFont18Char(char input){
  char output=' ';

  switch(input){

    case '年':
      output=' ';
      break;
    case '月':
      output='!';
      break;
    case '日':
      output='"';
      break;
    case '時':
      output='#';
      break;
    case '點':
      output='$';
      break;
    case '分':
      output='%';
      break;
    case '秒':
      output='&';
      break;
    case '上':
      output=',';
      break;
    case '下':
      output='(';
      break;
    case '午':
      output=')';
      break;
    case '星':
      output='*';
      break;
    case '期':
      output='+';
      break;

    case '一':
      output=',';
      break;
    case '二':
      output='-';
      break;
    case '三':
      output='.';
      break;
    case '四':
      output='/';
      break;
    case '五':
      output='0';
      break;
    case '六':
      output='1';
      break;
    case '日':
      output='2';
      break;
    case ' ':
      output='3';
      break;
    case '(':
      output='4';
      break;
    case ')':
      output='5';
      break;
    case '/':
      output='6';
      break;
    case '0':
      output='7';
      break;

    case '1':
      output='8';
      break;
    case '2':
      output='9';
      break;
    case '3':
      output=':';
      break;
    case '4':
      output=';';
      break;
    case '5':
      output='<';
      break;
    case '6':
      output='=';
      break;
    case '7':
      output='>';
      break;
    case '8':
      output='?';
      break;
    case '9':
      output='@';
      break;
    case ':':
      output='A';
      break;
    case '倒':
      output='B';
      break;
    case '數':
      output='C';
      break;
    case 'A':
      output='D';
      break;
    case 'P':
      output='E';
      break;
    case 'M':
      output='F';
      break;
  }

  return output;
}
