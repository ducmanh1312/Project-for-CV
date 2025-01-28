#include "tyu.h"

int led = A3;
unsigned long debounceTime = 50;    // Thời gian chờ giữa các lần đọc
unsigned long holdTime = 500;  // Ngưỡng thời gian nhấn tối thiểu
int state = HIGH;

int button1_pin = 2;
int button2_pin = 3;



#define  IS_PRESS    _BV(0)
#define  WAS_PRESS   _BV(1)
#define  ON_PRESS    _BV(2)
#define  ON_RELEASE  _BV(3)
#define  IS_HOLD     _BV(4)
#define  ON_HOLD     _BV(5)


void thButton(byte pin, Button *button )
{
  button->_pin = pin;
  pinMode( button->_pin, INPUT_PULLUP);  
}

void update(Button *button)
{
  word interval = millis() - button->_changeTime;
    // Read pin state to IS_PRESS
  if(interval > debounceTime )
  {
    if(digitalRead(button->_pin) == LOW)
    {
      button->_flags |= IS_PRESS;
    }else
    {
      button->_flags &= ~IS_PRESS;
    }
    
  }
  
  switch( button->_flags & (IS_PRESS | WAS_PRESS))
  {
    case IS_PRESS:
    {
      button->_flags = IS_PRESS | WAS_PRESS | ON_PRESS;
      button->_changeTime = millis();
      interval = 0;
      break;
    }
    case WAS_PRESS:
    {
      button->_flags = ON_RELEASE;
      button->_changeTime = millis();
      break;
    }
  }

  if((button->_flags & IS_PRESS)
    &&(!(button->_flags & IS_HOLD))
    && (interval >= holdTime))
   {
    button->_flags |= IS_HOLD | ON_HOLD;
   }
}

boolean isPress(Button *button)
{
  update(button);
  return (button->_flags & IS_PRESS);
}

boolean isHold(Button *button)
{
  update(button);
  return (button->_flags & IS_HOLD);
}

boolean onEvent(Button *button ,byte event)
{
  update(button);
  boolean result = button->_flags & event;
  button->_flags &= ~event;
  return result;
}
boolean onPress(Button *button)
{
  return onEvent(button, ON_PRESS);
}

boolean onHold(Button *button)
{
  return onEvent(button, ON_HOLD);
}



Button button1, button2; 
void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  thButton(button1_pin, &button1);
  thButton(button2_pin, &button2);
}





void loop()
{
  if(onPress(&button1))
  {
    digitalWrite(led, state);
    state = !state;
   
  }
   
  

}
