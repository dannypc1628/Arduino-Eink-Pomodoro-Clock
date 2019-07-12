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

#include <SPI.h>
#include "epd2in9.h"
#include "epdpaint.h"


#define COLORED     0
#define UNCOLORED   1

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
char time_string2_temp[]= {'0', '0', ':', ':', ':', '\0'};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (epd.Init(lut_full_update) != 0) {
      Serial.print("e-Paper init failed");
      return;
  }

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

//  paint.SetRotate(ROTATE_90);
//  paint.SetWidth(12);
//  paint.SetHeight(64);
//
//  /* For simplicity, the arguments are explicit numerical coordinates */
//  paint.Clear(COLORED);
//  paint.DrawStringAt(0, 4, "Hello world!", &Font16, COLORED);
//  epd.SetFrameMemory(paint.GetImage(), 0, 10, paint.GetWidth(), paint.GetHeight());
//  epd.DisplayFrame();
//  delay(1500);
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

epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
epd.DisplayFrame();
epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
epd.DisplayFrame();

epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
epd.DisplayFrame();
epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
epd.DisplayFrame();
delay(500);
time_start_ms = millis();
}

void loop() {

  
  // put your main code here, to run repeatedly:
  time_now_s = (millis() - time_start_ms) / 1000;
  char time_string[] = {'7', '7', 'A', '7', '7', '\0'};
  char time_string2[] = {'!', '!', '+', '!', '!', '\0'};
  char year_time_string2[] = {'9', '6', '8', '?', ' ', '=','!','8','8','"',',',')'};

  time_string[4] = time_now_s % 60 % 10 + '0';
  
//  if(time_string[4]=='0'){
//    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
//    epd.DisplayFrame();
//    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
//    epd.DisplayFrame();
//    x=random(180);
//    delay(500);
//  }
  time_string[0] = time_now_s / 60 / 10 + '7';
  time_string[1] = time_now_s / 60 % 10 + '7';
  time_string[3] = time_now_s % 60 / 10 + '7';
  time_string[4] = time_now_s % 60 % 10 + '7';

  time_string2[0] = time_now_s / 60 / 10 /60 + '!';
  time_string2[1] = time_now_s / 60 /60 % 10 + '!';
  time_string2[3] = time_now_s / 60 / 10 + '!';
  time_string2[4] = time_now_s / 60 % 10 + '!';

  
if(time_string2[3]!=time_string2_temp[3]||time_string2[4]!=time_string2_temp[4]){
  paint.SetWidth(70);
  paint.SetHeight(225);
  paint.SetRotate(ROTATE_90);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, time_string2, &TaipeiSansN48 ,COLORED);
  epd.SetFrameMemory(paint.GetImage(), 60, 0, paint.GetWidth(), paint.GetHeight());

  paint.SetWidth(30);
  paint.SetHeight(290);
  paint.SetRotate(ROTATE_90);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, year_time_string2, &TaipeiSans18 ,COLORED);
  epd.SetFrameMemory(paint.GetImage(), 37, 0, paint.GetWidth(), paint.GetHeight());
  epd.DisplayFrame();
  times=times+1;
  if(times%3==0){
    times=1;
  time_string2_temp[3]=time_string2[3];
  time_string2_temp[4]=time_string2[4];
  
  }
 
  
}

  int second,minute,hour,date,month,year,temperature; 
  second=Clock.getSecond();
  minute=Clock.getMinute();
  h12=true;
  hour=Clock.getHour(h12, PM);
  wek=Clock.getDoW();
  date=Clock.getDate();
  month=Clock.getMonth(Century);
  year=Clock.getYear();

  
  paint.SetWidth(30);
  paint.SetHeight(150);
  paint.SetRotate(ROTATE_90);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, time_string, &TaipeiSans18 ,COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 120, paint.GetWidth(), paint.GetHeight());
  
  epd.DisplayFrame();

  delay(500);
}

void pTimer(int setMinute){
  char time_string[] = {'0', '0', ':', '0', '0', '\0'};
  int minute , second;
  int minute_units_digit , minute_tens_digit; 
  int second_units_digit , second_tens_digit; 

  minute=Clock.getSecond();
  second=Clock.getSecond();
  
  if(hour>9){
    hour_tens_digit = hour/10; 
    hour_units_digit = hour%10;
  }
  else{
    hour_tens_digit = 0; 
    hour_units_digit = hour%10;
  }
 
  time_string2[0] = hour_tens_digit + '0';
  time_string2[1] = hour_units_digit + '0';
  time_string2[3] = second_tens_digit + '0';
  time_string2[4] = second_units_digit + '0';
  
  paint.SetWidth(70);
  paint.SetHeight(225);
  paint.SetRotate(ROTATE_90);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, time_string2, &TaipeiSansN48 ,COLORED);
  epd.SetFrameMemory(paint.GetImage(), 60, 0, paint.GetWidth(), paint.GetHeight());
}
void pClock(){
  char time_string[] = {'0', '0', ':', '0', '0', '\0'};
  int minute , hour;
  int hour_units_digit , hour_tens_digit; 
  int minute_units_digit , minute_tens_digit; 
  
  hour=Clock.getHour(false, false);
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
  time_string2[0] = hour_tens_digit + '0';
  time_string2[1] = hour_units_digit + '0';
  time_string2[3] = minute_tens_digit + '0';
  time_string2[4] = minute_units_digit + '0';
  
  paint.SetWidth(70);
  paint.SetHeight(225);
  paint.SetRotate(ROTATE_90);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, time_string2, &TaipeiSansN48 ,COLORED);
  epd.SetFrameMemory(paint.GetImage(), 60, 0, paint.GetWidth(), paint.GetHeight());
}
void pToDay(){
  String year_string="";
  String month_string="";
  String date_string="";
  String concat_string="";
  int year , month , date;
  
  year=Clock.getYear();
  year_string ="20" +String.valueOf(year)+"年";

  month=Clock.getMonth(Century);
  month_string = String.valueOf(month)+"月";
   
  date=Clock.getDate();
  date_string = String.valueOf(date)+"日";

  concat_string = year_string + month_string + date_string;
  char char_string[concat_string.length()+1];
  concat_string.toCherArry(char_string,concat_string.length()+1);

  paint.SetWidth(70);
  paint.SetHeight(225);
  paint.SetRotate(ROTATE_90);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, concat_string, &TaipeiSansN48 ,COLORED);
  epd.SetFrameMemory(paint.GetImage(), 60, 0, paint.GetWidth(), paint.GetHeight());
}
void pAMPM(){
  }
  
char getFont48Char(char input){
  char output='';

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
      output=',';
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
  char output='';

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
    case 'A':
      output='B';
      break;
    case 'P':
      output='C';
      break;
    case 'M':
      output='D';
      break;
  }

  return output;
}
