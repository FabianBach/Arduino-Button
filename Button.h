#ifndef Button_h
#define Button_h

#include "Arduino.h"

typedef void (*fptr)(); // makes callback pointer stuff easier

class Button
{
  public:
    Button(int pin, fptr singlePressCallback, int flickerDebounce);
    Button(int pin, fptr singlePressCallback, int flickerDebounce, fptr longPressCallback, int longPressDuration);
    ~Button(); // destructor
    void doTheThing();
    
  private:
    int pin;
    int flickerDebounce;
    fptr singlePressCallback;
    int longPressDuration;
    fptr longPressCallback;

    bool hasFired;
    bool hasLongPress;
    unsigned long pressDuration;
    unsigned long downStamp;

    void reset();
};

#endif
