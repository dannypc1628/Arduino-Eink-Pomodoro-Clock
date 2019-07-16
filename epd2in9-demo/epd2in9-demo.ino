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
//unsigned long time_start_ms;
//unsigned long time_now_s;
int x=0;

int lastMinute=0;
int lastSecond=0;
int TimerSecond=0;

bool h12=true;
bool PM;
bool Century=false;
const int t25pin=4;
const int t10pin=5;
const int StopPin=6;
const int buzzerPin =12;

bool  setedTimer=false;
bool  goTimer = false;
int lastVal25=LOW;
int lastVal10=LOW;
int pushed=0;

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
  pinMode(buzzerPin, OUTPUT);
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

epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
epd.DisplayFrame();
delay(500);

epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
epd.DisplayFrame();
delay(500);

}

void loop() {


  Serial.print("wait to getSecond()");
  Serial.print("\n");
  int sec =Clock.getSecond();
  Serial.print("Second  is ");
  Serial.print( sec,DEC);
  Serial.print("\n");

  int val25 = digitalRead(t25pin);
  int val10 = digitalRead(t10pin);
  int Stoped = digitalRead(StopPin);
  if(Stoped==HIGH){
    goOrStop(false);
  }
  if(val25 ==HIGH){
     pushed=pushed+1;
     if(goTimer==true){
        goOrStop(false);
     }
     else{
      if(setedTimer==false){
       setTimer(25);
    }
        goOrStop(true);
     }
     if(pushed>3){
      setTimer(25);
      goOrStop(true);
      pushed=0;
     } 
    
  }
  if(val10 ==HIGH){
    pushed=pushed+1;
   if(goTimer==true){
      goOrStop(false);
   }
   else{
    if(setedTimer==false){
       setTimer(10);
    }
    goOrStop(true);
   }
   
    if(pushed>3){
      setTimer(10);
      goOrStop(true);
      pushed=0;
    } 
  }
  if(goTimer==true){
    goingTimer();
    showTimer();
    delay(500);
  }
  


  Serial.print("pClock");
  Serial.print('\n');
  pClock();  

}

 
void setTimer(int t){
  TimerSecond=t*60;
  setedTimer=true;
}

void goOrStop(bool go){
  if(go){
    lastSecond=Clock.getSecond();
    goTimer=true;
  }
  else{
    goTimer=false;
  }
  
}

void goingTimer(){
 int nowSec = Clock.getSecond();

 if(nowSec>lastSecond){
  TimerSecond =TimerSecond-(nowSec-lastSecond);
  lastSecond=nowSec;
 }
 if(nowSec<lastSecond){
  TimerSecond=TimerSecond-(60+nowSec-lastSecond);
  lastSecond=nowSec;
 }
}

void showTimer(){
   char time_string[] = {'F','G','0', '0', ':', '0', '0', '\0'};
    int minute_units_digit , minute_tens_digit;
    int second_units_digit , second_tens_digit;
    int m = TimerSecond/60;
    int sec = TimerSecond % 60;

  if(m>9){
    minute_tens_digit = m/10; 
    minute_units_digit = m%10;
  }
  else{
    minute_tens_digit = 0; 
    minute_units_digit = m%10;
  }

  if(sec>9){
    second_tens_digit = sec/10; 
    second_units_digit = sec%10;
  }
  else{
    second_tens_digit = 0; 
    second_units_digit = sec%10;
  }

  time_string[2] = minute_tens_digit + '0';
  time_string[3] = minute_units_digit + '0';
  time_string[5] =  second_tens_digit + '0';
  time_string[6] =  second_units_digit + '0';
  Serial.print("inside "+ String(time_string));

  
  paint.SetWidth(20);
  paint.SetHeight(112);
  paint.SetRotate(ROTATE_90);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, time_string, &MaruGothic12 ,COLORED);
  Serial.print("SetFrameMemory");
  epd.SetFrameMemory(paint.GetImage(), 0, 170, paint.GetWidth(), paint.GetHeight());
  Serial.print("DisplayFrame");
  epd.DisplayFrame();
  Serial.print("Finish");


  if(TimerSecond<=0){
    goOrStop(false);
    setedTimer=false;
    buzzer();
  }
}

void buzzer(){

  for (int i = 0;i < 1; i++) {
    tone(buzzerPin, 5474);
    delay(50);  
  }
  noTone(buzzerPin);
}

void pClock(){
  char time_string[] = {'0', '0', ':', '0', '0', '\0'};
  int minute , hour;
  int hour_units_digit , hour_tens_digit; 
  int minute_units_digit , minute_tens_digit; 
  
  h12=true;
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
  for(int i =0 ;i<5;i++){
    time_string[i]= getFont48Char(time_string[i]);
  }
  char time_string1 []={'0','0',':','\0'};
  time_string1[0]=time_string[0];
  time_string1[1]=time_string[1];
  time_string1[2]=time_string[2];
  
  paint.SetWidth(60);
  paint.SetHeight(120);
  paint.SetRotate(ROTATE_90);
   Serial.print("pclock  ROTATE_90");
  Serial.print('\n');
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, time_string1, &Genyog48 ,COLORED);
  
if(minute!=lastMinute){
  if(minute==0){
    buzzer();
  }
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();
 
  epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
  epd.DisplayFrame();


  epd.SetFrameMemory(paint.GetImage(), 60, 3, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
      
  epd.SetFrameMemory(paint.GetImage(), 60, 3, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  delay(300);
  
  char time_string2 []={'0','0','\0'};
  time_string2[0]=time_string[3];
  time_string2[1]=time_string[4];
  
  paint.SetWidth(60);
  paint.SetHeight(80);
  paint.SetRotate(ROTATE_90);
   Serial.print("pclock  ROTATE_90");
  Serial.print('\n');
  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, time_string2, &Genyog48 ,COLORED);
  
      
    epd.SetFrameMemory(paint.GetImage(), 60, 123, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();
    
    epd.SetFrameMemory(paint.GetImage(), 60, 123, paint.GetWidth(), paint.GetHeight());
    epd.DisplayFrame();

    delay(300);
    pToDay();
    delay(300);
    pToDay();
    lastMinute=minute;
}
  
 // epd.DisplayFrame();
}
void pToDay(){
  String year_string="";
  String month_string="";
  String date_string="";
  String wek_string="";
  String concat_string="";
  int year , month , date,wek;

  
  year=Clock.getYear();
  year_string ="20"+String(year)+"*";//年

  month=Clock.getMonth(Century);
  month_string = String(month)+"+";//月
   
  date=Clock.getDate();
  date_string = String(date)+",";//日


  wek =Clock.getDoW();
  
  wek_string = " >?"+String(char(wek+' '));
  
  concat_string = year_string + month_string + date_string + wek_string;
  Serial.print("pToDay ");
    Serial.print(concat_string);
  Serial.print('\n');
  
  
  int len=concat_string.length()+1;
  char char_string[len];
  
  concat_string.toCharArray(char_string,len);
 

  paint.SetWidth(18);
  paint.SetHeight(240);
  paint.SetRotate(ROTATE_90);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, char_string, &MaruGothic12 ,COLORED);
  epd.SetFrameMemory(paint.GetImage(), 30, 0, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
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
