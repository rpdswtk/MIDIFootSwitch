#ifndef ButtonHandler_h
#define ButtonHandler_h

class ButtonHandler
{
  public:
    ButtonHandler(int pin, void(* onClick)());
    void tick();
  private:
    int _pin;
    int _buttonState;
    int _lastButtonState;
    unsigned long _lastDebounceTime;
    unsigned long _debounceDelay;
    void (* _onClick)();
};

#endif