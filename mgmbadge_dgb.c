// ------ Libraries and Definitions ------
#include "simpletools.h"
#include "badgewxtools.h"
#include "ws2812.h"
#define RGB_COUNT 4

// ------ Global Variables and Objects ------
ws2812 *ws2812b;
int RGBleds[4];

int ledsOn;
int xAccel;
int ledToLight;

// ------ Function Declarations ------
void display_accel();
void accel_led();

// ------ Main Program ------
int main() {
  badge_setup();
  ws2812b = ws2812b_open();
  // Allow the Badge WX to be programmed over WiFi
  high(17);
  ledsOn = 0;
  ledToLight = 1;
  while (1) {
    text_size(LARGE);
    cursor(0, 0);
    oledprint(" Dennis");
    cursor(0, 1);
    oledprint(" Brown");
    if ((button(2)) > 0) {
      switch (ledsOn) {
        case 1:
          ledsOn = 0;
          break;
        case 0:
          ledsOn = 1;
          break;
      }
    }

    for (int __ldx = ledToLight; __ldx <= ledToLight; __ldx++) {
      RGBleds[constrainInt(__ldx, 1, RGB_COUNT) - 1] = 0x000000;
    }
    ws2812_set(ws2812b, RGB_PIN, RGBleds, RGB_COUNT);
    if (ledsOn == 1) {
      accel_led();
    }

  }

}

// ------ Functions ------
void display_accel() {
  text_size(SMALL);
  cursor(0, 4);
  oledprint(" x:");
  oledprint("%d", accel(AX));
  oledprint(" y:");
  oledprint("%d", accel(AY));
  oledprint(" z:");
  oledprint("%d", accel(AZ));
  oledprint(" ");
}

void accel_led() {
  xAccel = (accel(AX));
  if (xAccel <= -30) {
    ledToLight = 1;
  }

  if (xAccel > -30 && xAccel <= 0) {
    ledToLight = 2;
  }

  if (xAccel > 0 && xAccel <= 30) {
    ledToLight = 3;
  }

  if (xAccel > 30) {
    ledToLight = 4;
  }

  for (int __ldx = ledToLight; __ldx <= ledToLight; __ldx++) {
    RGBleds[constrainInt(__ldx, 1, RGB_COUNT) - 1] = 0x004B99;
  }
  ws2812_set(ws2812b, RGB_PIN, RGBleds, RGB_COUNT);
}

