/*
Script for displaying the P&F screensaver on a 128x32 OLED display

Created by P&F, January 2024
*/

#include <SPI.h>
#include <U8g2lib.h>

// https://github.com/olikraus/u8g2/wiki/u8g2reference
U8G2_SSD1306_128X32_UNIVISION_1_SW_I2C u8g2(U8G2_R0, 0, 1);

// initial position and direction
int x_pos = -15;
int y_pos = -15;
int x_direction = 1;
int y_direction = 1;

// bitmap with P&F logo (created on https://xbm.jazzychad.net/)
static unsigned char logo_zw[] = {
 0x0f,0xf0,0xf7,0xef,0xfb,0xdf,0xfd,0xbf,0xc6,0x47,0xd6,0x77,
 0xc6,0x77,0xf6,0x67,0xf6,0x77,0xd6,0x77,0xa6,0x77,0x56,0x77,
 0x25,0xb6,0x6b,0xdf,0x97,0xee,0x0f,0xf0};

// inverted bitmap (just for fun)
static unsigned char logo_wz[] = {
 0xf0,0x0f,0x09,0x10,0x04,0x20,0x02,0x40,0x39,0xb8,0x29,0x88,
 0x39,0x88,0x09,0x98,0x09,0x88,0x29,0x88,0x59,0x88,0xa9,0x88,
 0xda,0x49,0x94,0x20,0x68,0x11,0xf0,0x0f};

void setup(void) {
  u8g2.begin();
}

void draw(void) {
  u8g2.drawXBM( x_pos, y_pos, 16, 16, logo_zw); 
}

void loop(void) {
  // picture loop
  u8g2.firstPage();  
  do {
    draw();
  } while( u8g2.nextPage() );
  
  // change direction near boundaries
  if (x_pos <= 1){
    x_direction = 1; 
  }
  if (y_pos <= 1){
    y_direction = 1; 
  }
  if (x_pos >= 112){
      x_direction = 0;
  };
  if (y_pos >= 16){
      y_direction = 0;
  };

  // move one step in x and y direction
  if (x_direction == 1){
    x_pos++;
  } else {
    x_pos--;
  };
  if (y_direction == 1){
    y_pos++;
  } else {
    y_pos--;
  };

  // rebuild the picture after some delay
  delay(30);
}

