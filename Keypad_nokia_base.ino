#include <Keypad.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

/*
wiring is as such:

TFT SCREEN:
VCC --> 5v
GND --> GND
CS --> D9
RESET --> -1
A0 --> D8
SDA --> D11
SCK --> D13
LED --> 3V3

KEYPAD:
1- D4
2- D5
3- D6
4- D7
5- A0
6- A1
7- A2
8- A3


*/
#define TFT_CS 9
#define TFT_RST -1  // Or set to -1 and connect to Arduino RESET pin
#define TFT_DC 8


char hexaKeys[4][4] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

char heldKeys[12][4] = {
  { 'a', 'b', 'c', 'd' },  //1
  { 'e', 'f', 'g', 'h' },  //2
  { 'i', 'j', 'k', 'l' },  //3
  { 'm', 'n', 'o', 'p' },  //A
  { 'q', 'r', 's', 't' },  //4
  { 'u', 'v', 'w', 'x' },  //5
  { 'y', 'z', '0', '1' },  //6
  { '2', '3', '4', '5' },  //B
  { '6', '7', '8', '9' },  //7
  { ' ', '.', '!', '?' },  //8
  { '(', ')', '<', '>' },  //9
  { ',', '-', '+', '*' },  //C
};
char keys[16] = { '1', '2', '3', 'A', '4', '5', '6', 'B', '7', '8', '9', 'C', '*', '0', '#', 'D' };

byte rowPins[4] = { 4, 5, 6, 7 };
byte colPins[4] = { A0, A1, A2, A3 };

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, 4, 4);
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

int currX = 0;
int currY = 0;
int x = 0;
int y = 0;

char currentKey;

void setup() {
  tft.initR(INITR_144GREENTAB);
  tft.fillScreen(ST77XX_BLACK);
  Serial.begin(9600);
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    if(customKey == '*'){
      //Empty func
    }else if(customKey == '0'){
      x+=6;
    }else if(customKey == '#'){
      x+=6;
      tft.fillRect(x, y, -7, 8, ST77XX_BLACK);
      x-=12;
      if(x < 0){x=0;}
      tft.setCursor(x, y);
    }else if(customKey == 'D'){
      y+=8;
      x=0;
      tft.setCursor(x, y);
    }else {
      Serial.println(customKey);
      if (customKey == currentKey) {
        if(currY < 3){
          currY++;

        }else{
          currY = 0;
        }
        tft.fillRect(x, y, 6, 8, ST77XX_BLACK);
        tft.setCursor(x, y);
        tft.write(heldKeys[currX][currY]); 
      }else {
          for(int i = 0; i < 12; i++){
            if(customKey == keys[i]){
              currentKey = customKey;
              Serial.println(i);
              currX = i;
              currY = 0;
              x+=6;
              tft.fillRect(x, y, 6, 8, ST77XX_BLACK);
              tft.setCursor(x, y);
              tft.write(heldKeys[currX][currY]);
              break;
            }
          }
          
     
        }
    }
  }
}
