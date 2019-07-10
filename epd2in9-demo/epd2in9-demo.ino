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
  time_start_ms = millis();
}

void loop() {

  
  // put your main code here, to run repeatedly:
  time_now_s = (millis() - time_start_ms) / 1000;
  char time_string[] = {'0', '0', ':', '0', '0', '\0'};
  char time_string2[] = {'0', '0', ':', '0', '0', '\0'};

  time_string[4] = time_now_s % 60 % 10 + '0';
  
  if(time_string[4]=='0'){
    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();
    epd.ClearFrameMemory(0xFF);   // bit set = white, bit reset = black
    epd.DisplayFrame();
    x=random(180);
    delay(500);
  }
  time_string[0] = time_now_s / 60 / 10 + '0';
  time_string[1] = time_now_s / 60 % 10 + '0';
  time_string[3] = time_now_s % 60 / 10 + '0';
  time_string[4] = time_now_s % 60 % 10 + '0';

  time_string2[0] = time_now_s / 60 / 10 /60 + '0';
  time_string2[1] = time_now_s / 60 /60 % 10 + '0';
  time_string2[3] = time_now_s / 60 / 10 + '0';
  time_string2[4] = time_now_s / 60 % 10 + '0';
if(time_string2[3]!=time_string2_temp[3]||time_string2[4]!=time_string2_temp[4]){
  paint.SetWidth(80);
  paint.SetHeight(200);
  paint.SetRotate(ROTATE_90);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, time_string2, &ClearSans48 ,COLORED);
  epd.SetFrameMemory(paint.GetImage(), 40, 0, paint.GetWidth(), paint.GetHeight());

  times=times+1;
  if(times%2==0){
  time_string2_temp[3]=time_string2[3];
  time_string2_temp[4]=time_string2[4];
  
  }
 
  
}


  paint.SetWidth(30);
  paint.SetHeight(100);
  paint.SetRotate(ROTATE_90);

  paint.Clear(UNCOLORED);
  paint.DrawStringAt(0, 4, time_string, &Font24 ,COLORED);
  epd.SetFrameMemory(paint.GetImage(), 0, 100, paint.GetWidth(), paint.GetHeight());
  
  epd.DisplayFrame();

  delay(500);
}
