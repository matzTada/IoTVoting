// mote.ino
// Program for Arduino version3
// Keio University Westlab 2017.12
// Author: Tada Matz

//<==== Please change according to an instruction
String MOTENAME = "version3-2"; //recommended to be between 1 ~ 10
int MOTEID = 2; //should be from 1 ~ 20
//====>Please change according to an instruction

#define LED_RED_PIN 3
#define LED_GREEN_PIN 5
#define LED_BLUE_PIN 6

#define BUTTON_RED_PIN 10
#define BUTTON_GREEN_PIN 11
#define BUTTON_BLUE_PIN 12

int oldR = 0, oldG = 0, oldB = 0; //old button values for click detection
#define CNT_MAX 2
int cntR = 0, cntG = 0, cntB = 0;
int colorR = 0, colorG = 0, colorB = 0;

#include "source.h"
MyXBee myxbee;
unsigned long pastMillis = millis();
#define SEND_INTERVAL 1000
#define LED_HEADER 'L'
#define ID_PACKET_OFFSET '0'

int clickDetection(int _pin, int * _oldstate) { //click detection
  int buttonClicked = 0;
  int newButtonState = digitalRead(_pin);
  if (*_oldstate == HIGH && newButtonState == LOW) buttonClicked = 1; //button pressed. CAUTION pull up
  *_oldstate = newButtonState;
  return buttonClicked;
}

void setup() {
  Serial.begin(9600);
  myxbee.init(Serial);

  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);
  pinMode(LED_BLUE_PIN, OUTPUT);

  pinMode(BUTTON_RED_PIN, INPUT_PULLUP);
  pinMode(BUTTON_GREEN_PIN, INPUT_PULLUP);
  pinMode(BUTTON_BLUE_PIN, INPUT_PULLUP);
}

void loop() {
  if (clickDetection(BUTTON_RED_PIN, &oldR)) {
    cntR = cntR + 1;
    if (cntR >= CNT_MAX) cntR = 0;
    colorR = (int)map(cntR, 0, CNT_MAX - 1, 0, 255);
  }

  if (clickDetection(BUTTON_GREEN_PIN, &oldG)) {
    cntG = cntG + 1;
    if (cntG >= CNT_MAX) cntG = 0;
    colorG = (int)map(cntG, 0, CNT_MAX - 1, 0, 255);
  }
  if (clickDetection(BUTTON_BLUE_PIN, &oldB)) {
    cntB = cntB + 1;
    if (cntB >= CNT_MAX) cntB = 0;
    colorB = (int)map(cntB, 0, CNT_MAX - 1, 0, 255);
  }

  // receiving
  String receiveStr = myxbee.receiveXBeeData();
  if (receiveStr.length() > 0 && receiveStr.charAt(0) == LED_HEADER) { // packet should be "L1RRRGGGBBB\n"
    // int senderid = int(receiveStr.charAt(1) - ID_PACKET_OFFSET);
    colorR = receiveStr.substring(2, 5).toInt();
    colorG = receiveStr.substring(5, 8).toInt();
    colorB = receiveStr.substring(8, 11).toInt();
  }

  // sending periodically
  if (millis() - pastMillis > SEND_INTERVAL) {
    pastMillis = millis();

    char tempsenddata[1 + 1 + 9];
    sprintf(tempsenddata, "%c%c%03d%03d%03d",
            LED_HEADER,
            MOTEID + int(ID_PACKET_OFFSET),
            colorR, colorG, colorB);
    String data = tempsenddata + MOTENAME + "\n"; // packet should be "L1RRRGGGBBB"
    myxbee.sendXBeeData(data);
  }

  // put on LED
  analogWrite(LED_RED_PIN, 255 - colorR);
  analogWrite(LED_GREEN_PIN, 255 - colorG);
  analogWrite(LED_BLUE_PIN, 255 - colorB);
}


