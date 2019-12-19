#include "Button.h"

Button *shortBtn;
Button *longBtn;


void setup() {
  Serial.begin(9600);
  
  shortBtn = new Button(4, onShortPress, 5);
  longBtn = new Button(5, onShortPress, 5, onLongPress, 1111);
}

void loop() {
  shortBtn->doTheThing();
  longBtn->doTheThing();
  Serial.println(0);
}

void onShortPress(){
  Serial.println(5);
}

void onLongPress(){
  Serial.println(10);
}
