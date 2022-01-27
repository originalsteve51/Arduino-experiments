/*
 *  Five AceButtons are tested that use button pressed and released events. 
 *  The white button toggles its LED on and off. The other four buttons simply
 *  turn their LEDs on and off.
 *  
 */

#include <AceButton.h>

using namespace ace_button;

#define WHITE_BTN 3
#define BLUE_BTN 2
#define BLACK_BTN 1
#define YELLOW_BTN 0
#define RED_BTN 4

#define LED_1_R 9
#define LED_2_G 8
#define LED_3_R 10
#define LED_4_G 11
#define LED_5_R 12


const int LED_PINS[] = {LED_1_R, LED_2_G, LED_3_R, LED_4_G, LED_5_R};
const int BUTTON_PINS[] = {WHITE_BTN, BLUE_BTN, BLACK_BTN, YELLOW_BTN, RED_BTN};
const int LED_ON = HIGH;
const int LED_OFF = LOW;
bool whiteToggled =  false;

AceButton white_button(BUTTON_PINS[0]), 
          blue_button(BUTTON_PINS[1]),
          black_button(BUTTON_PINS[2]),
          yellow_button(BUTTON_PINS[3]),
          red_button(BUTTON_PINS[4]);

// Forward reference to prevent Arduino compiler becoming confused.
void handleEvent(AceButton*, uint8_t, uint8_t);

void setup() {
  delay(2000);

  for (int idx=0; idx < 5; idx++)
  {
    pinMode(LED_PINS[idx], OUTPUT);
    pinMode(BUTTON_PINS[idx], INPUT_PULLUP);
  }
  
  white_button.setEventHandler(handleEvent);
  blue_button.setEventHandler(handleEvent);
  black_button.setEventHandler(handleEvent);
  yellow_button.setEventHandler(handleEvent);
  red_button.setEventHandler(handleEvent);
}

void loop() {
  white_button.check();
  blue_button.check();
  black_button.check();
  yellow_button.check();
  red_button.check();
}

void handleEvent(AceButton* button , uint8_t eventType,
    uint8_t /* buttonState */) 
{
  int led_idx = 0;
  int buttonPin = button->getPin();
  switch (buttonPin)
  {
    case WHITE_BTN:
      led_idx = 0;
      break;
    case BLUE_BTN:
      led_idx = 1;
      break;
    case BLACK_BTN:
      led_idx = 2;
      break;
    case YELLOW_BTN:
      led_idx = 3;
      break;
    case RED_BTN:
      led_idx = 4;
      break;
  }
  
  switch (eventType) 
  {
    case AceButton::kEventPressed:
      if (buttonPin != WHITE_BTN)
      {
        digitalWrite(LED_PINS[led_idx], LED_ON);
      }
      else
      {
        if (whiteToggled)
        {
          whiteToggled = false;
          digitalWrite(LED_PINS[led_idx], LED_OFF);
        }
        else
        {
          whiteToggled = true;
          digitalWrite(LED_PINS[led_idx], LED_ON);
        }
      }
      break;
    case AceButton::kEventReleased:
      if (buttonPin != WHITE_BTN)
      {
        digitalWrite(LED_PINS[led_idx], LED_OFF);
      }
      break;
  }
}
