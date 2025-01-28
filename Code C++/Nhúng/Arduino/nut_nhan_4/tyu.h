#ifndef TEW
#define TEW

typedef struct Buton
{
    thButton(byte pin);
    boolean onPress();
    boolean isPress();
    boolean onRelease();
    boolean isRelease();
    
    boolean onHold();
    boolean isHold();
    static void setHoldTime(word holdTime_ms);
    
    byte _pin; 
    byte _flags;
    word _changeTime; 
    
    void update();
    boolean onEvent(byte event);
} Button;




#endif
