#include <Time.h>
#include <TimeLib.h>
#include <PxMatrix.h>
#include <Ticker.h>
Ticker display_ticker;
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_D 12
#define P_E 0
#define P_OE 2

uint8_t display_draw_time = 20;

PxMATRIX display(32, 16, P_LAT, P_OE, P_A, P_B, P_D);

uint16_t myRed = display.color565(255, 0, 0);
uint16_t myGreen = display.color565(0, 255, 0);
uint16_t myBlue = display.color565(0, 0, 255);
uint16_t myWhite = display.color565(255, 255, 255);
uint16_t myYellow = display.color565(255, 255, 0);
uint16_t myCyan = display.color565(0, 255, 255);
uint16_t myMagenta = display.color565(255, 0, 255);
uint16_t myBlack = display.color565(0, 0, 0);
uint16_t myCOLORS[8] = {myRed, myGreen, myBlue, myWhite, myYellow, myCyan, myMagenta, myBlack};

//time_t t = now();

void display_updater()
{
  display.display(display_draw_time);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  display.begin(4);
  display.setScanPattern(ZAGGIZ);
  display.setMuxPattern(BINARY);
  display.flushDisplay();
  display.setTextSize(0);
  display_ticker.attach(0.002, display_updater);
  delay(500);
}

void displayText() {
  time_t t = now();
  String hourNow = String(hour(t));
  String minNow = String(minute(t));
  int hrLen = hourNow.length();
  int minLen = minNow.length();
  if ( hrLen < 2) {
    hourNow = 0 + hourNow;
  }
  if ( minLen < 2) {
    minNow = 0 + minNow;
  }
  String timeNow = hourNow + ":" + minNow;
  display.setTextColor(myGreen);
  display.setCursor(0, 0);
  display.clearDisplay();
  display.println("Time:");
  display.print(timeNow);
  Serial.print("timeNow: ");
  Serial.println(timeNow);
}

void loop() {
  displayText();
  delay(100);
}
