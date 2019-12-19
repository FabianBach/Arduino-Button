#include "Button.h"

Button::Button(int pin, fptr singlePressCallback, int flickerDebounce){
  this->hasLongPress = false;
  this->pin = pin;
  pinMode(pin, INPUT_PULLUP);

  this->singlePressCallback = singlePressCallback;
  this->flickerDebounce = flickerDebounce;

  this->reset();
}

Button::Button(int pin, fptr singlePressCallback, int flickerDebounce, fptr longPressCallback, int longPressDuration){
  this->hasLongPress = true;
  this->pin = pin;
  pinMode(pin, INPUT_PULLUP);
  
  this->singlePressCallback = singlePressCallback;
  this->flickerDebounce = flickerDebounce;
  this->longPressCallback = longPressCallback;
  this->longPressDuration = longPressDuration;

  this->reset();
}

Button::~Button(){} // destructor

void Button::reset(){
  this->hasFired = false;
  this->pressDuration = 0;
  this->downStamp = 0;
}

void Button::doTheThing(){
  int buttonState = digitalRead(this->pin);

  // freshly pressed
  if (buttonState == 0 && this->downStamp == 0){
    this->downStamp = millis();
  }
  // still pressed - getting duration
  if (buttonState == 0 && this->downStamp != 0){
    this->pressDuration = millis() - this->downStamp;
  }

  switch(this->hasLongPress){
    
    case(false):
      if (!this->hasFired && (this->pressDuration >= this->flickerDebounce)){
        this->hasFired = true;
        singlePressCallback();
      }

      // button has just been released
      if (buttonState == 1 && this->pressDuration != 0){
        this->reset();
      }
      break;

    case(true):    
      if (!this->hasFired && (this->pressDuration >= this->longPressDuration)){
        this->hasFired = true;
        longPressCallback();
      }
    
      // button has just been released
      if (buttonState == 1 && this->pressDuration != 0){
        bool shortPushed = !this->hasFired && (this->pressDuration < this->longPressDuration) && (this->pressDuration > this->flickerDebounce);
        if (shortPushed){
          singlePressCallback();
        }
        this->reset();
      }
      break;
  }  
}
